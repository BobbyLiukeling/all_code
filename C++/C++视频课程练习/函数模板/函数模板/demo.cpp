#include<iostream>

using namespace std;

template<typename T>
void display(T a)
{
	cout << a << endl;
}

template<typename T,class C>
void display(T t, C c)
{
	cout << t << "  " << c << endl;
}

template<typename T,int kise>
void display(T a)
{
	for (int i = 0; i < kise; i++)
	{
		cout << a << endl;
	}
}
int main()
{
	display<double>(10.89);
	display<int, double>(5, 4.5);
	display<double, 4>(2);
	getchar();
	return 0;
}
