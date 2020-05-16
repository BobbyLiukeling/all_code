package text8;

import java.util.HashMap;
import java.util.Map;

/**
* Filename:
* title:
* @date 创建时间：2018年4月17日 下午5:07:39 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/
public class Class_into_Map {
	public Map<Integer, Map<String, String>> transClass(Music[] musics) {
		int len = musics.length;
		
		Map<Integer, Map<String, String>> maps=new HashMap<Integer, Map<String, String>>();
		for (int i = 0; i < len; i++) {// 将数据压入map和数组中
			Map<String, String> map = new HashMap<String, String>();
			map.put("num", musics[i].getNum());
			map.put("name", musics[i].getName());
			map.put("lauage", musics[i].getLauage());
			map.put("type", musics[i].getType());
			map.put("singer", musics[i].getSinger());
			maps.put(i,map);
		}
		return maps;
	}

}
