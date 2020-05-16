package text9;

import java.io.Serializable;

/**
* Filename:
* title:
* @date 创建时间：2018年4月17日 下午9:38:19 
* @version 1.0 
* @parameter  
* Description: 
* @author Liu Keling
* 作者 E-mail: 1194380923@qq.com 
*/
public class Student implements Serializable{ 
	
        private String name;  
        private Integer age;  
        private String address;  
        public String getName() {  
            return name;  
        }  
        public void setName(String name) {  
            this.name = name;  
        }  
        public Integer getAge() {  
            return age;  
        }  
        public void setAge(Integer age) {  
            this.age = age;  
        }  
        public String getAddress() {  
            return address;  
        }  
        public void setAddress(String address) {  
            this.address = address;  
        }  
        public Student(String name, Integer age, String address) {  
            super();  
            this.name = name;  
            this.age = age;  
            this.address = address;  
        }  
        @Override  
        public String toString() {  
            return "Student [name=" + name + ", age=" + age + ", address="  
                    + address + "]";  
        } 
        
}
