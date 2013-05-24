#include "stdio.h"
#include "stdlib.h"

#if 0
int main()
{
#if 0
	int a;
	char b = 0xff;

	a = (unsigned char)b;
	//a = b;
	printf("a: %d\n", a);
#endif


#if 0
	char buf[10];

	memset(buf, 0, 10);

//	snprintf(buf, sizeof(buf), "%d", 2);

	if(strlen(buf) == 0)
	//if(buf == '\0')
	{
		printf("null\n");
	}
#endif


//	abort();
	printf("%d\n", abs(-25));

	return 0;
}
#endif


#if 0
/* atexit example */
#include <stdio.h>
#include <stdlib.h>

void fnExit1 (void)
{
  puts ("Exit function 1.");
}

void fnExit2 (void)
{
  puts ("Exit function 2.");
}

int main ()
{
  atexit (fnExit1);
  atexit (fnExit2);
  puts ("Main function.");
  return 0;
}
#endif


#if 0
/* div example */
#include <stdio.h>
#include <stdlib.h>

int main ()
{
  div_t divresult;
  divresult = div (38,5);
  printf ("38 div 5 => %d, remainder %d.\n", divresult.quot, divresult.rem);
  return 0;
}
#endif

#if 0
/* getenv example: getting path */
#include <stdio.h>
#include <stdlib.h>

int main ()
{
  char * pPath;
  pPath = getenv ("PATH");
  if (pPath!=NULL)
    printf ("The current path is: %s\n",pPath);
  return 0;
}
#endif


#if 0
/* strtod example */
#include <stdio.h>
#include <stdlib.h>

int main ()
{
  char szOrbits[] = "365.24 29.53";
  char * pEnd;
  double d1, d2;
  d1 = strtod (szOrbits,&pEnd);
  d2 = strtod (pEnd,NULL);
  printf ("The moon completes %.2lf orbits per Earth year.\n", d1/d2);
  return 0;
}
#endif


#include <iostream>
using namespace std;
class A
{
public:
    A(double _data = 0.0):data(_data){}
    A& operator = (const A& rhs)
    {
        data = rhs.data;
        return *this;
    }
     
    friend A operator + (const A& lhs,const A& rhs);
    friend A operator - (const A& lhs,const A& rhs);
    friend A operator * (const A& lhs,const A& rhs);
    friend A operator + (const A& lhs,double rhs);
    friend A operator + (double lhs,const A& rhs);
    friend A operator * (const A& lhs,double rhs);
    friend A operator * (double lhs,const A& rhs);
    friend A operator - (const A& lhs,double rhs);
    friend A operator - (double lhs,const A& rhs);
     
     
    friend ostream& operator << (ostream& fout,A& a);
//  A& operator += (const A& rhs);
//  A& operator -= (const A& rhs);
//  A& operator *= (const A& rhs);  
private:
    double data;
};
 
A operator + (const A& lhs,const A& rhs)
{
    A res(0);
    res.data = lhs.data + rhs.data;
    return res;
}

A operator - (const A& lhs,const A& rhs)
{
    A res(0);
    res.data = lhs.data - rhs.data;
    return res;
}

A operator * (const A& lhs,const A& rhs)
{
    A res(0);
    res.data = lhs.data * rhs.data;
    return res;
}

A operator + (const A& lhs,double rhs)
{
    A res(0);
    res.data = lhs.data + rhs;
    return res;
}
 
A operator + (double lhs,const A& rhs)
{
    A res(0);
    res.data = lhs + rhs.data;
    return res;
}
A operator * (const A& lhs,double rhs)
{
    A res(0);
    res.data = lhs.data * rhs;
    return res;
}
A operator * (double lhs,const A& rhs)
{
    A res(0);
    res.data = lhs * rhs.data;
    return res;
}
A operator - (const A& lhs,double rhs)
{
    A res(0);
    res.data = lhs.data - rhs;
    return res; 
}
A operator - (double lhs,const A& rhs)
{
    A res(0);
    res.data = lhs - rhs.data;
    return res; 
}
     
ostream& operator << (ostream& fout,A& a)
{
    fout << a.data ;
    return fout;
}

int main(int argc, char* argv[])
{
    A a(2.3);
    A b(1.2);
    A d(3.4);
    A c;
    c = a + b + d;
    c=a+b;
    c=a+1.0;
    c=a-b;
    c=a-1.0;
    c=a*b;
    c=a*1.0;
    cout << c << endl;
     
    c=1.0+2.0*a*a-3.0*a*b;
    cout << c << endl;
    return 0;
}






