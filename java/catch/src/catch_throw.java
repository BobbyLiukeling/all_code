
import java.util.Calendar;

/**
* Filename:catch
* title:catch_throw
* @date 创建时间：2017年12月25日 下午3:14:58 
* @version 1.0 
* @parameter  
* Description:捕获异常和实现自己的异常类 
* 在进行程序开发的过程中，自定义异常遵循以下四个步骤：
　　1）首先创建自定义异常类，语法格式：自定义异常类名 extends Exception。
　　2）在方法中通过关键字throw抛出异常对象。
　　3）若是在当前抛出异常的方法中处理异常，可以用try-catch语句捕获并处理；若不是，在方法的声明处通过关键字throws指明要抛出给方法调用的异常。
   4）在出现异常方法的调用中捕获并处理异常。
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/

class catchthrow extends Exception//定义异常类
{
	public catchthrow() {
		
	}
	
	public catchthrow(String msg) {
		super(msg);
	}
	
	public catchthrow(String msg,int x) {
		super(msg);
		i=x;
	}
	
	public int val() {
		return i;
	}
	private int i;
}

/**
 * 使用类
 */
public class catch_throw {
/**
 *<br>方法说明：使用MyException类中默认的构造器
 *<br>输入参数：
 *<br>返回类型：
 */
  public static void a() throws catchthrow 
  {
    System.out.println("Throwing catchthrow from a()");
    throw new catchthrow();
  }
  
  /**
   * 使用带信息的构造器
   */
	public static void b() throws catchthrow{
		System.out.println("Throwing catchthrow from b()");
		throw new catchthrow("b()");
	}
  
  /**
   * 使用有编码的构造器
   */
  public static void c() throws catchthrow {
	System.err.println("Throwing catchthrow from c()");
	throw new catchthrow("c()  " ,47);
}  
  
  /**
   * main
   */
  public static void main(String[] args) {
	try {
		a();
	}catch (catchthrow e) {
		// TODO: handle exception
		e.getMessage();
	}
	try {
		b();
		
	}catch (catchthrow e) {
		// TODO: handle exception
		e.toString();
	}
	try {
		c();
	} catch (catchthrow e) {
		// TODO: handle exception
		e.printStackTrace();
		System.out.println("error code:"+e.val());
	}
	Calendar t=Calendar.getInstance();
	System.out.println(t);
}  
}











