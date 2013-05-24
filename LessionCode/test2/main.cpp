#include<stddef.h>
#include "stdio.h"


#define AI_OFFSET(stype, member)                ( (ptrdiff_t) &(((stype*)(0))->member) )
//#define AI_OFFSET(stype, member)                (((ptrdiff_t)&(((stype*)sizeof(void*))->member)) - sizeof(void*))
#define AI_GET_STRUCT_PTR(mp, stype, member)    ((stype*)(((char*)mp) - AI_OFFSET(stype,member)))


typedef struct TestInfo_st
{
	int a;
	int b;
	int c;
	int d;
}TestInfo;


int main()
{
//	printf("%d\n", sizeof(void*));

	TestInfo	stTest;
	TestInfo	*pTest = NULL;

	stTest.a = 1;
	stTest.b = 2;
	stTest.c = 3;
	stTest.d = 4;

	//pTest = AI_GET_STRUCT_PTR( &(stTest.c), TestInfo, c);
	pTest = (TestInfo*) ( ((char*)(&(stTest.c))) - AI_OFFSET(TestInfo, c) );

	printf("pTest->a: %d\n", pTest->a);	
	printf("pTest->b: %d\n", pTest->b);	
	printf("pTest->c: %d\n", pTest->c);	
	printf("pTest->d: %d\n", pTest->d);	

#if 0
	printf("offset: %d\n", AI_OFFSET(TestInfo, c));

	int nOffset = ( (ptrdiff_t)& ( ((TestInfo*)sizeof(void*))->c ) ) - sizeof(void*);
	printf("nOffset: %d\n", nOffset);

	printf("%d\n",  (ptrdiff_t)& (    ((TestInfo*)0)->c    ) );

//	printf("%d\n", (ptrdiff_t) &( (TestInfo*)(0)->c );
#endif

	return 0;
}
