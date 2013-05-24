#include<iostream>
#include <vector>
#include <string>
using namespace std;


class Prototype //抽象基类 
{ 
private:
	string m_strName;
public: 
	Prototype(string strName){ m_strName = strName; }
	Prototype() { m_strName = " "; }
	void Show() 
	{
		cout<<m_strName<<endl;
	}
	virtual Prototype* Clone() = 0 ; 
}; 


// class ConcretePrototype1 
class ConcretePrototype1 : public Prototype 
{ 
public: 
	ConcretePrototype1(string strName) : Prototype(strName){}
	ConcretePrototype1(){}

	virtual Prototype* Clone() 
	{ 
		cout << "ConcretePrototype1" << endl;
		ConcretePrototype1 *p = new ConcretePrototype1() ; 
		*p = *this ; //复制对象 
		return p ; 
	} 

	void Print1()
	{
		cout << "ConcretePrototype1 Print1" << endl;
	}
}; 


// class ConcretePrototype2 
class ConcretePrototype2 : public Prototype 
{ 
public: 
	ConcretePrototype2(string strName) : Prototype(strName){}
	ConcretePrototype2(){}
#if 0
	virtual Prototype* Clone() 
	{ 
		cout << "ConcretePrototype2" << endl;
		ConcretePrototype2 *p = new ConcretePrototype2() ; 
		*p = *this ; //复制对象 
		return p ; 
	} 
#endif

	void Print()
	{
		cout << "ConcretePrototype2" << endl;
	}
}; 


//客户端
int main()
{
	ConcretePrototype1* test = new ConcretePrototype1("小王");
	ConcretePrototype2* test2 = (ConcretePrototype2*)(test->Clone());
	test->Show();
	test2->Show();
	test2->Print();

	return 0;
}




