#include <stdlib.h>
#include <iostream>
using namespace std;


class Product
{
public:
	Product()
	{
		std::cout << "construction of Product\n";
	}

	virtual ~Product()
	{
		std::cout << "destruction of Product\n";
	}
};

class Product1 : public Product
{
public:
	Product1()
	{
		std::cout << "construction of Product1\n";
	}

	virtual ~Product1()
	{
		std::cout << "destruction of Product1\n";
	}
};

class Product2 : public Product
{
public:
	Product2()
	{
		std::cout << "construction of Product2\n";
	}

	virtual ~Product2()
	{
		std::cout << "destruction of Product2\n";
	}
};

//////////////////////////////////////////////////////////////////////


class Creator
{
public:
	Creator(){}
	virtual ~Creator(){}
	void AnOperation();
protected:
	virtual Product* FactoryMethod() = 0;
};



class Creator1 : public Creator
{
public:
	Creator1();
	virtual ~Creator1();
protected:
	virtual Product* FactoryMethod();
};


class Creator2 : public Creator
{
public:
	Creator2();
	virtual ~Creator2();
protected:
	virtual Product* FactoryMethod();
};

//////////////////////////////////////////////////////////////////////


void Creator::AnOperation()
{
	Product* p = FactoryMethod();
	std::cout << "an operation of product\n";
}

Creator1::Creator1()
{
	std::cout << "construction of Creator1\n";
}

Creator1::~Creator1()
{
	std::cout << "destruction of Creator1\n";
}

Product* Creator1::FactoryMethod()
{
	return new Product();
}


Creator2::Creator2()
{
	std::cout << "construction of Creator2\n";
}

Creator2::~Creator2()
{
	std::cout << "destruction of Creator2\n";
}

Product* Creator2::FactoryMethod()
{
	return new Product();
}








int main(int argc,char* argv[])
{
	Creator *p = new Creator1();
	p->AnOperation();
	delete p;

	p = new Creator2();
	p->AnOperation();
	delete p;


	return 0;
}
