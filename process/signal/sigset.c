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

	for (int i = 0; i < 10; i++) {
		sigprocmask(SIG_BLOCK, &set, &oldset);
		for (int j = 0; j < 5; j++) {
			write(1, "*", 1);
			sleep(1);
		}
		write(1, "\n", 1);
		sigprocmask(SIG_SETMASK, &oldset, NULL);
	}

	exit(0);
}

