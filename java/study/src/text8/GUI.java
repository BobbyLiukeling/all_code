package text8;
/**
* Filename:
* title:
* @date 创建时间：2018年4月17日 上午8:22:26 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/
public class GUI {
	public void drawing() {
		System.out.println("***********************************************************");
		System.out.println("***************"+"歌曲管理"+"*****************");
		System.out.println("***********************************************************");
		System.out.println("        1---------------------查找歌曲");
		System.out.println("        2---------------------增加歌曲");
		System.out.println("        3---------------------删除歌曲");
		System.out.println("        4---------------------显示所有歌曲");
		System.out.println("        5---------------------退出系统");
		System.out.println("***********************************************************");
		System.out.println();
		System.out.println();
	}
	
	public void childrenDrawing1() {
		System.out.println("        1---------------------按歌名查找歌曲");
		System.out.println("        2---------------------按语言查找歌曲");
		System.out.println("        3---------------------按歌手查找歌曲");
		System.out.println("        4---------------------按类别查找歌曲");
	}
}
