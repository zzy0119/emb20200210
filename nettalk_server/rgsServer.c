#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <signal.h>

#include "proto.h"

static int socket_init(char *errmsg);

int main(void)
{
	char *err;
	struct sockaddr_in raddr;
	socklen_t raddrlen;
	rgs_t rcvbuf;
	pid_t pid;
	struct sigaction act, oldact;

	int sd = socket_init(err);
	if (sd < 0) {
		fprintf(stderr, "%s:%s\n", err, strerror(-errno));	
		exit(1);
	}

	// 子进程不收尸
	act.sa_handler = SIG_DFL;
	act.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGCHLD, &act, &oldact);

	raddrlen = sizeof(raddr);
	while (1) {
		// 接收客户端注册请求----》判断注册账号是否已被注册	
		cnt = recvfrom(sd, &rcvbuf, sizeof(rcvbuf), (void *)&raddr, &raddrlen);	
		if (cnt == -1) {
			perror("recvfrom()");
			goto ERROR;
		}
		// 并发 子进程判断能否注册 调用进程接收客户端请求
		pid = fork();
		if (pid == -1) {
			perror("fork()");
			goto ERROR;
		}
		if (pid == 0) {
			// 子进程
			ret = child_job(&rcvbuf);
			sendto(sd, &rcvbuf, sizeof(rcvbuf), 0, (void *)&raddr, raddrlen);
		}
	}

	return 0;
ERROR:
	close(sd);
	exit(1);
}

// 初始化套接字
static int socket_init(char *errmsg)
{
	int sd;
	struct sockaddr_in laddr;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		errmsg = "socket()";
		return -errno;
	}

	//
	laddr.sin_family = AF_INET;
	inet_aton(RGS_SERVER_IP, &laddr.sin_addr);
	laddr.sin_port = htons(RGS_SERVER_PORT);
	if (bind(sd, (void *)&laddr, sizeof(laddr)) < 0) {
		errmsg = "bind()";
		return -errno;
	}

	return sd;
}

int child_job(rgs_t *buf)
{

	// 链接数据库

	// 查询注册表--->判断此账号是否已注册

}






