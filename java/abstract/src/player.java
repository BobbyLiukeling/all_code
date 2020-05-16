
/**
* Filename:abstract
* title:player
* @date 创建时间：2017年12月25日 下午12:08:35 
* @version 1.0 
* @parameter  
* Description: 接口类,抽象类
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/

   
	//接口,接口类

	interface play
	{
		int flag=1;
		void playeer();
		void pause();
		void stop();
	}
	
	/**
	 * 抽象类:即不能声场实例的类，不可以生成对象的类，是一个半成品的类
	 */
	abstract class playing
	{
		public void diaplay(Object oPara)
		{
			System.out.println(oPara);
		}
		abstract void winRun();
	}
	
	
	
	public class player extends playing implements play//定义了player继承了playing并且实现了play方法
	{
	    public void playeer() {
	    	diaplay("newPlay.paly()");
	    }
		public void pause() {
			diaplay("newPlay.pause()");
		}
		public void stop() {
			diaplay("newPlay.stop()");
		}
	    void winRun()
	    {
	    	diaplay("newPlay.winRun()");
	    }
	
	public static void main(String[] args) {
		player p=new player();
		p.playeer();
		p.pause();
		p.stop();
		p.winRun();
	}
	

	
}
