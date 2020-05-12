#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{

	printf("good morning");

	// return 0; // 从main返回，终止进程
	// exit(EXIT_SUCCESS); 终止进程前　刷新缓存区
	// EXIT_FAILURE 1

	// _exit(0); // 直接终止返回到内核态 不会刷新缓存区
	_Exit(0);
}

