#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(void)
{
#if 0
	for (int i = 0; environ[i] != NULL; i++) {
		puts(environ[i]);
	}
#endif

	// putenv("PATH=.");
	setenv("PATH", ".", 1);
	printf("PATH:%s\n", getenv("PATH"));

	return 0;
}

