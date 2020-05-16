package text8;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

/**
 * Filename: title:
 * 
 * @date 创建时间：2018年4月16日 下午5:13:42
 * @version 1.0
 * @parameter Description:
 * @author Liu Keling 作者 E-mail: 1194380923@qq.com demand: 系统中的对象
 *         歌曲(Song.java)： 编号、歌名、语言（中文/英文）、类别（流行/通俗）、歌手  系统功能描述 对已有的曲目进行管理:
 *         查找歌曲信息(按歌名\语言\歌手\类别等进行查询) 增加歌曲 删除某歌曲  技术要求 List/Map
 */
public class demo {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		GUI gui = new GUI();//主菜单
		Find_song find_song = new Find_song();//查找	
		Print_Song print_Song =new Print_Song();//打印
		Class_into_Map tr=new Class_into_Map();//转换为map
		Music[] musics;
		GetDate getdate = new GetDate();//从数据库得到数据
		Add_song add_song =new Add_song();//添加数据
		Delete_song delete_song=new Delete_song();//删除数据
		musics = getdate.date();//	将数据装入对象数组
//		System.out.println(musics.length);
//		System.out.println("************");
		Map<Integer, Map<String, String>> maps=new HashMap<Integer, Map<String, String>>();
		maps = tr.transClass(musics);//将数据装入maps
		int count_song=musics.length;
		int[] arr=new int[count_song];
		for (int i = 0; i < count_song; i++) {//将歌曲的编号载入数组
			arr[i]=Integer.parseInt( maps.get(i).get("num"));
		}
		int key1;

		while (true) {// 验证序号合法性
			gui.drawing();// 画布
			System.out.println("请输入你要进行的操作编号：");
			key1 = scanner.nextInt();// 选择操作序号
			if (key1 < 1 || key1 > 5) {// 非法输入
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

			} else {
				break;
			}

		}
		
		switch (key1) {
		case 1:
			find_song.find(musics);
			break;
		case 2:			
			add_song.add_music(arr);
			break;
		case 3:
			for (int i = 0; i < musics.length; i++) {
				print_Song.print_map(maps.get(i));
			}
			delete_song.delete_music(arr);
			break;
		case 4:			
			for (int i = 0; i < musics.length; i++) {
				print_Song.print_map(maps.get(i));
			}			
			break;
		default:
			break;
		}
		
		

	}
}
