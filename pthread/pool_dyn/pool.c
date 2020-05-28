#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "pool.h"


// 任务线程接口
static void *threadpool_job(void *arg)
{
	threadpool_t *pool = arg;
	threadpool_task_t task;

	while (1) {
		pthread_mutex_lock(&pool->lock);	
		// 没有任务，但池未关闭
		while (pool->queue_cur_size == 0 && pool->shutdown == 0) {
			pthread_cond_wait(&pool->queue_not_empty, &pool->lock);	
			// 1. 有任务到来了 2. 需要终止了			
			if (pool->wait_exit_thr_num > 0) {
				pool->wait_exit_thr_num --;	
				if (pool->live_thr_num > pool->min_thr_num) {
					// 自杀
					pool->live_thr_num--;
					pthread_mutex_unlock(&pool->lock);
					pthread_exit(NULL);
				}
			}
		}
		// 池是否关闭了
		if (pool->shutdown) {
			pthread_mutex_unlock(&pool->lock);
			pthread_exit(NULL);
		}
		// 任务来了	
		queue_deq(pool->task_queue, &task);
		pool->queue_cur_size --;
		pthread_cond_broadcast(&pool->queue_not_full);
		pthread_mutex_unlock(&pool->lock);

		pthread_mutex_lock(&pool->busy_lock);
		pool->busy_thr_num ++;
		pthread_mutex_unlock(&pool->busy_lock);

		// 执行任务
		(task.function)(task.arg);
		pthread_mutex_lock(&pool->busy_lock);
		pool->busy_thr_num --;
		pthread_mutex_unlock(&pool->busy_lock);
	}
}

// 判断线程是否存在
static int get_free_pos(pthread_t *arr, int n)
{
	for (int i = 0; i < n; i++) {
		if ((arr[i] != 0 && pthread_kill(arr[i], 0)) || arr[i] == 0)
			return i;
	}

	return -1;
}

// 管理者线程
static void *adminthread_job(void *arg)
{
	threadpool_t *pool = arg;
	int busy_ths, live_thrs, kill_thrs, min_thrs;
	int pos;

	// 池未关闭
	while (!pool->shutdown) {
		pthread_mutex_lock(&pool->lock);	

		// 至少要有一定的线程 时刻准备接收新任务
		if (pool->queue_cur_size >= MIN_FREETHR_NUM && \
			   pool->live_thr_num < pool->max_thr_num) {
			for (int i = 0; i < MIN_FREETHR_NUM && \
					pool->live_thr_num < pool->max_thr_num; i++) {
				pos = get_free_pos(pool->threads, pool->max_thr_num);
				pthread_create(pool->threads+pos, NULL, threadpool_job, (void *)pool);	
				pool->live_thr_num++;
			}
		}
		live_thrs = pool->live_thr_num;
		min_thrs = pool->min_thr_num;
		pthread_mutex_unlock(&pool->lock);
		
		pthread_mutex_lock(&pool->busy_lock);
		busy_ths = pool->busy_thr_num;
		pthread_mutex_unlock(&pool->busy_lock);

		if (busy_ths * 2 < live_thrs && live_thrs > min_thrs) {
			pthread_mutex_lock(&pool->lock);
			pool->wait_exit_thr_num = live_thrs-min_thrs;
			kill_thrs = pool->wait_exit_thr_num;
			pthread_mutex_unlock(&pool->lock);

			for (int i = 0; i < kill_thrs; i++)
				pthread_cond_signal(&pool->queue_not_empty);
		}
		sleep(1);
	}
	pthread_exit(NULL);
}

threadpool_t *threadpool_init(int queue_max_size, int min_thr_num, int max_thr_num)
{
	threadpool_t *mypool = NULL;
	int err;

	mypool = malloc(sizeof(threadpool_t));
	if (NULL == mypool)
		return NULL;

	pthread_mutex_init(&mypool->lock, NULL);	
	pthread_mutex_init(&mypool->busy_lock, NULL);
	pthread_cond_init(&mypool->queue_not_empty, NULL);
	pthread_cond_init(&mypool->queue_not_full, NULL);

	// 任务队列
	mypool->queue_max_size = queue_max_size;
	mypool->task_queue = queue_init(sizeof(threadpool_task_t), queue_max_size);
	
	// 线程数组
	mypool->max_thr_num = max_thr_num;
	mypool->min_thr_num = min_thr_num;
	mypool->threads = calloc(max_thr_num, sizeof(pthread_t));
	if (NULL == mypool->threads) {
		queue_destroy(mypool->task_queue);
		free(mypool);
		return NULL;
	}
	mypool->busy_thr_num = 0;
	mypool->live_thr_num = min_thr_num;
	mypool->queue_cur_size = 0;
	mypool->wait_exit_thr_num = 0;

	// 启动至少池中的线程
	for (int i = 0; i < min_thr_num; i++) {
		err = pthread_create(mypool->threads+i, NULL, threadpool_job, (void *)mypool);
		if (err) {
			fprintf(stderr, "pthread_create():%s\n", strerror(err));
			queue_destroy(mypool->task_queue);
			free(mypool->threads);
			free(mypool);
			return NULL;
		}
	}

	mypool->shutdown = 0;
	
	// 创建管理者线程
	pthread_create(&mypool->admin_tid, NULL, adminthread_job, (void *)mypool);
	// if error

	return mypool;
}

int threadpool_add_task(threadpool_t *pool, threadpool_task_t task)
{
	pthread_mutex_lock(&pool->lock);
	while (queue_isfull(pool->task_queue))
		pthread_cond_wait(&pool->queue_not_full, &pool->lock);
	if (pool->shutdown) {
		pthread_mutex_unlock(&pool->lock);
		return -1;
	}
	queue_enq(pool->task_queue, &task);
	pool->queue_cur_size ++;
	pthread_cond_signal(&pool->queue_not_empty);
	pthread_mutex_unlock(&pool->lock);

	return 0;
}

void threadpool_destroy(threadpool_t *pool)
{
	// 关闭池
	pool->shutdown = 1;

	// 管理者线程收尸
	pthread_join(pool->admin_tid, NULL);

	for (int i = 0; i < pool->max_thr_num; i++) {
		if (pthread_kill((pool->threads)[i], 0))
			continue;
		pthread_cond_signal(&pool->queue_not_empty);
		pthread_join((pool->threads)[i], NULL);
	}

	free(pool->threads);
	queue_destroy(pool->task_queue);
	pthread_mutex_destroy(&pool->lock);
	pthread_mutex_destroy(&pool->busy_lock);
	pthread_cond_destroy(&pool->queue_not_empty);
	pthread_cond_destroy(&pool->queue_not_full);

	free(pool);
	pool = NULL;
}



