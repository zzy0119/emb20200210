#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
 
static void fun1(void)
{
	printf("%s is called\n", __FUNCTION__);
}

static void fun2(void)
{
	printf("%s is called\n", __FUNCTION__);
}

static void fun3(void)
{
	printf("%s is called\n", __FUNCTION__);
}

int main(void)
{
	pid_t pid;

	atexit(fun1);
	atexit(fun2);
	atexit(fun3);

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0) {
		// printf("child.....\n");
		// exit(0);
		execl("/bin/ls", "ls", "-l", NULL);
	}
	
	wait(NULL);

	printf("the calling process will be gone\n");

	exit(0);
	// return 0;
	// _exit(0);
}

