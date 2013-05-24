/// MathTest.cpp
// A TestFixture subclass.
// Announce: use as your owner risk.
// Author  : liqun (liqun@nsfocus.com)
// Data    : 2003-7-5

#include "MathTest.h"

// 把这个TestSuite注册到名字为"alltest"的TestSuite中, 如果没有定义会自动定义
// 也可以CPPUNIT_TEST_SUITE_REGISTRATION( MathTest );注册到全局的一个未命名的TestSuite中.
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( MathTest, "alltest" );

// 下面不变

void MathTest::setUp()
{
     m_value1 = 2;
     m_value2 = 3;
}

void MathTest::tearDown()
{

}

void MathTest::testAdd()
{
     int result = m_value1 + m_value2;
     CPPUNIT_ASSERT( result == 5 );
}

