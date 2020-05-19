#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

static void alrm_handler(int s)
{
	// alarm(5);
	write(1, "alrm!!!", 8);
}

int main(void)
{
	int ch;
	struct itimerval itm;

	// sigaction
	signal(SIGALRM, alrm_handler);
	// alarm(5);
	itm.it_interval.tv_sec = 0;
	itm.it_interval.tv_usec = 500000;
	itm.it_value.tv_sec = 0;
	itm.it_value.tv_usec = 300000;
	setitimer(ITIMER_REAL, &itm, NULL);

	while (1) {
		ch = getchar();
		if (ch == EOF)
			break;
		putchar(ch);
		fflush(NULL);
	}

	exit(0);
}

