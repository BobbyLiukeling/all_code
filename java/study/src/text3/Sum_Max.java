package text3;

import javax.crypto.interfaces.PBEKey;

/**
* Filename:
* title:
* @date 创建时间：2018年3月19日 下午6:35:02 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
* demand:
* 1. 编写一个 Java 程序，声明一个数组，各元素如：{12, 23, 456, 222, 768, 93245}计算出所有元素的和：SumArray.java
* 2. 编写一个 Java 程序，声明一个数组，各元素如：{12, 23, 456, 222, 768, 93245}打印出各元素的值，并打印出最大元素的值:MaxArray.java
*/
public class Sum_Max {
	public int sum(int[] arr) {
		int s=0;
		for(int i:arr)
		{
			s+=i;
		}
		return s;
	}
	
	public void print(int[] arr)
	{
		System.out.println("数组中的元素为：");
		for(int i:arr)
		{
			System.out.print(i);
			System.out.print(" ");
		}
	}
	
	public int max(int[] arr) {
		int max_number=0;
		for(int i:arr)
		{
			if(max_number<i)
			{
				max_number=i;
			}
		}
		return max_number;
	}
	public static void main(String[] args) {
		Sum_Max sm=new Sum_Max();
		int[] arr ={12, 23, 456, 222, 768, 93245};
		System.out.print("数组总的值为：");
		System.out.println(sm.sum(arr));
		sm.print(arr);
		System.out.println();
		System.out.println("数组中最大的数为：");
		System.out.println(sm.max(arr));
		
		
	}
}
