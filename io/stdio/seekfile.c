#include <stdio.h>

#define BUFSIZE	10

int main(int argc, char *argv[])
{
	FILE *fp;
	char buf[BUFSIZE] = {};

	if (argc < 2)	
		return 1;

	fp = fopen(argv[1], "r+");
	if (NULL == fp) {
		goto ERROR;
	}
	fseek(fp, 10, SEEK_SET);
	fread(buf, 1, BUFSIZE-1, fp);
	puts(buf);
	printf("%ld\n", ftell(fp));

	rewind(fp);
	printf("%ld\n", ftell(fp));

	fclose(fp);

	return 0;
ERROR:
	return 1;
}

