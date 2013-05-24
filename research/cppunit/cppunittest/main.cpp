/// main.cpp
// Main file for cppunit test.
// Announce: use as your owner risk.
// Compile : g++ -lcppunit MathTest.cpp main.cpp
// Run     : ./a.out
// Test    : RedHat 8.0 CppUnit1.8.0
// Author  : liqun ( a litthle modification. liqun@nsfocus.com)
// Data    : 2003-7-5

// �����ٰ�������TestFixture�����ͷ�ļ�
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

// ���������TestSuite, ���ļ����ڲ���Ҫ����. 

int main()
{
	CppUnit::TextUi::TestRunner runner;
	
	// ��ע���TestSuite�л�ȡ�ض���TestSuite, û�в�����ȡδ������TestSuite.
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry("alltest");
	// ������TestSuite��TestRunner��
	runner.addTest( registry.makeTest() );
	// ���в���
	runner.run();
}

