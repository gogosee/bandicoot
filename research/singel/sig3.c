#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <assert.h> 
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/types.h> 

void childfunc(int sig){ 
	fprintf(stderr, "Get Sig\n"); 
} 


int main() 
{ 
	pid_t pid; 
	int status; 
	assert((pid = fork()) >= 0); 

	if(pid == 0)
	{ 
		signal(SIGTERM, childfunc); //信号捕获
		sleep(30); 
		exit(0); 
	} 

	fprintf(stderr, "Parent [%d] Fork child pid=[%d]\n", getpid(), pid); 
	sleep(1); 

	kill(pid, SIGTERM); //向子进程发送信号
	wait(&status); 

	fprintf(stderr, "Kill child pid=[%d], exit status[%d]\n", pid, status>>8); 
	return 0; 

}
