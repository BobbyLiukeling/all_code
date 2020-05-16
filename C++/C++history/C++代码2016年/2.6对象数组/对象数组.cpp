 #include<iostream>
using namespace std;
class Box
{
public:
	Box(int h=10,int w=12,int l=15):height(h),width(w),length(l){}//声明有参构造函数，用参数初始化表对数据成员进行初始化
	int volume();
private:
    int height;
	int width;
	int length;
};

int Box::volume()
{
	return(height*width*length);
}

int main()
{
	Box a[3]=
	{
		Box(),
		Box(15,18,20)
    };
	cout<<"the volume of a[0] is "<<a[0].volume()<<endl;
	cout<<"the volume of a[1] is "<<a[1].volume()<<endl;
	system("pause");
	return 0;
}