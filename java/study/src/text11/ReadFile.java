package text11;
import java.awt.*;
import java.awt.event.*;
import java.net.*;
import java.io.*;
/**
* Filename:
* title:
* @date 创建时间：2018年4月28日 下午4:37:42 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
* demand:读取服务器端文件，创建一个 URL 对象，然后让 URL 对象返回输入流，通过该输入流读取 URL 所包含的资源文件。
*/
public class ReadFile {

}

public class ReadURLSource
{ public static void main(String args[])
 {
 new NetWin();
 }
}

class NetWin extends Frame implements ActionListener,Runnable
{ Button button;
 URL url;
 TextField text;
 TextArea area;
 byte b[]=new byte[118];
 Thread thread;
 NetWin()
 { text=new TextField(20);
 area=new TextArea(12,12);
 button=new Button("确定");
 button.addActionListener(this);
 thread=new Thread(this);
 Panel p=new Panel();
 p.add(new Label("输入网址:"));
 p.add(text);
 p.add(button);
 add(area,BorderLayout.CENTER);
 add(p,BorderLayout.NORTH);
 setBounds(60,60,360,300);
 setVisible(true);
 validate();
 addWindowListener(new WindowAdapter()
 { public void windowClosing(WindowEvent e)
 { System.exit(0);
}
 });
 }
 public void actionPerformed(ActionEvent e)
 {
 if(!(thread.isAlive()))
 thread=new Thread(this);
 try{
 thread.start();
 }
 catch(Exception ee)
 { text.setText("我正在读取"+url);
 }
 }
 public void run()
 { try { int n=-1;
 area.setText(null);
 String name=text.getText().trim();
 【代码 1】 //使用字符串 name 创建 url 对象
 String hostName=【代码 2】 //url 调用 getHost()
 int urlPortNumber=【代码 3】 //url 调用 getPort()
 String fileName=【代码 4】 //url 调用 getFile()
 InputStream in=【代码 5】 //url 调用方法返回一个输入流
 area.append("\n 主机:"+hostName+"端口:"+urlPortNumber+
"包含的文件名字:"+fileName);
 area.append("\n 文件的内容如下:");
 while((n=in.read(b))!=-1)
 { String s=new String(b,0,n);
 area.append(s);
 }
 }
 catch(MalformedURLException e1)
 { text.setText(""+e1);
 return;
 }
 catch(IOException e1)
 { text.setText(""+e1);
 return;
 }
 }