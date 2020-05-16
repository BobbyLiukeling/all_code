package counter;

import java.util.ArrayList;
import java.util.Scanner;

/**
* Filename:
* title:
* @date 创建时间：2018年6月11日 下午8:00:49 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/
public class lala {
public static void main(String[] args) {
	int num;
	Scanner scanner=new Scanner(System.in);
	num = scanner.nextInt();
	ArrayList list= new ArrayList();
	for (int i = num-1; i >0; i--) {
		if (num%i==0) {
			list.add(i);
			num=i;
			//continue;
		}
	}
	System.out.println("dsgjfl");
	for(Object i:list)
		System.out.println(i);
}

}
