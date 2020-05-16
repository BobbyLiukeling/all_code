import java.util.*;


/**
* Filename:003
* title:operateVector
* @date 创建时间：2017年12月24日 上午8:55:03 
* @version 1.0 
* @parameter  
* Description: vector
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/

public class operateVector 
{
	/**
	 * 生成 一个4*4的二维数组vector
	 * 输入参数
	 * 输出变量
	 */
	public Vector buildVector() {
		Vector vTemps=new Vector();
		//System.out.println("请输入一个4*4 的二维数组");
		for (int i = 0; i < 4; i++) {
			Vector vTemp =new Vector();
			for (int j = 0; j < 4; j++) {
				vTemp.addElement("Vector("+i+")("+j+")");
			}
			vTemps.addElement(vTemp);
		}
		return vTemps;
	}
	
	/**
	 * 插入数据
	 * vTemp:待插入的对象，iTemp：插入数据的位置，OTemp：插入数据的值
	 * 输出vector结果
	 * 说明：如果插入位置超出实例实际位置将返回NULL
	 */
	public Vector insert(Vector vTemp,int iTemp,Object oTemp) {
		if (iTemp>vTemp.size()) {
			System.out.println("数组越界！");
			return null;
		}
		else
		{
			vTemp.insertElementAt(oTemp, iTemp);//insertElementAt(Object obj, int index)obj要插入的元素，index要插入的位置
		}
		return vTemp;
	}
	
	/**
	 * 移除数据
	 * Vector vTemp待删除的对象，int iTemp 删除的数据的位置
	 * 输出变量vector
	 * 如果删除超界将返回null;
	 */
	public Vector delete(Vector vTemp,int iTemp) {
		if (iTemp>vTemp.size()) {
			return null;
		}
		else {
			vTemp.removeElementAt(iTemp);
		}
		return vTemp;
	}
	
	/**
	 * 修改数据
	 * Vector vtemp :待修该的数据对象，int iTemp修改的数据位置，object OTemp修改的数据的值，
	 * 如果修改超界将返回null
	 */
	public Vector update(Vector VTemp,int iTemp,Object oTemp) {
		if (iTemp>VTemp.size()) {//如果超界
			return null;
		}
		else
		{
			VTemp.setElementAt(oTemp, iTemp);
		}
		return VTemp;
	}
	
	/**
	 * 输出信息
	 * String STemp输出信息名称
	 * object OTemp 输出信息的值
	 * 无返回变量
	 */
	public void print(String sTemp,Vector oTemp)
	{
		System.out.println(sTemp+"数据：");
	    for(int i=0;i<oTemp.size();i++)	
	    {
	    	System.out.println(oTemp.elementAt(i));
	    }
	    System.out.println();
	    System.out.println();
	}
	
	/**
	 * 主函数
	 */
    public static void main(String[] args) {
		operateVector ov=new operateVector();
		Vector vTemp=ov.buildVector();
		ov.print("将输出4*4的二维数组vTemp0", vTemp);
		Vector vResult=ov.insert(vTemp, 2, "add the list");
		ov.print("将输出4*4的二维数组vTemp1", vResult);
		Vector vreset=ov.update(vResult, 3, "update list");
		ov.print("将输出4*4的二维数组vTemp1", vreset);
		Vector vDalete=ov.delete(vreset, 1);
		ov.print("删除了第一条数据",vDalete);
		
	}
	
	
	
	
	
	
	
	
	
}












