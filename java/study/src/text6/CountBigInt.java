package text6;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Scanner;
/**
* Filename:
* title:
* @date 创建时间：2018年3月26日 下午7:24:28 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
* demand:计算两个大整数的和、差、积和商，并计算一个大整数的因子个数（因子中不包括 1 和大整数本身）。

*/
public class CountBigInt {
	public void comput(BigInteger n1,BigInteger n2) {
		 BigInteger result=null;
		 System.out.println("参与计算的两个数为：");
		 System.out.println("n1:  "+n1);
		 System.out.println("n2:  "+n2);
		 result=n1.add(n2);//n1 和 n2 做加法运算
		 System.out.println("和:"+result.toString());
		 result=n1.subtract(n2);//n1 和 n2 做减法运算
		 System.out.println("差:"+result.toString());
		 result=n1.multiply(n2);//n1 和 n2 做乘法运算
		 System.out.println("积:"+result.toString());
		 result=n1.divide(n2);//n1 和 n2 做除法运算
		 System.out.println("商:"+result.toString());
	}
	
	public void get_divisor(BigInteger m) {
		BigInteger COUNT=new BigInteger("0"),
				 ONE=new BigInteger("1"),
				 TWO=new BigInteger("2");
		System.out.println(m.toString()+"的因子有:");
		 for(BigInteger i=TWO;i.compareTo(m)<0;i=i.add(ONE))
		 { 
			 if((m.remainder(i).compareTo(BigInteger.ZERO))==0)//remainder求余
			 { 
				 COUNT=COUNT.add(ONE);
				 System.out.print(" "+i.toString());
			 }
		 }
		System.out.println("");
		System.out.println(m.toString()+"一共有"+COUNT.toString()+"个因子");				 
	}
	
	public static void main(String args[]){
		CountBigInt bigInt = new CountBigInt();
		BigInteger n1=new BigInteger("987654321987654321987654321");
		BigInteger n2=new BigInteger("123456789123456789123456789");
		bigInt.comput(n1, n2);
		 
		BigInteger m=new BigInteger("1968957");
		bigInt.get_divisor(m);
		
		
	}

}
