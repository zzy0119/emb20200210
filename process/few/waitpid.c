#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;

	pid = fork();
	// if error

	if (pid == 0) {
		//child
		setpgid(0, getpid());
		printf("pid:%d, pgid:%d, sid:%d\n", getpid(), getpgrp(),\
				getsid(getpid()));
		exit(0);
	}
	waitpid(pid, NULL, 0);

	printf("pid:%d, pgid:%d, sid:%d\n", getpid(), getpgrp(),\
			getsid(getpid()));

	exit(0);
}

