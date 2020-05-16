package text9;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.Scanner;

/**
 * Filename: title:
 * 
 * @date 创建时间：2018年4月17日 下午9:20:31
 * @version 1.0
 * @parameter Description:
 * @author Liu Keling 作者 E-mail: 1194380923@qq.com 
 * demand: 2.用对象序列化把若干 Student 对象写到文件中,再读取出来
 */
public class Manage_student {
	public static void main(String[] args) throws Exception {
System.out.println("********************************");
		File file = new File("student.txt");
		ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(file));
		ObjectInputStream in = new ObjectInputStream(new FileInputStream(file));
		Student student = new Student("张三", 23, "111");
		// 序列化持久化对象
		try {		
		out.writeObject(student);
		out.close();
		
		// 反序列化，并得到对象
		
		Object newStudent = in.readObject(); // 没有强制转换到Person类型
		in.close();
		System.out.println(newStudent);}
		catch (FileNotFoundException e) {  
            e.printStackTrace();  
            System.out.println("fail");
        } catch (IOException e) {  
            e.printStackTrace();
            System.out.println("失败");
        }
		

	}
}
