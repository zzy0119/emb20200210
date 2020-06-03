#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/mman.h>

// 动态进程池

#include "proto.h"
#define MAX_PROC_NR	30
#define MIN_FREE_NR	5
#define MAX_FREE_NR	10

#define NOTIFY_SIG	SIGUSR1

enum {
	STATE_INVAL,// 空白状态
	STATE_FREE, 
	STATE_BUSY
};

typedef struct {
	pid_t pid;
	int state;
}pool_t;

static int pool_del_proc(pool_t *pool);
static int pool_add_proc(pool_t *t, int sd);
static void user1_handler(int s)
{
	;
}

int main(void)
{
	int sd, newsd;
	struct sockaddr_in laddr, raddr;
	socklen_t raddrlen;
	pool_t *pool;
	sigset_t set, oldset;
	struct sigaction act, oldact;

	// 创建池
	pool = mmap(NULL, sizeof(pool_t) * MAX_PROC_NR, PROT_READ | PROT_WRITE, \
			MAP_ANONYMOUS | MAP_SHARED, -1, 0);

	// 初始化池
	for (int i = 0; i < MAX_PROC_NR; i++) {
		pool[i].pid = -1;
		pool[i].state = STATE_INVAL;
	}

	// 创建流式套接字
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		exit(1);
	}

	// 绑定本地地址
	laddr.sin_family = AF_INET;
	inet_aton(SERVER_IP, &laddr.sin_addr);
	laddr.sin_port = htons(SERVER_PORT);
	if (bind(sd, (void *)&laddr, sizeof(laddr)) == -1) {
		perror("bind()");
		goto ERROR;
	}

	// 处于监听状态
	if (listen(sd, 20) == -1) {
		perror("listen()");
		goto ERROR;
	}

	// 子进程分离的---》不需要收尸
	act.sa_handler = SIG_DFL;
	act.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGCHLD, &act, NULL);

	// 注册信号行为
	act.sa_handler = user1_handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(NOTIFY_SIG, &act, &oldact);

	// 初始化信号集
	sigemptyset(&set);
	sigaddset(&set, NOTIFY_SIG);
	sigprocmask(SIG_BLOCK, &set, &oldset);

	// 至少保证MIN_FREE_NR任务子进程
	for (int i = 0; i < MIN_FREE_NR; i++) {
		pool_add_proc(pool, sd);
	}

	int freecnt, busycnt;
	while (1) {
		// 查看进程池-->如果空闲的进程少了 加 多了 删
		sigsuspend(&oldset);
		freecnt = 0;
		busycnt = 0;
		// 任务池中的进程状态变化了 --->信号量保证同步
		for (int i = 0; i < MAX_PROC_NR; i++) {
			if (pool[i].pid == -1 && pool[i].state == STATE_INVAL)				
				continue;
			if (kill(pool[i].pid, 0)) {
				// 进程不存在
				pool[i].pid = -1;
				pool[i].state = STATE_INVAL;
				continue;
			}
			if (pool[i].state == STATE_FREE)
				freecnt ++;
			else if (pool[i].state == STATE_BUSY)
				busycnt ++;
		}
		if (freecnt < MIN_FREE_NR) {
			for (int i = 0; i < MIN_FREE_NR-freecnt; i++)
				pool_add_proc(pool, sd);
		}
		if (freecnt > MAX_FREE_NR) {
			for (int i = 0; i < freecnt - MAX_FREE_NR; i++)
				pool_del_proc(pool);
		}
		// 展示池中进程状态
		for (int i = 0; i < MAX_PROC_NR; i++) {
			if (pool[i].pid > 0 && !kill(pool[i].pid, 0)) {
				if (pool[i].state == STATE_FREE)
					putchar('O');
				else
					putchar('X');
			} else 
				putchar('-');
		}
		putchar('\n');
	}

	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}

static int get_free_pos(const pool_t *pool)
{
	for (int i = 0; i < MAX_PROC_NR; i++) {
		if (pool[i].pid == -1 && pool[i].state == STATE_INVAL)
			return i;
	}
	return -1;
}

// 子进程工作
static int child_job(pool_t *pool, int pos, int sd)
{
	struct sockaddr_in raddr;
	socklen_t raddrlen;
	int newsd;

	raddrlen = sizeof(raddr);
	while (1) {
		pool[pos].state = STATE_FREE;	
		kill(getppid(), NOTIFY_SIG);
		newsd = accept(sd, (void *)&raddr, &raddrlen);	
		if (newsd == -1) {
			if (errno == EINTR)
				continue;
			perror("accept()");
			exit(1);
		}
		pool[pos].state = STATE_BUSY;
		kill(getppid(), NOTIFY_SIG);
		// 数据交换
		write(newsd, "afternoon", 9);
		sleep(3);
		close(newsd);
	}
}

// 向池中添加新进程
static int pool_add_proc(pool_t *pool, int sd)
{
	pid_t pid;
	int pos;

	pos = get_free_pos(pool);
	if (pos == -1)
		return -1;
	pid = fork();
	if (pid == -1) {
		perror("fork()");
		return -1;
	}
	if (pid == 0) {
		child_job(pool, pos, sd);	
		exit(0);
	}
	pool[pos].pid = pid;
	pool[pos].state = STATE_FREE;

	return 0;
}

static int pool_del_proc(pool_t *pool)
{
	int i;

	for (i = 0; i < MAX_PROC_NR; i++) {
		if (pool[i].state == STATE_FREE && !kill(pool[i].pid, 0)) {
			kill(pool[i].pid, SIGTERM);
			pool[i].pid = -1;
			pool[i].state = STATE_INVAL;
			break;
		}
	}

	return 0;
}


