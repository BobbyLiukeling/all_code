#include<iostream>
using namespace std;

class Complex
{
public:
	Complex()
	{
		real=0;
		imag=0;
	}
	Complex(double r,double i)
	{
		real=r;
		imag=i;
	}
	Complex operator+(Complex&c2);
	void display();
private:
	double real;
	double imag;
};


Complex Complex::operator+(Complex&c2)
{
	Complex c;
	c.real=real+c2.real;
    c.imag=imag+c2.imag;
	return c;

}

void Complex::display()
{
	cout<<"("<<real<<","<<imag<<")"<<endl;
}
int main()
{
	Complex c1(3,4),c2(5,-10),c3;
	c3=c1+c2;
	cout<<"c1=";
	c1.display();
	cout<<"c2=";
	c2.display();
	cout<<"c1+c2=";
	c3.display();
	system("pause");
	return 0;
}
