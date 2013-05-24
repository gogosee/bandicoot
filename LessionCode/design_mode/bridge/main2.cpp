#include <iostream>
#include <string>
#include <vector>
using namespace std;

//�ֻ����
class HandsetSoft
{
public:
	virtual void Run()=0;
};

//��Ϸ���
class HandsetGame : public HandsetSoft
{
public:
	virtual void Run()
	{
		cout<<"�����ֻ���Ϸ"<<endl;
	}
};

//ͨѶ¼���
class HandSetAddressList : public HandsetSoft
{
public:
	virtual void Run()
	{
		cout<<"�ֻ�ͨѶ¼"<<endl;
	}
};

//�ֻ�Ʒ��
class HandsetBrand
{
protected:
	HandsetSoft* m_soft;
public:
	void SetHandsetSoft(HandsetSoft* temp)
	{
		m_soft = temp;
	}
	virtual void Run()=0;
};

//MƷ��
class HandsetBrandM : public HandsetBrand
{
public:
	virtual void Run()
	{
		m_soft->Run();
	}
};

//NƷ��
class HandsetBrandN : public HandsetBrand
{
public:
	virtual void Run()
	{
		m_soft->Run();
	}
};

//�ͻ���
int main()
{
	HandsetBrand *brand;
	brand = new HandsetBrandM();
	brand->SetHandsetSoft(new HandsetGame());
	brand->Run();
	brand->SetHandsetSoft(new HandSetAddressList());
	brand->Run();

	return 0;
}
