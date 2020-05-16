package GUI;
import java.awt.*;
import javax.swing.*;
import javax.swing.text.StyledEditorKit.BoldAction;
/**
* Filename:
* title:
* @date 创建时间：2017年12月27日 下午6:51:22 
* @version 1.0 
* @parameter  
* Description: 改造后的frame,按钮像li那样排列
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/
public class newJFrame_two extends JFrame{
	JButton[] an= {null,null,null,null};
	public static void main(String[] args) {
		newJFrame_two frame=new newJFrame_two();
	}
	
	public newJFrame_two() {
		// TODO Auto-generated constructor stub
		an[0]=new JButton("吃");
		an[1]=new JButton("睡");
		an[2]=new JButton("玩");
		an[3]=new JButton("hahahahah!");
		//this.setLayout(new FlowLayout());//布局管理器，如果不加就只能显示最后一个按钮
		
		this.setLayout(new FlowLayout(FlowLayout.RIGHT));//buttond 位置，还有left
		/**
		 * 添加的位置
		 * 
		 */
		this.add(an[0]);
		this.add(an[1]);
		this.add(an[2]);
		this.add(an[3]);
		this.setLayout(new GridLayout(2, 2,15,15));//网格布局管理器：将按钮按按照两行两列显示,且每个按钮间间隔上下和左右15像素。这句话的位置一定要放在add以后
		this.setTitle("用户界面边界布局");
		this.setSize(750, 500);
		this.setLocation(250, 110);		
		this.setResizable(false);//窗体大小只能为设置的值，不能通过用户改变，默认是true
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);//默认有窗体
	}
}















