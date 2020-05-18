#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void alrm_handler(int s)
{
	alarm(5);
	write(1, "alrm!!!", 8);
}

int main(void)
{
	int ch;

	signal(SIGALRM, alrm_handler);
	alarm(5);

	while (1) {
		ch = getchar();
		if (ch == EOF)
			break;
		putchar(ch);
		fflush(NULL);
	}

	exit(0);
}

