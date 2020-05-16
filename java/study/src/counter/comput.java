package counter;

import java.awt.*;
import java.time.*;
import java.awt.event.*;
import java.sql.Time;
import java.util.*;

import javax.print.attribute.standard.RequestingUserName;
import javax.swing.*;
import javax.swing.text.html.HTMLDocument.Iterator;

import com.mysql.jdbc.log.Slf4JLogger;

import text7.Arr;

/**
 * Filename: title:
 * 
 * @date 创建时间：2018年5月12日 下午10:27:13
 * @version 1.0
 * @parameter Description:
 * @author Liu Keling 作者 E-mail: 1194380923@qq.com
 * 总结：容错!!!!!!!
 * 不足：未能实现正负号，及单操作数运算
 */
public class comput implements ActionListener {
	private JFrame f;
	private String string;
	JTextField display1 = new JTextField("0");// 初始界面
	JTextField display2 = new JTextField(" ");
	ArrayList list_gobel = new ArrayList();
	double sum_last = 0.0;

	public void init()// 初始化 ,并返回输入的list集合
	{
		f = new JFrame("计算器");
		f.setBounds(400, 150, 260, 360); // 起始位置（X,Y）长宽
		// f.setResizable(false);//不可改变大小
		String[] str = { "CE", "(", ")", "±", "9", "8", "7", "+", "6", "5", "4", "-", "3", "2", "1", "*", ".", "0", "=",
				"/" };
//		JTextField display1 = new JTextField("0");// 初始界面
//		JTextField display2 = new JTextField(" ");
		display1.setHorizontalAlignment(JTextField.RIGHT);
		display2.setHorizontalAlignment(JTextField.RIGHT);
		// display2.setBounds(0, 0, 250, 10);
		Container contentPane = f.getContentPane();
		JButton[] buttons = new JButton[str.length];
		JPanel panel = new JPanel();

		panel.setLayout(new GridLayout(5, 4));
		for (int j = 0; j < str.length; j++) {
			buttons[j] = new JButton(str[j]);
			panel.add(buttons[j]);
		}
		panel.setPreferredSize(new Dimension(0, 250));// 设置布局大小
		contentPane.add(display2, BorderLayout.NORTH);
		contentPane.add(display1, BorderLayout.CENTER);
		contentPane.add(panel, BorderLayout.SOUTH);
		myEvent(); // 关闭窗口
		f.setVisible(true); // 窗口可见
		for (int i = 0; i < buttons.length; i++) {
			buttons[i].addActionListener(this);
		}
	} // init()结束


	public void actionPerformed(ActionEvent e) {
		string = e.getActionCommand();		
		ArrayList number = new ArrayList();
		for (int i = 0; i < 10; i++) {
			number.add("" + i);
		}
		ArrayList operator = new ArrayList();
		operator.add("+");
		operator.add("-");
		operator.add("*");
		operator.add("/");
		

		if (string.equals("CE")) {
			display1.setText("0");
			display2.setText("0");
			list_gobel.clear();

		}
		display1.setText(string);
		if (string.equals("=") == false || string.equals("CE") == false) { //System.out.println(string);
			ArrayList temp = new ArrayList();// 用作交换
			temp.addAll(list_gobel);
			list_gobel.clear();
			list_gobel.addAll(conformity_input(temp, string));// 输入纠错
			
//			for (int i = 0; i < list_gobel.size(); i++) {
//				System.out.println(list_gobel.get(i));
//			}
			display1.setText(list_gobel.get(list_gobel.size()-1).toString());
			String S="";
			for (int i = 0; i < list_gobel.size(); i++) {
				S=S+list_gobel.get(i);//将list内容装入S
			}
			display2.setText(S);
		}
		
		if (string.equals("=")) {
			try {
				display2.setText(display2.getText() + string);// 把括号加到上面的文本框
				boolean key;
				ArrayList temp = new ArrayList();// 用作交换
				temp.addAll(list_gobel);
				list_gobel.clear();
				list_gobel.addAll(conformity_list(temp));// 清除list末尾的错误输入
				String s = "";
				if (list_gobel.size() == 1) {// 当操作数只有一个，没有操作符时直接将此操作数作为结果
					sum_last = Double.parseDouble(list_gobel.get(0).toString());
				} else {
					key = breaket(list_gobel);// 判断输入的括号是否成对
					// 判断是否可以计算，即至少两个运算数，一个运算符
					if (key) {// 如果括号成对，即输入正确，则进入计算
						sum_last = get_stack(list_gobel);
					}
				}
				for (int i = 0; i < list_gobel.size(); i++) {
					s = s + list_gobel.get(i).toString();
				}
				display2.setText(s + "=" + (sum_last + ""));
				display1.setText(sum_last + "");
				list_gobel.clear();// 准备下一次计算
				// 将list中内容计算
				// list 清零并等待下一次输入
			} catch (Exception e2) {
				e2.printStackTrace();
			}
			
		}
	}

