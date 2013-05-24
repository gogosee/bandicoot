#include <stdio.h>
#include <stdlib.h>

//#define NDEBUG 
#include <assert.h>


int main()
{
	char *p = NULL;	
	p =  (char *)malloc(sizeof(char) * 5);

	printf("Call assert().\n");

	assert(p==NULL);
	return 0;
}
