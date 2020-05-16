#include<iostream>
using namespace std;
int main()
{
	char animal[20]="bear";
	const char*bird="wren";
	char*ps;

	cout<<animal<<" and "<<bird<<endl;

	cout<<"Enter a kind of animal:"<<endl;
    cin>>animal;

	ps=animal;
	cout<<ps<<endl;

	cout<<animal<<" at "<<(int *)animal<<endl;
	cout<<ps<<" at "<<(int*)ps<<endl;
	//animal和ps指向同一块内存，所有最后输出的值和地址都一样；

	system("pause");
	return 0;
}