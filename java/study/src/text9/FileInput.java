package text9;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;  
import java.io.FileNotFoundException;  
import java.io.IOException;
import java.net.URL; 
/**
* Filename:
* title:
* @date 创建时间：2018年4月18日 上午9:10:32 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
* demand:
* 4.  编写一个 Java 应用程序，该程序使用 FileInputStream类，实现从磁盘读取本应用程序源代码文件，并将文件内容显示在屏幕上。
*/
public class FileInput {

	public static void main(String[] args) { 
//		URL string =ClassLoader.getSystemResource("") ;
//		System.out.println(string);
		String s= "System.getPr";
		System.out.println(s.lastIndexOf('s'));
		System.out.println(s.substring(1,3));
//		
//		String path = System.getProperty("user.dir");//当前文件绝对路径
//		String Javapath=path+"\\src\\text2\\alphabet.java";
//        //创建字节数组  
//        byte[] buf = new byte[2056];  
//          
//        try {  
//            FileInputStream fileInputStream = new FileInputStream(Javapath);            
//            int bytes = fileInputStream.read(buf, 0, 2056);               
//            String str = new String(buf, 0, bytes);  
//            System.out.println(str);  
//        } catch (Exception e) {  
//            e.printStackTrace();  
//        }  
    } //main 结束
}
