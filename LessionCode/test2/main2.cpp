#include <stdio.h>
#include <stddef.h>
#include <string.h>


int main(void)
{
	char *p = NULL;
	char str[] = "Hello world!";
	char *pstart = str;
	char *pend = str + strlen(str);
	ptrdiff_t difp = pend - pstart;
	p = pstart + difp;
	printf("%d\n", difp);
	printf("%c\n", p[0]);

	char t='\12';
	printf("%d\n", t);

	return 0;
}
