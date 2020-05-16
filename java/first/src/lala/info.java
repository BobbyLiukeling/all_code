package lala;
import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.Scanner;
public class info {
	public int getA() {
		return a;
	}
	public void setA(int a) {
		this.a = a;
	}
	private int a;
	public static void main(String[] args) {
		int[] arr1= {25,48,21,11,87,34,16}; 
		int[] arr2=new int[4];
		
		Arrays.fill(arr2, 5);
		for (int i = 0; i < arr2.length; i++) {
			System.out.println(arr2[i]);
		}		
		Arrays.sort(arr1);
		System.out.println("16是否存在"+Arrays.binarySearch(arr1, 16));
		int sum=0;
		for(int a:arr1){
			sum+=a;
			System.out.println(a);
		}
		System.out.println("总数和为"+sum);
		System.out.println();
		
	}
	
	
}
