#include<iostream>
using namespace std;

template<class numtype>//声明类模板，虚拟类型名numtype

class Compare//类模板名comepare
{
public:
	Compare(numtype a,numtype b)//定义构造函数
	{
		x=a;
		y=b;
	}
	numtype max()
	{
		return(x>y)?x:y;
	}
	numtype min()
	{
		return(x<y)?x:y;
	}
private:
	numtype x,y;
};

int main()
{
	Com pare<int>cmp1(3,7);
	cout<<cmp1.max()<<"is the Maximum of two integer number"<<endl;
    cout<<cmp1.min()<<"is the Minimum of two integer number"<<endl;
	system("pause");
	return 0;
}
