#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFSIZE	100

int main(void)
{
	int pfd[2] = {};
	pid_t pid;
	char buf[BUFSIZE] = {};
	int data = 10;

	if (pipe(pfd) == -1) {
		perror("pipe()");
		exit(1);
	}
	pid = fork();
	if (pid < 0) {
		perror("fork()");
		exit(1);
	}
	if (pid == 0) {
		data ++;
		printf("child~data:%d\n", data);
		close(pfd[0]);
		write(pfd[1], "good morning", 12);
		close(pfd[1]);
		exit(0);
	}
	wait(NULL);
	printf("parent~data:%d\n", data);
	close(pfd[1]);
	read(pfd[0], buf, BUFSIZE);
	puts(buf);
	close(pfd[0]);

	exit(0);
}

