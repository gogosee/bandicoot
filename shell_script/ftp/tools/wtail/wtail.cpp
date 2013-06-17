#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <iostream> 
#include <fstream>
#include <sys/stat.h>
#include <errno.h>
using namespace std;

extern char 	*optarg;
#define 	LOG_MAX_LINE_SIZE	4096

char filename[128] = {0x0};		// 读取的文件名
long tell_pos = 0;				// 读取文件的起始位置
long read_size = 0;				// 读取文件的字节数
bool entire_row_flag = false;	// 是否读取整行
bool result_flag = false;		// 是否保存实际读取的字节数
char result_file[128] = {0x0};	// 保存实际读取的字节数


void Usage(const char *sProgram)
{
	printf("NAME\n");
	printf("\twtail - read date from file\n");
	printf("SYNOPSIS\n");
	printf("\twtail -f FILE -t START_POSITION -s SIZE\n");
	printf("\twtail -e -f FILE -t START_POSITION -s SIZE\n");
	printf("\twtail -f FILE -t START_POSITION -s SIZE -r READ_SIZE_RECORD_FILE\n");
	printf("\twtail -e -f FILE -t START_POSITION -s SIZE -r READ_SIZE_RECORD_FILE\n");
	printf("DESCRIPTION\n");
	printf("\t-f\t the file name that will read\n");
	printf("\t-t\t the begin position of reading\n");
	printf("\t-s\t read size\n");
	printf("\t-r\t file that record the really read size\n");
	printf("\t-e\t if have this parame, the last line will not print when the last line is not a entire row \n");
	printf("\t\t and the really read size will be record in -r [RES_FILE] \n");
	printf("\t-h\t this manual\n");

}


int InitArgv(int argc, char *argv[])
{
    char liOptChar=' ';

    while( (liOptChar = getopt(argc, argv, "f:t:s:r:eh")) != EOF )
    {
        switch(liOptChar)
        {
            case 'f':
				strncpy(filename, optarg, std::min(strlen(optarg), sizeof(filename)-1));
                break;
            case 't':
				tell_pos = atoi(optarg);
            case 's':
				read_size = atoi(optarg);
                break;
            case 'r':
				result_flag = true;
				strncpy(result_file, optarg, std::min(strlen(optarg), sizeof(result_file)-1));
                break;
            case 'e':
				entire_row_flag = true;
				break;
            case 'h':
                Usage(argv[0]);
                return(-1);
            default:
                Usage(argv[0]);
                return(-1);
        }
    }

	return 0;
}


int main(int argc, char *argv[])
{
	if( argc < 7 || argc > 11 )
	{
		Usage(argv[0]);
		return 0;
	}

	if(0 != InitArgv(argc, argv))
	{
		return 0;
	}

	std::ifstream ifs;
	char line[LOG_MAX_LINE_SIZE] = {0x0};

	ifs.open (filename, std::ifstream::in);
	ifs.seekg (tell_pos);

	int rsize = 0;
	int need_size = 0;
	while(ifs.getline(line, sizeof(line))) 
	{
		rsize += strlen(line) + 1;

		if(rsize == read_size)
		{
			need_size = rsize;
			cout << line << endl;
			break;
		}
		else if(rsize < read_size)
		{
			need_size = rsize;
			cout << line << endl;
		}
		else if(rsize > read_size)
		{
			if(!entire_row_flag)
			{
				char tmp_line[LOG_MAX_LINE_SIZE] = {0x0};
				strncpy(tmp_line, line, read_size - need_size);
				cout << tmp_line << endl;
				need_size = read_size;
			}
			break;
		}
	}
	ifs.close();

	// 将实际读取的字节数，写入文件记录
	if (result_flag)
	{
		char real_read_size[128] = {0x0};
		std::ofstream ofs;
		ofs.open(result_file, std::ofstream::binary);

		snprintf(real_read_size, sizeof(real_read_size), "%d", need_size);
		ofs.write (real_read_size, strlen(real_read_size));
		ofs.close();
	}

    return 0;
}



