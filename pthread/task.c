#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define START 	100
#define END		300
#define THRNR	END-START+1

static int isprimer(int n)
{
	for (int i = 2; i < n; i++) {
		if (n % i == 0)
			return 0;
	}

	return 1;
}

static void *thr_fun(void *arg)
{
	// sleep(1);
	int n = (int)arg;

	if (isprimer(n))
		printf("%d is a primer\n", n);
	pthread_exit((void *)0);
}

int main(void)
{
	pthread_t tids[THRNR];
	int j = 0;
	int err;

	for (int i = START; i <= END; i++, j++) {
		err = pthread_create(tids+j, NULL, thr_fun, (void *)i);
		if (err) {
			fprintf(stderr, "phtread_create():%s\n", strerror(err));
			exit(0);
		}
	}

	for (int i = 0; i < THRNR; i++)
		pthread_join(tids[i], NULL);

	exit(0);
}

