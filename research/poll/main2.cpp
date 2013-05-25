// 说明：从标准输入流中读取内容，然后输出
// poll会阻塞

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
#define IN_FILES			1	
#define TIME_DELAY			3000
#define MAX(a, b)			((a > b)?(a):(b))

int main(void)
{
	struct pollfd fds[IN_FILES];
	char buf[MAX_BUFFER_SIZE];
	int i, res, real_read, maxfd;

	fds[0].fd = 0;

	for (i = 0; i < IN_FILES; i++)
	{
		fds[i].events = POLLIN | POLLERR;
	}

	while(fds[0].events)
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
   					//close(fds[i].fd);
					//fds[i].events = 0;
					printf("real_read: %d\n", real_read);
				}
				else
				{
					if ((buf[0] == 'q') || (buf[0] == 'Q'))
					{
						printf("quit .....\n");
						return 1;
					}

					buf[real_read] = '\0';
					printf("%s", buf);
				} 
			} 
			else
			{
				printf("other event.\n");
			}
		}

	} /*end of while */

	exit(0);
}



