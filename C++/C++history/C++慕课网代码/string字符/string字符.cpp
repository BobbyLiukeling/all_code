#include<iostream>//ÓÃ»§µÇÂ¼
#include<string>
using namespace std;

class Time
{
public:
private:
};

int main()
{
	string name;
	cout<<"please input the name:"<<endl;
	getline(cin,name);
	if(name.empty())
	{
		cout<<"input is null...."<<endl;
		system("pause");
     	return 0;
	}
	if(name=="imooc")
	{
		cout<<"you are a adminisstrator"<<endl;
	}
	cout<<"hello "+name<<endl;
	cout<<"your name lengthia:"<<name.size()<<endl;
	cout<<"yuor name firse letter is:"<<name[0]<<endl;
	system("pause");
	return 0;
}
