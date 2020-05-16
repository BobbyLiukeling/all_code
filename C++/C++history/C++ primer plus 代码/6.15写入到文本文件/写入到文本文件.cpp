#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	char automobile[50];
	int year;
	double a_price,d_price;

	ofstream outFile;
	outFile.open("carinfo.txt");

	cout<<"Enter the model and the automobile:";
	cin.getline(automobile,50);
	cout<<"Enter the moder year:";
	cin>>year;
	cout<<"Enter the original asking price:";
	cin>>a_price;
	d_price=0.193*a_price;

    cout<<fixed;
	cout.precision(2);
	cout.setf(ios_base::showpoint);
	cout<<"make and model:"<<automobile<<endl;
	cout<<"was asking $:"<<a_price<<endl;
	cout<<"Now asking $:"<<d_price<<endl;

	outFile<<fixed;
	outFile.precision(2);
	outFile.setf(ios_base::showpoint);
	outFile<<"Make and model:"<<automobile<<endl;
	outFile<<"Year:"<<year<<endl;
	cout<<"was asking $:"<<a_price<<endl;
	cout<<"Now asking $:"<<d_price<<endl;

	outFile.close();


	system("pause");
	return 0;
}