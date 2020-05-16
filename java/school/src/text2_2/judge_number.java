package text2_2;
import java.util.Scanner;
import java.lang.String;
/**
* Filename:
* title:
* @date 创建时间：2018年3月19日 下午4:17:59 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
* demand:编写一个 Java 应用程序。用户从键盘输入一个 1—9999 之间的数，程序将判断这个数是几位数，
* 并判断这个数是否是回文数。 回文数是指将该数含有的数字逆序排列后得到的数和原数相同，
*例如 12121、3223 都是回文数。
* int n = sc.nextInt();
*/
public class judge_number {
	
	public int limit(int n) {
		//限制输入为1-9999
		if (n%10000!=0)	
		{
			n=n%10000;
		}
		else {
			n=1;
		}		
		return n;
	}
	
	public int digit(int n) {
		//判断位数
		int count = 1;
		if(n>99)
		{
			if(n>999)
			{
				count=4;
			}
			else {
				count=3;
			}
		}
		else {
			if(n>9)
			{
				count=2;
			}
			else {
				count=1;
			}
		}
		return count;
	}
	
	public String reverse1(int n)

	{
	   String str=""+n;
	   return new StringBuffer(str).reverse().toString();
	}
	
	public boolean plalindrome(String str,int n) {
		String s=""+n;
		if(str.equals(s))
			{
				return true;
			}
			
		else {
			return false;
		}
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		judge_number judge=new judge_number();
		System.out.println("请输入一个数");
		int n=sc.nextInt();
		n=judge.limit(n);//限制输入的数为1-9999
		int count=judge.digit(n);//判断几位数
		System.out.println("n是"+count+"位数");
		String str =judge.reverse1(n);
		boolean plalindrome =judge.plalindrome(str,n);//判断是否为回文
		if(plalindrome==true)
		{
			System.out.println("是回文");
		}
		else {
			System.out.println("不是回文");
		}
		
	}
}
