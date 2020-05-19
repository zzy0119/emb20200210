#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "tbf.h"

#define CPS		10
#define BURST	100
#define BUFSIZE	10

int main(int argc, char *argv[])
{
	int fd;
	char buf[BUFSIZE] = {};
	int cnt;
	int td;
	int n;

	if (argc < 2)
		return 1;

	// 创建令牌桶
	td = tbfInit(CPS, BURST);
	if (td < 0) {
		exit(1);	
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "open() error\n");
		return 1;
	}

	
	while (1) {
		n = tbfFetchToken(td, CPS);
		cnt = read(fd, buf, n);	
		if (cnt == 0)
			break;
		if (cnt == -1) {
			fprintf(stderr, "read() error\n");
			goto ERROR;
		}
		if (cnt < n) {
			tbfReturnToken(td, n-cnt);
		}
		write(1, buf, cnt); // !!!!
	}

	tbfDestroy(td);
	close(fd);
	return 0;
ERROR:
	close(fd);
	return 1;
}

