#include<iostream>
#include<string>
#include"Teacher.h"

using namespace std;




int main()
{
	Teacher t;
	
	cout<<t.getName()<<"  "<<t.getGender()<<"  "<<t.getAge<<endl;

	Teacher m("merry",12);
		cout<<m.getName()<<"  "<<m.getGender()<<"  "<<m.getAge<<endl;

//	t.taech(); 
	system("pause");
	return 0;
}
