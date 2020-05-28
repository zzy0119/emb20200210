#ifndef __POOL_H
#define __POOL_H

#define MIN_FREETHR_NUM	5

// 线程池任务
typedef struct {
	void *(*function)(void *);
	void *arg;
}threadpool_task_t;

// ADT
typedef struct {
	pthread_mutex_t lock; // 多线程操作池同步
	pthread_mutex_t busy_lock; // 管理者线程和任务线程 操作busy_thr_num
	// 任务队列
	// 任务队列的容量
	int queue_max_size;
	int queue_cur_size;// 当然任务队列有多少任务
	queue_t *task_queue;	
	pthread_cond_t queue_not_empty;
	pthread_cond_t queue_not_full;
	// 线程数组
	pthread_t *threads;
	pthread_t *admin_tid;// 管理者线程

	// 线程池属性
	int min_thr_num; // 池中至少的线程数
	int max_thr_num; // 池中最多存放的线程个数
	int live_thr_num; // 存活的线程数
	int busy_thr_num; // 忙碌的线程
	int wait_exit_thr_num; // 待终止的线程个数
	
	// 池状态
	int shutdown;	
}threadpool_t;

// 创建线程池
threadpool_t *threadpool_init(int queue_max_size, int min_thr_num, int max_thr_num);

int threadpool_add_task(threadpool_t *pool, threadpool_task_t task);

void threadpool_destroy(threadpool_t *pool);

#endif

