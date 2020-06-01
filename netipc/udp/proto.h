
#ifndef __PROTO_H
#define __PROTO_H

#define SERVER_IP 	"192.168.1.38"
#define SERVER_PORT		1111

#pragma pack(0) // 结构单字节对齐
#define MSGSIZE		1024

struct msg_st {
	char msg[MSGSIZE];
};

#endif



