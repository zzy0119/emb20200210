#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main(int argc, char *argv[])
{
	struct stat res;

	if (argc < 2)
		return 1;

	if (lstat(argv[1], &res) == -1) {
		perror("stat()");
		return 1;
	}

	// 文件类型
	if ((res.st_mode & S_IFMT) == S_IFREG) {
		printf("-");
	} else if ((res.st_mode & S_IFMT) == S_IFDIR) {
		putchar('d');
	} else if (S_ISLNK(res.st_mode)) {
		putchar('l');
	}

	// 文件权限
	if (res.st_mode & S_IRUSR)
		putchar('r');
	else
		putchar('-');
	if (res.st_mode & S_IWUSR)
		putchar('w');
	else
		putchar('-');
	if (res.st_mode & S_IXUSR) {
		if (res.st_mode & S_ISUID)
			putchar('s');
		else
			putchar('x');
	}
	else
		putchar('-');

	// 硬链接
	printf(" %ld ", res.st_nlink);

	// 文件拥有者
	struct passwd *pwd;
	pwd = getpwuid(res.st_uid);
	if (NULL == pwd) {
		perror("getspuid()");
		return 1;
	}
	printf("%s ", pwd->pw_name);
	// 文件所属组 man 5 group getgrgid(3)
	struct group *grp;

	grp = getgrgid(res.st_gid);
	if (NULL == grp) {
		perror("getgrgid()");
		return 1;
	}
	printf("%s ", grp->gr_name);

	// 文件字节个数
	printf("%ld ", res.st_size);

	// atime ctime mtime
	struct tm *tmp;
	tmp = localtime(&res.st_mtim.tv_sec);
	if (NULL == tmp) {
		return 1;
	}
	char tmbuf[100] = {};
	// strftime(tmbuf, 100, "%Y-%m-%d %H:%M:%S", tmp);
	strftime(tmbuf, 100, "%m  %d %H:%M", tmp);
	printf("%s ", tmbuf);

	printf("%s ", argv[1]);
	
	putchar('\n');

	return 0;
}


