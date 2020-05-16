package text10;
/**
* Filename:
* title:
* @date 创建时间：2018年4月28日 下午4:06:45 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
* demand :编写一个应用程序，除了主线程外，还有两个线程：first 和 second。first 负责模拟一个红色的按钮从坐标(10，60)运动到(100，60)；
* second 负责模拟一个绿色的按钮从坐标(100，60)运动到(200，60)。
*/

import java.awt.Button;
import java.awt.Color;
import java.awt.Component;
import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class MoveButton extends Frame implements Runnable, ActionListener {
	Thread first, secend; // 用 Thread 类声明 first,second 两个线程对象
	Button redButton, greenButton, startButton;
	int distance = 10;

	MoveButton() {
		first = new Thread(this); // 创建 first 线程，当前窗口做为该线程的目标对象
		secend = new Thread(this); // 创建 first 线程，当前窗口做为该线程的目标对象
		redButton = new Button();
		greenButton = new Button();
		redButton.setBackground(Color.red);
		greenButton.setBackground(Color.green);
		startButton = new Button("start");
		startButton.addActionListener(this);
		setLayout(null);
		add(redButton);
		redButton.setBounds(10, 60, 15, 15);
		add(greenButton);
		greenButton.setBounds(100, 60, 15, 15);
		add(startButton);
		startButton.setBounds(10, 100, 30, 30);
		setBounds(0, 0, 300, 200);
		setVisible(true);
		validate();
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
	}

	public void actionPerformed(ActionEvent e) {
		try {
			first.start();
			secend.start();
		} catch (Exception exp) {
		}
	}

	public void run() {
		while (true) {
			if (Thread.currentThread() == first) // 判断当前占有 CPU 资源的线程是否是 first
			{
				moveComponent(redButton);
				try {
					Thread.sleep(20);
				} catch (Exception exp) {
				}
			}
			if (Thread.currentThread() == secend) // 判断当前占有 CPU 资源的线程是否是 second
			{
				moveComponent(greenButton);
				try {
					Thread.sleep(5);
				} catch (Exception exp) {
				}
			}
		}
	}

	public synchronized void moveComponent(Component b) {
		if (Thread.currentThread() == first) {
			while (distance > 100 && distance <= 200)
				try {
					wait();
				} catch (Exception exp) {
				}
			distance = distance + 1;
			b.setLocation(distance, 60);
			if (distance >= 100) {
				b.setLocation(10, 60);
				notifyAll();
			}
		}
		if (Thread.currentThread() == secend) {
			while (distance >= 10 && distance < 100)
				try {
					wait();
				} catch (Exception exp) {
				}
			distance = distance + 1;
			b.setLocation(distance, 60);
			if (distance > 200) {
				distance = 10;
				b.setLocation(100, 60);
				notifyAll();
			}
		}
	}
}
