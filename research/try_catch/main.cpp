#include <cstdlib>
#include <iostream>     //����ͷ�ļ�  
using namespace std;

double fuc(double x, double y) //���庯��  
{  
	if(y==0)  
	{  
		int		ie = -1;
		string	ee  = "error";

		y = 100;
		//throw y;     //����Ϊ0���׳��쳣  

		throw ee;     //����Ϊ0���׳��쳣  
		//throw ie;     //����Ϊ0���׳��쳣  
	}  
	return x/y;     //���򷵻�����������  
}  


int main()  
{  
	double res;  
	try  //�����쳣  
	{  
		res=fuc(2,3);  
		cout<<"The result of x/y is : "<<res<<endl;  
		res=fuc(4,0); // �����쳣�������ڲ����׳��쳣  
	}  
	catch(double v)             //���񲢴����쳣  
	{  
		cerr << "double error: error of dividing zero.\n";
		cerr << "throw error value is: " << v << "\n";
		exit(1);                //�쳣�˳�����  
	}  
	catch(string v)             //���񲢴����쳣  
	{  
		cerr<<"string error: error of dividing zero.\n";  
		cerr << "throw error value is: " << v << "\n";
		exit(1);                //�쳣�˳�����  
	}  
	catch( ... )
	{
		cerr<<"other error: error of dividing zero.\n";  
		exit(1);                //�쳣�˳�����  
	}

	return 0;
}
