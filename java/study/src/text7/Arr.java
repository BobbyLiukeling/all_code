package text7;

import java.lang.reflect.Array;
import java.util.Arrays;

/**
 * Filename: title:
 * 
 * @date 创建时间：2018年3月26日 下午8:09:51
 * @version 1.0
 * @parameter Description:
 * @author Liu Keling 作者 E-mail: 1194380923@qq.com 
 * demand:1. 数组拷贝 CopyArray.java 定义数组 int[] a = { 1，2， 3， 4，5， 6， 7， 8，9，10 }和 b。 
 * （1）将数组 a 中的所以元素拷贝到数组 b 中,打印 b 中元素。（用循环实现） 结果参考： 1，2，3，4，5，6，7，8，9， 
 * （2）将数组 a 中从第 3 个元素起连续 5 个元素拷贝到数组 b 中,打印 b 中的元素（用 api 中 提供的数组拷贝方法实现）
 *  结果参考： 3，4，5，6，7 2. 排序 UpSort.java 定义一个数组，例如 int[] a = { 5, 4, 9, 2, 7 } 将数组中的元素按升序排列。(可以用sort 方法实现) 。
 * 
 */
public class Arr {
	public void copyArray(int[] a) {
		int len = a.length;
		int[] b = new int[len];
		for (int i = 0; i < len; i++) {
			b[i] = a[i];
		}
		System.out.println("b中的元素为：");
		for (int i : b) {
			System.out.print(i + "  ");
		}

		System.out.println();
		System.out.println("a中3-8元素即现在b中元素为：");
		for (int i = 0; i < 6; i++) {
			b[i] = a[i + 2];
			System.out.print(b[i] + " ");
		}
	}

	public int[] sortArr(int[] a) {
		Arrays.sort(a);
		return a;
	}

	public void print_Arr(int[] a) {
		for (Object i : a) {
			System.out.print(i + "  ");
		}
		System.out.println();
	}

	public static void main(String[] args) {
		Arr arr = new Arr();
		int[] a = { 1, 44, 3, 12, 5, 10, 7, 59, 9, 140 };
		arr.copyArray(a);
		System.out.println();
		System.out.println("排序前的数组a:");
		arr.print_Arr(a);
		arr.sortArr(a);
		System.out.println("排序后的数组a:");
		arr.print_Arr(a);

	}
}
