#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE	10

int main(int argc, char *argv[])
{
	int fd;
	char buf[BUFSIZE] = {};
	int cnt;

	if (argc < 2)
		return 1;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "open() error\n");
		return 1;
	}
	
	while (1) {
		cnt = read(fd, buf, BUFSIZE);	
		if (cnt == 0)
			break;
		if (cnt == -1) {
			fprintf(stderr, "read() error\n");
			goto ERROR;
		}
		write(1, buf, cnt); // !!!!
	}

	close(fd);
	return 0;
ERROR:
	close(fd);
	return 1;
}

