package text5;
/**
* Filename:
* title:
* @date 创建时间：2018年3月25日 上午10:24:59 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
* demand:编写一个 Java 应用程序，判断两个字符串是否相同，判断字符串的前缀、后缀是否和某个字符串相
* 同，按字典顺序比较两个字符串的大小关系，检索字符串，创建字符串，将数字型字符串转换为数字，将字符
* 串存放到数组中，用字符数组创建字符串
*/

import javax.print.attribute.standard.MediaName;

import java.awt.Window.Type;
import java.util.Scanner;

public class ConvertString {
	public static void main(String[] args) {
		System.out.println("比较两个字符串是否相同");
		String s1=new String("you are a student");
		String s2=new String("how are you");
		if(s1.equals(s2)) // 使用 equals 方法判断 s1 与 s2 是否相同
		 {
			System.out.println(s1+"和"+s2+"  s1 与 s2 相同");
		 }
		 {
			System.out.println(s1+"和 "+s2+"  s1 与 s2 不相同");
		 }
		
		System.out.println();
		String s3=new String("22030219851022024");
		System.out.println("判断字符串前缀，字符串为： "+s3);
		 
		 if(s3.startsWith("220302")) //判断 s3 的前缀是否是“220302”。
		 {
		 System.out.println("吉林省的身份证");
		 }
		 
		 System.out.println();
		 String s4=new String("你"),
		 s5=new String("我");
		 System.out.println("字符串为："+s4+"  和     "+s5);
		 if(s4.compareTo(s5)>0)//按着字典序 s4 大于 s5 的表达式。compareto 返回的是数值
		 {
		 System.out.println("按字典序 s4 大于 s5");
		 }
		 else
		 {
		 System.out.println("按字典序 s4 小于 s5");
		 }		 
		 
		 System.out.println();
		 String path="c:\\java\\jsp\\A.java";
		 System.out.println("判断字符串位置，及截取字符串，原字符串为：  "+path);
		 int position=0;		 
		 position=path.lastIndexOf("\\");  //获取 path 中最后出现目录分隔符号的位置
		 System.out.println("c:\\java\\jsp\\A.java 中最后出现\\的位置: "+position);
		 
		 String fileName=path.substring(position+1);//获取 path 中“A.java”子字符串。
		 System.out.println("c:\\java\\jsp\\A.java 中含有的文件名:"+fileName);
		 
		 System.out.println();
		 String s6=new String("100"),
		 s7=new String("123.678");
		 System.out.println("将字符串转换为数值，原字符串为： "+s7);		 
		 int n1=Integer.parseInt(s6);  //将 s6 转化成 int 型数据。
		 double n2=Double.parseDouble(s7); //将 s7 转化成 double 型数据。
		 double m=n1+n2;
		 System.out.println(m);
		 
		 System.out.println();
		 System.out.println("将数值转换为字符串");
		 String s8=""+m; //String 调用 valuOf(int n)方法将 m 转化为字符串对象		 
		 position=s8.indexOf(".");
		 String temp=s8.substring(position+1);
		 System.out.println("数字"+m+"有"+temp.length()+"位小数") ;
		 
		 System.out.println();
		 String s9=new String("ABCDEF");
		 System.out.println("字符串放进字符数组: "+s9);		 
		 char a[]= s9.toCharArray(); //将 s9 存放到数组 a 中。
		 for(int i=a.length-1;i>=0;i--)
		 {
		 System.out.print(" "+a[i]);
		 }		 		
	}
}
