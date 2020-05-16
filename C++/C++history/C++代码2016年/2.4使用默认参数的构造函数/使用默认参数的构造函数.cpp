#include<iostream>
using namespace std;

class Box
{
public:
	Box(int h=10,int w=10,int l=10);
	int volume();
private:
	int height;
	int width;
	int length;
};

Box::Box(int h,int w,int l)
{
	height=h;
	width=h;
	length=l;
}

int Box::volume()
{
	return(height*width*length);
}

int main()
{
	Box box1;
	cout<<"the volume of box1"<<box1.volume()<<endl;
	Box box2(15);
	cout<<"the volume of box1"<<box2.volume()<<endl;
	Box box3(15,30);
	cout<<"the volume of box1"<<box3.volume()<<endl;
	Box box4(15,30,20);
	cout<<"the volume of box1"<<box4.volume()<<endl;
	system("pause");
	return 0;
}