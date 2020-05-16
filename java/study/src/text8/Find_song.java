package text8;

import java.awt.List;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

/**
 * Filename: title:
 * 
 * @date 创建时间：2018年4月17日 上午8:57:15
 * @version 1.0
 * @parameter Description:
 * @author Liu Keling 作者 E-mail: 1194380923@qq.com
 */
public class Find_song {
	public void find(Music[] musics) {
		Print_Song print_Song =new Print_Song();
		GUI gui = new GUI();// 画布
		Find_Manager find_Manager = new Find_Manager();
		Class_into_Map trans=new Class_into_Map();
		int len = musics.length;
		Map<Integer, Map<String, String>> maps=new HashMap<Integer, Map<String, String>>();
		maps = trans.transClass(musics);//拿到maps
		Scanner scanner = new Scanner(System.in);
		
		
		int key1;
		while (true) {// 验证序号合法性
			gui.childrenDrawing1();
			;// 画布
			System.out.println("请输入你要进行的操作编号：");
			key1 = scanner.nextInt();// 选择操作序号
			
			if (key1 < 1 || key1 > 4) {// 非法输入
				System.out.println(key1 + "  不是正确选项");
				System.out.println("是否继续操作： 是请按 1，否则按任意键退出");
				try {
					int key2 = scanner.nextInt();
					if (key2 != 1) {
						System.out.println("你退出了操作");
						break;
					}
					
				} catch (Exception e) {
					System.out.println("你退出了操作");
					break;
				}
			} 
			else {
				
				break;
			}
		}
		
		String keyword;
		keyword=find_Manager.choice(key1);//判断系统调用那种查询方法
		System.out.println("请输入你要查找的"+keyword);
		String check=scanner.next();
		find_Manager.found_by_name(maps, check, len,keyword);//调用查询结果
	
	}

}
