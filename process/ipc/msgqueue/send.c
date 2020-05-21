#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

#include "proto.h"

int main(int argc, char *argv[])
{
	key_t key;
	int msgid;
	msg_t buf;
	int created = 1;

	if (argc < 3)
		exit(1);

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

	buf.mtype = atoi(argv[1]);
	memset(buf.text, '\0', MSGSIZE);
	strncpy(buf.text, argv[2], strlen(argv[2]));
	if (msgsnd(msgid, &buf, strlen(argv[2])+1, 0) == -1) {
		perror("msgsnd()");
		exit(1);
	}

#if 0
	if (created)
		msgctl(msgid, IPC_RMID, NULL);
#endif

	exit(0);
}

