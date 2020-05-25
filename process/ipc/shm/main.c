#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define SHMSIZE	1024

int main(void)
{
	int shmid;
	pid_t pid;
	char *ptr;

	shmid = shmget(IPC_PRIVATE, SHMSIZE, IPC_CREAT | IPC_EXCL | 0600);
	if (shmid == -1) {
		perror("shmget()");
		exit(1);
	}

	pid = fork();
	if (pid == -1) {
		perror("fork()");
		goto ERROR;
	}
	if (pid == 0) {
		ptr = shmat(shmid, NULL, 0);
		if ((void *)-1 == ptr) {
			perror("shmat()");
			exit(1);
		}
		memcpy(ptr, "good morning", 12);
		shmdt(ptr);
		exit(0);
	}
	wait(NULL);
	ptr = shmat(shmid, NULL, 0);
	puts(ptr);
	shmdt(ptr);

	shmctl(shmid, IPC_RMID, NULL);
	exit(0);
ERROR:
	shmctl(shmid, IPC_RMID, NULL);
	exit(1);
}

