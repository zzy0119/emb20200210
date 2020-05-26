#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void *thr_job(void *arg)
{
	for (int i = 0; i < 4; i ++) {
		write(1, "*", 1);
		sleep(1);
	}

	return (void *)0; // 启动例程返回
}

int main(void)
{
	pthread_t tid;
	int err;

	err = pthread_create(&tid, NULL, thr_job, NULL);
	if (err) {
		fprintf(stderr, "pthread_create():%s\n", strerror(err));
		exit(1);
	}

	pthread_join(tid, NULL);

	exit(0);
}

