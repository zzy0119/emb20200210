#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE	100

int main(int argc, char *argv[])
{
	time_t cur_time, after_time;
	struct tm *tmp;
	char buf[BUFSIZE] = {};

	if (argc < 2)
		return 1;

	time(&cur_time);

	tmp = localtime(&cur_time);

	tmp->tm_mday += atoi(argv[1]);

	// n天后时间戳
	after_time = mktime(tmp);
	
	tmp = localtime(&after_time);
	strftime(buf, BUFSIZE, "%Y-%m-%d %H:%M:%S", tmp);
	puts(buf);

	return 0;
}

