package indentifier;
/**
* Filename:indentifier
* title:indentifier
* @date 创建时间：2017年12月25日 下午2:49:23 
* @version 1.0 
* @parameter  private public protect
* Description: 标识符
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/
public class indentifier {
	/**
	 * 公有类
	 */
	public void mechod1() {
		System.out.println("这是一个公有的了，任何类都可以访问");
	}
	
	/**
	 * 受保护的类	
	 */
	private void mechod2() {
		System.out.println("这是一个受保护的类，只有子类可以访问他");
	}
	
	/**
	 * 私有
	 */
	private void mechod3() {
		System.out.println("这是一个私有的方法，只有类本身可以访问");
	}
	
	public static void main(String[] args) {
		indentifier I=new indentifier();
		I.mechod1();
		I.mechod2();
		I.mechod3();
	}	
	
}
