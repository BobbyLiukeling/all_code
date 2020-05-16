#include<iostream>
using namespace std;
int main()
{
	int quizscores[10]={20,20,20,20,20,19,20,18,20,20};
	cout<<"doing it right:"<<endl;
	int i;
	for(i=0;quizscores[i]==20;i++)
	{
		cout<<"quiz"<<i<<" is 20"<<endl;
	}

	system("pause");
	return 0;
}