	public ArrayList conformity_input(ArrayList list, String str)// 整合规范输入,在连续输入数字后将数字整合，操作符后面只能是数字或者右括号，等！！！！！！！
	{
		ArrayList number = new ArrayList();
		for (int i = 0; i < 10; i++) {
			number.add("" + i);
		}
		ArrayList operator = new ArrayList();
		operator.add("+");
		operator.add("-");
		operator.add("*");
		operator.add("/");

		if (list.size() == 0) {
			if (number.contains(str) || str.equals("("))// 第一个输入只能为数字或左括号
			{
				list.add(str);
			} else {
				return list;
			}
		} else// 不是第一个输入
		{
			String s=list.get(list.size() - 1).toString();
			String decimal="([1-9]+[0-9]*|0)(\\.[\\d]+)?";//匹配list最后是小数的数字
			if (number.contains(s)||s.matches(decimal))// list最后一位是数字，以下四种输入情况
			{
				if (number.contains(str)) {// 当前输入为数字，合并数字从新装入list
					String string = list.get(list.size() - 1).toString();// 获取最后一个
					list.remove(list.size() - 1);// 删除最后一个元素
					list.add(string + str);// 重新装入，不要装反了！！！！
				}
				if (operator.contains(str) || str.equals(")") || str.equals(".")) {// 当前输入操作符,或者右括号
					list.add(str);
				}
				if (str.equals("(")) {// 数字后面的左括号，错误输入忽略
					return list;
				}
			}

			if (operator.contains(s)) {// list最后一位是操作符
				if (number.contains(str) || str.equals("(")) {// 当前输入为数字,或者左括号
					list.add(str);
				}
				if (operator.contains(str)) {// 当前输入操作符
					list.remove(list.size() - 1);// 删除list最后一个元素
					list.add(str);// 重新装入当前操作符
				}
				if (str.equals(")") || str.equals(".")) {// 数字后面的左括号，错误输入忽略
					return list;
				}
			}

			if (s.equals("(")) {// list最后一位是左括号
				if (number.contains(str)) {// 当前输入为操作数，
					list.add(str);
				} else {
					return list;// 除数字外都是错误输入
				}
			}

			if (s.equals(")")) {// list最后为右括号
				if (operator.contains(str)) {// 右括号的后面一定只能接操作符
					list.add(str);
				} else {
					return list;
				}
			}
			if (s.equals(".")) {// list最后为小数点
				if (number.contains(str)) {// 小数点最后只能是数字
					//String symbol = list.get(list.size()-1).toString();//取出小数点
					list.remove(list.size()-1);// 删除list最后的小数点
					String num_old = list.get(list.size() - 1).toString();// 取出小数点前面的操作数
					list.remove(list.size()-1);// 删除老的操作数					
					String num_new = num_old + "." + str;// 新的操作					
					list.add(num_new);// 添加新的操作数
				}
				if (operator.contains(str)||str.equals(")")) {//当前输入为操作符。取消前面的小数点
					list.remove(list.size()-1);// 删除list最后的小数点
					list.add(str);
				}
				if (str.equals("(")) {
					return list;
				}					
			}
		}
		return list;
	}// 输入整合结束

	public boolean breaket(ArrayList list) {// 查看括号是否正确输入
		boolean key = false;
		int right = 0, left = 0;// 右括号个数
		for (int i = 0; i < list.size(); i++) {
			if (list.get(i).toString().equals("(")) {
				left++;
			} 
			if (list.get(i).toString().equals(")")) {
				right++;
			}
		}
		if (right == left) {// 左括号个数等于右括号操作数和操作符个数正确
			key = true;
		} else {
			key = false;
			System.out.println("输入括号不成对，无法完成计算");
		}
		return key;
	}

	public ArrayList conformity_list(ArrayList list) {// 删除list末尾的不合适输入
		ArrayList number = new ArrayList();
		for (int i = 0; i < 10; i++) {
			number.add("" + i);
		}
		ArrayList operator = new ArrayList();
		operator.add("+");
		operator.add("-");
		operator.add("*");
		operator.add("/");
		String endList = list.get(list.size() - 1).toString();
		if (number.contains(endList) || endList.equals(")")) {// 以数字或者右括号结尾
			return list;
		}
		if (endList.equals(".") || operator.contains(endList)) {// 以小数点，左括号，操作符结尾
			list.remove(list.size() - 1);// 移除
		}
		if (endList.equals("(")) {
			if (operator.contains(list.get(list.size() - 2).toString())) {// 倒数第二个为操作符
				list.remove(list.size() - 1);// 删除一个左括号
				list.remove(list.size() - 1);// 再删除操作符
			} else {
				list.remove(list.size() - 1);
			}
		}
		return list;
	}

