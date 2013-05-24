#include <stdio.h>


int fun(int a, int b)
{
	return (a + b);
}



int main()
{
	int value = 0;
	int (*fun_pointer)(int, int);
	
	fun_pointer = fun;
	value = fun_pointer(1, 2);
	printf("value: %d\n", value);

	return 0;
}
