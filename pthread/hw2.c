#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#define THRNR	20
#define FLNAME	"./test"
#define BUFSIZE	100

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

static void *thr_job(void *arg)
{
	FILE *fp;
	char buf[BUFSIZE] = {};

	fp = fopen(FLNAME, "r+");
	// if error
	pthread_mutex_lock(&mut);	
	fread(buf, 1, BUFSIZE, fp);	
	rewind(fp);
	fprintf(fp, "%d", atoi(buf)+1);
	fclose(fp);
	pthread_mutex_unlock(&mut);

	pthread_exit((void *)0);
}

int main(void)
{
	pthread_t tids[THRNR];
	FILE *fp;
	int err;

	fp = fopen(FLNAME, "w");
	// if error
	fprintf(fp, "0");
	fclose(fp);

	for (int i = 0; i < THRNR; i++) {
		err = pthread_create(tids+i, NULL, thr_job, NULL);
		if (err) {
			fprintf(stderr, "pthread_create():%s\n", strerror(err));
			exit(0);
		}
	}

	for (int i = 0; i < THRNR; i++) {
		pthread_join(tids[i], NULL);
	}

	exit(0);
}

