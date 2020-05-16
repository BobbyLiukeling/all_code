package text8;

import java.sql.DriverManager;
import java.sql.SQLException;

import javax.print.attribute.standard.MediaName;

import com.mysql.jdbc.Connection;
import com.mysql.jdbc.Statement;

/**
* Filename:
* title:
* @date 创建时间：2018年4月16日 下午7:44:01 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/
public class conner {  
	  
	    private static final String URL="jdbc:mysql://localhost:3306/song";//数据库连接字符串，这里的deom为数据库名  
	    private static final String NAME="bobby";//登录名  
	    private static final String PASSWORD="520lkl";//密码  
	      
	    public java.sql.Connection open()  
	    {  
	        //1.加载驱动  
	        try {  
	            Class.forName("com.mysql.jdbc.Driver");  
	        } catch (ClassNotFoundException e) {  
	            System.out.println("未能成功加载驱动程序，请检查是否导入驱动程序！");  
	                        //添加一个println，如果加载驱动异常，检查是否添加驱动，或者添加驱动字符串是否错误  
	            e.printStackTrace();  
	        } 

	        java.sql.Connection conn = null; 
	        
	        try {  
	            conn = DriverManager.getConnection(URL, NAME, PASSWORD);  
	                System.out.println("获取数据库连接成功！");  
	        } catch (SQLException e) {  
	            System.out.println("获取数据库连接失败！");  //添加一个println，如果连接失败，检查连接字符串或者登录名以及密码是否错误 
	                         
	            e.printStackTrace();  
	        }  
	        return conn;    
	  }
	    
	    //数据库打开后就要关闭  
	    public void close(Connection conn) {
			
	        if(conn!=null)  
	        {  
	            try {  
	                conn.close();  
	            } catch (SQLException e) {  
	                // TODO Auto-generated catch block  
	                e.printStackTrace();  
	                conn=null;  
	            }  
	        }  
	    } 
//	    public static void main(String[] args) {
//			
//		}

		
	} 