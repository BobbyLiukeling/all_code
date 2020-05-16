package base;

import java.sql.Date;
import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

import javax.xml.stream.events.StartDocument;



/**
* Filename:1-1
* title:test
* @date 创建时间：2017年12月28日 上午9:51:53 
* @version 1.0 
* @parameter  
* Description: 课后练习
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/
public class test {
	public int lg(int n) {
		int key=1;
		int i=n/2;
		while(i>1)
		{
			key++;
			n=i;
			i=n/2;
		}
		return key;
	}
	
	public static void A(int[] a,int key) {//1.1.15
		
		for (int i = 0; i < a.length; i++) {
			a[i]=(int)(Math.random()*key);
		}
		Arrays.sort(a);
		int[] b=new int[key];
		int j=0;
		int i=0;
		
		//判断a[0]是不是从0 开始的
		int l=a[0]-0;
		if (l>0) 
		{
			for(;i<a[0];i++)
				{
					b[i]=0;
				}
		}
		
		for (i = a[0]; i < b.length; i++) 
		{
			
				int number=1;
				while(a[j]==a[j+1]&&(j-1)<a.length)
				{				
						number++;
						j++;				
				}
				b[i]=number;
				j++;
				int k=a[j]-a[j-1];
				if (k>1) {//中间没有的数b[i]都置为0
					
					for(int p=i+1;p<i+k;p++)
					{
						b[p]=0;
					}
					i=i+k-1;
				}
				if (j==a.length-1||(i+1)==b.length) {//a中元素加完了，但是b数组后面还没加
					b[a[j]]=1;
					break;
				}
				
				
		}
		int nu=0;
		int count=0;
		for(Object o:b)
		{ 
			
			System.out.println("数字 "+nu+" 的数目:"+o);
			nu++;
			count+=(int)o;
		}
		System.out.println("count:"+count);
		
	}
	
	
	public static void a1(int[] a,int key) {//1.1.15
		for (int i = 0; i < a.length; i++) {
			a[i]=(int)(Math.random()*key);
		}
		Arrays.sort(a);
		int[] b=new int[key];
		for(int i=0;i<a.length-1;i++)
		{			
				b[a[i]]++;			
			if(a[i]==a[i+1]) {
				b[a[i]]++;
				i++;
			}
			
			
		}
		if (a[a.length-1]!=a[a.length-2]) {
			b[a[a.length-1]]=1;
		}
		int nu=0;
		int count=0;
		for(Object o:a)
		{
			System.out.println(o);
		}
		for(Object o:b)
		{ 
			
			System.out.println("数字 "+nu+" 的数目:"+o);
			nu++;
			count+=(int)o;
		}
		System.out.println("count:"+count);
	}
	
	public static void a2(int[] a,int key) {//1.1.15
		for (int i = 0; i < a.length; i++) {
			a[i]=(int)(Math.random()*key);
		}
		Arrays.sort(a);
		int[] b=new int[key];
		
		for(int i=0;i<a.length-1;i++)
		{		
			if( (i!=0&&a[i]!=a[i-1])||i==0) {
				b[a[i]]=1;
			}			
			int j=i;
			for (; a[j]==a[j+1]; j++) 
			{
				b[a[j]]++;
			}
			if (j!=i) {
				i=j-1;
			}			
		}	
		if (a[a.length-1]!=a[a.length-2]) {
			b[a[a.length-1]]=1;
		}
		int nu=0;
		int count=0;
		
		for(Object o:b)
		{ 
			
			System.out.println("数字 "+nu+" 的数目:"+o);
			nu++;
			count+=(int)o;
		}
		System.out.println("count:"+count);
	}
	
	public static void a3(int[] a,int key) {//1.1.15
		for (int i = 0; i < a.length; i++) {
			a[i]=(int)(Math.random()*key);
		}
		Arrays.sort(a);
		int[] b=new int[key];
		int k=0;
		for (int i = 0; i < b.length; i++) {
			int count=0;
			while (k < a.length) {
				if (a[k]==i) {
					count++;
					k++;
					continue;
				}
				else
					break;
			}			
			b[i]=count;
		}
		
		int nu=0;
		int count=0;
		
		for(Object o:b)
		{ 			
			System.out.println("数字 "+nu+" 的数目:"+o);
			nu++;
			count+=(int)o;
		}
		System.out.println("count:"+count);
	}
	
	public static String exrl(int n) {//1.1.16
		if (n<0||n==0) 
			return " ";
		return exrl(n-3)+n+exrl(n-2)+n;
		
	}
	
	
	public static int mystery(int a,int b) {
		if (b==0) 
			return 0;
		if (b%2==0) {
			return mystery(a+a, b/2);
		}
		return mystery(a+a, b/2)+a;
		
	}
	
	public static String mystery(String string) {
		int n=string.length();
		if (n==1||n<1) {
			return string;
		}
		String a=string.substring(0,n/2);
		String b=string.substring(n/2,n);
		return mystery(b)+mystery(a);
	}
	
		public static void main(String[] args) {
//			double t=2.0e-6*1000000000.1;
//			System.out.println(t);
//			System.out.println(('a'+4));
//			int k=23;
//			System.out.println(Integer.toBinaryString(k));
			
//			//返回不大于以二为底的最大整数
//			int a;
//			int p;
//			Scanner scanner=new Scanner(System.in);
//			System.out.println("请输入需要判断的数p");
//			p=scanner.nextInt();
//			test T=new test();
//			a=T.lg(p);
//			System.out.println("对数p："+p+"的指数a为"+a);
			
			//int []a=new int [100];
		   //A(a, 10);
			//a1(a, 10);
			//a2(a, 10);
			//a3(a, 10);//这个最有用最简单，最不会出错
			
			//System.out.println(exrl(6));
			
			//System.out.println(mystery(5, 6));
			
//			int d=Integer.parseInt(args[0]);
//			int m=Integer.parseInt(args[1]);
//			int y=Integer.parseInt(args[2]);
//			Date date=new Date (d,m,y);
//			System.out.println("日期是："+date);
			
			System.out.println(mystery("123456"));
	
					
		}
}



