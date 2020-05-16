#include<iostream>
using namespace std;
int main()
{
	int max_4(int a,int b,int c,int d);
	int a,b,c,d,max;
	cout<<"please enter 4 interger number";
	cin>>a>>b>>c>>d;
	max=max_4(a,b,c,d);
	cout<<"max="<<max<<endl;
	return 0;
}
int max_4(int a,int b, int c, int d)
{
	int max(int,int);
	int m;
	m=max(a,b);
	m=max(m,c);
	m=max(m,d);
	return m;
}
int max(int x,int y)
{
	if(x>y)
		return x;
	else
		return y;
}
