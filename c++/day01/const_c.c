#include <stdio.h>

int main(void)
{
	const int n = 1;

	int *p = (int *)&n;
	*p = 100;

	printf("n:%d\n", n);

	return 0;
}
