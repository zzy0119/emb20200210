#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;
	int num = 100;

	printf("good afternoon");

	pid = vfork(); // 子进程不复制父进程虚拟地址空间 会阻塞父进程
	if (pid == -1) {
		perror("vfork()");
		exit(1);
	}
	if (pid == 0) {
		sleep(1);
		num ++;
		printf("byebye");
		exit(0);
	}
	printf("num:%d\n", num);
	wait(NULL);

	return 0;
}

