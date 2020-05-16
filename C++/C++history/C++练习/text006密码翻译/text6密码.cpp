#include<iostream>
using namespace std;
int main()
{
    char admin[100];
	int i;
	cout<<"ÇëÊäÈëÔ­ÃÜÂë£º";
	cin>>admin;
	for(i=0;admin[i]!='\0';i++)
	{
		admin[i]=admin[i]-4;
	}
	cout<<"·­ÒëÂëÎª£º"<<admin<<'\n';
}