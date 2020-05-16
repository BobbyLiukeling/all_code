package GUI;
import java.awt.*;
import javax.swing.*;
/**
* Filename:
* title:jframe
* @date 创建时间：2017年12月27日 下午4:58:33 
* @version 1.0 
* @parameter  
* Description: 图形化界面之jframe
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/
public class jframe {
	public static void main(String[] args) {
		JFrame aa=new JFrame();
		aa.setTitle("用户界面");//默认是没有窗体和大小的
		
		aa.setSize(750,500);//窗体的大小
		aa.setLocation(250,100);//窗体的位置
		
		JButton an1=new JButton("一个按钮");//新建一个按钮
		aa.add(an1);//将按钮添加到窗口中
		aa.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//关闭窗口是关闭进程
		aa.setVisible(true);
	}
}














