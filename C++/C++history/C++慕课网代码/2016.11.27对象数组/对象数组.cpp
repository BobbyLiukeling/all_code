#include<iostream>
#include"Coordinate.h"
using namespace std;


int main()
{
	Coordinate coor[3];
	coor[0].ix=3;
	coor[0].iy=4;
	cout<<"coor[0].ix="<<coor[0].ix<<"coor[0].iy="<<coor[0].iy<<endl;

	Coordinate *p=new Coordinate[3];
	p->ix=7;
	p[0].iy=8;
	cout<<"p[0].ix="<<p[0].ix<<"   p[0].iy="<<p[0].iy<<endl;

	p++;//p+=1,Ö¸ÕëÏòºóÒÆ
	p->ix=1;
	cout<<"p[0].ix="<<p[0].ix<<endl;
	

	delete []p;
	p=NULL;

	system("pause");
	return 0;
}
