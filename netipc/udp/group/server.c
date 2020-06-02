#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <net/if.h>

#include "proto.h"

#define SERVER_IP 	"192.168.1.38"
#define SERVER_PORT		1111

int main(void)
{
	int sd;
	struct sockaddr_in laddr, raddr;
	socklen_t raddrlen; 
	struct msg_st rcvbuf;
	struct ip_mreqn imq;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sd) {
		perror("socket()");
		exit(1);
	}

#if 0
	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(SERVER_PORT); // 转换为网络字节序
	inet_aton(SERVER_IP, &laddr.sin_addr); // 点分十进制地址---》地址结构体
	if (bind(sd, (void *)&laddr, sizeof(laddr)) == -1) {
		perror("bind()");
		close(sd);
		exit(1);
	}
#endif

	// 设置多播组
	inet_aton(MULTI_IP, &imq.imr_multiaddr);
	inet_aton(SERVER_IP, &imq.imr_address);
	imq.imr_ifindex = if_nametoindex("ens33");
	if (setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, &imq, sizeof(imq)) == -1) {
		perror("setsockopt()");
		close(sd);
		exit(1);
	}

	raddr.sin_family = AF_INET;
	inet_aton(MULTI_IP, &raddr.sin_addr);
	raddr.sin_port	= htons(RCV_PORT);
	strcpy(rcvbuf.msg, "hello");
	while (1) {
		sendto(sd, &rcvbuf, 5, 0, (void *)&raddr, sizeof(raddr));
		sleep(1);
	}
	close(sd);

	exit(0);
}

