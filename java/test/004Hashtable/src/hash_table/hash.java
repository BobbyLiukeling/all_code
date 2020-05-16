package hash_table;
import java.util.*;
/**
* Filename:004hash_table
* title:hash
* @date 创建时间：2017年12月24日 下午7:16:51 
* @version 1.0 
* @parameter  
* Description: 哈希表的简单应用
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/
public class hash {
    private static Hashtable rightList=new Hashtable();
    
    /**
     * 初始化数据
     * 输入参数，返回类型
     */
    public void init() {
		String[] accRoleList=
			{"admin","satrap","manager","user","guest"};
		String[] rightCodeList=
			{"10001","10011","10021","20011","24011"};
		for (int i = 0; i < accRoleList.length; i++) {
			rightList.put(accRoleList[i],rightCodeList[i]);//前面是value，后面是key
		}
	}
    
    /**
     * 获取角色权限代码
     * 输入角色名称
     * 返回string权限代码
     */
    public String getRight(String accRole) {
		if (rightList.containsKey(accRole)) {
			return (String)rightList.get(accRole);//返回的是map应的value值
		}
		else {
			return null;
		}
	}
    
    /**
     * 添加角色和代码信息
     * 输入accRole的角色名称，rightCode的角色权限
     * 无返回类型
     */
    public void insert(String accRole,String RightCode) {
		rightList.put(accRole, RightCode);
	}
    
    /**
     *删除角色权限；
     *输入accRole角色名称
     *无返回类型
     */
    public void delete(String accRole) {
		if (rightList.containsKey(accRole)) {
			rightList.remove(accRole);
		}
	}
    
    /**
     * 修改角色权限代码
     * 输入角色accRole，以及角色权限代码rightCode
     * 无返回类型
     */
    public void update(String accRole,String rightCode) {
		this.insert(accRole, rightCode);
	}
    
    /**
     * 打印角色及相应权限代码
     */
    
    public void print() {//遍历输出
		Enumeration RlKey =rightList.keys();//创建每枚举
		while(RlKey.hasMoreElements())//判断表中是否有值
		{
			String accRole=RlKey.nextElement().toString();
			System.out.println(accRole+"="+this.getRight(accRole));
		}
	}
    
    /**
     * 打印信息过载
     */
    
    public void print(Object oPara) {
		System.out.println(oPara);
	}
    
    
    /**
     * 查找
     */
    
    public void find(String index) {
		String key=(String)rightList.get(index);
		if (key!=null) {
			System.out.println(index+"="+key);
		}
	}
    /**
     * main
     */
    public static void main(String[] args) {
		hash RR=new hash();
		RR.init();
		System.out.println("---init---");
		RR.print();
		RR.print("--------------------------------");
		RR.insert("presider", "10110");
		System.out.println("---insert---");
		RR.print();
		RR.print("--------------------------------");
		RR.update("presider", "10100");
		System.out.println("---update---");
		RR.print();
		RR.print("--------------------------------");
		RR.delete("presider");
		System.out.println("---delete---");
		RR.print();
		RR.print("--------------------------------");
		System.out.println("---find---");
		RR.find("manager");
	}
    
}
