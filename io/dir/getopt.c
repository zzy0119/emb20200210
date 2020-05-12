#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
	char *optstirng = "-am:l::";
	char ch;
	struct option opts[3] = {
		{"help", no_argument, NULL, 'h'},
		{"list", optional_argument, NULL, 't'},
		{0, 0, 0, 0}
	};

	while (1) {
// 		ch = getopt(argc, argv, optstirng);
		ch = getopt_long(argc, argv, optstirng, opts, NULL);
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
		} else if (ch == 'h') {
			printf("help....\n");
		} else if (ch == 't') {
			printf("list....\n");
			if (optarg) {
				printf("参数:%s\n", optarg);
			}
		}
	}

	return 0;
}

