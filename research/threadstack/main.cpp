#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
pthread_attr_t Attr;
void * get_stack(void *arg)
{
//	char buf[1024 * 1024 * 7];
	size_t stack_size;
	pthread_attr_t Attr;
	pthread_attr_init(&Attr);
	// void *stack_addr;
	pthread_attr_getstacksize(&Attr, &stack_size);//获取栈大小
	printf("stack size = %d\n", stack_size);
}


int main(int argc, char **argv)
{
	pthread_t id;
	pthread_attr_init(&Attr);
//	pthread_attr_setdetachstate(&Attr, PTHREAD_CREATE_JOINABLE);
//	pthread_attr_setstacksize(&Attr,4096*1024);//设置线程的栈大小
//	if (pthread_create(&id, &Attr, (void *)get_stack, NULL) != 0)

	size_t stack_size;
	// void *stack_addr;
	pthread_attr_getstacksize(&Attr, &stack_size);//获取栈大小
	printf("stack size = %d\n", stack_size);

int count = 0;
while(1)
{
	if (pthread_create(&id, &Attr, get_stack, NULL) != 0)
	{	
		perror("pthread_create error!\n");
   		return -1;
	}
	printf("count: %d\n", count++);
}
	pthread_join(id, NULL);
	pthread_attr_destroy(&Attr);
	return 0;
}
