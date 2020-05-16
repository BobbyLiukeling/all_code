package counter;
/**
* Filename:
* title:
* @date 创建时间：2018年5月15日 下午8:57:47 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/
public class compile {
	public static void main(String[] args) {
		//Pattern.compile("([1-9]+[0-9]*|0)(\\.[\\d]+)?").matcher(str).matches();
		String likeType = "23";
		  String pattern = "([1-9]+[0-9]*|0)(\\.[\\d]+)?";
		  String sourceStr = "2.3";
		     System.out.println(sourceStr.matches(pattern)); 
	}
}
