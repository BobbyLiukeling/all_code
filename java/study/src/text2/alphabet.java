package text2;
import java.lang.String;
/**
* Filename:
* title:
* @date 创建时间：2018年3月19日 下午4:05:52 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
* demand:编写一个 Java 应用程序，该程序在命令行窗口输出大小写英文字母表。
* ascii:A-Z 65-90  a-z:97-122
*/
public class alphabet {
	public static void main(String[] args) {
		System.out.println("打印大写字母");
		for(int i=65;i<91;i++)
		{
			char t=(char)i;
			System.out.print(t);
			System.out.print(" ");
		}
		
		System.out.println("打印小写字母");
		for(int i=97;i<123;i++)
		{
			char t=(char)i;
			System.out.print(t);
			System.out.print(" ");
		}	
				
		System.out.println("打印完毕");
		
	}
}
