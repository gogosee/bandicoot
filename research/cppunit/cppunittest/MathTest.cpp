/// MathTest.cpp
// A TestFixture subclass.
// Announce: use as your owner risk.
// Author  : liqun (liqun@nsfocus.com)
// Data    : 2003-7-5

#include "MathTest.h"

// �����TestSuiteע�ᵽ����Ϊ"alltest"��TestSuite��, ���û�ж�����Զ�����
// Ҳ����CPPUNIT_TEST_SUITE_REGISTRATION( MathTest );ע�ᵽȫ�ֵ�һ��δ������TestSuite��.
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( MathTest, "alltest" );

// ���治��

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

