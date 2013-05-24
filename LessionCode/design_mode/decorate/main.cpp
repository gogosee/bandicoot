#include <string>
#include <iostream>
using namespace std;

//��
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
		cout<<" װ�����:"<<m_strName<<endl;
	}

};

//װ����
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

//T��
class TShirts: public Finery
{
public:
	virtual void Show()
	{
		cout<<" T Shirts"<<endl;
		m_component->Show();
	}
};

//����
class BigTrouser :public  Finery
{
public:
	virtual void Show()
	{
		cout<<" Big Trouser"<<endl;
		m_component->Show();
	}
};

// Ь��
class Shoes :public  Finery
{
public:
	virtual void Show()
	{
		cout<<" Nice Shoes "<<endl;
		m_component->Show();
	}
};

//�ͻ���
int main()
{
	Person *p=new Person("С��");
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


