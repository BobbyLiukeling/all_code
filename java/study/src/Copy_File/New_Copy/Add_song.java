package text8;

import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.*;
import java.util.Scanner;

/**
 * Filename: title:
 * 
 * @date 创建时间：2018年4月17日 下午5:20:59
 * @version 1.0
 * @parameter Description:
 * @author Liu Keling 作者 E-mail: 1194380923@qq.com
 */
public class Add_song {
	public void add_music(int[] arr) {
		Scanner scanner = new Scanner(System.in);
		conner conn = new conner();
		java.sql.Connection con = conn.open();

		System.out.println("请新增输入歌曲相关信息");
		int num;
		while (true) {//判断歌曲序号的唯一性
			System.out.println("编号：");
			num = scanner.nextInt();
			boolean t=false;
			for (int i = 0; i < arr.length; i++) {
				if (num == arr[i]) {
					t=true;
					break;
				}
			}
			if (t==true) {
				System.out.println("请重新输入歌曲序号，且不要与下面序号相同");
				for (int i = 0; i < arr.length; i++) {
					System.out.print("  "+arr[i]);
				}
				System.out.println();
				continue;
			}
			else {
				break;
			}
		}
		System.out.println("歌名：");
		String name = scanner.next();
		System.out.println("语言：");
		String language = scanner.next();
		System.out.println("类型：");
		String type = scanner.next();
		System.out.println("歌手：");
		String singer = scanner.next();

		// 将数据库内容装载入
		String sql="insert into music_ifo(num,name,lauage,type,singeer) values(?,?,?,?,?)";
		try {
			PreparedStatement pstmt = con.prepareStatement(sql);
			pstmt.setInt(1, num);
			pstmt.setString(2, name);
			pstmt.setString(3, language);
			pstmt.setString(4, type);
			pstmt.setString(5, singer);
			pstmt.executeUpdate();
			System.out.println("写入数据成功");
			con.close();
		} catch (Exception e) {
			System.out.println("写入数据失败");
			e.printStackTrace();
			//return null;
		}
	}
}
