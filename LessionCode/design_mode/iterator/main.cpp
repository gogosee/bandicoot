#include <iostream>
using namespace std;


class IntStack
{
public:
    IntStack();
    virtual ~IntStack();

    void Push(int);
    int Pop();
    friend class IntStackIterator;
private:
    enum { SIZE = 100 }; 
    int m_nStack[SIZE];
    int m_nTop;
};


IntStack::IntStack()
{
    m_nTop = 0;
}


IntStack::~IntStack()
{

}


void IntStack::Push(int nData)
{
    if(m_nTop < SIZE)
    {
        m_nStack[m_nTop++] = nData;
    }
    else
    {
        cout << "³¬³öÈÝÁ¿·¶Î§¡£" << endl;
    }
}


int IntStack::Pop()
{
    if(m_nTop > 0)
    {
        return m_nStack[--m_nTop];
    }

    return 0;
}
///////////////////////////////////////////////////////////////////////////////



class Iterator  
{
public:
    Iterator();
    virtual ~Iterator();

    virtual int operator++() = 0;
    virtual int operator++(int) = 0;
};


Iterator::Iterator()
{

}


Iterator::~Iterator()
{

}
///////////////////////////////////////////////////////////////////////////////



class IntStackIterator : public Iterator
{
public:
    IntStackIterator(IntStack*);
    virtual ~IntStackIterator();

    int operator++();
    int operator++(int);
private:
    IntStack* m_pStack;
    int m_nIndex;
};


IntStackIterator::IntStackIterator(IntStack* pStack)
{
    m_pStack = pStack;
    m_nIndex = 0;
}


IntStackIterator::~IntStackIterator()
{
    if(m_pStack != NULL)
    {
        delete m_pStack;
        m_pStack = NULL;
    }
}


int IntStackIterator::operator++()
{
    if(m_nIndex < m_pStack->m_nTop)
    {
        return m_pStack->m_nStack[++m_nIndex];
    }

    return 0;
}


int IntStackIterator::operator++(int)
{
    if(m_nIndex < m_pStack->m_nTop)
    {
        return m_pStack->m_nStack[m_nIndex++];
    }

    return 0;
}
///////////////////////////////////////////////////////////////////////////////



int main(int argc, char* argv[])
{
    IntStack* pStack = new IntStack;
    for(int i = 0; i < 20; ++i)
    {
        pStack->Push(i);
    }

    Iterator* pIt = new IntStackIterator(pStack);
    for(int i = 0; i < 20; ++i)
    {
        cout << (*pIt)++ << endl;
    }

    return 0;
}




