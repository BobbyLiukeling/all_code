package GUI;
import java.awt.*;
import javax.swing.*;
import javax.swing.text.StyledEditorKit.BoldAction;
/**
* Filename:
* title:
* @date 创建时间：2017年12月27日 下午6:51:22 
* @version 1.0 
* @parameter  Jbutton
* Description: 改造后的frame,按钮在指定位置上
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/
public class newJFrame extends JFrame{
	JButton an1,an2,an3,an4,an5;
	public static void main(String[] args) {
		newJFrame frame=new newJFrame();
	}
	
	public newJFrame() {
		// TODO Auto-generated constructor stub
		this.setTitle("用户界面边界布局");
		this.setSize(750, 500);
		this.setLocation(250, 110);
		an1 =new JButton("按钮");
		an2=new JButton("东");
		an3=new JButton("南");
		an4=new JButton("西");
		an5=new JButton("北");
		/**
		 * 添加的位置
		 * 
		 */
		this.add(an1,BorderLayout.CENTER);
		this.add(an2, BorderLayout.EAST);
		this.add(an3, BorderLayout.SOUTH);
		this.add(an4, BorderLayout.WEST);
		this.add(an5, BorderLayout.NORTH);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
		
	}
}















