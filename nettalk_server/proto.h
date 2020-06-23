#ifndef __PROTO_H
#define __PROTO_H

// 注册
#define RGS_SERVER_IP	"192.168.1.38"
#define RGS_SERVER_PORT	1122
#define COUNT_SIZE		32
#define PWD_SIZE		128

enum {
	RGS_OK,
	RGS_EXISTS
};

typedef struct {
	char count[COUNT_SIZE];
	char password[PWD_SIZE];
	int8_t rgs_state;
}rgs_t;

#endif

