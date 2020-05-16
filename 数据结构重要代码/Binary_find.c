//二分查找，只在有序的孙旭表中进行
int Binary_find(SqList List,int key)
{
    int low = 0, height = List.lenght-1,mid;
    while(low<height||low==height)//注意判断条件
    {
        mid = (low+height)/2;
        if(List[mid] == key)
            return mid;//找到！
        else if (List[mid]<key)
        {
            low = mid + 1;
        }
        else
        {
            height = mid - 1;
        }   
        
    }
    return -1;//没找到
}