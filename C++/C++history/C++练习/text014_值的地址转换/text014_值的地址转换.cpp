#include<iostream>
using namespace std;
int main()
{
	void swap(int ,int);
	int i=3,j=5;
	swap(i,j);
	cout<<i<<" "<<j<<endl;
	return 0;
}

void swap(int a,int b)
{
	int temp;
	temp=a;
	a=b;
	b=temp; 
	cout<<a<<" "<<b <<endl;
}
//最后a,b的值交换了i，j的值并未交换
