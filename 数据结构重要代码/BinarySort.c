//折半查找
//采用二分查找的方法进行插入
//时间复杂度:查找插入位置O(nLogn)，移动关键字O(n^2)，所以总共还是

int BinarySort(int a[] , int len)
{
    int i,j,low,heigh,mid;
    for(i = 2;i<len||i ==len;i++)//从第二个元素开始比较，默认0号位置放置带插入元素，1号位置元素已经排序完成
    {
        a[0] = a[i];//将带插入元素放置到0号位置
        //确定查找位置为1->i-1
        low = 1;
        heigh = i-1;
        while (low>heigh ||low==heigh)//找到待插入位置，最后为heigh+1
        {
            mid = (heigh + low)/2;
            if(a[0]>a[mid])
                low = mid+1;
            else
            {
                heigh = mid -1;
            }            
        }

        //将heigh位置以后的元素均向后移动一位，腾出位置插入待插入元素
        for(j = i;j>heigh+1;j--)
        {
            a[j] = a[j-1];
        }
        a[heigh+1] = a[0];//插入a[i]
        
    }
}