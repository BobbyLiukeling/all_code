#include<iostream>
using namespace std;
int time=0;//全局变量，计算搬动次数
//第N个圆盘从X柱搬到Z柱
void move(int n,char x,char z)
{
	cout<<"第"<<++time<<"步：将"<<n<<"号盘从"<<x<<"移到"<<z<<endl;
}
//将x柱按直径自上而下从小号到大编号从x柱搬到z柱上y柱作为辅助 
void hanoi(int n,char x,char y,int z)
{
	if (n==1)
		move(1,x,z);//将编号为一的圆盘从x移到y
	else
	{
		hanoi(n-1,x,y,z);//将x上编号为1至n-1的圆盘移到y，z作为辅助
		move(n,x,y);//将编号为n的圆盘从x移到z
		hanoi(n-1,y,x,z);//将y上编号为1至n-1的圆盘移到z，x作为辅助
	}
}
int main()
{
	int n;
	cout<<"3个柱为a,b,c圆盘最初在a柱上，请输入圆盘数：";
	cin>>n;
	hanoi(n,'a','b','c');
	system("pause");
	return 0;
}

