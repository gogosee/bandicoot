
// reference: http://www.360doc.com/content/06/0111/15/3044_56734.shtml

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main(void)
{
	typedef vector<int>    int_vector;
	typedef istream_iterator<int>    istream_itr;
	typedef ostream_iterator<int>    ostream_itr;
	typedef back_insert_iterator< int_vector > back_ins_itr;

	// STL�е�vector����
	int_vector num;

	// �ӱ�׼�����豸���������� 
	// ֱ��������Ƿ���������Ϊֹ
	copy(istream_itr(cin), istream_itr(), back_ins_itr(num));

	// STL�е������㷨
	sort(num.begin(), num.end());

	// ���������������׼����豸
	copy(num.begin(), num.end(), ostream_itr(cout, "\n"));

	return 0;
}
