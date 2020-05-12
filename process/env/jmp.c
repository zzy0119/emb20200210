#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

static int div2num(int m, int n)
{
	if (n == 0)
		// 跳到main读入变量的位置
		longjmp(env, 1);
	return m / n;
}

int main(void)
{
	int num1, num2;

	if (setjmp(env) == 0)
		printf("请输入两个整型数:");
	else 
		printf("请重新输入:");
	scanf("%d%d", &num1, &num2);
	printf("%d/%d=%d\n", num1, num2, div2num(num1, num2));

	return 0;
}

