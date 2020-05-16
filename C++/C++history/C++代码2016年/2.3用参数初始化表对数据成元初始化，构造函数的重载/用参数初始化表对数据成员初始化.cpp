#include<iostream>
using namespace std;

class Box
{
public:
	Box();//声明一个无参的构造函数
	Box(int h,int w,int l):height(h),width(w),length(l){}//定义一个有参的构造函数，用参数的初始化表对数据成员进行初始化
	int volume();
private:
	int height;
	int width;
	int length;
};

Box::Box()
{
	height=10;
	width=10;
	length=10;
}

int Box::volume()
{
	return (height*width*length);
}

int main()
{
	Box box1;//没有参数
	cout<<"the volume of box1 is"<<box1.volume()<<endl;
	Box box4(15,30,20);
	cout<<"the volume of box1 is"<<box4.volume()<<endl;
	system("pause");
	return 0; 




}