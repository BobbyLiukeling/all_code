package text8;

import java.util.HashMap;
import java.util.Map;

/**
* Filename:
* title:
* @date 创建时间：2018年4月17日 下午1:10:35 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/
public class Find_Manager {
	Print_Song print_Song=new Print_Song();
	public void found_by_name(Map<Integer, Map<String, String>> maps,String check,int len,String keyword)
	{
		boolean b=false;
		Map<Integer, Map<String, String>> maps1= new HashMap<Integer, Map<String, String>>();//maps1装载查找的的元素
		int count=1;
		for(int i=0;i<len;i++)
		{
			String date=maps.get(i).get(keyword);
			if(check.equals(date))
			{
				maps1.put(count, maps.get(i));
				count++;
				b=true;
			}
		}
		if (b==false) {
			System.out.println("没有找到相关歌曲信息");
		}
		else
		{
			System.out.println("根据"+check+"信息，找到你要的歌曲："+(count-1)+"首");
			for(int i=1;i<count;i++)
			{
				print_Song.print_map(maps1.get(i));
			}
		}
	}
	
	public String choice(int key) {
		if(key==1)
		{return "name";}
		if(key==2)
		{return "lauage";}
		if (key==3) {
			return "singer";
		}
		if(key==4)
		{
			return "type";
		}
		else
			return null;
	}
}
