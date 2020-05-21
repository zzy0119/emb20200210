#ifndef __PRO_H
#define __PRO_H

// 同一个key
#define PATHNAME	"/etc/passwd"
#define PROID		'a'

#define MSGSIZE		1024

// 数据格式
typedef struct {
	long mtype;
	char text[MSGSIZE];
}msg_t;

#endif

