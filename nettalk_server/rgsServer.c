#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <signal.h>
#include <sqlite3.h>
#include <string.h>

#include "proto.h"

static int socket_init(char **errmsg);
int child_job(rgs_t *buf);

int main(void)
{
	char *err;
	struct sockaddr_in raddr;
	socklen_t raddrlen;
	rgs_t rcvbuf;
	pid_t pid;
	struct sigaction act, oldact;
	sqlite3 *db = NULL;
	int ret, cnt;
	char *sql;
	char *errmsg = NULL;

	int sd = socket_init(&err);
	if (sd < 0) {
		fprintf(stderr, "%s:%s\n", err, strerror(-errno));	
		exit(1);
	}

	// 子进程不收尸
	act.sa_handler = SIG_DFL;
	act.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGCHLD, &act, &oldact);

	// 打开数据库并创建注册表
	ret = sqlite3_open("./net_server.db", &db);
	if (ret) {
		fprintf(stderr, "can not open database:%s\n", sqlite3_errmsg(db));	
		exit(1);
	}
	sql = "CREATE TABLE IF NOT EXISTS rgsTable(\
		   count TEXT PRIMARY KEY NOT NULL,\
		   password TEXT NOT NULL\
		   );";	
	if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK) {
		fprintf(stderr, "sqlite3_exec():%s\n", errmsg);
		goto ERROR2;
	}
	sqlite3_close(db);

	raddrlen = sizeof(raddr);
	while (1) {
		// 接收客户端注册请求----》判断注册账号是否已被注册	
		cnt = recvfrom(sd, &rcvbuf, sizeof(rcvbuf), 0,  (void *)&raddr, &raddrlen);	
		if (cnt == -1) {
			perror("recvfrom()");
			goto ERROR;
		}
		fprintf(stdout, "recvfrom() ip:%s, port:%d\n", \
				inet_ntoa(raddr.sin_addr), ntohs(raddr.sin_port));
		// 并发 子进程判断能否注册 调用进程接收客户端请求
		pid = fork();
		if (pid == -1) {
			perror("fork()");
			goto ERROR;
		}
		if (pid == 0) {
			// 子进程
			ret = child_job(&rcvbuf);
			if (ret == -1) {
				fprintf(stderr, "child_job() failed\n");
				exit(1);
			}
			sendto(sd, &rcvbuf, sizeof(rcvbuf), 0, (void *)&raddr, raddrlen);
			exit(0);
		}
	}

	return 0;
ERROR2:
	sqlite3_close(db);
ERROR:
	close(sd);
	exit(1);
}

// 初始化套接字
static int socket_init(char **errmsg)
{
	int sd;
	struct sockaddr_in laddr;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		*errmsg = "socket()";
		return -errno;
	}

	//
	laddr.sin_family = AF_INET;
	inet_aton(RGS_SERVER_IP, &laddr.sin_addr);
	laddr.sin_port = htons(RGS_SERVER_PORT);
	if (bind(sd, (void *)&laddr, sizeof(laddr)) < 0) {
		*errmsg = "bind()";
		return -errno;
	}

	return sd;
}

int child_job(rgs_t *buf)
{
	sqlite3 *db = NULL;
	char *sql = NULL;
	sqlite3_stmt *stmt = NULL;
	char sqlbuf[100] = {};
	int ret;
	char *errmsg = NULL;

	// 链接数据库
	if (sqlite3_open("./net_server.db", &db)!= SQLITE_OK) {
		fprintf(stderr, "sqlite3_open():%s\n", sqlite3_errmsg(db));
		return -1;
	}

	// 查询注册表--->判断此账号是否已注册
	sql = "select * from rgsTable where count=?";
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		fprintf(stderr, "sqlite3_prepare_v2() failed\n");
		goto ERROR;
	}
	// 为stmt结构中的变量绑定值
	sqlite3_bind_text(stmt, 1, buf->count, -1, NULL);
	ret = sqlite3_step(stmt);
	if (ret == SQLITE_ERROR) {
		fprintf(stderr, "[%d]sqlite3_step() error\n", __LINE__);
		goto ERROR2;
	}
	sqlite3_finalize(stmt);
	if (ret == SQLITE_ROW) {
		// 此账号已注册
		buf->rgs_state = RGS_EXISTS;
	} else {
		// 没有注册过
		buf->rgs_state = RGS_OK;
		// 将此账号写入注册表
		snprintf(sqlbuf, 100,"insert into rgsTable(count, password) values('%s','%s')", buf->count, buf->password);
		if (sqlite3_exec(db, sqlbuf, NULL, NULL, &errmsg) != SQLITE_OK) {
			fprintf(stderr, "sqlite3_exec():%s\n", errmsg);
			goto ERROR;
		}
	}

	return 0;
ERROR2:
	sqlite3_finalize(stmt);
ERROR:
	sqlite3_close(db);
	return -1;
}






