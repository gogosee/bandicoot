//#include "Bridge.h"
#include <stdlib.h>
#include <iostream>


class Implementor;

class Abstraction
{
public:
	Abstraction(Implementor* pImplementor);
	virtual ~Abstraction();
	void Operation();
protected:
	Implementor* m_pImplementor;
};


class Implementor
{
public:
	Implementor(){}
	virtual ~Implementor(){}
	virtual void OperationImpl() = 0;
};


class ConcreateImplementorA : public Implementor
{
public:
	ConcreateImplementorA(){}
	virtual ~ConcreateImplementorA(){}
	virtual void OperationImpl();
};


class ConcreateImplementorB : public Implementor
{
public:
	ConcreateImplementorB(){}
	virtual ~ConcreateImplementorB(){}
	virtual void OperationImpl();
};
////////////////////////////////////////////////////////////////////////


void ConcreateImplementorA::OperationImpl()
{
	std::cout << "Implementation by ConcreateImplementorA\n";
}

void ConcreateImplementorB::OperationImpl()
{
	std::cout << "Implementation by ConcreateImplementorB\n";
}

Abstraction::Abstraction(Implementor* pImplementor) : m_pImplementor(pImplementor)
{
}

Abstraction::~Abstraction()
{
	delete m_pImplementor;
	m_pImplementor = NULL;
}

void Abstraction::Operation()
{
	m_pImplementor->OperationImpl();
}
//////////////////////////////////////////////////////////



int main()
{
	ConcreateImplementorA *pImplA = new ConcreateImplementorA();
	Abstraction *pAbstraction1 = new Abstraction(pImplA);
	pAbstraction1->Operation();

	ConcreateImplementorB *pImplB = new ConcreateImplementorB();
	Abstraction *pAbstraction2 = new Abstraction(pImplB);
	pAbstraction2->Operation();

	delete pAbstraction1;
	delete pAbstraction2;

	return 0;
}

