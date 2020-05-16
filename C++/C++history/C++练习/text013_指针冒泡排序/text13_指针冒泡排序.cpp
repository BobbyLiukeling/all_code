#include<iostream>
using namespace std;
int main()
{
	void selet_sort(int *p,int n);
	int a[10],i;
	cout<<"enter the originl array:"<<endl;
	for(i=0;i<10;i++)
		cin>>a[i];
	cout<<endl;
	selet_sort(a,10);
	cout<<"the sorted array"<<endl;
	for(i=0;i<10;i++)
		cout<<a[i]<<" "<<endl;
	return 0;
}

void selet_sort(int *p,int n)
{
	int i,j,k,t;
	for(i=0;i<n-1;i++)
	{
		k=i;
		for(j=i+1;j<n;j++)
		{
			if(*(p+j)>*(p+k))
			    k=j;
			t=*(p+k);
			*(p+k)=*(p+j);
			*(p+j)=t;
		}
	}
}