#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define THRNR	5

static int curid = 0;
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static void *thr_job(void *arg)
{
	int myid = (int)arg;
	while (1) {
		pthread_mutex_lock(&mut);	
		while (curid != myid) {
			pthread_cond_wait(&cond, &mut);
		}
		printf("%c", 'a'+curid);
		fflush(NULL);
		curid = (curid + 1) % THRNR;
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&mut);
	}
}

int main(void)
{
	pthread_t tids[THRNR];
	int err;
	pthread_attr_t attr;

	// 线程属性---》分离  // pthread_detach
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
	for (int i = 0; i < THRNR; i++) {
		err = pthread_create(tids+i, &attr, thr_job, (void *)i);
		if (err) {
			fprintf(stderr, "pthread_create():%s\n", strerror(err));
			exit(0);
		}
	}

	for (int i = 0; i < 5; i++)
		sleep(1);

	exit(0);
}


