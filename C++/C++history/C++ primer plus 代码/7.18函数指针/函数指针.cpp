#include<iostream>
using namespace std;
double betsy(int);
double pam(int);
void estimate(int lines,double(*pf)(int));

int main()
{
	int code;
    cout<<"How many lines of code do yuo need";
	cin>>code;
	cout<<"here's Betsy's estimate"<<endl;
	estimate(code,betsy);
	cout<<"here's Pam's estimate"<<endl;
	estimate(code,pam);
	system("pause");
	return 0;
}

double betsy(int lns)
{
	return 0.05*lns;
}

double pam(int lns)
{
	return 0.03*lns+0.0004*lns*lns;
}

void estimate(int lines,double(*pf)(int))
{
	cout<<lines<<"lines will take";
	cout<<(*pf)(lines)<<"hour"<<endl;
}
