#include<iostream>
using namespace std;
template<typename T>
T max(T a, T b, T c)
{
	if (b > a)
		a = b;
	if (c > a)
		a = c;
	return a;
}

int main()
{
	int i1 = 8, i2 = 5, i3 = 6,i;
	double d1 = 21.3, d2 = 34.1, d3 = 14.2,d;
	i = max<int>(i1, i2, i3);
	d = max<double>(d1, d2, d3);
	cout << "i_max=" << i << endl;
	cout << "d_max=" << d << endl;
	system("pause");
	return 0;
}