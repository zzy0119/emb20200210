#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>
#include <signal.h>

jmp_buf env;
typedef void (*sighandler_t)(int);
/*
 信号会大端阻塞系统调用
 标准信号会丢失
 不允许在信号处理函数中进行longjmp跳转
 */
// 信号处理函数
static void sig_handler(int s)
{
	int i = 0;
	while (i++ < 5){
#if 0
		// 不允许
		if (i == 2)
			longjmp(env, 1);
#endif
		write(1, "!", 1);	
		sleep(1);
	}
}

int main(void)
{
	sighandler_t ret;	
	int i = 0;

	ret = signal(SIGINT, sig_handler);
	if (SIG_ERR == ret) {
		perror("signal()");
		exit(1);
	}

	//setjmp(env);
	while (1) {
		write(1, "*", 1);
		sleep(1);
		i++;
		if (i == 10) {
			signal(SIGINT, ret);	
		}
	}

	exit(0);
}

