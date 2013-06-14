#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <sys/stat.h>
#include <errno.h>
using namespace std;

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("NAME\n");
		printf("\tstat - display file last update time\n");
		printf("SYNOPSIS\n");
		printf("\tstat FILE...\n");
		return 0;
	}

    struct stat stStat;
    if(-1 == stat(argv[1], &stStat))
	{
		printf("Command failed, Errno: %d\n", errno);
		return 0;
	}

	//struct tm *lpUTCTm = gmtime(&stStat.st_mtime);
	//time_t locale_time = stStat.st_mtime + 28800;
	//time_t locale_time = stStat.st_mtime;
	//struct tm *lpTm = gmtime(&locale_time);
	struct tm *lpTm = localtime(&stStat.st_mtime);
	printf("locale_time: %ld\n", stStat.st_mtime);

	char buf[56] = {0x0};
	strftime ( buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", lpTm);

	printf("Modify: %s\n", buf);

    return 0;
}

