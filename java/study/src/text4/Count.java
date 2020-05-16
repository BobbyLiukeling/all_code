package text4;
import java.lang.Math;
/**
* Filename:
* title:
* @date ����ʱ�䣺2018��3��19�� ����9:08:51 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* ���� E-mail: 1194380923@qq.com 
* demand:����һ����״�ࣨShape�������������ܳ�������������ࣺ�����ࣨRectangle�� ������ķ�����differ���� ���㳤���Բ����
* ��Circle���������ࣨTriangle���������ࣨSquare�� ���ε��������ɼ�����ͬ����״���󣬷���һ�� Shape ���͵�������ֱ���ÿ��
* ��״���ܳ�������������״������һ�����Σ��Ҳ��������Σ�����㳤�� 
*/
public class Count {
	public static void main(String[] args) {
				
		Rectangle rectangle =new Rectangle(3,4);
		Circle circle = new Circle(2);
		Triangle triangle = new Triangle(3,5,4);
		Square square=new Square(3);	
		Shape[] shape = {rectangle, circle,triangle,square};
		
		
		for(int i=0;i<4;i++)
		{
			System.out.println(shape[i].getsum());
			System.out.println(shape[i].getarea());
			System.out.println();
		}
		
	}
}

class Shape {
	public double sum = 0.0;
	public double area = 0.0;
	public double getsum() {
		return 0.0;
	}
	public double getarea() {
		return 0.0;
	}
	
}

class Rectangle extends Shape {
	private double len;
	private double width;
	
	public Rectangle() {}
	public Rectangle(double l,double w) {
		this.len=l;
		this.width =w;
	}
	
	public double getsum() {
		System.out.println("the length of Rectangle");
		return 2*(this.width+this.len);
	}
	
	public double getarea() {
		System.out.println("the area of Rectangle");
		return this.width*this.len;
	}

}

class Circle extends Shape{
	private double radius;
	public Circle(double c) {
		this.radius=c;
	}
	
	
	public double getsum() {
		System.out.println("the length of Circle");
		return Math.PI*2*this.radius;
	}
	
	public  double getarea() {
		System.out.println("the area of circle");
		return Math.PI*this.radius*this.radius;
	}	
	
}

class Triangle extends Shape{
	private double a,b,c;
	public Triangle(double A,double B,double C)
	{
		this.a=A;
		this.b = B;
		this.c = C;
	}
	
	
	public double getsum() {
		System.out.println("the length of Triangle");
		return this.a+this.b+this.c;
	}
	
	/* (non-Javadoc)
	 * @see text4.Shape#area()
	 */
	@Override
	public double getarea() {
		System.out.println("the area of Triangle");
		double len = (this.a+this.b+this.c)/2;
		double area =Math.sqrt(len*(len-this.a)*(len-this.b)*(len-this.c));				
		return area;
	}

}

class Square extends Rectangle{
	private double side;

	public Square(double len) {
		this.side = len;
	}
	
	public double getsum() {
		System.out.println("the length of Squiare");
		return 4*this.side;
	}
	public double getarea() {
		System.out.println("the area of square");
		return this.side*this.side;
	}
}


