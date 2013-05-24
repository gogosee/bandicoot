#include <string>
#include <iostream>
using namespace std;

//人
class Person
{
private:
	string m_strName;
public:
	Person(string strName)
	{
		m_strName=strName;
	}
	Person(){}
	virtual void Show()
	{
		cout<<" 装扮的是:"<<m_strName<<endl;
	}

};

//装饰类
class Finery : public Person
{
protected:
	Person* m_component;
public:
	void Decorate(Person* component)
	{
		m_component=component;
	}
	virtual void Show()
	{
		   m_component->Show();
	}
};

//T恤
class TShirts: public Finery
{
public:
	virtual void Show()
	{
		cout<<" T Shirts"<<endl;
		m_component->Show();
	}
};

//裤子
class BigTrouser :public  Finery
{
public:
	virtual void Show()
	{
		cout<<" Big Trouser"<<endl;
		m_component->Show();
	}
};

// 鞋子
class Shoes :public  Finery
{
public:
	virtual void Show()
	{
		cout<<" Nice Shoes "<<endl;
		m_component->Show();
	}
};

//客户端
int main()
{
	Person *p=new Person("小李");
	BigTrouser *bt=new BigTrouser();
	TShirts *ts=new TShirts();
	Shoes *sh = new Shoes();

#if 0
	bt->Decorate(p);
	ts->Decorate(bt);
	ts->Show();
#endif

	bt->Decorate(p);
	ts->Decorate(bt);
	sh->Decorate(ts);
	sh->Show();

	return 0;
}


