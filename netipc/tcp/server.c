#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#include "proto.h"

int main(void)
{
	int sd, newsd;
	struct sockaddr_in laddr, raddr;
	socklen_t raddrlen;

	// 创建流式套接字
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		exit(1);
	}

	// 绑定本地地址
	laddr.sin_family = AF_INET;
	inet_aton(SERVER_IP, &laddr.sin_addr);
	laddr.sin_port = htons(SERVER_PORT);
	if (bind(sd, (void *)&laddr, sizeof(laddr)) == -1) {
		perror("bind()");
		goto ERROR;
	}

	// 处于监听状态
	if (listen(sd, 20) == -1) {
		perror("listen()");
		goto ERROR;
	}

	raddrlen = sizeof(raddr);
	while (1) {
		// 接收连接请求
		newsd = accept(sd, (void *)&raddr, &raddrlen);
		if (newsd == -1) {
			if (errno == EINTR)
				continue;
			perror("accept()");
			goto ERROR;
		}

		// read() / write()
		write(newsd, "good morning", 12);
		close(newsd);
	}

	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}

