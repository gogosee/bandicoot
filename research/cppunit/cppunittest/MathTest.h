/// MathTest.h
// A TestFixture subclass.
// Announce: use as your owner risk.
// Author  : liqun (liqun@nsfocus.com)
// Data    : 2003-7-5

#include "cppunit/extensions/HelperMacros.h"


class MathTest : public CppUnit::TestFixture {
	// ����һ��TestSuite
	CPPUNIT_TEST_SUITE( MathTest );
	// ��Ӳ���������TestSuite, �����µĲ���������Ҫ���������һ��
	CPPUNIT_TEST( testAdd );
	// TestSuite�������
	CPPUNIT_TEST_SUITE_END();
	// ���಻��

protected:
	int m_value1, m_value2;
	
public:
	MathTest() {}
	
	// ��ʼ������
	void setUp ();
	// ������
	void tearDown();
	
	// ���Լӷ��Ĳ��Ժ���
	void testAdd ();
	// ��������µĲ��Ժ���
};

