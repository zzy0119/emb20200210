#include <stdio.h>
#include <unistd.h>

#define BUFSIZE	10

// cat /etc/passwd
int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	int ch;
	char buf[BUFSIZE];

	if (argc < 2)
		return 1;

	fp = fopen(argv[1], "r");
	if (NULL == fp) {
		return 1;
	}

	// r-->fp w-->stdout
	while (1) {
#if 0
		// 按字符读写
		ch = fgetc(fp);	
		if (ch == EOF) {
			// 文件结束标志/出错
			if (ferror(fp)) {
				// 出错
				goto ERROR;
			}
			break;
		}
		fputc(ch, stdout);
#endif
#if 0
		//　按行读写

		if (fgets(buf, BUFSIZE, fp) == NULL) {
			if (feof(fp))
				break;
			goto ERROR;
		}
		fputs(buf, stdout);
		fflush(stdout);
		sleep(1);
#endif
		// 二进制读写
		ch = fread(buf, 1, BUFSIZE, fp);
		if (ch == 0) {
			if (feof(fp))
				break;
			goto ERROR;
		}
		fwrite(buf, 1, ch, stdout);
	}

	fclose(fp);

	return 0;
ERROR:
	return 1;
}
