#include<iostream>
#include<string>
using namespace std;
int main()
{
	char word[5]="?ate";
	for (char ch='a';strcmp(word,"mate");ch++)//ch++是ASSCI相加
	{
		cout<<word<<endl;
		word[0]=ch;//换掉第一个字母
	}
    cout<<"After loop ends,word is"<<word<<endl;
	system("pause");
	return 0;
}