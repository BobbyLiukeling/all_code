package base;

import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;



/**
* Filename:
* title:binary_search
* @date 创建时间：2017年12月27日 下午9:20:18 
* @version 1.0 
* @parameter  
* Description: 二分查找
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/


public class binary_search {
	public static int rank(int key,int[] a)
	{
		//数组必须是有序的
		int lo=0;
		int hi=a.length-1;
		while(lo<=hi)
			{
				//被查找的数要么不存在，要么存在a[lo-hi]之间
				int mid=lo+(hi-lo)/2;
				if (key<a[mid]) {
					hi=mid-1;
				}
				else if (key>a[mid]) {
					lo=mid+1;
				}
				else {
					return mid;
					
				}
			}
		return -1;//没有找到
	}
	
	public static void main(String[] args) {
		int[] a=new int[10];
		for(int i=0;i<10;i++)
		{
			a[i]=(int)(Math.random()*100);//math.random所产生的随机数是在0-1之间的双精度数
			System.out.println(a[i]);
		}	
		Arrays.sort(a);//要排序后才能进行二分查找
		System.out.println("请输入要查找的数，退出请按1！");
		Scanner scanner=new Scanner(System.in);
		int key=scanner.nextInt();	
		
		while (key!=1) {
			int t=rank(key, a);
			if (t!=-1) {
				System.out.println("要查找的数是："+key+"  且已找到");
			}
			else
				System.out.println("要查找的数："+key+"没有找到");
			System.out.println("请输入要查找的数，退出请按1！");
			key=scanner.nextInt();
		}
		
	}
}















