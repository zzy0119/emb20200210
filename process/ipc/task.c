#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define BUFSIZE	100

int copyfile(int fd1, int fd2);
int main(int argc, char *argv[])
{
	pid_t pid1, pid2;
	int pfd[2] = {};

	if (argc < 2)
		exit(1);

	if (pipe(pfd) == -1) {
		perror("pipe()");
		exit(1);
	}
	pid1 = fork();
	if (pid1 == -1) {
		perror("fork()");
		goto ERROR;
	}
	if (pid1 == 0) {
		int fd;
		close(pfd[0]);
		fd = open(argv[1], O_RDONLY);
		// if error
		copyfile(fd, pfd[1]);	
		close(pfd[0]);
		close(fd);
		exit(0);
	}

	pid2 = fork();
	// if error
	if (pid2 == 0) {
		close(pfd[1]);
		copyfile(pfd[0], 1);
		close(pfd[1]);
		exit(0);
	}
	close(pfd[0]);
	close(pfd[1]);
	wait(NULL);
	wait(NULL);

	exit(0);
ERROR:
	close(pfd[0]);
	close(pfd[1]);
	exit(1);
}

// 读fd1, 写fd2
int copyfile(int fd1, int fd2)
{
	char buf[BUFSIZE] = {};
	int cnt;

	while (1) {
		cnt = read(fd1, buf, BUFSIZE);		
		if (cnt < 0) {
			if (errno == EINTR)
				continue;
			perror("read()");
			return -1;			
		}
		if (cnt == 0)
			break;
		write(fd2, buf, cnt);	
	}	

	return 0;
}

