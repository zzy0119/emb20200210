
#ifndef __PROTO_H
#define __PROTO_H

#define MULTI_IP	"224.2.3.4"
#define RCV_PORT	1122

#pragma pack(0) // 结构单字节对齐
#define MSGSIZE		1024

struct msg_st {
	char msg[MSGSIZE];
};

#endif



