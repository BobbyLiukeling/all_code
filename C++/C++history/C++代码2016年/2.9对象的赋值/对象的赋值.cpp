#include<iostream>
using namespace std;

class Box
{
public:
	Box(int=10,int =10,int =10);
	int volume();
private:
	int height;
	int width;
	int length;
};

Box::Box(int h,int w,int l)
{
	height=h;
	width=w;
	length=l;
}

int Box::volume()
{
	return(height*width*length);
}

int main()
{
    Box box1(15,25,39),box2;
	cout<<"the volume of box1 is"<<box1.volume()<<endl;
	box2=box1;
	cout<<"the volume of box2 is"<<box2.volume()<<endl;
	system("pause");
	return 0;
}
