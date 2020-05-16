#include<iostream>
using namespace std;
typedef struct
 {
	int x;
	int y;
}Coor;

int main(void)
{
	Coor c;
	Coor&c1=c;//&就是引用符号
	c1.x=10;
	c1.y=20;
	cout<<c.x<<,<<c.y<<endl;

	system("pause");
	return 0;
}