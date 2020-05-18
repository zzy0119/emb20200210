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
#include <syslog.h>
#include <errno.h>
#include <string.h>
#include <sys/file.h>

#define TMPFILE		"/tmp/out"
#define BUFSIZE		100
#define LOCKFILE	"/var/run/daemon.pid"

static int mydaemon(void);
int signal_running(void);
int main(void)
{
	time_t tm;
	struct tm *tmp = NULL;
	FILE *fp = NULL;
	char buf[BUFSIZE] = {};

	// 创建日志链接
	openlog("mydaemon", LOG_PID, LOG_DAEMON);

	// 守护进程
#if 0
	if (mydaemon() < 0) {
		fprintf(stderr, "mydaemon() failed\n");
		exit(1);
	}
#endif
	if (daemon(0, 0) == -1) {
		perror("daemon");
		exit(1);
	}

	// 单实例
	if (signal_running() == -1) {
		syslog(LOG_ERR, "signal_running() failed");
		exit(1);
	}


	fp = fopen(TMPFILE, "w");
	if (NULL == fp) {
		// perror("fopen()");
		syslog(LOG_ERR, "fopen():%s", strerror(errno));
		goto ERROR;
	}

	while (1) {
		time(&tm);
		tmp = localtime(&tm);
		if (NULL == tmp) {
			syslog(LOG_ERR, "localtime() failed");
			goto ERROR2;
		}
		memset(buf, '\0', BUFSIZE);
		strftime(buf, BUFSIZE, "%Y-%m-%d %H:%M:%S\n", tmp);
		fputs(buf, fp);
		
//		syslog(LOG_INFO, "%s write into the file", buf);

		fflush(NULL);	
		sleep(1);
	}

	fclose(fp);
	closelog();

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

// 单实例守护进程
int signal_running(void)
{
	int fd;
	char buf[BUFSIZE] = {};

	fd = open(LOCKFILE, O_RDWR | O_CREAT, 0666);	
	if (fd == -1) {
		syslog(LOG_ERR, "open():%s", strerror(errno));
		return -1;
	}

	if (flock(fd, LOCK_EX | LOCK_NB) == -1) {
		syslog(LOG_ERR, "flock():%s", strerror(errno));
		close(fd);	
		return -1;
	}
	// 成功
	ftruncate(fd, 0);
	snprintf(buf, BUFSIZE, "%d", getpid());
	write(fd, buf, strlen(buf));

	return 0;
}



