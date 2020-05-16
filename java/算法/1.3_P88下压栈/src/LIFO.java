import java.awt.event.ItemEvent;
import java.util.Iterator;
import java.util.Stack;

/**
* Filename:LIFO
* title:LIFO
* @date 创建时间：2018年1月3日 下午5:04:21 
* @version 1.0 
* @parameter  
* Description: 下压栈，能动态调节数组大小的栈
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/


public class LIFO {
	public class ResizingArrayStack<Item> implements Iterable<Item>{
	    private Item[] a = (Item[]) new Object[1];//栈元素
	    private int N = 0;//元素数量

	    public boolean isEmpty(){
	        return N == 0;  
	    }
	    public int size(){
	        return N;
	    }
	    private void resize(int max){
	        Item[] temp = (Item[]) new Object[max];
	        for(int i = 0;i <N;i++)
	            temp[i] = a[i];
	        a = temp;
	    }
	    public void push(Item item){
	        if(N == a.length)
	            resize(2*N);
	        a[N++] = item;
	    }
	    public Item pop(){
	        Item item = a[--N];
	        a[N] = null;//避免游离对象
	        if(N > 0 && N == a.length/4)
	            resize(a.length/2); 
	        return item;
	    }
	    public Iterator<Item> iterator(){
	        return new ReserveArrayIterator();
	    }
	    private class ReserveArrayIterator implements Iterator<Item>{
	        private int i = N;
	       
	        public boolean hasNext(){
	            return i > 0;
	        }
	        public Item next(){
	            return a[--i];
	        }
	        public void remove(){

	        }                                                                                                                                                                                                                                                                                                                                                                                                                   
	    }
	}
	
	
	
}
