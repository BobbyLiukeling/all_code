package collection;
import java.util.*;

/**
* Filename:
* title:ListTest
* @date 创建时间：2017年12月25日 下午9:08:25 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/

/**
 * 备选课程
 * @author x1c
 *
 */
public class ListTest {
	/**
	 * 用于存放备选课程的list
	 */
	public List coursesToSelect;//备选课程
	
	public ListTest() {
		// TODO Auto-generated constructor stub
		this.coursesToSelect=new ArrayList();
	}
	
	/**
		 * 用于往courseToSelect中添加课程
		 */
	public void testADD() {
		/**
		 *创建一个course对象，并用add方法添加到备选课程的list中
		 */
		Course cr1=new Course("1", "数据结构");
		coursesToSelect.add(cr1);
		System.out.println("添加了课程");
		Course temp1=(Course)coursesToSelect.get(0);//转换为Course类型
		System.out.println("添加了课程"+ temp1.id+":"+temp1.name);//从Course类型输出
		Course cr2=new Course("2", "C++");
		coursesToSelect.add(0,cr2);//数据结构将被往下顺移
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
		
		/**
		 * 添加重复课程
		 */
		Course cr3=new Course("1", "数据结构");
		coursesToSelect.add(cr3);
		System.out.println("添加了课程");
		Course temp7=(Course)coursesToSelect.get(6);
		System.out.println("添加了课程"+ temp1.id+":"+temp1.name);
		Course cr4=new Course("2", "C++");
		coursesToSelect.add(6,cr4);
		Course temp8=(Course)coursesToSelect.get(5);
		System.out.println("添加了课程"+temp2.id+":"+temp2.name);
		
	}
	
	/**
	 * 取得list中的值
	 */
	public void testget() {
		int size=coursesToSelect.size();
		for (int i = 0; i < size; i++) {
			Course cr=(Course)coursesToSelect.get(i);
			System.out.println("课程"+cr.id+":"+cr.name);
		}
	}
	/**
	 * 通过迭代器遍历list
	 */
	public void testIterator() {
		Iterator it=coursesToSelect.iterator();
		while (it.hasNext()) {
			Course	cr=(Course) it.next();
			System.out.println("课程："+cr.id+":"+cr.name);
		}
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
	 * 修改list中元素
	 */
	public void testModfy(int Index,Course cr) {
		coursesToSelect.set(Index, cr);
	}
	
	/**
	 * 删除list中的元素
	 */
	public void testRemove(int index) {
		coursesToSelect.remove(index);
	}
	
	/**
	 * main
	 */
	public static void main(String[] args) {
		ListTest iT= new ListTest();
		iT.testADD();
		System.out.println();
		System.out.println("有如下课程待选");
		iT.testget();
		System.out.println();
		System.out.println("迭代器");
		iT.testIterator();
		System.out.println();
		System.out.println("Foreach 遍历");
		iT.testForeach();
		System.out.println();
		System.out.println("修改元素");
		//Course c=new Course("7", "毛概");
		iT.testModfy(6,new Course("7", "毛概"));
		iT.testIterator();
		System.out.println();
		int key;
		Scanner s= new Scanner(System.in);
		System.out.println("请输入需要删除的位置");
		key=s.nextInt()-1;
		iT.testRemove(key);
		System.out.println("删除了位置 "+(key+1)+" 的值后的list");
		iT.testForeach();
	}
	
}















