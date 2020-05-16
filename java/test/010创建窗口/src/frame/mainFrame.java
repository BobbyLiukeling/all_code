package frame;
import javax.swing.*;
import java.awt.*;
/**
* Filename:frame
* title:mainframe
* @date 创建时间：2017年12月26日 下午10:00:57 
* @version 1.0 
* @parameter  Toolkit.getDefaultToolkit().getScreenSize()，其中toolkit是一个抽象类，Toolkit getDefaultToolkit()获取默认工具包
* 
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/
public class mainFrame extends JFrame
{
	/**
	 * 构造函数通过传递参数来完成窗口绘制，
	 * 输入String STitle窗口标题，int IWidth 窗口宽度，int IHeight 窗口高度
	 */
	public mainFrame(String sTitle,int iWidth,int iHeight)
	{
		Dimension dim=Toolkit.getDefaultToolkit().getScreenSize();//获取屏幕尺寸即分辨率
		//ImageIcon ii=new ImageIcon("img14.jpg");	//链接图片
		setTitle(sTitle);//设置窗体标题
		//setIconImage(ii.getImage());//设置窗体的图标
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);//设置关闭窗体时退出程序
		setSize(iWidth, iHeight);//设置窗体大小
		int w=getSize().width;//获取窗体宽
		int h=getSize().height;
		//System.out.println("窗体宽："+w+"窗体高:"+h);
		//将窗口移到屏幕中间
		int x=(dim.width-w)/2;
		int y=(dim.height -h)/2;
		setLocation(x, y);//将窗体移到屏幕中间
		setVisible(true);//显示窗体		
	}
	
	/**
	 * main
	 */
	public static void main(String[] args) {
		JFrame.setDefaultLookAndFeelDecorated(true);//使用最新的swing外观
		mainFrame mainFrame=new mainFrame("main frame Demo", 400, 300);
	}
	
	
	
	
	
	
}























