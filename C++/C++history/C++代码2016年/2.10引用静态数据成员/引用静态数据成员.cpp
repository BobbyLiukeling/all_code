#include<iostream>
using namespace std;

class Box
{
public:
	Box(int,int);
	int volume();
	static int height;
	int width;
	int length;
private:
};

Box::Box(int w,int l)
{
	width=w;
	length=l;
}

int Box::volume()
{
	return(height*width*length);
}

int Box::height=10;

int main()
{
	Box a(15,20),b(20,30);
	cout<<a.height<<endl;
	cout<<b.height<<endl;
	cout<<Box::height<<endl;
	cout<<a.volume()<<endl; 
	system("pause");
	return 0;
}
