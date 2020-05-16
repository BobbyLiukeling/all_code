#include<iostream>
using namespace std;
int main()
{
	const int ArSize=20;
	char name[ArSize];
	char dessert[ArSize];

	cout<<"Enter your name"<<endl;
	cin.getline(name,ArSize);
	cout<<"Enter you favorite desserst"<<endl;
	cin.getline(dessert,ArSize);
	cout<<"I have some delicious "<<dessert;
	cout<<" for you "<<name<<endl;
	system("pause");
	return 0;
}