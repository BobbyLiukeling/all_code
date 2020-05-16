package text9;
import java.io.File;
/**
 * Filename: title:
 * 
 * @date 创建时间：2018年4月17日 下午9:04:32
 * @version 1.0
 * @parameter Description:
 * @author Liu Keling 作者 E-mail: 1194380923@qq.com *
 * demand:1.创建类：FindFile.java，遍历当前目录，打印目录中文件名称，目录打印”is Directory”,文件打印“is file”。
 * 修改程序打印当前目录及 子目录信息。 提示：当前目录名用”.”表示 
 * 3.写一个程序,列出某目录下所有的.java 文件(包括子目录)
 *  
 */
public class FindFile {
	public static void main(String[] args) {
		String path = System.getProperty("user.dir");//当前文件绝对路径
		//打当前文件夹下文件及目录
		FindFile file=new FindFile();
		System.out.println("当前目录"+path+"下所有文件：");
		file.getFileName(path);
		//打印指定目录下的java文件
		
		String fileName=path+"\\src\\text7";
		System.out.println();
		System.out.println("指定目录 "+fileName+"下所有java文件");
		file.listJavaFile(fileName);
		
	}

	public void getFileName(String path) {
		File f = new File(path);

		File fa[] = f.listFiles();
		for (int i = 0; i < fa.length; i++) {
			File fs = fa[i];
			if (fs.isDirectory()) {
				System.out.println(fs.getName() + " is Directory");
			} else {
				System.out.println(fs.getName()+"is file");
			}
		}
	}
	
	 public void listJavaFile(String fileName) {  
	        File file = new File(fileName);  
	        if (file.isDirectory()) {  
	            File[] files = file.listFiles();  
	            for (int i = 0; i < files.length; i++) {  
	                String name = files[i].getName();  
	                if (name.trim().toLowerCase().endsWith(".java")) {  
	                    System.out.println(name + "\t");  
	                }  
	                if (files[i].isDirectory()) {  
	                    String path = files[i].getPath();  
	                    listJavaFile(path);  
	                }  
	            }  
	        }  
	    }  
}
