#include <stdio.h>
#include <glob.h>

int main(void)
{
	glob_t res;

	if (glob("/etc/*", GLOB_NOSORT, NULL, &res) != 0) {
		return 1;
	}

	glob("/etc/.*", GLOB_APPEND | GLOB_NOSORT, NULL, &res);

	for (int i = 0; i < res.gl_pathc; i++) {
		puts((res.gl_pathv)[i]);
	}

	globfree(&res);

	return 0;
}

