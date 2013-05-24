#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


pthread_spinlock_t lock;


void *handler_1(void *argv)
{
	pthread_spin_lock(&lock);
	printf("%s get lock.\n", __FUNCTION__);
	sleep(5);	
	pthread_spin_unlock(&lock);
}


void *handler_2(void *argv)
{
	pthread_spin_lock(&lock);
	printf("%s get lock.\n", __FUNCTION__);
	sleep(5);	
	pthread_spin_unlock(&lock);
}


int main()
{
	pthread_t	pid;

	pthread_spin_init(&lock, 0);


	pthread_create(&pid, NULL, &handler_1, NULL);
	sleep(1);
	pthread_create(&pid, NULL, &handler_2, NULL);

	pthread_spin_destroy(&lock);

	sleep(15);

	return 0;
}
