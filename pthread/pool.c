#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define START 	100
#define END		300
#define THRNR	4

static int job; // 任务变量 0无任务 >0已分配任务 -1所有任务发放完成
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

static int isprimer(int n)
{
	for (int i = 2; i < n; i++) {
		if (n % i == 0)
			return 0;
	}

	return 1;
}
// 任务线程
static void *thr_job(void *arg)
{
	int num;
	int id = (int)arg;

	while (1) {
		pthread_mutex_lock(&mut);
		if (job == -1) {
			pthread_mutex_unlock(&mut);
			pthread_exit((void *)0);
		}
		if (job == 0) {
			pthread_mutex_unlock(&mut);
			continue;
		}
		num = job;
		job = 0;
		pthread_mutex_unlock(&mut);
		if (isprimer(num)) {
			printf("[%d]%d is a primer\n", id, num);
		}
	}
}

int main(void)
{
	// 创建任务线程  发放任务数值
	pthread_t tids[THRNR];
	int err;

	for (int i = 0; i < THRNR; i++) {
		err = pthread_create(tids+i, NULL, thr_job, (void *)i);
		if (err) {
			fprintf(stderr, "pthread_create():%s\n", strerror(err));
			exit(1);
		}
	}

	for (int i = START; i <= END; i++) {
		pthread_mutex_lock(&mut);
		while (job != 0) {
			pthread_mutex_unlock(&mut);
			pthread_mutex_lock(&mut);
		}
		job = i;
		pthread_mutex_unlock(&mut);
	}

	// 所有任务发放完成
	pthread_mutex_lock(&mut);
	while (job > 0) {
		pthread_mutex_unlock(&mut);
		pthread_mutex_lock(&mut);
	}
	job = -1;
	pthread_mutex_unlock(&mut);

	for (int i = 0; i < THRNR; i++)
		pthread_join(tids[i], NULL);

	pthread_mutex_destroy(&mut);	

	exit(0);
}

