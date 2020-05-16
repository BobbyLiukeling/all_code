package collection;
import java.util.*;
/**
* Filename:
* title:SteTest
* @date 创建时间：2017年12月26日 上午11:44:31 
* @version 1.0 
* @parameter set 
* Description: set 的练习
* 说明：set中的元素是不会重复的，且可以添加空对象 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/


 

public class SetTest {
	public List<Course> coursesToSelect;
	public SetTest() {
		coursesToSelect =new ArrayList<Course>();
	}
	
	/**
	 * add
	 */
	public void testADD() {
		/**
		 *创建一个course对象，并用add方法添加到备选课程的list中
		 */
		Course cr1=new Course("1", "数据结构");
		coursesToSelect.add(cr1);
		System.out.println("添加了课程");
		Course temp1=(Course)coursesToSelect.get(0);
		System.out.println("添加了课程"+ temp1.id+":"+temp1.name);
		Course cr2=new Course("2", "C++");
		coursesToSelect.add(0,cr2);
		Course temp2=(Course)coursesToSelect.get(0);
		System.out.println("添加了课程"+temp2.id+":"+temp2.name);
		
		/**
		 * 第二种添加方法
		 */
		Course[] courses =
			{new Course("3", "离散数学"),new Course("4", "汇编语言")	};
		coursesToSelect.addAll(Arrays.asList(courses));
		Course temp3=(Course)coursesToSelect.get(2);
		Course temp4=(Course)coursesToSelect.get(3);
		System.out.println("添加的两门课程"+temp3.id+":"+temp3.name+" ;  "+temp4.id+":"+temp4.name);
		
		/**
		 * 第三种添加方法
		 */
		Course[] courses2=
			{new Course("5", "Math"),new Course("6", "English")};
		coursesToSelect.addAll(2,Arrays.asList(courses2));
		Course temp5=(Course)coursesToSelect.get(2);
		Course temp6=(Course)coursesToSelect.get(3);
		System.out.println("添加了两门课程"+temp5.id+":"+temp5.name+"  ;  "+temp6.id+":"+temp6.name);
	}	
	

	/**
	 * for each 方法遍历
	 */
	public void testForeach() {
		for(Object obj:coursesToSelect)
		{
			Course cr=(Course)obj;
			System.err.println("课程"+cr.id+":"+cr.name);
		}
	}	
	
	/**
	 * list 的contains 方法
	 * @param args
	 */
	public void testListcontains() {
		//取得备选课程的第0 个元素
		Course course = coursesToSelect.get(0);
		//打印输出coursesToSelect是否包含course
		System.out.println("取得课程："+course.name);
		System.out.println("备选课程是否包含课程:"+course.name+","+coursesToSelect.contains(course));
	}
	
	

	
	public static void main(String[] args) {
		SetTest sT=new SetTest();
		sT.testADD();
		sT.testListcontains();
//		sT.testForeach();
//		//创建一个学生对象
//		Student student=new Student("1", "小明");
//		System.out.println("欢迎学生："+student.id+":"+student.name+"选课");
//		//创建一个学生对象，并从键盘输入
//		Scanner scanner=new Scanner(System.in);
//		for(int i=0;i<3;i++)
//		{
//			System.out.println("请输入课程id");
//			String courseId=scanner.next();
//			for (Course cr:sT.coursesToSelect) {
//				if (cr.id.equals(courseId)) {
//					student.courses.add(cr);
//				}
//			}
//			for(Course course : student.courses)
//			{
//				System.out.println("选择了课程："+course.id+":"+course.name);
//			}
//		}
		
	}	
	
}




















