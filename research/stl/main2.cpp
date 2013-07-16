#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
//#include <ifstream>
//#include <ofstream>
//#include <iofstream>

using namespace std;

int main()
{
	std::fstream file;
	try
	{
		file.open("a.log");
		if ( (file.rdstate() & std::ifstream::failbit ) != 0 )
		{
			std::cerr << "Error opening 'test.txt'\n";
		}
	}
	catch(std::exception &e)
	{
		printf("nono");
		cout<<e.what()<<endl;
	}
}

