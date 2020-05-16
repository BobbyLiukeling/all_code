package text8;

import java.util.HashMap;
import java.util.Map;

/**
* Filename:
* title:
* @date 创建时间：2018年4月17日 下午12:45:56 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/
public class Print_Song {
	public void print_map(Map<String,String> map) {
		for(Map.Entry<String, String>entry : map.entrySet())
		{
			System.out.print(entry.getKey() + ":" + entry.getValue()+"   "); 
		}
		System.out.println();
	}
}
