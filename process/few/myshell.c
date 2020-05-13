#include <stdio.h>
#include <string.h>
#include <glob.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int parse_string(char *s, glob_t *globres);
int main(void)
{
	char *lineptr = NULL;
	size_t n = 0;
	glob_t globres;
	pid_t pid;

	while (1) {
		printf("[emb@uplooking]$ ");
		// 读命令
		// "ls -l -a"
		if (getline(&lineptr, &n, stdin) == -1) {
			perror("getline()");
			exit(1);
		}
		if (strcmp(lineptr, "exit\n") == 0)
			break;
//		parse_string(lineptr, &globres);
		
		pid = fork();
		// error
		if (pid == 0) {
			// 执行读到的指令
//			execvp((globres.gl_pathv)[0], globres.gl_pathv);
			execl("/bin/sh", "sh", "-c", lineptr, NULL);
			perror("execvp()");
			exit(1);
		}
		wait(NULL);
		//globfree(&globres);
		free(lineptr);
		lineptr = NULL;
		n = 0;
	}

	exit(0);
}

int parse_string(char *s, glob_t *globres)
{
	char *tok = NULL;
	int i = 0;

	while (1) {
		tok = strtok(s, " \n");
		if (NULL == tok)
			break;
		glob(tok, GLOB_NOCHECK | GLOB_APPEND*i, NULL, globres);
		i = 1;
		s = NULL;
	}

}

