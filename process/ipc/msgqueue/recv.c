#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

#include "proto.h"

int main(void)
{
	key_t key;
	int msgid;
	msg_t buf;
	int created = 1;

	key = ftok(PATHNAME, PROID);
	if (key == -1) {
		perror("ftok()");
		exit(1);
	}

	msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0666);
	if (msgid == -1) {
		if (errno != EEXIST) {
			perror("msgget()");
			exit(1);
		}
		msgid = msgget(key, 0);
		created = 0;
	}

	if (msgrcv(msgid, &buf, MSGSIZE, -3, 0) == -1) {
		perror("msgrcv()");
		exit(1);
	}
	puts(buf.text);

#if 0
	if (created)
		msgctl(msgid, IPC_RMID, NULL);
#endif

	exit(0);
}

