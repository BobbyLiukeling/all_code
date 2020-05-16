package text4;

import java.sql.Date;
import java.util.Scanner;

/**
* Filename:
* title:
* @date 创建时间：2018年3月24日 下午2:36:57 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*demand:
*某公司的雇员分为以下若干类：
Employee：这是所有员工总的父类，属性：员工的生日月份。方法：getSalary(int month) 根
据参数月份来确定工资，如果该月员工过生日，则公司会额外奖励 100 元。
SalariedEmployee：Employee 的子类，拿固定工资的员工。属性：月薪
HourlyEmployee：Employee 的子类，按小时拿工资的员工，每月工作超出 160 小时的部分
按照 1.5 倍工资发放。属性：每小时的工资、每月工作的小时数 SalesEmployee：Employee
的子 类，销售 人员，工资由 月销售额 和提成率决定 。属性： 月销售额、提 成率
BasePlusSalesEmployee：SalesEmployee 的子类，有固定底薪的销售人员，工资由底薪加上
销售提成部分。属性：底薪。
写一个程序，把若干各种类型的员工放在一个 Employee 数组里，写一个函数，打印出某月
每个员工的工资数额。注意：不允许非私有化属性。
*/
public class Work {
	public static void main(String[] args) {
		Employee employee[] = new Employee[4];
		employee[0] = new SalariedEmployee(1,"A",3000);
		employee[1] = new HourlyEmployee(3, "B", 190, 15);
		employee[2] = new SalesEmployee(8, "C", 100000, (float)0.035);
		employee[3] = new BasePlusSalesEmployee(11, "D", 100000, (float)0.022, 2000);
	
		System.out.println("请输入现在的月份：");
		Scanner scanner = new Scanner(System.in);
		int month = scanner.nextInt();
		for(int i = 0;i<4;i++)
		{
			
			System.err.println("this is "+employee[i].getname()+" salary:  "+employee[i].getSalary(month));
			System.out.println();
			
		}
	}
	
}

class Employee{
	private int month;
	private String name;
	public String getname() {
		return this.name;
	}
	public Employee(int month,String name){
		this.name = name;
		this.month = month;		
	}
	
	public float getSalary(int month) {
		if (month == this.month)
			return 100;
		else
			return 0;
	}	
}

class SalariedEmployee extends Employee{
	private int salary;
	public SalariedEmployee(int month,String name, int salary){		
		super(month,name);
		this.salary = salary;	
	}
	
	public float getSalary(int month) {
		return this.salary + super.getSalary(month);	
	}
}

class HourlyEmployee extends Employee{
	private int hour;
	private int price;
	public HourlyEmployee(int month,String name,int hour,int price){		
		super(month,name);
		this.hour = hour;
		this.price = price;
	}
	
	public float getSalary(int month) {
		if(this.hour<=160)
		{
			return this.hour*this.price + super.getSalary(month);
		}
		else
		{
			return (int)1.5*(this.hour-160)*this.price + 160*this.price+super.getSalary(month);
		}
	}
}

class SalesEmployee extends Employee{
	private int sum;
	private float percent;
	public SalesEmployee(int month,String name, int sum,float percent){		
		super(month,name);
		this.sum = sum;
		this.percent = percent;
	}
	
	public float getSalary(int month) {
		return this.sum*this.percent+super.getSalary(month);		
	}
}

class BasePlusSalesEmployee extends SalesEmployee{
	private int s;
	public BasePlusSalesEmployee(int month,String name, int sum,float percent,int salary) {
		super(month, name, sum, percent);
		this.s= salary;
	}
	
	public float getSalary(int month) {
		return this.s+super.getSalary(month);
	}
	
}
