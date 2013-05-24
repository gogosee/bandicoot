/// MathTest.h
// A TestFixture subclass.
// Announce: use as your owner risk.
// Author  : liqun (liqun@nsfocus.com)
// Data    : 2003-7-5

#include "cppunit/extensions/HelperMacros.h"


class MathTest : public CppUnit::TestFixture {
	// 声明一个TestSuite
	CPPUNIT_TEST_SUITE( MathTest );
	// 添加测试用例到TestSuite, 定义新的测试用例需要在这儿声明一下
	CPPUNIT_TEST( testAdd );
	// TestSuite声明完成
	CPPUNIT_TEST_SUITE_END();
	// 其余不变

protected:
	int m_value1, m_value2;
	
public:
	MathTest() {}
	
	// 初始化函数
	void setUp ();
	// 清理函数
	void tearDown();
	
	// 测试加法的测试函数
	void testAdd ();
	// 可以添加新的测试函数
};

