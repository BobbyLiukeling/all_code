#include<iostream>
using namespace std;
 class Box
 {
 public:
	 Box(int,int,int);
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
	 return (height*width*length);
 }
 int main()
 {
	 Box box1(12,34,56);
	 cout<<"tne valume of box is "<<box1.volume()<<endl;
	 system("pause");
	 return 0;

 }