#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

static void cleanup1(void *arg)
{
	printf("%s is called\n", __FUNCTION__);
}
static void cleanup2(void *arg)
{
	printf("%s is called\n", __FUNCTION__);
}

static void *thr_job(void *arg)
{
	pthread_cleanup_push(cleanup1, NULL);
	pthread_cleanup_push(cleanup2, NULL);

	for (int i = 0; i < 10; i++) {
		write(1, "*", 1);
		sleep(1);
	}
//	return (void *)0;
	pthread_exit(NULL);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
}

int main(void)
{
	pthread_t tid;

	pthread_create(&tid, NULL, thr_job, NULL);

//	sleep(2);
//	pthread_cancel(tid);

	pthread_join(tid, NULL);

	exit(0);
}

