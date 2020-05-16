package collection;
import java.util.*;
/**
* Filename:
* title:Student
* @date 创建时间：2017年12月25日 下午9:04:12 
* @version 1.0 
* @parameter  set hashSet
* Description: 学生类
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/
public class Student {
	public String id;
	public String name;
	public Set<Course> courses;
	
	public Student(String id,String name) {
		this.id=id;
		this.name=name;
		this.courses=new HashSet<Course>();
	}
}
