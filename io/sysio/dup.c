#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int fd = dup(1);

	write(fd, "good afternoon", 14);

	dup2(1, 0);

	write(0, "hello", 5);

	return 0;
}

