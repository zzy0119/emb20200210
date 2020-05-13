#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	char *buf[] = {"ls", "-l", NULL};


	pid = fork();
	if (pid == -1) {
		perror("fork()");
		exit(1);
	}
	if (pid == 0) {
		// execl("/bin/ls", "ls", "-l", NULL);
		// execlp("ls", "ls", "-l", NULL);
		// execv("/bin/ls", buf);
		execvp("ls", buf);
		perror("execl()");
		exit(1);
	}

	wait(NULL);
	printf("this calling process\n");

	exit(0);
}

