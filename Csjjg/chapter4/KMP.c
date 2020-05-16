#include<stdio.h>
#include <stdlib.h>
#include<string.h>
//子串的最长匹配序列
void profix_table(char pattern[],int profix[],int n)
{
    profix[0] = 0;//单个元素的前后相似匹配为0
    int len =0;
    int i = 1;
    while (i<n)
    {
        if (pattern[i] == pattern[len] )//第i+1个子串的len个匹配
        {
            len++;
            profix[i] = len;
            i++;//下一步进入第i+2个子串
        }//if未匹配到len位

        else{
            if(len>0){//当len位未匹配到时，向后退一位，继续上一个if，i不变
            len = profix[len-1];
            }
            else{//profix的第一位和子串的最后一位不匹配，继续下一个子串的匹配
                profix[i] = len;//此时len=0
                i++;
            }
        }//else

    }//while
}//profix_table


//将子串最长匹配序列全部向后移动一位，并在第一位上添加-1
void mov_profix-table(int profix[],int n)
{
    int i;
    for(i = n-1; i>0 ;i++)
    {
        profix[i] = profix[i-1];
    }
    profix[0] = -1;
}//mov


//进行匹配
void kmp_search(chae text[],char pattern[])
{
    int n = strlen(pattern);
    int m = strlen(text)
    int *profix = malloc(sizeof(int)*n);
    profix_table(pattern,profix,n);//profix为指针
    mov_profix(profix,n);
    
    //text[i],       len(text) = m
    //pattern[j], len(pattern) = n

    int  i =0;
    int j = 0;
    while(i<m)
    {
        if(j == n-1 && text[i] == pattern[j])//找到子串，并输出子串第一个字符在原字符串中的位置
        {
            printf("found pattern in %d",i-j);
        }

        if(text[i] == pattern[i])//
        {
            i++;
            j++;
        }
        else 
        {
            j = profix[j]//j退回到上一个子串最长匹配地点
            if (j == -1)//子串的第一个字符与text的第i个字符不相匹配，两个字符串直接同时向下移动
            {
                i++;
                j++;
            }
        }//else

    }//while
}//kmp_search


int main()
{
    char text[] = "abecabrcabc";
    char pattern[] = "abc";
    kmp_search(text,pattern);
}//main

