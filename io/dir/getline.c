#include <stdio.h>

int main(void)
{
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t cnt;

	while (1) {
		cnt = getline(&lineptr, &n,stdin);
		if (-1 == cnt) {
			perror("getline()");
			return 1;
		}
		printf("%s, 开辟了:%ld, 读到:%ld\n", lineptr, n, cnt);
	}


	return 0;
}

