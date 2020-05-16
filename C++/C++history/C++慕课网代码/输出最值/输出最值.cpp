#include<iostream>
using namespace std;



int getMaxOrMin(int *arr,int count,bool isMax)
{
	int temp=arr[0];
	for(int i=1;i<count;i++)
	{
		if(isMax)
		{
           if(temp<arr[i])
		   {
		   	temp=arr[i];
		   }
		}
		else(isMax)
		{
			if(temp>arr[i])
			{
				temp=arr[i];
			}
		}
		
	}
	return temp;
}

int main()
{
	int arr[4]={1,48,2,9};
	bool isMax=true;
	cin>>isMax;
	cout<<getMaxOrMin(arr,4,isMax)<<endl;
	system("pause");
	return 0;
}
