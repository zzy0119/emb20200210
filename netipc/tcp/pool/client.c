#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#include "proto.h"

#define BUFSIZE	1024

int main(void)
{
	int sd;
	struct sockaddr_in raddr;
	char buf[BUFSIZE] = {};

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		exit(1);
	}

	// bind()可省略

	// 请求与服务端链接
	raddr.sin_family = AF_INET;
	inet_aton(SERVER_IP, &raddr.sin_addr);
	raddr.sin_port = htons(SERVER_PORT);
	if (connect(sd, (void *)&raddr, sizeof(raddr)) == -1) {
		perror("connect()");
		goto ERROR;
	}

	// read() / write()
	read(sd, buf, BUFSIZE);
	puts(buf);

	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}

