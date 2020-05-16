#include<iostream>
using namespace std;
int main()
{

	double wages[3]={1000.0,20.0,40.0};
	short stacks[3]={3,2,1};	

	double *pw=wages;
	short *ps=&stacks[0];
	cout<<"pw="<<pw<<", *pw="<<*pw<<endl;

	pw=pw+1;//不能用自加pw+=pw,
	cout<<"add 1 to the pw pointer"<<endl;
	cout<<"pw="<<pw<<", *pw="<<*pw<<endl;

	cout<<"ps="<<ps<<",*ps="<<*ps<<endl;

	ps=ps+1;
	cout<<"add 1 to the ps pointer"<<endl;
	cout<<"ps="<<ps<<", *ps="<<*ps<<endl;

	cout<<sizeof(*pw)<<"  ;  "<<sizeof(*ps)<<endl;


	system("pause");
	return 0;
}