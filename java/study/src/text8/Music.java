package text8;
/**
* Filename:
* title:
* @date 创建时间：2018年4月16日 下午4:46:36 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
* demand: 系统中的对象
歌曲(Song.java)：
 编号、歌名、语言（中文/英文）、类别（流行/通俗）、歌手
 系统功能描述
对已有的曲目进行管理:
查找歌曲信息(按歌名\语言\歌手\类别等进行查询)
增加歌曲
删除某歌曲
 技术要求
 List/Map

*/
public class Music {
	private String number;
	private String song_name;
	private String song_lauage;
	private String song_type;
	private String singer;
	/**
	 * 初始化
	 */
	public Music(String num,String name,String lauage,String type,String singeer) {
		number = num;
		song_lauage = lauage;
		song_name = name;
		song_type = type;
		singer = singeer;
	}
	
	public String getNum() {
		return ""+number;
	}
	public String getName() {
		return song_name;
	}
	public String getLauage() {
		return song_lauage;
	}
	public String getType() {
		return song_type;
	}
	public String getSinger() {
		return singer;
	}

}
