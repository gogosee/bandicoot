
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
// SIGHUP 1 /* hangup */ 
// // SIGINT 2 /* interrupt */ 
// // SIGQUIT 3 /* quit */ 
// // SIGABRT 6 /* used by abort */ 
// // SIGKILL 9 /* hard kill */ 
// // SIGALRM 14 /* alarm clock */   
// // SIGCONT 19 /* continue a stopped process */   
// // SIGCHLD 20 /* to parent on child stop or exit */ 
// //arg 是信号类
//
//
bool loop = true;

void hello(int arg)
{
	printf("void hello(int arg)  Signal Type: %d",arg);
}


void hello2(int arg)
{
	printf("void hello(int arg)  Signal Type: %d",arg);
}


void exitHandle(int arg)
{
	printf("退出信号  Signal Type: %d",arg);
}


void childfunc(int sig){ 
	fprintf(stderr, "Get Sig\n"); 
	loop = false;
} 


int main(int argc, char *argv[])
{
//	signal(SIGINT,hello2);
//	signal(SIGHUP,exitHandle);
	signal(SIGTERM, childfunc);

	while(loop)
	{
		sleep(1);
		printf("loop\n");
	}
	printf("quit\n");

//	getchar();
//	system("PAUSE");   
//
	return EXIT_SUCCESS;
}