	public double get_stack(ArrayList list) {	
		ArrayList number = new ArrayList();
		Stack<String> stack_operator = new Stack<String>();// 数字队列
		Stack<Double> stack_number = new Stack<Double>();// 运算符队列
		for (int i = 0; i < 10; i++) {
			number.add("" + i);
		}
		ArrayList operator = new ArrayList();
		operator.add("+");
		operator.add("-");
		operator.add("*");
		operator.add("/");

		for (int i = list.size()-1; i>-1; i--) {
			
			if (list.get(i).toString().equals(")")) {// 左括号忽略，因为list是从后面开始向前入栈，所以遇到括号的规则调换即遇右括号忽略，左括号弹出操作符和运算符
				continue;
			}
			
			String decimal="([1-9]+[0-9]*|0)(\\.[\\d]+)?";//匹配list最后是小数的数字
			if (number.contains(list.get(i).toString())||list.get(i).toString().matches(decimal))// 如果是数字入栈,需要考虑带小数的数字!!!!!!
			{
				stack_number.push(Double.parseDouble(list.get(i).toString()));
				continue;
			}
			
			
			if (operator.contains(list.get(i).toString())) {// 运算符入栈
				stack_operator.push(list.get(i).toString());
				continue;
			}
			if (list.get(i).toString().equals("("))// 右括号弹栈
			{
				try {
					double operand1 = Double.parseDouble(stack_number.pop().toString());// 转换为 操作数
					//
					double operand2 = Double.parseDouble(stack_number.pop().toString());// 转换为 操作数
					String operat = stack_operator.pop().toString();
					double sum = count(operand1, operand2, operat);// 获取运算结果
					stack_number.push(sum);// 运算结果入栈
					continue;
				} catch (Exception e) {
					e.printStackTrace();
					continue;
				}
			}			
		} // for结束 在for循环中将括号中的计算计算
		double result = 0.0;
		
		result = get_result(stack_number, stack_operator);
		return result;
	}// get_queue end!

	public double get_result(Stack<Double>stack_number, Stack<String>stack_operator) {// 计算没有括号的算式
		double sum = 0.0;			
		for (;stack_operator.size()>0;) {
			if (stack_operator.size()==1) {
				String operat1 = stack_operator.pop();
				double operand1 = stack_number.pop();// 转换为 操作数
				double operand2 = stack_number.pop();
				// 转换为 操作数
				sum = count(operand1, operand2, operat1);
			}
			else {
				String operat1 = stack_operator.pop();
				String operat2 = stack_operator.pop();
				double operand1 = stack_number.pop();// 转换为 操作数
				double operand2 = stack_number.pop();
				;// 转换为 操作数
				if ((operat1.equals("+") || operat1.equals("-")) && (operat2.equals("*") || operat2.equals("/")))// 前面的运算符优先级高于后面
				{
					double operand3 = stack_number.pop();// 转换为 操作数
					sum = count(operand2, operand3, operat2);
					stack_number.push(sum);
					stack_number.push(operand1);
					stack_operator.push(operat1);// 弹出的操作符进栈
				} else {// 前面一个的操作符
					sum = count(operand1, operand2, operat1);
					stack_number.push(sum);
					stack_operator.push(operat2);// 弹出的操作符进栈
				}
			}
		}
		return sum;
	}

	public double count(double operand1, double operand2, String operat) {// 计算
		double sum = 0.0;
		if (operat.equals("+")) {
			sum = operand1 + operand2;			
		}
		if (operat.equals("-")) {
			sum = operand1 - operand2;			
		}
		if (operat.equals("*")) {
			sum = operand1 * operand2;			
		}
		if (operand2 != 0 && operat.equals("/")) {
			sum = operand1 / operand2;			
		} 
		if (operand2 == 0 && operat.equals("/")) {
			System.out.println("除数不能为0");			
		}
		//System.out.println(sum);
		return sum;
	}

	public void myEvent()// 退出组件
	{
		f.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				System.exit(0);// 这个方法的 关闭的是虚拟机，退出虚拟机，当然就退出了程序
			}
		});
		// 让按钮具备退出程序的功能。
	}

	// 主函数，用于测试
	public static void main(String[] args) {
		// ArrayList list = new ArrayList();
		// boolean key;
		comput com = new comput();
		com.init();
	}
}
