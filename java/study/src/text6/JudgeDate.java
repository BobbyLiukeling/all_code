package text6;
import javax.swing.JOptionPane;
import java.util.Calendar;
import java.sql.Date;
/**
* Filename:
* title:
* @date 创建时间：2018年3月26日 下午7:09:18 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
* demand:编写一个 Java 应用程序，用户从输入对话框输入了两个日期，程序将判断两个日期的大小关系，以及两个日期之间的间隔天数。
*/
public class JudgeDate {
	public static void main(String args[ ]) {
		 String str=JOptionPane.showInputDialog("输入第一个日期的年份:");
		 int yearOne=Integer.parseInt(str);
		 str=JOptionPane.showInputDialog("输入该年的月份:");
		 int monthOne=Integer.parseInt(str);
		 str=JOptionPane.showInputDialog("输入该月份的日期:");
		 int dayOne=Integer.parseInt(str);
		 str=JOptionPane.showInputDialog("输入第二个日期的年份:");
		 int yearTwo=Integer.parseInt(str);
		 str=JOptionPane.showInputDialog("输入该年的月份:");
		 int monthTwo=Integer.parseInt(str);
		 str=JOptionPane.showInputDialog("输入该月份的日期:");
		 int dayTwo=Integer.parseInt(str);
		 
		 
		 Calendar calendar=Calendar.getInstance();
		 calendar.set(yearOne,monthOne,dayOne);
		 long timeOne=calendar.getTimeInMillis();
		 calendar.set(yearTwo,monthTwo,dayTwo);
	     long timeTwo=calendar.getTimeInMillis();
	       
	     Date date1=new Date(timeOne);
	     Date date2=new Date(timeTwo); 
	     if(date2.equals(date1))
	     {System.out.println("两个日期的年、月、日完全相同");}
	     else if(date2.after(date1))
	     {System.out.println("您输入的第二个日期大于第一个日期");}
	     else if(date2.before(date1))
	     {System.out.println("您输入的第二个日期小于第一个日期");}
	       
	     long days=(timeOne-timeTwo)/(1000*60*60*24);
	     System.out.println(yearOne+"年"+monthOne+"月"+dayOne+"日和"+yearTwo+"年"+monthTwo+"月"+dayTwo+"相隔"+days+"天");      
		 }
		
		

}
