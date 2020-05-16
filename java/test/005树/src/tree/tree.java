package tree;



/**
* Filename:树
* title:tree
* @date 创建时间：2017年12月25日 上午10:47:46 
* @version 1.0 
* @parameter extends  
* Description: 继承与派生
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/
class tree {
    /**
     * 树根  
     */
	public void root() {
		String sSite="土壤中";
		String sFunction="吸收养分";
		System.out.println("位置"+sSite);
		System.out.println("功能"+sFunction);		
	}
	
	/**
	 * 树干
	 */
	public void bolo() {
		String sSite="地面";
		String sFunction="传递养分";
		System.out.println("位置"+sSite);
		System.out.println("功能"+sFunction);
	}
	
	/**
	 * 树枝
	 */
	public void branch() {
		String sSite="树干上";
		String sFunction="传递养分";
		System.out.println("位置"+sSite);
		System.out.println("功能"+sFunction);
	}
	
	/**
	 * 叶子
	 */
	public void left() {
		String sSite="树梢";
		String sFunction="光合作用";
		String sColor="绿色";
		System.err.println("位置"+sSite);
		System.out.println("功能"+sFunction);
		System.out.println("颜色"+sColor);
	}
	
	/**
	 * 显示信息，即大印
	 */
	public void print(Object oPara) {
		System.out.println();
		System.out.println(oPara);
		
	}
	
	/**
	 * 主函数
	 */
	public static void main(String[] args) {
		tree t=new tree();
		t.print("描述一棵树");
		t.print("树根：");
		t.root();
		t.print("树干");
		t.bolo();
		t.print("树枝");
		t.branch();
		t.print("树叶");
		t.left();
		System.out.println();
		System.out.println();
	}
}	

	
	
	
	
	
	
	
	
	
	





























