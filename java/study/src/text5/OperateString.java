package text5;
/**
* Filename:
* title:
* @date 创建时间：2018年3月26日 下午5:08:12 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
* demand:编写 Java 程序，返回一个路径中的文件名，文件类型，文件所在目录，例如一个路径为 E:\eclipse\plugins\com.jcraft.jsch_0.1.28.jar，
* 则应返回其文件名为：com.jcraft.jsch_0.1.28，文件类型为：jar，文件所在目录为：E:\eclipse\plugins。
*/

import java.util.Scanner;

import javax.crypto.interfaces.PBEKey;

public class OperateString {
	public void getFile(String path) {
		int position1 = path.lastIndexOf("\\");
		String file = path.substring(position1+1);		
		int position2 = file.lastIndexOf(".");
		String file_type = file.substring(position2+1);
		String file_name = file.replaceAll(file_type,"");
		System.out.println("文件名为：  "+file_name);
		System.out.println("文件类型为： "+ file_type);
		String file_path = path.replace(file,"");
		System.out.println("文件路径为： "+file_path);
	}
	
	public void formate_string(int substr_len,String str) {
		int len=str.length();
		int c =len%substr_len==0?len/substr_len:len/substr_len+1;
		int k=1;
		for(int i=0;i<c;i++)
		{
			if(i!=c-1)
			{
				System.out.println("第 "+k+"次输出"+str.substring(i*(substr_len), (i+1)*substr_len));
			}
			else
				System.out.println("第 "+k+"次输出"+str.substring(i*(substr_len)));
			k++;
		}		
	}
	
	public static void main(String[] args) {
		String path="E:\\eclipse\\plugins\\com.jcraft.jsch_0.1.28.jar";
		OperateString operateString = new OperateString();
		operateString.getFile(path);
		Scanner scanner=new Scanner(System.in);		
		System.out.println("原字符串为： "+path);
		System.out.println("请输入每次需要输出的字符串长度");
		int len = scanner.nextInt();
		operateString.formate_string(len, path);
		
	}
}
