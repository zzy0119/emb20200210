#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define TTY1	"/dev/tty9"
#define TTY2	"/dev/tty10"
#define BUFSIZE	1024

enum {
	FSM_R=1,
	FSM_W,
	FSM_E,
	FSM_T
};

// 抽象数据类型
typedef struct {
	int rfd;
	int wfd;
	int state;
	int rcnt;
	char buf[BUFSIZE];	
	int pos;// 每一次写的数据在buf中的位置
	char *errfun;
}fsm_t;

// 状态机推动
int fsm_drive(fsm_t *fsm)
{
	int ret;

	switch(fsm->state) {
		case FSM_R:
			fsm->rcnt = read(fsm->rfd, fsm->buf, BUFSIZE);
			if (fsm->rcnt == -1) {
				// 非阻塞io假错情况
				if (errno != EAGAIN) {
					fsm->state = FSM_E;
					fsm->errfun = "read()";
				}
			} else {
				if (fsm->rcnt == 0) {
					// eof
					fsm->state = FSM_T;
				} else {
					fsm->pos = 0;
					fsm->state = FSM_W;
				}
			}
			break;
		case FSM_W:
			ret = write(fsm->wfd, fsm->buf+fsm->pos, fsm->rcnt);
			if (ret == -1) {
				if (errno != EAGAIN) {
					fsm->errfun = "write()";
					fsm->state = FSM_E;
				}
			} else {
				if (fsm->rcnt - ret > 0) {
					// 没写完
					fsm->pos += ret;	
					fsm->rcnt -= ret;
				} else {
					// 已经全部写完	
					fsm->state = FSM_R;
				}
			}

			break;
		case FSM_E:
			perror(fsm->errfun);
			fsm->state = FSM_T;
			break;
		case FSM_T:
			exit(0);
			break;
	}

	return 0;
}

int fsm_create(int fd1, int fd2)
{
	fsm_t fd12;
	fsm_t fd21;
	int fd1_old, fd2_old;

	// fd1 fd2一定要是非阻塞io
	fd1_old = fcntl(fd1, F_GETFL);
	fcntl(fd1, F_SETFL, fd1_old | O_NONBLOCK);
	fd2_old = fcntl(fd2, F_GETFL);
	fcntl(fd2, F_SETFL, fd2_old | O_NONBLOCK);

	fd12.rfd = fd1;
	fd12.wfd = fd2;
	memset(fd12.buf, '\0', BUFSIZE);
	fd12.state = FSM_R;
	fd12.errfun = NULL;
	fd12.pos = 0;

	fd21.rfd = fd2;
	fd21.wfd = fd1;
	memset(fd21.buf, '\0', BUFSIZE);
	fd21.state = FSM_R;
	fd21.errfun = NULL;
	fd21.pos = 0;

	// 推动
	while (fd12.state != FSM_T || fd21.state != FSM_T) {
		fsm_drive(&fd12);
		fsm_drive(&fd21);
	}

	fcntl(fd1, F_SETFL, fd1_old);
	fcntl(fd2, F_SETFL, fd2_old);

	return 0;
}

int main(void)
{
	int fd1, fd2;

	fd1 = open(TTY1, O_RDWR | O_NONBLOCK);
	if (fd1 == -1) {
		perror("open()");
		exit(1);
	}
	write(fd1, "***TTY9***", 10);
	fd2 = open(TTY2, O_RDWR);
	if (fd2 == -1) {
		perror("open()");
		close(fd1);
		exit(1);
	}
	write(fd2, "***TTY10***", 11);

	fsm_create(fd1, fd2);

	exit(0);
}


