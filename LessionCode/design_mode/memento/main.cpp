#include <iostream>
#include <string>
using namespace std;

class Memo;

//发起人类
class Originator
{
public:
	string state;
    Memo* CreateMemo();
	void SetMemo(Memo* memo);
	void Show()
	{
		cout<<"状态："<<state<<endl;
	}
};

//备忘录类
class Memo
{
public:
	string state;
	Memo(string strState)
	{
		state= strState;
	}
};

Memo* Originator::CreateMemo()
{
	return new Memo(state);
}

void Originator::SetMemo(Memo* memo)
{
	state = memo->state;
}

//管理者类
class Caretaker
{
public:
	Memo* memo;
};

//客户端：
int main()
{
	Originator* on=new Originator();
	on->state = "on";
	on->Show();

	Caretaker* c= new Caretaker();
	c->memo = on->CreateMemo();

	on->state = "off";
	on->Show();

	on->SetMemo(c->memo);
	on->Show();
	return 0;
}



