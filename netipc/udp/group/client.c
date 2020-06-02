#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <errno.h>

#include "proto.h"

int main(int argc, char *argv[])
{
	int sd;
	struct sockaddr_in  raddr, laddr;
	struct msg_st buf;
	struct ip_mreqn mrq;
	int len;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sd) {
		perror("socket()");
		exit(1);
	}

	// 绑定本地地址
	laddr.sin_family = AF_INET;
	laddr.sin_addr.s_addr = INADDR_ANY; // 本地地址
	laddr.sin_port = htons(RCV_PORT);
	if (bind(sd, (void *)&laddr, sizeof(laddr)) == -1) {
		perror("bind()");
		close(sd);
		exit(1);
	}

	// 加入多播组
	inet_aton(MULTI_IP, &mrq.imr_multiaddr);
	inet_aton("0.0.0.0", &mrq.imr_address);
	mrq.imr_ifindex = if_nametoindex("ens33");
	if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mrq, sizeof(mrq)) == -1) {
		perror("setsockopt()");
		close(sd);
		exit(1);
	}

	while (1) {
		len = recvfrom(sd, &buf, MSGSIZE, 0, NULL, NULL);
		if (len == -1) {
			if (errno == EINTR)
				continue;
			perror("recvfrom()");
			close(sd);
			exit(1);
		}
		write(1, buf.msg, len);
	}

	close(sd);

	exit(0);
}

