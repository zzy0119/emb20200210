#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUFSIZE	100

int main(int argc, char *argv[])
{
	int rfd, wfd; 
	char buf[BUFSIZE] = {};
	int cnt;

	if (argc < 3)
		return 1;

	rfd = open(argv[1], O_RDONLY);
	if (-1 == rfd) {
		// fprintf(stderr, "open():%s\n", strerror(errno));	
		perror("open()");
		goto ERROR;
	}
	wfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (-1 == wfd) {
		// fprintf(stderr, "open() failed\n");
		perror("open()");
		goto ERROR2;
	}

	while (1) {
		cnt = read(rfd, buf, BUFSIZE);
		if (cnt == 0)
			break;
		if (cnt == -1) {
			// fprintf(stderr, "read() failed\n");
			perror("read()");
			goto ERROR3;
		}
		write(wfd, buf, cnt);
	}

	close(rfd);
	close(wfd);

	return 0;
ERROR3:
	close(wfd);
ERROR2:
	close(rfd);
ERROR:
	return 1;
}

