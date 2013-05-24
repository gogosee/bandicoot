#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

#define COUNT 5

class Iterator
{
public:
virtual bool hasNext() = 0;
virtual int next() = 0;
};

class Menu
{
public:
virtual Iterator* createIterator() = 0;
};

class CAggregateAIter : public Iterator
{
public:
CAggregateAIter(vector<int> vData);
bool hasNext();
int next();
private:
vector<int> m_vData;
int m_iPosition;
};

class CAggregateBIter : public Iterator
{
public:
CAggregateBIter(int* piData);
bool hasNext();
int next();
private:
int m_iPosition;
int m_iData[COUNT];
};

class CAggregateA : public Menu
{
public:
CAggregateA();
Iterator* createIterator();
private:
vector<int> m_vData;
};

class CAggregateB : public Menu
{
public:
CAggregateB();
Iterator* createIterator();
private:
int m_iData[COUNT];
};

class AggregateMg
{
public:
void printAggr();
void printAggr(Iterator* piter);
private:
CAggregateA m_aggrA;
CAggregateB m_aggrB;
};

CAggregateAIter::CAggregateAIter(vector<int> vData)
{
m_iPosition = 0;
for (int i=0; i<vData.size(); ++i)
{
m_vData.push_back(vData.at(i));
}
}
bool CAggregateAIter::hasNext()
{
if (m_iPosition < m_vData.size())
{
return true;
}
else
{
return false;
}
}
int CAggregateAIter::next()
{
int iData = m_vData.at(m_iPosition);
++m_iPosition;
return iData;
}

CAggregateBIter::CAggregateBIter(int* piData)
{
m_iPosition = 0;
for (int i=0; i<COUNT; ++i)
{
m_iData[i] = piData[i];
}
}
bool CAggregateBIter::hasNext()
{
if (m_iPosition < COUNT)
{
return true;
}
else
{
return false;
}
}
int CAggregateBIter::next()
{
int iData = m_iData[m_iPosition];
++m_iPosition;
return iData;
}

CAggregateA::CAggregateA()
{
for (int i=0; i<COUNT; ++i)
{
m_vData.push_back(i*(i+1));
}
}
Iterator* CAggregateA::createIterator()
{
return new CAggregateAIter(m_vData);
}

CAggregateB::CAggregateB()
{
for (int i = 0; i < COUNT; ++i)
{
m_iData[i] = i*(i+1);
}
}
Iterator* CAggregateB::createIterator()
{
return new CAggregateBIter(m_iData);
}

void AggregateMg::printAggr()
{
Iterator* piter1 = m_aggrA.createIterator();
Iterator* piter2 = m_aggrB.createIterator();
printAggr(piter1);
printAggr(piter2);
delete piter1;
delete piter2;
}

void AggregateMg::printAggr(Iterator* piter)
{
while(piter->hasNext())
{
	printf("%d\n",piter->next());
}
}

int main()
{
AggregateMg aggrMg;
aggrMg.printAggr();
return 0; 
}
