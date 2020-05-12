#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define START 	100
#define END		300

static int is_primer(int n)
{
	int i;

	for (i = 2; i < n; i++)
		if (n % i == 0)
			return 0;
	return 1;
}

int main(void)
{
	pid_t pid;	

	for (int i = START; i <= END; i++) {
		pid = fork();
		if (pid < 0) {
			perror("fork()");
			exit(1);
		}
		if (pid == 0) {
			// child
			if (is_primer(i)) {
				printf("%d is a primer\n", i);
			}
			exit(0);
		}
	}

	for (int i = START; i <= END; i++) {
		wait(NULL);
	}

	exit(0);
}

