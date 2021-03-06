// 从文件中读取内容，输出
// read读到文件末尾后，poll判读还是可读，再用read去读时，read返回值为0
// 读文件，用poll去判断是否可读时，poll总是判读为可读，不管是不是到了文件末尾, poll不会阻塞
// 原因可能是因为，poll去判断文件是否可读时，是去看文件描述符中，对应的内在/磁盘是否有内容

/* multiplex_poll.c */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <poll.h>

#define MAX_BUFFER_SIZE		1024 
#define IN_FILES			2	
#define TIME_DELAY			6000000
#define MAX(a, b)			((a > b)?(a):(b))

int main(void)
{
	struct pollfd fds[IN_FILES];
	char buf[MAX_BUFFER_SIZE];
	int i, res, real_read, maxfd;
	int fd1, fd2;

	if( (fd1 = open ("in1", O_RDONLY/*|O_NONBLOCK*/)) < 0 )
	{
	   printf("Open in1 error\n");
	   return 1;
	}
      
	if( (fd2 = open ("in2", O_RDONLY/*|O_NONBLOCK*/)) < 0 )
	{
		printf("Open in2 error\n");
		return 1;
	}

	fds[0].fd = fd1;
	fds[1].fd = fd2;

	for (i = 0; i < IN_FILES; i++)
	{
		fds[i].events = POLLIN | POLLERR;
	}

	while(fds[0].events || fds[1].events)
	{
		int retval = 0;

		retval = poll(fds, IN_FILES, TIME_DELAY);
		if( retval < 0)
		{
			printf("Poll error\n");
			return 1;
		}

		if( retval == 0 )
		{
			printf("timeout, continue\n");
			continue;
		}

		for (i = 0; i< IN_FILES; i++)
		{
			if (fds[i].revents == POLLERR)
			{
				printf("poll error.\n");
			}

			if (fds[i].revents == POLLIN)
			{
				memset(buf, 0, MAX_BUFFER_SIZE);
				real_read = read(fds[i].fd, buf, MAX_BUFFER_SIZE);
				if (real_read < 0)
				{
					if (errno != EAGAIN)
					{
						printf("EAGAIN.....\n");
						return 1;
					}
				}
				else if (real_read == 0)
				{
   					close(fds[i].fd);
					fds[i].events = 0;
					printf("real_read: %d\n", real_read);
				}
				else
				{
					/*
					if (i == 0)
					{
						if ((buf[0] == 'q') || (buf[0] == 'Q'))
						{
							printf("quit .....\n");
							return 1;
						}
					}
					else
					*/
					{
						buf[real_read] = '\0';
						printf("%s", buf);
					}
				} /* end of if real_read*/

			} /* end of if revents */
			else
			{
				printf("other event.\n");
			}


		}

	} /*end of while */

	exit(0);
}



