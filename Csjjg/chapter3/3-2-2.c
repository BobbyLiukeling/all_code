/* 
对于输入的任意一个字符串，检验括号是否配对 
（限于()、[]）
2019.05.04  
*/
typedef char SElemType;
 #include"c1.h"
 #include"c3-1.h"
 #include"bo3-1.c"

//对于输入的字符串检验括号是否成对出现
void check()
{
    SqStack s;
    SElemType ch[80],*p,e;
    if(InitStack(&s))//初始化栈成功
    {
        printf("请输入表达式\n");
        gets(ch);
        p = ch;
        while(*p)//遍历*P
        {
            switch(*p)
            {
                case '(':
                case'[':
                    Push(&s,*p++);
                    break;
                case ')':
                case ']':
                    if(!StackEmpty(s))//当栈不为空
                    {
                        Pop(&s,&e);//弹出栈顶元素
                        if(*p==)
                    }
            }
        }
    }
}