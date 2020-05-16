package collection;
import java.util.*;
import java.util.Map.Entry;



/**
* Filename:
* title:MapTest
* @date 创建时间：2017年12月26日 下午1:24:56 
* @version 1.0 
* @parameter  
* Description: hashmap
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/



public class MapTest {
	/**
	 * 用来承装学生类型对象
	 */
	public Map<String, Student>students;
	
	/**
	 * 在构造器中初始化student属性
	 */
	public MapTest()
	{
		this.students=new HashMap<String,Student>();
	}
	
	/**
	 * 向map中添加信息
	 * 输入学生id，判断是否被占用，若为被占用，则输入学生姓名，创建新的对象，并且添加到map中
	 */
	public void testPut() {
		//创建一个scanner对象
		Scanner console=new Scanner(System.in);
		int i=0;
		while (i<3) {
			System.out.println("请输入学生ID");
			String ID =console.next();
			//判断ID是否被占用
			Student st = students.get(ID);
			if (st==null) {
				//提示输入学生姓名
				System.out.println("请输入学生姓名");
				String name=console.next();
				//创建现在对象
				Student newstudent=new Student(ID, name);
				//通过调用put对象向map中添加新增的数据
				students.put(ID, newstudent);
				System.out.println("成功添加学生"+students.get(ID).name);
				i++;
			}
			else {
				System.out.println("该学生ID已被占用");
				continue;
			}
			
		}
	}
	
	/**
	 * 测试map的可以set方法
	 */
	public void testKeySet() {
		//同keyset方法返map中所有键的集合
		Set<String> keySet=students.keySet();
		//遍历keyset对象来取得map 中的每一个键，在通过get方法取得每一个键所对应的的值
		for(String string:keySet)
		{
			Student st =students.get(string);
			if (st!=null) {
				System.out.println("学生："+st.name);
			}
		}
	}
	
	/**
	 * 删除映射
	 */
	public void testRemove() {
		Scanner scanner=new Scanner(System.in);
		while(true)
		{
			System.out.println("请输入要删除的学生的ID");
			//从键盘获取id
			
			String ID=scanner.next();
			//判断是否有次学生对象
			Student student=students.get(ID);
			if (student==null) {
				System.out.println("该学生不存在");
				continue;
			}
			students.remove(ID);
			System.out.println("成功删除此学生");
			break;
		}				
	}
	
	/**
	 * 通过entrySet方法遍历Map
	 */
	public void testEntrySet() {
		//通过entrySet返回map键值对
		Set<Entry<String,Student>> entrySet=students.entrySet();
		for(Entry<String,Student> entry:entrySet)
		{
			System.out.println("取得键"+entry.getKey());
			System.out.println("对应的值为"+entry.getValue().name);
		}
	}
	
	/**
	 * 修改内容
	 */
	public void testModify() {
		//提示输入要修改的id
		System.out.println("请输入要修改的学生的id");
		Scanner scanner=new Scanner(System.in);
		while (true){
			//从键盘获取id
			String id=scanner.next();
			//查找id
			Student student=students.get(id);
			if(student==null)
			{
				System.out.println("该用户不存在,亲重新输入");
				continue;
			}
			//提示当前要修改的学生姓名是什么
			System.out.println("当前要修改的学生的id："+student.name);
			//提示输入新的学生姓名
			System.out.println("请输入新的学生姓名");
			String name=scanner.next();
			Student newstudent=new Student(id, name);
			students.put(id, newstudent);
			System.out.println("修改成功");
			break;
		}
	}
	
	
	
	
	
	/**
	 * main
	 */
	public static void main(String[] args) {
		MapTest mapTest=new MapTest();
		System.out.println("开始！！");
		mapTest.testPut();
		mapTest.testKeySet();
		mapTest.testRemove();
		mapTest.testEntrySet();
		mapTest.testModify();
		mapTest.testPut();
		
	}
	
}

















