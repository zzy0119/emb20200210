#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "proto.h"

int main(int argc, char *argv[])
{
	int sd;
	struct sockaddr_in  raddr;
	struct msg_st sndbuf;

	if (argc < 2)
		exit(1);

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sd) {
		perror("socket()");
		exit(1);
	}

	// 发送数据
	strncpy(sndbuf.msg, argv[1], MSGSIZE);
	raddr.sin_family = AF_INET;
	inet_aton(SERVER_IP, &raddr.sin_addr);
	raddr.sin_port = htons(SERVER_PORT);
	if (sendto(sd, &sndbuf, strlen(sndbuf.msg), 0, (void *)&raddr, sizeof(raddr)) == -1) {
		perror("sendto()");
		close(sd);
		exit(1);
	}

	close(sd);

	exit(0);
}

