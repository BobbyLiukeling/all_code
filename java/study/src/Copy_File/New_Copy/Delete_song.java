package text8;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

import javax.swing.tree.DefaultTreeCellEditor.EditorContainer;

/**
 * Filename: title:
 * 
 * @date 创建时间：2018年4月17日 下午7:36:40
 * @version 1.0
 * @parameter Description:
 * @author Liu Keling 作者 E-mail: 1194380923@qq.com
 */
public class Delete_song {
	public void delete_music(int[] arr) {
		Scanner scanner = new Scanner(System.in);
		conner conn = new conner();
		java.sql.Connection con = conn.open();
		System.out.println("请输入删除歌曲编号");
		int num;
		while (true) {
			System.out.println("编号：");
			num = scanner.nextInt();
			boolean t = false;
			for (int i = 0; i < arr.length; i++) {
				if (num == arr[i]) {
					t = true;
					break;
				}
			}
			if (t == false) {
				System.out.println("输入歌曲编号不存在，请从以下编号中选择歌曲序号串行输入");
				for (int i = 0; i < arr.length; i++) {
					System.out.print("  " + arr[i]);
				}
				System.out.println();
				continue;
			} else {
				break;
			}
		}

		String sql1 = "select * from music_ifo where num=?";
		try {// 将选中歌曲信息显示出来，然后询问是否删除
			PreparedStatement pstmt = con.prepareStatement(sql1);
			pstmt.setInt(1, num);
			ResultSet resultSet = pstmt.executeQuery();
			System.out.println("要删除的歌曲是：");
			while (resultSet.next()) {
				System.out.println("number:" + resultSet.getInt("num") 
						+ "  name:" + resultSet.getString("name")
						+ "  language:" + resultSet.getString("lauage") 
						+ "  type:" + resultSet.getString("type")
						+ "  singer:" + resultSet.getString("singeer"));
			}
		} catch (Exception e) {
			System.out.println("读取要删除数据失败！");
			e.printStackTrace();
		}

		System.out.println("是否要删除： 是请按1 否则按任意键退出");
		String confirm = scanner.next();
		if (confirm.equals("1")) {// 执行删除
			String sql2 = "delete from music_ifo where num=?";
			try {
				PreparedStatement pstmt = con.prepareStatement(sql2);
				pstmt.setInt(1, num);
				pstmt.executeUpdate();
				System.out.println("成功删除");
			} catch (Exception e) {
				e.printStackTrace();
				System.out.println("删除不成功");
			}
		}

	}
}
