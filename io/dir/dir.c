#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	DIR *dp = NULL;
	struct dirent *entry = NULL;
	struct stat res;

	if (argc < 2)
		return 1;
	if (stat(argv[1], &res) == -1) {
		perror("stat()");
		return 1;
	}

	if (!S_ISDIR(res.st_mode))
		return 1;

	dp = opendir(argv[1]);
	if (NULL == dp) {
		perror("opendir()");
		return 1;
	}

	while (1) {
		entry = readdir(dp);
		if (NULL == entry) {
			if (errno) {
				// 出错
				perror("readdir()");
				goto ERROR;
			}
			break;
		}
		printf("%ld %s\n", entry->d_ino, entry->d_name);
	}

	closedir(dp);


	return 0;
ERROR:
	return 1;
}

