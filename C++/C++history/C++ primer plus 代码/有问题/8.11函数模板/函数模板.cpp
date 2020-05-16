#include<iostream>
using namespace std;
template <typename T>
void swap(T &a,T &b);
int main()
{
	int i=10;
	int j=20;
	cout<<"i="<<i<<"   j="<<j<<endl;
	cout<<"Using compiler-generate int swapper"<<endl;
	swap(i,j);
	cout<<"Now i="<<i<<"¡¡¡¡j="<<j<<endl;
	double x=18.9;
	double y=11.22;
	cout<<"x="<<x<<"  y="<<y<<endl;
    cout<<"Using compiler-generate double swapper"<<endl;
	swap(x,y);
	cout<<"Now x="<<x<<"   y="<<y<<endl;

	system("pause");
	return 0;
}


template<typename T>
void swap(T &a,T &b)
{
	T temp;
	temp=a;
	a=b;
	b=temp;
}