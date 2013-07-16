#include <cstdlib>
#include <iostream>     //包含头文件  
using namespace std;

double fuc(double x, double y) //定义函数  
{  
	if(y==0)  
	{  
		int		ie = -1;
		string	ee  = "error";

		y = 100;
		//throw y;     //除数为0，抛出异常  

		throw ee;     //除数为0，抛出异常  
		//throw ie;     //除数为0，抛出异常  
	}  
	return x/y;     //否则返回两个数的商  
}  


int main()  
{  
	double res;  
	try  //定义异常  
	{  
		res=fuc(2,3);  
		cout<<"The result of x/y is : "<<res<<endl;  
		res=fuc(4,0); // 出现异常，函数内部会抛出异常  
	}  
	catch(double v)             //捕获并处理异常  
	{  
		cerr << "double error: error of dividing zero.\n";
		cerr << "throw error value is: " << v << "\n";
		exit(1);                //异常退出程序  
	}  
	catch(string v)             //捕获并处理异常  
	{  
		cerr<<"string error: error of dividing zero.\n";  
		cerr << "throw error value is: " << v << "\n";
		exit(1);                //异常退出程序  
	}  
	catch( ... )
	{
		cerr<<"other error: error of dividing zero.\n";  
		exit(1);                //异常退出程序  
	}

	return 0;
}
