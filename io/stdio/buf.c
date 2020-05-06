#include <stdio.h>

int main(void)
{
	printf("hello world");

	fflush(NULL); // 刷新所有打开的流

	while (1)
		;

	return 0;
}

