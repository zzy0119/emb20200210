#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char *optstirng = "-am:l::";
	char ch;

	while (1) {
		ch = getopt(argc, argv, optstirng);
		if (ch == -1)
			break;
		if (ch == 'a') {
			printf("-a......\n");
		} else if (ch == 'm') {
			printf("-m.....\n");
			printf("参数:%s\n", optarg);
		} else if (ch == '?') {
			printf("i don't know\n");
		} else if (ch == 1) {
			printf("nonoption-arguments\n");
		} else if (ch == 'l') {
			printf("optional arguments\n");
			if (optarg) {
				printf("参数:%s\n", optarg);
			}
		}
	}

	return 0;
}

