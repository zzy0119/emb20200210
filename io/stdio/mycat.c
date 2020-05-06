#include <stdio.h>

// cat /etc/passwd
int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	int ch;

	if (argc < 2)
		return 1;

	fp = fopen(argv[1], "r");
	if (NULL == fp) {
		return 1;
	}

	// r-->fp w-->stdout
	while (1) {
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
	}

	fclose(fp);

	return 0;
ERROR:
	return 1;
}
