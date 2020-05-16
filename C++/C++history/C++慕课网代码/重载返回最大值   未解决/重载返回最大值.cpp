#include<iostream>
using namespace std;

int getmax(int a,int b)
{
	return a>b?a:b;
} 

int getmax(int arr[])
{
     int i=arr[0];
	 for(int j=1;arr[j]!=NULL;j++)
	 {
		 if(i>arr[j])
			 i=arr[j];
	 }
	 return i;
}

int main()
{
	int arr[3]={3,8,4};
	cout<<getmax(arr[1],arr[2])<<endl;
	cout<<getmax(arr)<<endl;
	system("pause");
	return 0;
}
