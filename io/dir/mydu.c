#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

#define BUFSIZE	128

int mydu_blocks(const char *path);
int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;

	// argv[1]
	printf("%dK %s\n", mydu_blocks(argv[1]) / 2, argv[1]);

	return 0;
}

int mydu_blocks(const char *path)
{
	struct stat res;
	DIR *dp;
	int sum = 0;
	struct dirent *entry = NULL;
	char pathbuf[BUFSIZE] = {};

	if (stat(path, &res) == -1) {
		perror("stat()");
		return -1;
	}
	// 是否是目录文件
	if (!S_ISDIR(res.st_mode)) {
		puts(path);
		return res.st_blocks;	
	}
	// 是目录－－－》读目录
	puts(path);
	sum = res.st_blocks;// 目录本身
	dp = opendir(path);
	if (NULL == dp) {
		perror("opendir()");
		return -1;
	}
	while (1) {
		entry = readdir(dp);	
		if (NULL == entry) {
			if (errno) {
				perror("readdir()");
				goto ERROR;
			}
			break;
		}
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;
		// path:/etc   passwd---->/etc/passwd
		memset(pathbuf, '\0', BUFSIZE);
		strcpy(pathbuf, path);
		strcat(pathbuf, "/");
		strcat(pathbuf, entry->d_name);
		sum += mydu_blocks(pathbuf);
	}
	closedir(dp);

	return sum;
ERROR:
	closedir(dp);
	return -1;
}






