package Botton;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.AbstractButton;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JPanel;

import javax.swing.JFrame;



/**
* Filename:ButtonDemo
* title:Button
* @date 创建时间：2017年12月27日 上午9:14:46 
* @version 1.0 
* @parameter  
* Description: 按钮演示
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/
public class Botton extends JPanel implements ActionListener{
	protected JButton b1,b2,b3;
	/**
	 * 使用构造函数初始化界面
	 */
	public Botton() {
		ImageIcon leftButtonIcon = createImageIcon("images/right.gif");//createImageIcon是自定义函数，
		ImageIcon middleButtonIcon=createImageIcon("img2.jpg");
		ImageIcon rightButtonIcon=createImageIcon("img3.jpg");
		
		b1=new JButton("失效中间按钮",leftButtonIcon);
		b1.setVerticalTextPosition(AbstractButton.CENTER);//水平中间对齐
		b1.setHorizontalTextPosition(AbstractButton.LEADING);//相当于left
		b1.setMnemonic(KeyEvent.VK_D);//将b1绑定ALT+D键
		b1.setActionCommand("disable");
		
		b2=new JButton("M中间键",middleButtonIcon);
		b2.setVerticalTextPosition(AbstractButton.BOTTOM);
		b2.setHorizontalTextPosition(AbstractButton.CENTER);
		b2.setMnemonic(KeyEvent.VK_M);
		
		b3 = new JButton("E激活中间按钮", rightButtonIcon);
        b3.setMnemonic(KeyEvent.VK_E);//将b3邦定alt+E键
        b3.setActionCommand("enable");
        b3.setEnabled(false);

		
	}
	
	
	
	
	/**
	 * 创建图标，输入图标所在位置，返回图标对象
	 */
	protected static ImageIcon createImageIcon(String path) {
		java.net.URL imageurl=Botton.class.getResource(path);
		if (imageurl!=null) {
			return new ImageIcon(imageurl);
		}		
		else
		{
			System.out.println("can't find the image file:"+path);
			return null;
		}
	}
}
	
	
	
	
	















