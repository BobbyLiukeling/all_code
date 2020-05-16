#include<iostream>
using namespace std;
int main()
{
	int max(int a,int b,int c=0);//有默认参数
	int a,b,c;
	cout<<"please enter three numbers";
	cin>>a>>b>>c;
	//两种输出方式的结果不一样
	cout<<"max(a,b,c)"<<max(a,b,c)<<endl;
	cout<<"max(a,b,c)"<<max(a,b)<<endl;
	return 0;
}
int max(int a,int b,int c)
{
	if(a<b)
		a=b;
	if(a<c)
		a=c;
	return a;
}
