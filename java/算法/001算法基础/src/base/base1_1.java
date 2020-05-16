package base;
/**
* Filename:001base
* title:base1_1
* @date 创建时间：2017年12月27日 下午8:51:25 
* @version 1.0 
* @parameter  
* Description: 返回两个是的最大公约数
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/
public class base1_1 {
	
	public static int  gcd(int p,int q) {
		if (q==0) {
			return p;		
		}
		int i=p%q;
		return gcd(q,i);
	}
	public static void main(String[] args) {
		base1_1 b=new base1_1();
		int k=b.gcd(42, 36);
		System.out.println("输出最大公约数"+k);
	}
}
