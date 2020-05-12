#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

//父子进程间没有严格的执行顺序

int main(void)
{
	pid_t pid;

	printf("pid:%d, ppid:%d\n", getpid(), getppid());

	printf("i will create a child process");

	fflush(NULL); // 是的所创建的子进程缓存区是空的
	pid = fork();
	if (pid == -1) {
		perror("fork()");
		exit(1);
	}
	if (pid == 0) {
		// child
		write(1, "hello", 5);
		printf("child pid:%d, ppid:%d\n", getpid(), getppid());
	} else {
		// parent
		wait(NULL); // 给任意子进程收尸
		write(1, "world", 5);
	}

	return 0;
}
