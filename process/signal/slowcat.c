#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#define CPS		10
#define BUFSIZE	10

static int token;

static void handler(int s)
{
	alarm(1);
	token = 1;
}

int main(int argc, char *argv[])
{
	int fd;
	char buf[BUFSIZE] = {};
	int cnt;
	struct sigaction act, oldact;

//	signal(SIGALRM, handler);
	
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGALRM, &act, &oldact);

	alarm(1);

	if (argc < 2)
		return 1;

	while (1) {
		fd = open(argv[1], O_RDONLY);
		if (fd == -1) {
			if (errno == EINTR)
				continue;
			fprintf(stderr, "open() error\n");
			return 1;
		}
		break;
	}
	
	while (1) {
		while (token == 0) {
			// 没有权限读写
			pause();
		}
		token = 0;
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

