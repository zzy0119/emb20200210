#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *ret;

	if (argc < 2)
		return 1;
	char *str = argv[1];
	char *delim = "a ";

#if 0
	while (1) {
		ret = strtok(str, delim);	
		if (ret == NULL)
			break;
		puts(ret);
		str = NULL;
	}
#endif
	while (1) {
		ret = strsep(&str, delim);
		if (NULL == ret)
			break;
		if (strcmp("", ret) == 0)
			continue;
		puts(ret); //""
	}

	return 0;
}

