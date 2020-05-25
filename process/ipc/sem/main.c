#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define FLNAME	"/tmp/test"

static int semid;
void V(void);
void P(void);
int main(void)
{
	FILE *fp = NULL;
	pid_t pid;
	char buf[100] = {};

	fp = fopen(FLNAME, "w");
	if (NULL == fp) {
		perror("fopen()");
		exit(1);
	}
	fprintf(fp, "%d", 0);
	fclose(fp);

	semid = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0600);
	if (semid == -1) {
		perror("semget()");
		exit(1);
	}
	// 向信号量中存信号
	semctl(semid, 0, SETVAL, 1);

	for (int i = 0; i < 20; i++) {
		pid = fork();
		if (pid < 0) {
			perror("fork()");
			exit(1);
		}
		if (pid == 0) {
			// 取信号量中的信号	
			fp = fopen(FLNAME, "r+");
			P();
			// if error
			fgets(buf, 100, fp);
			rewind(fp);
			sleep(1);
			fprintf(fp, "%d", atoi(buf)+1);
			fflush(NULL);
			V(); // 还信号
			fclose(fp);
			exit(0);
		}
	}

	for (int i = 0; i < 20; i++)
		wait(NULL);
	semctl(semid, 0, IPC_RMID);

	exit(0);
}

// 取信号
void P(void)
{
	struct sembuf sem;

	sem.sem_num = 0;
	sem.sem_op = -1;
	sem.sem_flg = 0;
	if (semop(semid, &sem, 1) < 0) {
		perror("semop()");
		exit(1);
	}
}

void V(void)
{
	struct sembuf sem;

	sem.sem_num = 0;
	sem.sem_op = 1;
	sem.sem_flg = 0;
	if (semop(semid, &sem, 1) < 0) {
		perror("semop()");
		exit(1);
	}
}


