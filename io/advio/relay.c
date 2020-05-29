
#define TTY1	"/dev/tty9"
#define TTY2	"/dev/tty10"
#define BUFSIZE	1024

// 抽象数据类型
typedef struct {
	int rfd;
	int wfd;
	int rcnt;
	char buf[BUFSZIE];	
	char *errfun;
}fsm_t;

// 状态机推动
int fsm_drive()
{
	switch(现态) {
		case 读:
			break;
		case 写:
			break;
		case 异常:
			break;
		case 终态:
			break;
	}

}

int fsm_create(int fd1, int fd2)
{
	fsm_t fd12;
	fsm_t fd21;

	while (1) {
		fsm_drive(&fd12);
		fsm_drive(&fd21);
	}
}

int main(void)
{
	int fd1, fd2;

	fd1 = open(TTY1);

	fd2 = open(TTY2);

	fsm_drive(fd1, fd2);

}


