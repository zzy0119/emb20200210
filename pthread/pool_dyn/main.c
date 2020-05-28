#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "pool.h"

#define START 	100
#define END		300

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
}

int main(void)
{
	threadpool_t *pool;
	threadpool_task_t task;
	int err;

	pool = threadpool_init(50, 5, 20);
	// if error

	for (int i = START; i <= END; i++) {
		task.function = thr_fun;
		task.arg = (void *)i;
		threadpool_add_task(pool, task);
	}

	while (1) {
		// 等待客户端请求
		;
	}
	threadpool_destroy(pool);

	exit(0);
}

