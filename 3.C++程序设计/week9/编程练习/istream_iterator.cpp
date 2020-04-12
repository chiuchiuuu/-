#include <iostream>
#include <string>
using namespace std;

// �ڴ˴�������Ĵ���
template<class T>
class  CMyistream_iterator : public iterator<input_iterator_tag, T> {
private:
	T n;
	istream & os;
public:
	CMyistream_iterator(istream &os) : os(os) {
		os >> n;
	}
	T operator*() {
		return n;
	}
	void operator++(int) {
		os >> n;
	}
	//���캯��ִ�й����оͻ�Ҫ�����룬Ȼ��ÿ��ִ��++�����ȡ�������е���һ����Ŀ��ִ�� * �򷵻��ϴδ��������ж�ȡ����Ŀ

};
int main()
{
	CMyistream_iterator<int> inputInt(cin);
	int n1, n2, n3;
	n1 = *inputInt; //���� n1
	int tmp = *inputInt;
	cout << tmp << endl;
	inputInt++;
	n2 = *inputInt; //���� n2
	inputInt++;
	n3 = *inputInt; //���� n3
	cout << n1 << "," << n2 << "," << n3 << endl;
	CMyistream_iterator<string> inputStr(cin);
	string s1, s2;
	s1 = *inputStr;
	inputStr++;
	s2 = *inputStr;
	cout << s1 << "," << s2 << endl;
	return 0;
}