package text2;
import java.util.Random;
import java.util.Scanner;

/**
* Filename:
* title:
* @date 创建时间：2018年3月19日 下午5:09:50 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
* demand:程序随机分配给客户一个 1—100 之间的整数，用户在输入对话框中输入自己的猜测。程序
返回提示信息，提示信息分别是：“猜大了”、“猜小了”和“猜对了”。用户可根据提示
信息再次输入猜测，直到提示信息是“猜对了”。
*/
public class rand {
	public static Scanner sc = new Scanner(System.in);
	public String guss(int a) {
		String s = " ";
		
		while(true)
		{
			System.out.println("请输入一个数");
			int n=sc.nextInt();
			if(n>a)
			{
				return "猜大了";
			}
			else 
			{
				if(n==a)
			{
				return "猜中了";
			}
				else
				{
					return "猜小了";
				}
			}
		}
		
	} 
	public static void main(String[] args) {
		Random random = new Random();
		int a=random.nextInt(100);
		rand r = new rand();
		while (true) {
			System.out.println(r.guss(a));
			System.out.println("是否继续输入，继续输入请按1 ，否则按任意键退出");
			int key=sc.nextInt();
			if (key!=1) {
				System.out.println("猜数结束");
				break;
			}
		}			
	}
}


