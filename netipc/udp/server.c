#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "proto.h"

int main(void)
{
	int sd;
	struct sockaddr_in laddr, raddr;
	socklen_t raddrlen; 
	struct msg_st rcvbuf;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sd) {
		perror("socket()");
		exit(1);
	}

	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(SERVER_PORT); // 转换为网络字节序
	inet_aton(SERVER_IP, &laddr.sin_addr); // 点分十进制地址---》地址结构体
	if (bind(sd, (void *)&laddr, sizeof(laddr)) == -1) {
		perror("bind()");
		close(sd);
		exit(1);
	}

	while (1) {
		// 对端地址长度需提前初始化
		raddrlen = sizeof(raddr);
		memset(rcvbuf.msg, '\0', MSGSIZE);
		if (recvfrom(sd, &rcvbuf, sizeof(rcvbuf), 0, (void *)&raddr, &raddrlen) == -1) {
			perror("recvfrom()");
			close(sd);
			exit(1);
		}
		printf("client ip:%s, port:%d, msg:%s\n", inet_ntoa(raddr.sin_addr), \
				ntohs(raddr.sin_port), rcvbuf.msg);
		if (strcmp(rcvbuf.msg, "close") == 0)
			break;
	}
	close(sd);

	exit(0);
}

