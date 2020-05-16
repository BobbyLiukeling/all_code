package text3;
import java.util.Scanner;
/**
* Filename:
* title:
* @date 创建时间：2018年3月19日 下午6:11:57 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
* demand:在屏幕上显示一个由星型符号“*”组成的金字塔图案，要求用户设置金字塔的高度，程序能根据用户设置的高度打印金字塔，
* 
*/
public class Pyramid {
	public static Scanner sc = new Scanner(System.in);
	public void print(int hight) {
		for(int i=hight;i>0;i--)
		{
			for(int j=0;j<i;j++)
			{
				System.out.print(" ");
			}
			for(int j=2*(hight-i)+1;j>0;j--)
			{
				System.out.print("*");
			}	
			System.out.println();
		}
	}
	public static void main(String[] args) {
		System.out.println("请输入金字塔的高度");
		int hight = sc.nextInt();
		Pyramid pyramid = new Pyramid();
		pyramid.print(hight);
		System.out.println("打印完毕");
	}

}
