


class A
{
public:
	A(){}
	~A(){}

	int add()
	{
		return (a + b);
	}


private:
	int a;
	int b;
};


class A1 : public A
{
public:
	A1(){}
	~A1(){}


};


class A2 : public A
{
public:
	A2(){}
	~A2(){}


};





int main()
{
	A1	a1;
	A1	a11;
	A2	a2;
//	a1 =  a2;
	a1	= a11;


	return 0;
}


