#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void handler(int s)
{
	write(1, "!", 1);
}

int main(void)
{
	sigset_t set, oldset;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	sigaddset(&set, SIGRTMIN);

	signal(SIGINT, handler);
	signal(SIGRTMIN, handler);

	sigprocmask(SIG_BLOCK, &set, &oldset);
	for (int i = 0; i < 10; i++) {
		sigsuspend(&oldset);
		/*
		 sigprocmask(SIG_SETMASK, &oldset, &save);
		 pause();
		 sigprocmask(SIG_SETMASK, &save, NULL);
		 */
		for (int j = 0; j < 5; j++) {
			write(1, "*", 1);
			sleep(1);
		}
		write(1, "\n", 1);
	}

	exit(0);
}

