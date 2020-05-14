/*
 将当前时间字符串(y-m-d H:M:S)写入"/tmp/out"文件
 一秒钟写一次并每次占一行
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TMPFILE	"/tmp/out"
#define BUFSIZE	100

static int mydaemon(void);
int main(void)
{
	time_t tm;
	struct tm *tmp = NULL;
	FILE *fp = NULL;
	char buf[BUFSIZE] = {};

	// 守护进程
	if (mydaemon() < 0) {
		fprintf(stderr, "mydaemon() failed\n");
		exit(1);
	}

	fp = fopen(TMPFILE, "w");
	if (NULL == fp) {
		perror("fopen()");
		goto ERROR;
	}

	while (1) {
		time(&tm);
		tmp = localtime(&tm);
		if (NULL == tmp) {
			goto ERROR2;
		}
		memset(buf, '\0', BUFSIZE);
		strftime(buf, BUFSIZE, "%Y-%m-%d %H:%M:%S\n", tmp);
		fputs(buf, fp);
		fflush(NULL);	
		sleep(1);
	}

	fclose(fp);

	exit(0);
ERROR2:
	fclose(fp);
ERROR:
	exit(1);
}

static int mydaemon(void)
{
	pid_t pid;
	int fd;

	pid = fork();
	if (pid == -1) {
		perror("fork()");
		return -1;
	}
	if (pid > 0)
		exit(0);
	if (setsid() == 0) {
		perror("fork()");
		return -1;
	}
	// PID == PGID == SID

	// 0, 1, 2　重定向
	fd = open("/dev/null", O_RDWR);
	if (fd < 0) {
		perror("open()");
		return -1;
	}
	dup2(fd, 0);
	dup2(fd, 1);
	dup2(fd, 2);
	if (fd > 2)
		close(fd);

	umask(0);
	chdir("/");
	return 0;
}

