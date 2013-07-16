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
		signal(SIGTERM, childfunc); //�źŲ���
		sleep(30); 
		exit(0); 
	} 

	fprintf(stderr, "Parent [%d] Fork child pid=[%d]\n", getpid(), pid); 
	sleep(1); 

	kill(pid, SIGTERM); //���ӽ��̷����ź�
	wait(&status); 

	fprintf(stderr, "Kill child pid=[%d], exit status[%d]\n", pid, status>>8); 
	return 0; 

}
