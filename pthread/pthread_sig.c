#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

static int flag = 0;
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static sigset_t set;

// 处理信号
static void *new_thr(void *arg)
{
	int signum;

	while (1) {
		sigwait(&set, &signum);
		switch (signum) {
			case SIGINT:
				pthread_mutex_lock(&mut);
				flag = 1;
				pthread_cond_signal(&cond);
				pthread_mutex_unlock(&mut);
				pthread_exit(NULL);
			case SIGQUIT:
				printf("quit is commint....\n");
				break;
			default:
				abort();
				break;
		}
	}

}

int main(void)
{
	sigset_t oldset;
	pthread_t tid;

	sigemptyset(&set);		
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	
	pthread_sigmask(SIG_BLOCK, &set, &oldset);
	
	pthread_create(&tid, NULL, new_thr, NULL);
	//if error;

	pthread_mutex_lock(&mut);
	while (flag == 0)
		pthread_cond_wait(&cond, &mut);
	pthread_mutex_unlock(&mut);

	printf("flag:%d\n", flag);
	pthread_join(tid, NULL);
	pthread_sigmask(SIG_SETMASK, &oldset, NULL);

	exit(0);
}

