#include <time.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main (int argc, char *argv[])
{
	if( argc != 2 || strcmp(argv[1], "help") ==0 )
	{
		printf("NAME\n");
		printf("\twdate - display system current time timestamp(utc)\n");
		printf("\twdate - convert time string to timestamp(utc)\n");
		printf("SYNOPSIS\n");
		printf("\twdate -c\n");
		printf("\twdate \"2012-12-12 10:10:11\"\n");
		return 0;
	}


	if( strcmp(argv[1], "-c") == 0)
	{
		// 获取系统当前时间戳(utc)
		time_t timep;
		time(&timep); /*当前time_t类型UTC时间*/	
		cout << timep << endl;
	}
	else
	{
		// 转换时间字符串("2012-12-12 12:12:12")为时间戳（utc）
		struct tm* tmp_time = (struct tm*)malloc(sizeof(struct tm));
		strptime(argv[1],"%Y-%m-%d %H:%M:%S",tmp_time);
		time_t t = mktime(tmp_time);
		cout << t << endl;
	}

	return 0;
}
