#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd;
	struct stat res;
	char *s;

	if (argc < 2) 
		exit(1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		perror("open()");
		exit(1);
	}

	fstat(fd, &res);
	// if error

	s = mmap(NULL, res.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (MAP_FAILED == s) {
		perror("map()");
		close(fd);
		exit(1);
	}
	puts(s);
	munmap(s, res.st_size);

	close(fd);

	exit(0);
}
