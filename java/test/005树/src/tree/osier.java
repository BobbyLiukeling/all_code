package tree;
/**
* Filename:
* title:
* @date 创建时间：2017年12月25日 上午11:14:07 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/
/**
 * 柳树
 */
class osier extends tree
{
/**
 * 过载树的树叶
 */
public void left() {
	super.left();
	String sShape="长形";
	super.print("形状"+sShape);
}

/**
 * 扩展树的花
 */
public void flower() {
	System.err.println("柳树没有花");
}

/**
 * main
 */
public static void main(String[] args) {
	osier o= new osier();
	o.print("柳树的根：");
	o.root();
	o.print("柳树的树干");
	o.bolo();
	o.print("柳树的树枝");
	o.branch();
	o.print("柳树的树叶");
	o.left();
	o.print("柳树的花");
	o.flower();
}






}
