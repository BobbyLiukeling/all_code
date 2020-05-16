package text7;

import java.util.Scanner;

/**
 * Filename: title:
 * 
 * @date 创建时间：2018年4月13日 下午4:18:31
 * @version 1.0
 * @parameter Description:
 * @author Liu Keling 作者 E-mail: 1194380923@qq.com
 * demand:. 定义一个矩阵类 Matrix，具有的功能：转置，相加，按行优先存储，按列优先存储，求鞍点等功能。
 * 
 */
public class Matrix {
	Scanner scanner = new Scanner(System.in);
	
	//初始化矩陣
	public int[][] createMatrix(int x,int y) {
		System.out.println("请输入"+x+"*"+y+"列的矩阵数据：");
		int[][] array = new int[x][y];		
		for (int i = 0; i < array.length; i++)
			for (int j = 0; j < array[i].length; j++)
			{
				array[i][j] = scanner.nextInt();
			}
		return array;
	}
	
	// 矩阵输出 
	public void output(int[][] matraix)
	{
		for (int i = 0; i < matraix.length; i++)
		{
			for (int j = 0; j < matraix[i].length; j++)			
				System.out.print(matraix[i][j] + " ");							
			System.out.println();
		}
		System.out.println();
	}	
	
	// 矩阵求和 
	public int[][] addMatrix(int[][] list1, int[][] list2)
	{
		int[][] list3 = new int[list1.length][list1[0].length];
		if (list1.length!=list2.length||list1[0].length!=list2[0].length) 
			System.out.println("这个矩阵格式不符不能相加");
		else
		{
			for (int i = 0; i < list1.length; i++)
				 for (int j = 0; j < list1[0].length; j++)
					 list3[i][j] = list1[i][j] + list2[i][j];
		}
		return list3;
	}
			   
	// 矩阵转置 
	public int[][] transMatrix(int[][] list) { 
		int[][] list6 = new int[list.length][list[0].length];
		for (int i = 0; i < list.length; i++)
		for (int j = 0; j < list[0].length; j++)    
			list6[i][j] = list[j][i]; 
		return list6; 
	} 
		
	//鞍点
	public void SaddlePoint(int[][] list) {
		boolean flag=true;		
		  for(int i=0;i<list.length;i++)  
		    {  
		        int max=list[i][0];/*假设每一行的第一个元素是最大的*/  
		        int maxj=0;/*纪录最大元素的列号*/  
		        for(int j=0;j<list[i].length;j++)/*寻找每一行中最大的元素*/  
		            if(list[i][maxj]<list[i][j])  
		            {  
		                maxj=j;  
		                max=list[i][j];  
		            }  
		        //flag=true;/*标记位，用来标记是否找到鞍点*/  
		        for(int k=0;k<list.length;k++)/*在最大元素的所在列判断该元素是否为最小元素*/  
		        {  
		            if(list[k][maxj]<max)/*如果不是最小的，则跳出最近这个循环*/  
		            {  
		                flag=false;  
		                break;
		            }  
		        }  
		        if(flag)/*如果条件成立，则表明成功找到鞍点*/  
		        {  
		            System.out.println("在第 "+i+" 行 "+maxj+" 列，找到鞍點： "+max); 
		            break;  
		        }  
		  
		    }  
		    if(!flag)  
		        System.out.println("此矩陣沒有鞍點");
	}

	//Main函数测试 
	public static void main(String[] args) { 
		Matrix matrix = new Matrix();
		Scanner input = new Scanner(System.in);
		System.out.println("请输入所要创建第一个矩阵的行数和列数（如：3 3）：");
		int x = input.nextInt();
		int y = input.nextInt(); 
		int[][] list1 =matrix.createMatrix(x, y);// 创建矩阵1 
		System.out.println("请输入所要创建第2个矩阵的行数和列数（如：3 3）：");
		x = input.nextInt();
		y = input.nextInt(); 
		int[][] list2 = matrix.createMatrix(x, y);// 创建矩阵2
		int[][] list3 = matrix.addMatrix(list1, list2); // 矩阵相加
		System.out.println("原矩陣為：");
		matrix.output(list1);
		matrix.output(list2);
		System.out.println("相加后的矩陣為：");
		matrix.output(list3);
		int[][] list4 = matrix.transMatrix(list1);// 矩阵转置
		System.out.println("轉置前的矩陣是：");
		matrix.output(list1);
		System.out.println("轉置后的矩陣是 ：");
		matrix.output(list4);
		matrix.SaddlePoint(list1);
	}

}
