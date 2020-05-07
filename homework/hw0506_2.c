#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE	10

int cpfile(FILE *sfp, FILE *dfp, int n);
int main(int argc, char *argv[])
{
	if (argc < 4)
		return 1;

	FILE *fp1, *fp2;
	
	fp1 = fopen(argv[1], "r+");
	if (fp1 == NULL) {
		fprintf(stderr, "fopen() failed\n");
		return 1;
	}
	fp2 = tmpfile(); // 创建临时文件
	cpfile(fp1, fp2, atoi(argv[2])-1);
	fputs(argv[3], fp2);
	cpfile(fp1, fp2, -1);
	rewind(fp1);
	rewind(fp2);
	cpfile(fp2, fp1, -1);

	fclose(fp1);
	fclose(fp2);

	return 0;
}

// 将一个文件写入另一个文件 n == -1　全部内容 n > 0　写入n行
int cpfile(FILE *sfp, FILE *dfp, int n)
{
	char buf[BUFSIZE] = {};

	while (n != 0) {
		memset(buf, '\0', BUFSIZE);
		if (fgets(buf, BUFSIZE, sfp) == NULL) {
			if (feof(sfp))
				break;
			return -1;
		}
		if (n > 0 && strchr(buf, '\n') != NULL) {
			// 完整行
			n --;
		}
		fputs(buf, dfp);	
	}
	return 0;
}

