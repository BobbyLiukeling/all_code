package text8;

import com.mysql.jdbc.Connection;

import text4.Count;

import java.sql.ResultSet;
import java.awt.Window.Type;
//import com.mysql.jdbc.Statement;
import java.sql.*;

import javax.naming.spi.DirStateFactory.Result;

/**
 * Filename: title:
 * 
 * @date 创建时间：2018年4月17日 上午8:33:03
 * @version 1.0
 * @parameter Description:
 * @author Liu Keling 作者 E-mail: 1194380923@qq.com
 */
public class GetDate {
	public Music[] date() {
		conner conn = new conner();
		java.sql.Connection con = conn.open();
		String sql = "select * from music_ifo";
		Statement statement;
		Music[] music = null;
		int count=0;//拿到结果集的数据的条数
		try {
			statement = con.createStatement();
			ResultSet resultSet = statement.executeQuery(sql);
			while(resultSet.next())
			{
				count++;
			}	
			resultSet.close();
		} catch (Exception e) {
			System.out.println("拿到结果集的数据的条数失败");
		}
		// 将数据库内容装载入
		try {
			statement = con.createStatement();
			ResultSet resultSet = statement.executeQuery(sql);	
			music = new Music[count];// 初始化对象数组
			int i = 0;

			while (resultSet.next()) {//将数据结果装载入类对象数组
				Music sing = new Music(
						""+resultSet.getInt("num"), 
						resultSet.getString("name"),
						resultSet.getString("lauage"), 
						resultSet.getString("type"), 
						resultSet.getString("singeer"));
				music[i] = sing;
				i++;
			}
			resultSet.close();
			con.close();
			return music;
		} catch (Exception e) {
			System.out.println("获取数据失败");
			e.printStackTrace();
			return null;
		}		
	}
//	public static void main(String[] args) {
//		GetDate da=new GetDate();
//		da.date();
//	}
}
