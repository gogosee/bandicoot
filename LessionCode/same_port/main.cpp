#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>


bool DataProcess ( )
{
	try
	{
		signal(SIGPIPE, SIG_IGN);
		signal(SIGCHLD, SIG_IGN);

		// tcp绑定同一端口测试
		int listen_fd;
		int	n;
		struct sockaddr_in sin;

		bzero(&sin, sizeof(sin));
    	sin.sin_family 		= AF_INET;
	    sin.sin_addr.s_addr = INADDR_ANY;
		sin.sin_port 		= htons(34567);


		listen_fd = socket(AF_INET, SOCK_STREAM, 0);
		if (-1 == listen_fd)
		{
			perror("call to socket");
			exit(1);
		}

		n = bind(listen_fd, (struct sockaddr *)&sin, sizeof(sin));
		if (-1 == n)
		{
			perror("call to bind");
			exit(1);
		}

		n = listen(listen_fd, 20);
		if (-1 == n)
		{
			perror("call to listen");
			exit(1);
		}

		printf("Accepting connections...\n");


		sleep(500);

	}
	catch ( ... )
	{

	}

	exit(0);	
}



bool StartSingleDataProcess ( )
{
    pid_t pid = fork();
    int status = 0;

    if ( pid < 0 )
    {
        printf( "数据处理进程fork失败" );
        return false;
    }

    if ( pid == 0 )
    {
        pid_t pid2 = fork();

        if ( pid2 < 0 )
        {
            printf( "公共数据管理进程fork失败" );
            exit ( 1 );
        }

        if ( 0 == pid2 )
        {
			DataProcess ();
        }
        else
        {
            exit ( 0 );
        }
    }
    else
    {
        //等待启动完成
        if ( waitpid ( pid, &status, 0 ) > 0 )
        {
            if ( 0 == status )
            {
            }
            else
            {
                return false;
            }
        }
        else
        {
        }

    }
}








int main()
{
	int	nThreadCount = 3;


	for(int i = 0; i < nThreadCount; ++i)
	{
		StartSingleDataProcess();
	}


	return 0;
}
