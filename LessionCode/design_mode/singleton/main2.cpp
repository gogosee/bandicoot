#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Singelton
{
private:
	Singelton(){}
	static Singelton* singel;

public:
	static Singelton* GetInstance()
	{
		if(singel == NULL)
		{
			singel = new Singelton();
		}
		return singel;
	}

};
Singelton* Singelton::singel = NULL;//注意静态变量类外初始化

//客户端：
int main()
{
	Singelton* s1=Singelton::GetInstance();
	Singelton* s2=Singelton::GetInstance();
	if(s1 == s2)
		cout<<"ok"<<endl;
	else
		cout<<"no"<<endl;
	return 0;
}

