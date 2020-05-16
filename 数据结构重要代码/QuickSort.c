int Partition(int A[],int low,int high)//一趟排序结果
{
    int pivot = A[low];//领每次传入数组的第一个元素为枢轴


    //将数组调整为以枢轴为中间值数组前面元素均小于枢轴，后面元素均大于枢轴
    while(low<high)//外层循环多趟
    {
        //从后往前查找一个比枢轴元素小的第一个出现的元素：小的往前调
        while (low<high && (A[high]>pivot || A[high] == pivot)) 
            --high;
        A[low] == A[high];//将从后往前查找到的第一个比枢轴小的数放在low（枢轴）的位置，high的位置空出来了

        //从前往后遍历查找到第一个 比pivot大的元素
        while (low<high && (A[low]<pivot || A[low] == pivot))//大的往后调
            ++low;
        A[high] = A[low];//之前high的位置是空出来的，现在low的位置空出来，
        //下一次外层while循环的low位置是空出来的
    }//while(low<high)

    A[low] = pivot;//最终将初始枢轴位置存放，最后一次外层循环时low的位置是空出来的，刚好用来存放pivot的值
    return low;//返回下一次枢轴位置
}



void QuickSort(int A[],int low,int high)
{
    //递归调用
    if(low<high)
    {
        int pivot = Partition(A,low,high);//得到本次枢轴的值，向下继续递归传递
        QuickSort(A,low,pivot-1);
        QuickSort(A,pivot+1,high);
    }
}