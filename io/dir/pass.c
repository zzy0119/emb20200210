#include <stdio.h>
#include <unistd.h>
#include <shadow.h>
#include <string.h>

#define NAMESIZE	32

int main(void)
{
	char name[NAMESIZE] = {};
	char *passwd_str;
	struct spwd *sp;
	char *my_crypt;

	// 读用户名和密码
	printf("用户名:");
	fgets(name, NAMESIZE, stdin);
	*strchr(name, '\n') = '\0';
	passwd_str = getpass("密码:");

	// 获取原密码
	sp = getspnam(name);
	if (NULL == sp) {
		perror("getspnam()");
		return 1;
	}

	// 加密
	my_crypt = crypt(passwd_str, sp->sp_pwdp);
	if (NULL == my_crypt) {
		perror("crypt()");
		return 1;
	}

	// 比较
	if (strcmp(sp->sp_pwdp, my_crypt) == 0) {
		printf("登录成功\n");
	} else {
		printf("鉴定错误\n");
	}

	return 0;
}

