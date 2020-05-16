package login;

/**
* Filename:
* title:
* @date 创建时间：2018年5月21日 下午4:10:12 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/
import javax.swing.*;

import java.awt.*; //导入必要的包
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.SimpleDateFormat;
import java.util.Date;

public class login_main implements ActionListener {
	static String string;
	JTextField jTextField;// 定义文本框组件
	JPasswordField jPasswordField;// 定义密码框组件
	JLabel jLabel1, jLabel2;
	JPanel jp1, jp2, jp3, jp4;
	JButton jb1, jb2, jb3; // 创建按钮
	String username = "bobby";
	String password = "123";
	JFrame frame = new JFrame("登陆");
	JRadioButton r1 = new JRadioButton("北京");
	JRadioButton r2 = new JRadioButton("上海");
	JRadioButton r3 = new JRadioButton("青岛");
	static String location = "llll";

	public login_main() {//login

		jTextField = new JTextField(12);
		jPasswordField = new JPasswordField(13);
		jLabel1 = new JLabel("用户名");
		jLabel2 = new JLabel("密码");
		jb1 = new JButton("登陆");
		jb2 = new JButton("取消");

		jb3 = new JButton("请选择地址");
		jp1 = new JPanel();
		jp2 = new JPanel();
		jp3 = new JPanel();
		jp4 = new JPanel();
		jb1.addActionListener(this);
		jb2.addActionListener(this);
		// jb3.addActionListener(this);
		// 设置布局
		frame.setLayout(new GridLayout(4, 1));

		jp1.add(jLabel1);
		jp1.add(jTextField);// 第一块面板添加用户名和文本框

		jp2.add(jLabel2);
		jp2.add(jPasswordField);// 第二块面板添加密码和密码输入框

		jp3.add(jb1);
		jp3.add(jb2);

		ButtonGroup bg = new ButtonGroup();// 创建一个ButtonGroup对象
		bg.add(r1);
		bg.add(r2);
		bg.add(r3);
		jp4.add(r1);
		jp4.add(r2);
		jp4.add(r3);

		frame.add(jp1);
		frame.add(jp2);
		frame.add(jp4);
		frame.add(jp3); // 将三块面板添加到登陆框上面
		// 设置显示
		frame.setSize(300, 200);
		// this.pack();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);

	}

	public void actionPerformed(ActionEvent e) {//actionlister login
		string = e.getActionCommand();
		if (string.equals("登陆")) {
			if (r1.isSelected()) {
				location = r1.getText();
			}
			if (r2.isSelected()) {
				location = r2.getText();
			}
			if (r3.isSelected()) {
				location = r3.getText();
			}
			String name = jTextField.getText().toString();
			String admin = new String(jPasswordField.getPassword());
			login_check(name, admin, location);
		}
		if (string.equals("取消")) {// 退出
			frame.setVisible(false);// 隐藏窗体
			System.exit(0);// 退出程序
		}
	}

	public void login_check(String name, String admin, String location) {
		if (name.equals(username) && admin.equals(password)) {
			// 跳转
			Myfram(location, username);
		} else {// 提示是否重新输入，并光标归位
			prompt();
			if (string.equals("重新输入")) {
			}
			if (string.equals("退出"))
				;
		}
	}

	public void Myfram(String Sitting, String username) {
		frame.setVisible(false);//隐藏登录界面		
		JFrame f = new JFrame("用户界面");
		f.setSize(200, 300);
		f.setLayout(new GridLayout(2,1));
		JPanel jp5 = new JPanel();
		JButton jb5 = new JButton("退出");
		JPanel jp6 = new JPanel();
		jp6.add(jb5);
		JTextArea readonly =new JTextArea();
		Date date = new Date();
		SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd :hh:mm:ss");
		String time = dateFormat.format(date);
		String helloword = "  wellcome "+ username+ " from " + Sitting  ;
		jp5.add(readonly);
		f.add(jp5);
		readonly.append("登录时间:  " + time + "\r\n"+helloword);
		readonly.setEditable(false);//只读
		jp6.add(jb5);//退出按钮
		jb5.addActionListener(new ActionListener() {//退出响应			
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				f.setVisible(false);
			}
		});
		f.add(jp6);
		
		//背景

		JPanel jp7 = new RePanel();		
		f.add(jp7);
     
		
		
		f.setSize(300, 200);
		// this.pack();
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		f.setVisible(true);
	}
	


	public void prompt() {// 输入错误提示
		JFrame f = new JFrame("提示");
		JPanel jp5 = new JPanel();
		JButton jb4, jb5, jb6;
		jb4 = new JButton("密码或用户名不正确，是否重新输入");
		jb5 = new JButton("重新输入");
		jb6 = new JButton("退出");

		jb5.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {// 重新输入
				f.setVisible(false);
				jTextField.setText("");
				jPasswordField.setText("");
				jTextField.requestFocus();// 将光标移到文本框
			}
		});
		jb6.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {// 退出窗口
				// TODO Auto-generated method stub
				f.setVisible(false);
				frame.setVisible(false);

			}
		});
		jp5.add(jb4);
		jp5.add(jb5);
		jp5.add(jb6);
		f.add(jp5);
		f.setSize(300, 200);
		// this.pack();
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		f.setVisible(true);
	}

	public static void main(String[] args) {
		login_main login = new login_main();

	}
}



class  RePanel extends JPanel{
	ImageIcon icon;  
	Image img;

	public RePanel() {
		icon = new ImageIcon(getClass().getResource("/login/img12.jpg"));
		img = icon.getImage();
	}
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		// 下面这行是为了背景图片可以跟随窗口自行调整大小，可以自己设置成固定大小
		g.drawImage(img, 0, 0, this.getWidth(), this.getHeight(), this);
	}
//    public void paintComponent(Graphics g){
//        super.paintComponent(g);
//        g.drawImage(new ImageIcon("img12.jpg").getImage(), 0, 0, 200, 200, this);
//     }
}