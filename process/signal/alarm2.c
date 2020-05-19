#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	alarm(2);
	alarm(5);
	alarm(1);

	while (1) {
		write(1, "*", 1);
		sleep(1);
	}

	exit(0);
}

