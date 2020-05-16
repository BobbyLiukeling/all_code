F:\GitHubCode\Code\Csjjg\严蔚敏《数据结构》的全部代码实现（C语言）\ch1
**********algo1-2.c**********
 /* algo1-2.cpp 计算1-1/x+1/x*x…的更快捷的算法 */
 #include<stdio.h>
 #include<sys/timeb.h>
 void main()
 {
   struct timeb t1,t2;
   long t=0;
   double x,sum1=1,sum=1;
   int i,n;
   printf("请输入x n: ");
   scanf("%lf%d",&x,&n);
   ftime(&t1); /* 求得当前时间 */
   for(i=1;i<=n;i++)
   {
     sum1=-sum1/x;
     sum+=sum1;
   }
   ftime(&t2); /* 求得当前时间 */
   t=(t2.time-t1.time)*1000+(t2.millitm-t1.millitm); /* 计算时间差 */
   printf("sum=%lf 用时%ld毫秒\n",sum,t);
 }

**********Bo1-1.c**********
 /* bo1-1.c 抽象数据类型Triplet和ElemType(由c1-1.h定义)的基本操作(8个) */
 Status InitTriplet(Triplet *T,ElemType v1,ElemType v2,ElemType v3)
 { /* 操作结果:构造三元组T,依次置T的三个元素的初值为v1,v2和v3 */
   *T=(ElemType *)malloc(3*sizeof(ElemType));
   if(!*T)
     exit(OVERFLOW);
   (*T)[0]=v1,(*T)[1]=v2,(*T)[2]=v3;
   return OK;
 }

 Status DestroyTriplet(Triplet *T)
 { /* 操作结果：三元组T被销毁 */
   free(*T);
   *T=NULL;
   return OK;
 }

 Status Get(Triplet T,int i, ElemType *e)
 { /* 初始条件：三元组T已存在，1≤i≤3。操作结果：用e返回T的第i元的值 */
   if(i<1||i>3)
     return ERROR;
   *e=T[i-1];
   return OK;
 }

 Status Put(Triplet T,int i,ElemType e)
 { /* 初始条件：三元组T已存在，1≤i≤3。操作结果：改变T的第i元的值为e */
   if(i<1||i>3)
     return ERROR;
   T[i-1]=e;
   return OK;
 }

 Status IsAscending(Triplet T)
 { /* 初始条件：三元组T已存在。操作结果：如果T的三个元素按升序排列，返回1，否则返回0 */
   return(T[0]<=T[1]&&T[1]<=T[2]);
 }

 Status IsDescending(Triplet T)
 { /* 初始条件：三元组T已存在。操作结果：如果T的三个元素按降序排列，返回1，否则返回0 */
   return(T[0]>=T[1]&&T[1]>=T[2]);
 }

 Status Max(Triplet T,ElemType *e)
 { /* 初始条件：三元组T已存在。操作结果：用e返回T的三个元素中的最大值 */
   *e=T[0]>=T[1]?T[0]>=T[2]?T[0]:T[2]:T[1]>=T[2]?T[1]:T[2];
   return OK;
 }

 Status Min(Triplet T,ElemType *e)
 { /* 初始条件：三元组T已存在。操作结果：用e返回T的三个元素中的最小值 */
   *e=T[0]<=T[1]?T[0]<=T[2]?T[0]:T[2]:T[1]<=T[2]?T[1]:T[2];
   return OK;
 }

**********c1-1.h**********
 /* c1-1.h 采用动态分配的顺序存储结构 */
 typedef ElemType *Triplet; /* 由InitTriplet分配三个元素存储空间 */
 /* Triplet类型是ElemType类型的指针，存放ElemType类型的地址 */

**********c1.h**********
 /* c1.h (程序名) */
 #include<string.h>
 #include<ctype.h>
 #include<malloc.h> /* malloc()等 */
 #include<limits.h> /* INT_MAX等 */
 #include<stdio.h> /* EOF(=^Z或F6),NULL */
 #include<stdlib.h> /* atoi() */
 #include<io.h> /* eof() */
 #include<math.h> /* floor(),ceil(),abs() */
 #include<process.h> /* exit() */
 /* 函数结果状态代码 */
 #define TRUE 1
 #define FALSE 0
 #define OK 1
 #define ERROR 0
 #define INFEASIBLE -1
 /* #define OVERFLOW -2 因为在math.h中已定义OVERFLOW的值为3,故去掉此行 */
 typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
 typedef int Boolean; /* Boolean是布尔类型,其值是TRUE或FALSE */

**********f.c**********
 /* f.c 用函数指针代替C++的引用参数 */
 #include<stdio.h>
 void fa(int a) /* 在函数中改变a，将不会带回主调函数(主调函数中的a仍是原值) */
 {
   a=5;
   printf("在函数fa中：a=%d\n",a);
 }

 void fb(int *a) /* a为指针类型，在函数中改变*a，改变后的值将带回主调函数 */
 {
   *a=5;
   printf("在函数fb中：*a=%d\n",*a);
 }

 void main()
 {
   int n=1;
   printf("在主程中，调用函数fa之前：n=%d\n",n);
   fa(n);
   printf("在主程中，调用函数fa之后,调用函数fb之前：n=%d\n",n);
   fb(&n); /* 实参为n的地址 */
   printf("在主程中，调用函数fb之后：n=%d\n",n);
 }

**********main1-1.c**********
 /* main1-1.c 检验基本操作bo1-1.c的主函数 */
 #include"c1.h" /* 要将程序中所有#include命令所包含的文件拷贝到当前目录下 */
 /* 以下2行可根据需要选用一个（且只能选用一个），而不需改变基本操作bo1-1.c */
 typedef int ElemType; /* 定义抽象数据类型ElemType在本程序中为整型 */
 /*typedef double ElemType; /* 定义抽象数据类型ElemType在本程序中为双精度型 */
 #include"c1-1.h" /* 在此命令之前要定义ElemType的类型 */
 #include"bo1-1.c" /* 在此命令之前要包括c1-1.h文件（因为其中定义了Triplet） */
 void main()
 {
   Triplet T;
   ElemType m;
   Status i;
   i=InitTriplet(&T,5,7,9);
 /*i=InitTriplet(&T,5.0,7.1,9.3); /* 当ElemType为双精度型时,可取代上句 */
   printf("调用初始化函数后，i=%d(1:成功) T的三个值为：%d %d %d\n",i,T[0],T[1],T[2]); /* 当ElemType的类型变化时，要相应改变printf()的格式符。 */
   i=Get(T,2,&m);
   if(i==OK)
     printf("T的第2个值为：%d\n",m);
   i=Put(T,2,6);
   if(i==OK)
     printf("将T的第2个值改为6后，T的三个值为：%d %d %d\n",T[0],T[1],T[2]);
   i=IsAscending(T); /* 此类函数实参与ElemType的类型无关,当ElemType的类型变化时,实参不需改变 */
   printf("调用测试升序的函数后，i=%d(0:否 1:是)\n",i);
   i=IsDescending(T);
   printf("调用测试降序的函数后，i=%d(0:否 1:是)\n",i);
   if((i=Max(T,&m))==OK) /* 先赋值再比较 */
     printf("T中的最大值为：%d\n",m);
   if((i=Min(T,&m))==OK)
     printf("T中的最小值为：%d\n",m);
   DestroyTriplet(&T); /* 函数也可以不带回返回值 */
   printf("销毁T后，T=%u(NULL)\n",T);
 }

F:\GitHubCode\Code\Csjjg\严蔚敏《数据结构》的全部代码实现（C语言）\ch1\Debug
F:\GitHubCode\Code\Csjjg\严蔚敏《数据结构》的全部代码实现（C语言）\ch10
**********alg10-11.c**********
 /* alg10-11.c 链式基数排序 */
 typedef int InfoType; /* 定义其它数据项的类型 */
 typedef int KeyType; /* 定义RedType类型的关键字为整型 */
 typedef struct
 {
   KeyType key; /* 关键字项 */
   InfoType otherinfo; /* 其它数据项 */
 }RedType; /* 记录类型(同c10-1.h) */
 typedef char KeysType; /* 定义关键字类型为字符型 */
 #include"c1.h"
 #include"c10-3.h"
 void InitList(SLList *L,RedType D[],int n)
 { /* 初始化静态链表L（把数组D中的数据存于L中） */
   char c[MAX_NUM_OF_KEY],c1[MAX_NUM_OF_KEY];
   int i,j,max=D[0].key; /* max为关键字的最大值 */
   for(i=1;i<n;i++)
     if(max<D[i].key)
       max=D[i].key;
   (*L).keynum=(int)(ceil(log10(max)));
   (*L).recnum=n;
   for(i=1;i<=n;i++)
   {
     (*L).r[i].otheritems=D[i-1].otherinfo;
     itoa(D[i-1].key,c,10); /* 将10进制整型转化为字符型,存入c */
     for(j=strlen(c);j<(*L).keynum;j++) /* 若c的长度<max的位数,在c前补'0' */
     {
       strcpy(c1,"0");
       strcat(c1,c);
       strcpy(c,c1);
     }
     for(j=0;j<(*L).keynum;j++)
       (*L).r[i].keys[j]=c[(*L).keynum-1-j];
   }
 }

 int ord(char c)
 { /* 返回k的映射(个位整数) */
   return c-'0';
 }

 void Distribute(SLCell r[],int i,ArrType f,ArrType e) /* 算法10.15 */
 { /* 静态键表L的r域中记录已按(keys[0],...,keys[i-1])有序。本算法按 */
   /* 第i个关键字keys[i]建立RADIX个子表,使同一子表中记录的keys[i]相同。 */
   /* f[0..RADIX-1]和e[0..RADIX-1]分别指向各子表中第一个和最后一个记录 */
   int j,p;
   for(j=0;j<RADIX;++j)
     f[j]=0; /* 各子表初始化为空表 */
   for(p=r[0].next;p;p=r[p].next)
   {
     j=ord(r[p].keys[i]); /* ord将记录中第i个关键字映射到[0..RADIX-1] */
     if(!f[j])
       f[j]=p;
     else
       r[e[j]].next=p;
     e[j]=p; /* 将p所指的结点插入第j个子表中 */
   }
 }

 int succ(int i)
 { /* 求后继函数 */
   return ++i;
 }

 void Collect(SLCell r[],ArrType f,ArrType e)
 { /* 本算法按keys[i]自小至大地将f[0..RADIX-1]所指各子表依次链接成 */
   /* 一个链表，e[0..RADIX-1]为各子表的尾指针。算法10.16 */
   int j,t;
   for(j=0;!f[j];j=succ(j)); /* 找第一个非空子表，succ为求后继函数 */
   r[0].next=f[j];
   t=e[j]; /* r[0].next指向第一个非空子表中第一个结点 */
   while(j<RADIX-1)
   {
     for(j=succ(j);j<RADIX-1&&!f[j];j=succ(j)); /* 找下一个非空子表 */
     if(f[j])
     { /* 链接两个非空子表 */
       r[t].next=f[j];
       t=e[j];
     }
   }
   r[t].next=0; /* t指向最后一个非空子表中的最后一个结点 */
 }

 void printl(SLList L)
 { /* 按链表输出静态链表 */
   int i=L.r[0].next,j;
   while(i)
   {
     for(j=L.keynum-1;j>=0;j--)
       printf("%c",L.r[i].keys[j]);
     printf(" ");
     i=L.r[i].next;
   }
 }

 void RadixSort(SLList *L)
 { /* L是采用静态链表表示的顺序表。对L作基数排序，使得L成为按关键字 */
   /* 自小到大的有序静态链表，L.r[0]为头结点。算法10.17 */
   int i;
   ArrType f,e;
   for(i=0;i<(*L).recnum;++i)
     (*L).r[i].next=i+1;
   (*L).r[(*L).recnum].next=0; /* 将L改造为静态链表 */
   for(i=0;i<(*L).keynum;++i)
   { /* 按最低位优先依次对各关键字进行分配和收集 */
     Distribute((*L).r,i,f,e); /* 第i趟分配 */
     Collect((*L).r,f,e); /* 第i趟收集 */
     printf("第%d趟收集后:\n",i+1);
     printl(*L);
     printf("\n");
   }
 }

 void print(SLList L)
 { /* 按数组序号输出静态链表 */
   int i,j;
   printf("keynum=%d recnum=%d\n",L.keynum,L.recnum);
   for(i=1;i<=L.recnum;i++)
   {
     printf("keys=");
     for(j=L.keynum-1;j>=0;j--)
       printf("%c",L.r[i].keys[j]);
     printf(" otheritems=%d next=%d\n",L.r[i].otheritems,L.r[i].next);
   }
 }

 void Sort(SLList L,int adr[]) /* 改此句(类型) */
 { /* 求得adr[1..L.length]，adr[i]为静态链表L的第i个最小记录的序号 */
   int i=1,p=L.r[0].next;
   while(p)
   {
     adr[i++]=p;
     p=L.r[p].next;
   }
 }

 void Rearrange(SLList *L,int adr[]) /* 改此句(类型) */
 { /* adr给出静态链表L的有序次序，即L.r[adr[i]]是第i小的记录。 */
   /* 本算法按adr重排L.r，使其有序。算法10.18(L的类型有变) */
   int i,j,k;
   for(i=1;i<(*L).recnum;++i) /* 改此句(类型) */
     if(adr[i]!=i)
     {
       j=i;
       (*L).r[0]=(*L).r[i]; /* 暂存记录(*L).r[i] */
       while(adr[j]!=i)
       { /* 调整(*L).r[adr[j]]的记录到位直到adr[j]=i为止 */
         k=adr[j];
         (*L).r[j]=(*L).r[k];
         adr[j]=j;
         j=k; /* 记录按序到位 */
       }
       (*L).r[j]=(*L).r[0];
       adr[j]=j;
     }
 }

 #define N 10
 void main()
 {
   RedType d[N]={{278,1},{109,2},{63,3},{930,4},{589,5},{184,6},{505,7},{269,8},{8,9},{83,10}};
   SLList l;
   int *adr;
   InitList(&l,d,N);
   printf("排序前(next域还没赋值):\n");
   print(l);
   RadixSort(&l);
   printf("排序后(静态链表):\n");
   print(l);
   adr=(int*)malloc((l.recnum)*sizeof(int));
   Sort(l,adr);
   Rearrange(&l,adr);
   printf("排序后(重排记录):\n");
   print(l);
 }

**********Algo10-1.c**********
 /* algo10-1.c 检验bo10-1.c的程序 */
 #include"c1.h"
 typedef int InfoType; /* 定义其它数据项的类型 */
 #include"c9.h"
 #include"c10-1.h"
 #include"bo10-1.c"
 void print(SqList L)
 {
   int i;
   for(i=1;i<=L.length;i++)
     printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
   printf("\n");
 }

 #define N 8
 void main()
 {
   RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
   SqList l1,l2,l3;
   int i;
   for(i=0;i<N;i++) /* 给l1.r赋值 */
     l1.r[i+1]=d[i];
   l1.length=N;
   l2=l3=l1; /* 复制顺序表l2、l3与l1相同 */
   printf("排序前:\n");
   print(l1);
   InsertSort(&l1);
   printf("直接插入排序后:\n");
   print(l1);
   BInsertSort(&l2);
   printf("折半插入排序后:\n");
   print(l2);
   P2_InsertSort(&l3);
   printf("2_路插入排序后:\n");
   print(l3);
 }

**********Algo10-2.c**********
 /* algo10-2.c 静态链表 */
 #include"c1.h"
 typedef int InfoType; /* 定义其它数据项的类型 */
 #include"c10-2.h"
 void TableInsert(SLinkListType *SL,RedType D[],int n)
 { /* 由数组D建立n个元素的表插入排序的静态链表SL */
   int i,p,q;
   (*SL).r[0].rc.key=INT_MAX; /* 表头结点记录的关键字取最大整数(非降序链表的表尾) */
   (*SL).r[0].next=0; /* next域为0表示表尾(现为空表，初始化) */
   for(i=0;i<n;i++)
   {
     (*SL).r[i+1].rc=D[i]; /* 将数组D的值赋给静态链表SL */
     q=0;
     p=(*SL).r[0].next;
     while((*SL).r[p].rc.key<=(*SL).r[i+1].rc.key)
     { /* 静态链表向后移 */
       q=p;
       p=(*SL).r[p].next;
     }
     (*SL).r[i+1].next=p; /* 将当前记录插入静态链表 */
     (*SL).r[q].next=i+1;
   }
   (*SL).length=n;
 }

 void Arrange(SLinkListType *SL)
 { /* 根据静态链表SL中各结点的指针值调整记录位置，使得SL中记录按关键字 */
   /* 非递减有序顺序排列 算法10.3 */
   int i,p,q;
   SLNode t;
   p=(*SL).r[0].next; /* p指示第一个记录的当前位置 */
   for(i=1;i<(*SL).length;++i)
   { /* (*SL).r[1..i-1]中记录已按关键字有序排列,第i个记录在SL中的当前位置应不小于i */
     while(p<i)
       p=(*SL).r[p].next; /* 找到第i个记录，并用p指示其在SL中当前位置 */
     q=(*SL).r[p].next; /* q指示尚未调整的表尾 */
     if(p!=i)
     {
       t=(*SL).r[p]; /* 交换记录，使第i个记录到位 */
       (*SL).r[p]=(*SL).r[i];
       (*SL).r[i]=t;
       (*SL).r[i].next=p; /* 指向被移走的记录，使得以后可由while循环找回 */
     }
     p=q; /* p指示尚未调整的表尾，为找第i+1个记录作准备 */
   }
 }

 void Sort(SLinkListType L,int adr[])
 { /* 求得adr[1..L.length]，adr[i]为静态链表L的第i个最小记录的序号 */
   int i=1,p=L.r[0].next;
   while(p)
   {
     adr[i++]=p;
     p=L.r[p].next;
   }
 }

 void Rearrange(SLinkListType *L,int adr[])
 { /* adr给出静态链表L的有序次序，即L.r[adr[i]]是第i小的记录。 */
   /* 本算法按adr重排L.r，使其有序。算法10.18(L的类型有变) */
   int i,j,k;
   for(i=1;i<(*L).length;++i)
     if(adr[i]!=i)
     {
       j=i;
       (*L).r[0]=(*L).r[i]; /* 暂存记录(*L).r[i] */
       while(adr[j]!=i)
       { /* 调整(*L).r[adr[j]]的记录到位直到adr[j]=i为止 */
         k=adr[j];
         (*L).r[j]=(*L).r[k];
         adr[j]=j;
         j=k; /* 记录按序到位 */
       }
       (*L).r[j]=(*L).r[0];
       adr[j]=j;
     }
 }

 void print(SLinkListType L)
 {
   int i;
   for(i=1;i<=L.length;i++)
     printf("key=%d ord=%d next=%d\n",L.r[i].rc.key,L.r[i].rc.otherinfo,L.r[i].next);
 }

 #define N 8
 void main()
 {
   RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
   SLinkListType l1,l2;
   int *adr,i;
   TableInsert(&l1,d,N);
   l2=l1; /* 复制静态链表l2与l1相同 */
   printf("排序前:\n");
   print(l1);
   Arrange(&l1);
   printf("l1排序后:\n");
   print(l1);
   adr=(int*)malloc((l2.length+1)*sizeof(int));
   Sort(l2,adr);
   for(i=1;i<=l2.length;i++)
     printf("adr[%d]=%d ",i,adr[i]);
   printf("\n");
   Rearrange(&l2,adr);
   printf("l2排序后:\n");
   print(l2);
 }

**********algo10-3.c**********
 /* algo10-3.c 希尔排序 */
 #include<stdio.h>
 typedef int InfoType; /* 定义其它数据项的类型 */
 #include"c9.h"
 #include"c10-1.h"
 void ShellInsert(SqList *L,int dk)
 { /* 对顺序表L作一趟希尔插入排序。本算法是和一趟直接插入排序相比， */
   /* 作了以下修改： */
   /* 1.前后记录位置的增量是dk,而不是1; */
   /* 2.r[0]只是暂存单元,不是哨兵。当j<=0时,插入位置已找到。算法10.4 */
   int i,j;
   for(i=dk+1;i<=(*L).length;++i)
     if LT((*L).r[i].key,(*L).r[i-dk].key)
     { /* 需将(*L).r[i]插入有序增量子表 */
       (*L).r[0]=(*L).r[i]; /* 暂存在(*L).r[0] */
       for(j=i-dk;j>0&&LT((*L).r[0].key,(*L).r[j].key);j-=dk)
         (*L).r[j+dk]=(*L).r[j]; /* 记录后移，查找插入位置 */
       (*L).r[j+dk]=(*L).r[0]; /* 插入 */
     }
 }

 void print(SqList L)
 {
   int i;
   for(i=1;i<=L.length;i++)
     printf("%d ",L.r[i].key);
   printf("\n");
 }

 void print1(SqList L)
 {
   int i;
   for(i=1;i<=L.length;i++)
     printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
   printf("\n");
 }

 void ShellSort(SqList *L,int dlta[],int t)
 { /* 按增量序列dlta[0..t-1]对顺序表L作希尔排序。算法10.5 */
   int k;
   for(k=0;k<t;++k)
   {
     ShellInsert(L,dlta[k]); /* 一趟增量为dlta[k]的插入排序 */
     printf("第%d趟排序结果: ",k+1);
     print(*L);
   }
 }

 #define N 10
 #define T 3
 void main()
 {
   RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8},{55,9},{4,10}};
   SqList l;
   int i,dt[T]={5,3,1}; /* 增量序列数组 */
   for(i=0;i<N;i++)
     l.r[i+1]=d[i];
   l.length=N;
   printf("排序前: ");
   print(l);
   ShellSort(&l,dt,T);
   printf("排序后: ");
   print1(l);
 }

**********algo10-4.c**********
 /* algo10-4.c 调用起泡排序(在教科书1.4.3 算法效率的度量中)的程序 */
 #include"c1.h"
 #define N 8
 void bubble_sort(int a[],int n)
 { /* 将a中整数序列重新排列成自小至大有序的整数序列(起泡排序) */
   int i,j,t;
   Status change;
   for(i=n-1,change=TRUE;i>1&&change;--i)
   {
     change=FALSE;
     for(j=0;j<i;++j)
       if(a[j]>a[j+1])
       {
         t=a[j];
         a[j]=a[j+1];
         a[j+1]=t;
         change=TRUE;
       }
   }
 }

 void print(int r[],int n)
 {
   int i;
   for(i=0;i<n;i++)
     printf("%d ",r[i]);
   printf("\n");
 }

 void main()
 {
   int d[N]={49,38,65,97,76,13,27,49};
   printf("排序前:\n");
   print(d,N);
   bubble_sort(d,N);
   printf("排序后:\n");
   print(d,N);
 }

**********algo10-5.c**********
 /* algo10-5.c 调用算法10.6(a)的程序 */
 #include<stdio.h>
 typedef int InfoType; /* 定义其它数据项的类型 */
 #include"c10-1.h"
 int Partition(SqList *L,int low,int high)
 { /* 交换顺序表L中子表L.r[low..high]的记录，使枢轴记录到位， */
   /* 并返回其所在位置，此时在它之前(后)的记录均不大(小)于它。算法10.6(a) */
   RedType t;
   KeyType pivotkey;
   pivotkey=(*L).r[low].key; /* 用子表的第一个记录作枢轴记录 */
   while(low<high)
   { /* 从表的两端交替地向中间扫描 */
     while(low<high&&(*L).r[high].key>=pivotkey)
       --high;
     t=(*L).r[low]; /* 将比枢轴记录小的记录交换到低端 */
     (*L).r[low]=(*L).r[high];
     (*L).r[high]=t;
     while(low<high&&(*L).r[low].key<=pivotkey)
       ++low;
     t=(*L).r[low]; /* 将比枢轴记录大的记录交换到高端 */
     (*L).r[low]=(*L).r[high];
     (*L).r[high]=t;
   }
   return low; /* 返回枢轴所在位置 */
 }

 #include"bo10-2.c"
 #define N 8
 void main()
 {
   RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
   SqList l;
   int i;
   for(i=0;i<N;i++)
     l.r[i+1]=d[i];
   l.length=N;
   printf("排序前:\n");
   print(l);
   QuickSort(&l);
   printf("排序后:\n");
   print(l);
 }

**********Algo10-6.c**********
 /* algo10-6.c 调用算法10.6(b)的程序(算法10.6(a)的改进) */
 #include<stdio.h>
 typedef int InfoType; /* 定义其它数据项的类型 */
 #include"c10-1.h"
 int Partition(SqList *L,int low,int high)
 { /* 交换顺序表L中子表r[low..high]的记录，枢轴记录到位，并返回其 */
   /* 所在位置，此时在它之前（后）的记录均不大（小）于它。算法10.6(b) */
   KeyType pivotkey;
   (*L).r[0]=(*L).r[low]; /* 用子表的第一个记录作枢轴记录 */
   pivotkey=(*L).r[low].key; /* 枢轴记录关键字 */
   while(low< high)
   { /* 从表的两端交替地向中间扫描 */
     while(low<high&&(*L).r[high].key>=pivotkey)
       --high;
     (*L).r[low]=(*L).r[high]; /* 将比枢轴记录小的记录移到低端 */
     while(low<high&&(*L).r[low].key<=pivotkey)
       ++low;
     (*L).r[high]=(*L).r[low]; /* 将比枢轴记录大的记录移到高端 */
   }
   (*L).r[low]=(*L).r[0]; /* 枢轴记录到位 */
   return low; /* 返回枢轴位置 */
 }

 #include"bo10-2.c"
 #define N 8
 void main()
 {
   RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
   SqList l;
   int i;
   for(i=0;i<N;i++)
     l.r[i+1]=d[i];
   l.length=N;
   printf("排序前:\n");
   print(l);
   QuickSort(&l);
   printf("排序后:\n");
   print(l);
 }

**********algo10-7.c**********
 /* algo10-7.c 简单选择排序 */
 #include<stdio.h>
 typedef int InfoType; /* 定义其它数据项的类型 */
 #include"c10-1.h"
 int SelectMinKey(SqList L,int i)
 { /* 返回在L.r[i..L.length]中key最小的记录的序号 */
   KeyType min;
   int j,k;
   k=i; /* 设第i个为最小 */
   min=L.r[i].key;
   for(j=i+1;j<=L.length;j++)
     if(L.r[j].key<min) /* 找到更小的 */
     {
       k=j;
       min=L.r[j].key;
     }
   return k;
 }

 void SelectSort(SqList *L)
 { /* 对顺序表L作简单选择排序。算法10.9 */
   int i,j;
   RedType t;
   for(i=1;i<(*L).length;++i)
   { /*  选择第i小的记录，并交换到位 */
     j=SelectMinKey(*L,i); /* 在L.r[i..L.length]中选择key最小的记录 */
     if(i!=j)
     { /* 与第i个记录交换 */
       t=(*L).r[i];
       (*L).r[i]=(*L).r[j];
       (*L).r[j]=t;
     }
   }
 }

 void print(SqList L)
 {
   int i;
   for(i=1;i<=L.length;i++)
     printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
   printf("\n");
 }

 #define N 8
 void main()
 {
   RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
   SqList l;
   int i;
   for(i=0;i<N;i++)
     l.r[i+1]=d[i];
   l.length=N;
   printf("排序前:\n");
   print(l);
   SelectSort(&l);
   printf("排序后:\n");
   print(l);
 }
**********algo10-8.c**********
 /* algo10-8.c 树形选择排序 */
 #include"c1.h"
 typedef int InfoType; /* 定义其它数据项的类型 */
 #include"c10-1.h"
 void TreeSort(SqList *L)
 { /* 树形选择排序 */
   int i,j,j1,k,k1,l,n=(*L).length;
   RedType *t;
   l=(int)ceil(log(n)/log(2))+1; /* 完全二叉树的层数 */
   k=(int)pow(2,l)-1; /* l层完全二叉树的结点总数 */
   k1=(int)pow(2,l-1)-1; /* l-1层完全二叉树的结点总数 */
   t=(RedType*)malloc(k*sizeof(RedType)); /* 二叉树采用顺序存储结构 */
   for(i=1;i<=n;i++) /* 将L.r赋给叶子结点 */
     t[k1+i-1]=(*L).r[i];
   for(i=k1+n;i<k;i++) /* 给多余的叶子的关键字赋无穷大 */
     t[i].key=INT_MAX;
   j1=k1;
   j=k;
   while(j1)
   { /* 给非叶子结点赋值 */
     for(i=j1;i<j;i+=2)
       t[i].key<t[i+1].key?(t[(i+1)/2-1]=t[i]):(t[(i+1)/2-1]=t[i+1]);
     j=j1;
     j1=(j1-1)/2;
   }
   for(i=0;i<n;i++)
   {
     (*L).r[i+1]=t[0]; /* 将当前最小值赋给L.r[i] */
     j1=0;
     for(j=1;j<l;j++) /* 沿树根找结点t[0]在叶子中的序号j1 */
       t[2*j1+1].key==t[j1].key?(j1=2*j1+1):(j1=2*j1+2);
     t[j1].key=INT_MAX;
     while(j1)
     {
       j1=(j1+1)/2-1; /* 序号为j1的结点的双亲结点序号 */
       t[2*j1+1].key<=t[2*j1+2].key?(t[j1]=t[2*j1+1]):(t[j1]=t[2*j1+2]);
     }
   }
   free(t);
 }

 void print(SqList L)
 {
   int i;
   for(i=1;i<=L.length;i++)
     printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
   printf("\n");
 }

 #define N 8
 void main()
 {
   RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
   SqList l;
   int i;
   for(i=0;i<N;i++)
     l.r[i+1]=d[i];
   l.length=N;
   printf("排序前:\n");
   print(l);
   TreeSort(&l);
   printf("排序后:\n");
   print(l);
 }
**********algo10-9.c**********
 /* algo10-9.c 堆排序 */
 #include<stdio.h>
 typedef int InfoType; /* 定义其它数据项的类型 */
 #include"c9.h"
 #include"c10-1.h"
 typedef SqList HeapType; /* 堆采用顺序表存储表示 */
 void HeapAdjust(HeapType *H,int s,int m) /* 算法10.10 */
 { /* 已知H.r[s..m]中记录的关键字除H.r[s].key之外均满足堆的定义，本函数 */
   /* 调整H.r[s]的关键字,使H.r[s..m]成为一个大顶堆(对其中记录的关键字而言) */
   RedType rc;
   int j;
   rc=(*H).r[s];
   for(j=2*s;j<=m;j*=2)
   { /* 沿key较大的孩子结点向下筛选 */
     if(j<m&&LT((*H).r[j].key,(*H).r[j+1].key))
       ++j; /* j为key较大的记录的下标 */
     if(!LT(rc.key,(*H).r[j].key))
       break; /* rc应插入在位置s上 */
     (*H).r[s]=(*H).r[j];
     s=j;
   }
   (*H).r[s]=rc; /* 插入 */
 }

 void HeapSort(HeapType *H)
 { /* 对顺序表H进行堆排序。算法10.11 */
   RedType t;
   int i;
   for(i=(*H).length/2;i>0;--i) /* 把H.r[1..H.length]建成大顶堆 */
     HeapAdjust(H,i,(*H).length);
   for(i=(*H).length;i>1;--i)
   { /* 将堆顶记录和当前未经排序子序列H.r[1..i]中最后一个记录相互交换 */
     t=(*H).r[1];
     (*H).r[1]=(*H).r[i];
     (*H).r[i]=t;
     HeapAdjust(H,1,i-1); /* 将H.r[1..i-1]重新调整为大顶堆 */
   }
 }

 void print(HeapType H)
 {
   int i;
   for(i=1;i<=H.length;i++)
     printf("(%d,%d)",H.r[i].key,H.r[i].otherinfo);
   printf("\n");
 }

 #define N 8
 void main()
 {
   RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
   HeapType h;
   int i;
   for(i=0;i<N;i++)
     h.r[i+1]=d[i];
   h.length=N;
   printf("排序前:\n");
   print(h);
   HeapSort(&h);
   printf("排序后:\n");
   print(h);
 }
**********bo10-1.c**********
 /* bo10-1.c 顺序表插入排序的函数(3个) */
 void InsertSort(SqList *L)
 { /* 对顺序表L作直接插入排序。算法10.1 */
   int i,j;
   for(i=2;i<=(*L).length;++i)
     if LT((*L).r[i].key,(*L).r[i-1].key) /* "<",需将L.r[i]插入有序子表 */
     {
       (*L).r[0]=(*L).r[i]; /* 复制为哨兵 */
       for(j=i-1;LT((*L).r[0].key,(*L).r[j].key);--j)
	 (*L).r[j+1]=(*L).r[j]; /* 记录后移 */
       (*L).r[j+1]=(*L).r[0]; /* 插入到正确位置 */
     }
 }

 void BInsertSort(SqList *L)
 { /* 对顺序表L作折半插入排序。算法10.2 */
   int i,j,m,low,high;
   for(i=2;i<=(*L).length;++i)
   {
     (*L).r[0]=(*L).r[i]; /* 将L.r[i]暂存到L.r[0] */
     low=1;
     high=i-1;
     while(low<=high)
     { /* 在r[low..high]中折半查找有序插入的位置 */
       m=(low+high)/2; /* 折半 */
       if LT((*L).r[0].key,(*L).r[m].key)
         high=m-1; /* 插入点在低半区 */
       else
         low=m+1; /* 插入点在高半区 */
     }
     for(j=i-1;j>=high+1;--j)
       (*L).r[j+1]=(*L).r[j]; /* 记录后移 */
     (*L).r[high+1]=(*L).r[0]; /* 插入 */
   }
 }

 void P2_InsertSort(SqList *L)
 { /* 2_路插入排序 */
   int i,j,first,final;
   RedType *d;
   d=(RedType*)malloc((*L).length*sizeof(RedType)); /* 生成L.length个记录的临时空间 */
   d[0]=(*L).r[1]; /* 设L的第1个记录为d中排好序的记录(在位置[0]) */
   first=final=0; /* first、final分别指示d中排好序的记录的第1个和最后1个记录的位置 */
   for(i=2;i<=(*L).length;++i)
   { /* 依次将L的第2个～最后1个记录插入d中 */
     if((*L).r[i].key<d[first].key)
     { /* 待插记录小于d中最小值，插到d[first]之前(不需移动d数组的元素) */
       first=(first-1+(*L).length)%(*L).length; /* 设d为循环向量 */
       d[first]=(*L).r[i];
     }
     else if((*L).r[i].key>d[final].key)
     { /* 待插记录大于d中最大值，插到d[final]之后(不需移动d数组的元素) */
       final=final+1;
       d[final]=(*L).r[i];
     }
     else
     { /* 待插记录大于d中最小值，小于d中最大值，插到d的中间(需要移动d数组的元素) */
       j=final++; /* 移动d的尾部元素以便按序插入记录 */
       while((*L).r[i].key<d[j].key)
       {
         d[(j+1)%(*L).length]=d[j];
         j=(j-1+(*L).length)%(*L).length;
       }
       d[j+1]=(*L).r[i];
     }
   }
   for(i=1;i<=(*L).length;i++) /* 把d赋给L.r */
     (*L).r[i]=d[(i+first-1)%(*L).length]; /* 线性关系 */
 }

**********bo10-2.c**********
 /* bo10-2.c 快速排序的函数 */
 void QSort(SqList *L,int low,int high)
 { /* 对顺序表L中的子序列L.r[low..high]作快速排序。算法10.7 */
   int pivotloc;
   if(low<high)
   { /* 长度大于1 */
     pivotloc=Partition(L,low,high); /* 将L.r[low..high]一分为二 */
     QSort(L,low,pivotloc-1); /* 对低子表递归排序，pivotloc是枢轴位置 */
     QSort(L,pivotloc+1,high); /* 对高子表递归排序 */
   }
 }

 void QuickSort(SqList *L)
 { /* 对顺序表L作快速排序。算法10.8 */
   QSort(L,1,(*L).length);
 }

 void print(SqList L)
 {
   int i;
   for(i=1;i<=L.length;i++)
     printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
   printf("\n");
 }
**********C10-1.H**********
 /* c10-1.h 待排记录的数据类型 */
 #define MAXSIZE 20 /* 一个用作示例的小顺序表的最大长度 */
 typedef int KeyType; /* 定义关键字类型为整型 */
 typedef struct
 {
   KeyType key; /* 关键字项 */
   InfoType otherinfo; /* 其它数据项，具体类型在主程中定义 */
 }RedType; /* 记录类型 */

 typedef struct
 {
   RedType r[MAXSIZE+1]; /* r[0]闲置或用作哨兵单元 */
   int length; /* 顺序表长度 */
 }SqList; /* 顺序表类型 */

**********C10-2.H**********
 /* c10-2.h 静态链表类型 */
 #define SIZE 100 /* 静态链表容量 */
 typedef int KeyType; /* 定义关键字类型为整型 */

 typedef struct
 {
   KeyType key; /* 关键字项 */
   InfoType otherinfo; /* 其它数据项，具体类型在主程中定义 */
 }RedType; /* 记录类型 */

 typedef struct
 {
   RedType rc; /* 记录项 */
   int next; /* 指针项 */
 }SLNode; /* 表结点类型 */

 typedef struct
 {
   SLNode r[SIZE]; /* 0号单元为表头结点 */
   int length; /* 链表当前长度 */
 }SLinkListType; /* 静态链表类型 */

**********C10-3.H**********
 /* c10-3.h 基数排序的数据类型 */
 #define MAX_NUM_OF_KEY 8 /* 关键字项数的最大值 */
 #define RADIX 10 /* 关键字基数，此时是十进制整数的基数 */
 #define MAX_SPACE 1000
 typedef struct
 {
   KeysType keys[MAX_NUM_OF_KEY]; /* 关键字 */
   InfoType otheritems; /* 其它数据项 */
   int next;
 }SLCell; /* 静态链表的结点类型 */

 typedef struct
 {
   SLCell r[MAX_SPACE]; /* 静态链表的可利用空间，r[0]为头结点 */
   int keynum; /* 记录的当前关键字个数 */
   int recnum; /*  静态链表的当前长度 */
 }SLList; /* 静态链表类型 */

 typedef int ArrType[RADIX]; /* 指针数组类型 */

F:\GitHubCode\Code\Csjjg\严蔚敏《数据结构》的全部代码实现（C语言）\ch11
**********algo11-2.C**********
 /* algo11-2.c 通过置换－选择排序产生不等长的初始归并段文件 */
 #include"c1.h"
 typedef int InfoType; /* 定义其它数据项的类型 */
 #include"c10-1.h" /* 定义KeyType、RedType及SqList */
 #define MAXKEY INT_MAX
 #define RUNEND_SYMBOL INT_MAX
 #define w 6 /* 内存工作区可容纳的记录个数 */
 #define M 10 /* 设输出M个数据换行 */
 #define N 24 /* 设大文件有N个数据 */

 typedef int LoserTree[w]; /* 败者树是完全二叉树且不含叶子，可采用顺序存储结构 */
 typedef struct
 {
   RedType rec; /* 记录 */
   KeyType key; /* 从记录中抽取的关键字 */
   int rnum; /* 所属归并段的段号 */
 }RedNode,WorkArea[w]; /* 内存工作区，容量为w */

 void Select_MiniMax(LoserTree ls,WorkArea wa,int q) /* 算法11.6 */
 { /* 从wa[q]起到败者树的根比较选择MINIMAX记录，并由q指示它所在的归并段 */
   int p,s,t;
   for(t=(w+q)/2,p=ls[t];t>0;t=t/2,p=ls[t])
     if(wa[p].rnum<wa[q].rnum||wa[p].rnum==wa[q].rnum&&wa[p].key<wa[q].key)
     {
       s=q;
       q=ls[t]; /* q指示新的胜利者 */
       ls[t]=s;
     }
   ls[0]=q;
 }

 void Construct_Loser(LoserTree ls,WorkArea wa,FILE *fi)
 { /* 输入w个记录到内存工作区wa,建得败者树ls,选出关键字最小的记录并由s指示 */
   /* 其在wa中的位置。算法11.7 */
   int i;
   for(i=0;i<w;++i)
     wa[i].rnum=wa[i].key=ls[i]=0; /* 工作区初始化 */
   for(i=w-1;i>=0;--i)
   {
     fread(&wa[i].rec,sizeof(RedType),1,fi); /* 输入一个记录 */
     wa[i].key=wa[i].rec.key; /* 提取关键字 */
     wa[i].rnum=1; /* 其段号为＂1＂ */
     Select_MiniMax(ls,wa,i); /* 调整败者 */
   }
 }

 void get_run(LoserTree ls,WorkArea wa,int rc,int *rmax,FILE *fi,FILE *fo)
 { /* 求得一个初始归并段，fi为输入文件指针，fo为输出文件指针。算法11.5 */
   int q;
   KeyType minimax;
   while(wa[ls[0]].rnum==rc) /* 选得的MINIMAX记录属当前段时 */
   {
     q=ls[0]; /* q指示MINIMAX记录在wa中的位置 */
     minimax=wa[q].key;
     fwrite(&wa[q].rec,sizeof(RedType),1,fo); /* 将刚选得的MINIMAX记录写入输出文件 */
     fread(&wa[q].rec,sizeof(RedType),1,fi); /* 从输入文件读入下一记录(改) */
     if(feof(fi))
     { /* 输入文件结束，虚设记录（属＂rmax+1＂段） */
       wa[q].rnum=*rmax+1;
       wa[q].key=MAXKEY;
     }
     else
     { /* 输入文件非空时 */
       wa[q].key=wa[q].rec.key; /* 提取关键字 */
       if(wa[q].key<minimax)
       { /* 新读入的记录属下一段 */
         *rmax=rc+1;
	 wa[q].rnum=*rmax;
       }
       else /* 新读入的记录属当前段 */
	 wa[q].rnum=rc;
     }
     Select_MiniMax(ls,wa,q); /* 选择新的MINIMAX记录 */
   }
 }

 void Replace_Selection(LoserTree ls,WorkArea wa,FILE *fi,FILE *fo)
 { /* 在败者树ls和内存工作区wa上用置换－选择排序求初始归并段，fi为输入文件 */
   /* (只读文件)指针,fo为输出文件(只写文件)指针,两个文件均已打开。算法11.4 */
   int rc,rmax;
   RedType j;
   j.key=RUNEND_SYMBOL;
   Construct_Loser(ls,wa,fi); /* 初建败者树 */
   rc=rmax=1; /* rc指示当前生成的初始归并段的段号，rmax指示wa中关键字所属初始归并段的最大段号 */
   while(rc<=rmax) /* ＂rc=rmax+1＂标志输入文件的置换－选择排序已完成 */
   {
     get_run(ls,wa,rc,&rmax,fi,fo); /* 求得一个初始归并段 */
     j.otherinfo=rc;
     fwrite(&j,sizeof(RedType),1,fo); /* 将段结束标志写入输出文件 */
     rc=wa[ls[0]].rnum; /* 设置下一段的段号 */
   }
 }

 void print(RedType t)
 {
   printf("(%d,%d)",t.key,t.otherinfo);
 }

 void main()
 {
   RedType b,a[N]={{51,1},{49,2},{39,3},{46,4},{38,5},{29,6},{14,7},{61,8},{15,9},{30,10},{1,11},{48,12},{52,13},{3,14},{63,15},{27,16},{4,17},{13,18},{89,19},{24,20},{46,21},{58,22},{33,23},{76,24}};
   FILE *fi,*fo;
   LoserTree ls;
   WorkArea wa;
   int i,k,j=RUNEND_SYMBOL;
   char s[3],fname[4];
   fo=fopen("ori","wb"); /* 以写的方式打开大文件ori */
   fwrite(a,sizeof(RedType),N,fo); /* 将数组a写入大文件ori */
   fclose(fo);
   fi=fopen("ori","rb"); /* 以读的方式重新打开大文件ori */
   printf("大文件的记录为:\n");
   for(i=1;i<=N;i++)
   {
     fread(&b,sizeof(RedType),1,fi); /* 依次将大文件ori的数据读入b */
     print(b); /* 输出b的内容 */
     if(i%M==0)
       printf("\n");
   }
   printf("\n");
   rewind(fi); /* 使fi的指针重新返回大文件ori的起始位置，以便重新读入内存，产生有序的子文件 */
   fo=fopen("out","wb"); /* 以写的方式打开初始归并段文件out */
   Replace_Selection(ls,wa,fi,fo); /* 用置换－选择排序求初始归并段 */
   fclose(fo);
   fclose(fi);
   fi=fopen("out","rb"); /* 以读的方式重新打开初始归并段文件out */
   printf("初始归并段文件的记录为:\n");
   i=1;
   do
   {
     k=fread(&b,sizeof(RedType),1,fi); /* 依次将大文件out的数据读入b */
     if(k==1)
     {
       print(b); /* 输出b的内容 */
       if(i++%M==0)
         printf("\n");
     }
   }while(k==1);
   printf("\n");
   rewind(fi); /* 使fi的指针重新返回大文件ori的起始位置，以便重新读入内存，产生有序的子文件 */
   k=0;
   while(!feof(fi)) /* 按段输出初始归并段文件out */
   {
     itoa(k,s,10); /* 依次生成文件名f0,f1,… */
     strcpy(fname,"f");
     strcat(fname,s);
     fo=fopen(fname,"wb"); /* 依次以写的方式打开文件f0,f1,… */
     do
     {
       i=fread(&b,sizeof(RedType),1,fi);
       if(i==1) /* fread()调用成功 */
       {
	 fwrite(&b,sizeof(RedType),1,fo); /* 将b写入文件f0,f1,… */
         if(b.key==j) /* 1个归并段结束 */
         {
           k++;
           fclose(fo);
           break;
         }
       }
     }while(i==1);
   };
   fclose(fi);
   printf("共产生%d个初始归并段文件\n",k);
 }

**********algo11-3.C**********
 /* algo11-3.c 将algo11-2.c产生的有序子文件f0,f1,f2归并成1个有序的大文件out */
 #include"c1.h"
 typedef int InfoType; /* 定义其它数据项的类型 */
 #include"c10-1.h" /* 定义KeyType、RedType及SqList */
 #define k 3 /* k路归并 */
 #define M 10 /* 设输出M个数据换行 */
 #include"bo11-1.c"

 void print(RedType t)
 {
   printf("(%d,%d)",t.key,t.otherinfo);
 }

 void main()
 {
   RedType r;
   int i,j;
   char fname[k][4],fout[5]="out",s[3];
   LoserTree ls;
   for(i=0;i<k;i++)
   { /* 依次打开f0,f1,f2,…,k个文件 */
     itoa(i,s,10); /* 生成k个文件名f0,f1,f2,… */
     strcpy(fname[i],"f");
     strcat(fname[i],s);
     fp[i]=fopen(fname[i],"rb"); /* 以读的方式打开文件f0,f1,… */
     printf("有序子文件f%d的记录为:\n",i);
     do
     {
       j=fread(&r,sizeof(RedType),1,fp[i]); /* 依次将f0,f1,…的数据读入r */
       if(j==1)
         print(r); /* 输出r的内容 */
     }while(j==1);
     printf("\n");
     rewind(fp[i]); /* 使fp[i]的指针重新返回f0,f1,…的起始位置，以便重新读入内存 */
   }
   fp[k]=fopen(fout,"wb"); /* 以写的方式打开大文件fout */
   K_Merge(ls,b); /* 利用败者树ls将k个输入归并段中的记录归并到输出归并段，即大文件fout */
   for(i=0;i<=k;i++)
     fclose(fp[i]); /* 关闭文件f0,f1,…和文件fout */
   fp[k]=fopen(fout,"rb"); /* 以读的方式重新打开大文件fout验证排序 */
   printf("排序后的大文件的记录为:\n");
   i=1;
   do
   {
     j=fread(&r,sizeof(RedType),1,fp[k]); /* 将fout的数据读入r */
     if(j==1)
       print(r); /* 输出r的内容 */
     if(i++%M==0)
       printf("\n"); /* 换行 */
   }while(j==1);
   printf("\n");
   fclose(fp[k]); /* 关闭大文件fout */
 }

**********bo11-1.c**********
 /* bo11-1.c k路平衡归并的函数 */
 FILE *fp[k+1]; /* k+1个文件指针(fp[k]为大文件指针)，全局变量 */
 typedef int LoserTree[k]; /* 败者树是完全二叉树且不含叶子，可采用顺序存储结构 */
 typedef RedType ExNode,External[k+1]; /* 外结点,有改变 */
 External b; /* 全局变量 */
 #define MINKEY INT_MIN
 #define MAXKEY INT_MAX

 void input(int i,KeyType *a)
 { /* 从第i个文件(第i个归并段)读入该段当前第1个记录的关键字到外结点 */
   fread(a,sizeof(KeyType),1,fp[i]);
 }

 void output(int i)
 { /* 将第i个文件(第i个归并段)中当前的记录写至输出归并段 */
   ExNode a;
   a.key=b[i].key; /* 当前记录的关键字已读到b[i].key中 */
   fread(&a.otherinfo,sizeof(InfoType),1,fp[i]);
   fwrite(&a,sizeof(ExNode),1,fp[k]);
 }

 void Adjust(LoserTree ls,int s)
 { /* 沿从叶子结点b[s]到根结点ls[0]的路径调整败者树。算法11.2 */
   int i,t;
   t=(s+k)/2; /* ls[t]是b[s]的双亲结点 */
   while(t>0)
   {
     if(b[s].key>b[ls[t]].key)
     {
       i=s;
       s=ls[t]; /* s指示新的胜者 */
       ls[t]=i;
     }
     t=t/2;
   }
   ls[0]=s;
 }

 void CreateLoserTree(LoserTree ls)
 { /* 已知b[0]到b[k-1]为完全二叉树ls的叶子结点，存有k个关键字，沿从叶子 */
   /* 到根的k条路径将ls调整成为败者树。算法11.3 */
   int i;
   b[k].key=MINKEY;
   for(i=0;i<k;++i)
     ls[i]=k; /* 设置ls中“败者”的初值 */
   for(i=k-1;i>=0;--i) /* 依次从b[k-1]，b[k-2]，…，b[0]出发调整败者 */
     Adjust(ls,i);
 }

 void K_Merge(LoserTree ls,External b)
 { /* 利用败者树ls将编号从0到k-1的k个输入归并段中的记录归并到输出归并段。 */
   /* b[0]至b[k-1]为败者树上的k个叶子结点，分别存放k个输入归并段中当前 */
   /* 记录的关键字。算法11.1 */
   int i,q;
   for(i=0;i<k;++i) /* 分别从k个输入归并段读人该段当前第一个记录的关键字到外结点 */
     input(i,&b[i].key);
   CreateLoserTree(ls); /* 建败者树ls，选得最小关键字为b[ls[0]].key */
   while(b[ls[0]].key!=MAXKEY)
   {
     q=ls[0]; /* q指示当前最小关键字所在归并段 */
     output(q); /* 将编号为q的归并段中当前（关键字为b[q].key）的记录写至输出归并段 */
     input(q,&b[q].key); /* 从编号为q的输入归并段中读人下一个记录的关键字 */
     Adjust(ls,q); /* 调整败者树，选择新的最小关键字 */
   }
   output(ls[0]); /* 将含最大关键字MAXKEY的记录写至输出归并段 */
 }

F:\GitHubCode\Code\Csjjg\严蔚敏《数据结构》的全部代码实现（C语言）\ch12
F:\GitHubCode\Code\Csjjg\严蔚敏《数据结构》的全部代码实现（C语言）\ch2
**********ALGO2-1.c**********
 /* algo2-1.c 实现算法2.1的程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-1.h" /* 采用线性表的动态分配顺序存储结构 */
 #include"bo2-1.c" /* 可以使用bo2-1.c中的基本操作 */

 Status equal(ElemType c1,ElemType c2)
 { /* 判断是否相等的函数，Union()用到 */
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 void Union(SqList *La,SqList Lb) /* 算法2.1 */
 { /* 将所有在线性表Lb中但不在La中的数据元素插入到La中 */
   ElemType e;
   int La_len,Lb_len;
   int i;
   La_len=ListLength(*La); /* 求线性表的长度 */
   Lb_len=ListLength(Lb);
   for(i=1;i<=Lb_len;i++)
   {
     GetElem(Lb,i,&e); /* 取Lb中第i个数据元素赋给e */
     if(!LocateElem(*La,e,equal)) /* La中不存在和e相同的元素,则插入之 */
       ListInsert(La,++La_len,e);
   }
 }

 void print(ElemType *c)
 {
   printf("%d ",*c);
 }

 void main()
 {
   SqList La,Lb;
   Status i;
   int j;
   i=InitList(&La);
   if(i==1) /* 创建空表La成功 */
     for(j=1;j<=5;j++) /* 在表La中插入5个元素 */
       i=ListInsert(&La,j,j);
   printf("La= "); /* 输出表La的内容 */
   ListTraverse(La,print);
   InitList(&Lb); /* 也可不判断是否创建成功 */
   for(j=1;j<=5;j++) /* 在表Lb中插入5个元素 */
     i=ListInsert(&Lb,j,2*j);
   printf("Lb= "); /* 输出表Lb的内容 */
   ListTraverse(Lb,print);
   Union(&La,Lb);
   printf("new La= "); /* 输出新表La的内容 */
   ListTraverse(La,print);
 }
**********Algo2-10.c**********
 /* algo2-10.c 两个仅设表尾指针的循环链表的合并（教科书图2.13） */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-2.h"
 #include"bo2-4.c"

 void MergeList_CL(LinkList *La,LinkList Lb)
 {
   LinkList p=Lb->next;
   Lb->next=(*La)->next;
   (*La)->next=p->next;
   free(p);
   *La=Lb;
 }

 void visit(ElemType c)
 {
   printf("%d ",c);
 }

 void main()
 {
   int n=5,i;
   LinkList La,Lb;
   InitList_CL(&La);
   for(i=1;i<=n;i++)
     ListInsert_CL(&La,i,i);
   printf("La="); /* 输出链表La的内容 */
   ListTraverse_CL(La,visit);
   InitList_CL(&Lb);
   for(i=1;i<=n;i++)
     ListInsert_CL(&Lb,1,i*2);
   printf("Lb="); /* 输出链表Lb的内容 */
   ListTraverse_CL(Lb,visit);
   MergeList_CL(&La,Lb);
   printf("La+Lb="); /* 输出合并后的链表的内容 */
   ListTraverse_CL(La,visit);
 }

**********Algo2-11.c**********
 /* algo2-11.c 实现算法2.20、2.21的程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-5.h"
 #include"bo2-6.c"

 Status ListInsert_L(LinkList *L,int i,ElemType e) /* 算法2.20 */
 { /* 在带头结点的单链线性表L的第i个元素之前插入元素e */
   Link h,s;
   if(!LocatePos(*L,i-1,&h))
     return ERROR; /* i值不合法 */
   if(!MakeNode(&s,e))
     return ERROR; /* 结点分配失败 */
   InsFirst(L,h,s); /*对于从第i个结点开始的链表,第i-1个结点是它的头结点 */
   return OK;
 }

 Status MergeList_L(LinkList La,LinkList Lb,LinkList *Lc,int(*compare)(ElemType,ElemType))
 { /* 已知单链线性表La和Lb的元素按值非递减排列。归并La和Lb得到新的单链 */
   /* 线性表Lc，Lc的元素也按值非递减排列。（不改变La、Lb）算法2.21 */
   Link ha,hb,pa,pb,q;
   ElemType a,b;
   if(!InitList(Lc))
     return ERROR; /* 存储空间分配失败 */
   ha=GetHead(La); /* ha和hb分别指向La和Lb的头结点 */
   hb=GetHead(Lb);
   pa=NextPos(ha); /* pa和pb分别指向La和Lb的第一个结点 */
   pb=NextPos(hb);
   while(!ListEmpty(La)&&!ListEmpty(Lb)) /* La和Lb均非空 */
   {
     a=GetCurElem(pa); /* a和b为两表中当前比较元素 */
     b=GetCurElem(pb);
     if(compare(a,b)<=0)
     {
       DelFirst(&La,ha,&q);
       InsFirst(Lc,(*Lc).tail,q);
       pa=NextPos(ha);
     }
     else /* a>b */
     {
       DelFirst(&Lb,hb,&q);
       InsFirst(Lc,(*Lc).tail,q);
       pb=NextPos(hb);
     }
   }
   if(!ListEmpty(La))
     Append(Lc,pa);
   else
     Append(Lc,pb);
   FreeNode(&ha);
   FreeNode(&hb);
   return OK;
 }

 int comp(ElemType c1,ElemType c2)
 {
   return c1-c2;
 }

 void visit(ElemType c)
 {
   printf("%d ",c); /* 整型 */
 }

 void main()
 {
   LinkList La,Lb,Lc;
   int j;
   InitList(&La);
   for(j=1;j<=5;j++)
     ListInsert_L(&La,j,j); /* 顺序插入 1 2 3 4 5 */
   printf("La=");
   ListTraverse(La,visit);
   InitList(&Lb);
   for(j=1;j<=5;j++)
     ListInsert_L(&Lb,j,2*j); /* 顺序插入 2 4 6 8 10 */
   printf("Lb=");
   ListTraverse(Lb,visit);
   InitList(&Lc);
   MergeList_L(La,Lb,&Lc,comp); /* 归并La和Lb，产生Lc */
   printf("Lc=");
   ListTraverse(Lc,visit);
   DestroyList(&Lc);
 }

**********algo2-12.c**********
 /* algo2-12.c 用单链表实现算法2.1,仅有4句与algo2-1.c不同 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-2.h" /* 此句与algo2-1.c不同(因为采用不同的结构) */
 #include"bo2-2.c" /* 此句与algo2-1.c不同(因为采用不同的结构) */

 Status equal(ElemType c1,ElemType c2)
 { /* 判断是否相等的函数，Union()用到 */
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 void Union(LinkList La,LinkList Lb) /* 算法2.1,此句与algo2-1.c不同 */
 { /* 将所有在线性表Lb中但不在La中的数据元素插入到La中 */
   ElemType e;
   int La_len,Lb_len;
   int i;
   La_len=ListLength(La); /* 求线性表的长度 */
   Lb_len=ListLength(Lb);
   for(i=1;i<=Lb_len;i++)
   {
     GetElem(Lb,i,&e); /* 取Lb中第i个数据元素赋给e */
     if(!LocateElem(La,e,equal)) /* La中不存在和e相同的元素,则插入之 */
       ListInsert(La,++La_len,e);
   }
 }

 void print(ElemType c)
 {
   printf("%d ",c);
 }

 void main()
 {
   LinkList La,Lb; /* 此句与algo2-1.c不同(因为采用不同的结构) */
   Status i;
   int j;
   i=InitList(&La);
   if(i==1) /* 创建空表La成功 */
     for(j=1;j<=5;j++) /* 在表La中插入5个元素 */
       i=ListInsert(La,j,j);
   printf("La= "); /* 输出表La的内容 */
   ListTraverse(La,print);
   InitList(&Lb); /* 也可不判断是否创建成功 */
   for(j=1;j<=5;j++) /* 在表Lb中插入5个元素 */
     i=ListInsert(Lb,j,2*j);
   printf("Lb= "); /* 输出表Lb的内容 */
   ListTraverse(Lb,print);
   Union(La,Lb);
   printf("new La= "); /* 输出新表La的内容 */
   ListTraverse(La,print);
 }
**********algo2-13.c**********
 /* algo2-13.c 采用链表结构实现算法2.2的程序，仅有4句与algo2-2.c不同 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-2.h" /* 此句与algo2-2.c不同 */
 #include"bo2-2.c" /* 此句与algo2-2.c不同 */

 void MergeList(LinkList La,LinkList Lb,LinkList *Lc) /* 算法2.2,此句与algo2-2.c不同 */
 { /* 已知线性表La和Lb中的数据元素按值非递减排列。 */
   /* 归并La和Lb得到新的线性表Lc,Lc的数据元素也按值非递减排列 */
   int i=1,j=1,k=0;
   int La_len,Lb_len;
   ElemType ai,bj;
   InitList(Lc); /* 创建空表Lc */
   La_len=ListLength(La);
   Lb_len=ListLength(Lb);
   while(i<=La_len&&j<=Lb_len) /* 表La和表Lb均非空 */
   {
     GetElem(La,i,&ai);
     GetElem(Lb,j,&bj);
     if(ai<=bj)
     {
       ListInsert(*Lc,++k,ai);
       ++i;
     }
     else
     {
       ListInsert(*Lc,++k,bj);
       ++j;
     }
   }
   while(i<=La_len) /* 表La非空且表Lb空 */
   {
     GetElem(La,i++,&ai);
     ListInsert(*Lc,++k,ai);
   }
   while(j<=Lb_len) /* 表Lb非空且表La空 */
   {
     GetElem(Lb,j++,&bj);
     ListInsert(*Lc,++k,bj);
   }
 }

 void print(ElemType c)
 {
   printf("%d ",c);
 }

 void main()
 {
   LinkList La,Lb,Lc; /* 此句与algo2-2.c不同 */
   int j,a[4]={3,5,8,11},b[7]={2,6,8,9,11,15,20};
   InitList(&La); /* 创建空表La */
   for(j=1;j<=4;j++) /* 在表La中插入4个元素 */
     ListInsert(La,j,a[j-1]);
   printf("La= "); /* 输出表La的内容 */
   ListTraverse(La,print);
   InitList(&Lb); /* 创建空表Lb */
   for(j=1;j<=7;j++) /* 在表Lb中插入7个元素 */
     ListInsert(Lb,j,b[j-1]);
   printf("Lb= "); /* 输出表Lb的内容 */
   ListTraverse(Lb,print);
   MergeList(La,Lb,&Lc);
   printf("Lc= "); /* 输出表Lc的内容 */
   ListTraverse(Lc,print);
 }
**********ALGO2-2.c**********
 /* algo2-2.c 实现算法2.2的程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-1.h"
 #include"bo2-1.c"

 void MergeList(SqList La,SqList Lb,SqList *Lc) /* 算法2.2 */
 { /* 已知线性表La和Lb中的数据元素按值非递减排列。 */
   /* 归并La和Lb得到新的线性表Lc,Lc的数据元素也按值非递减排列 */
   int i=1,j=1,k=0;
   int La_len,Lb_len;
   ElemType ai,bj;
   InitList(Lc); /* 创建空表Lc */
   La_len=ListLength(La);
   Lb_len=ListLength(Lb);
   while(i<=La_len&&j<=Lb_len) /* 表La和表Lb均非空 */
   {
     GetElem(La,i,&ai);
     GetElem(Lb,j,&bj);
     if(ai<=bj)
     {
       ListInsert(Lc,++k,ai);
       ++i;
     }
     else
     {
       ListInsert(Lc,++k,bj);
       ++j;
     }
   }
   while(i<=La_len) /* 表La非空且表Lb空 */
   {
     GetElem(La,i++,&ai);
     ListInsert(Lc,++k,ai);
   }
   while(j<=Lb_len) /* 表Lb非空且表La空 */
   {
     GetElem(Lb,j++,&bj);
     ListInsert(Lc,++k,bj);
   }
 }

 void print(ElemType *c)
 {
   printf("%d ",*c);
 }

 void main()
 {
   SqList La,Lb,Lc;
   int j,a[4]={3,5,8,11},b[7]={2,6,8,9,11,15,20};
   InitList(&La); /* 创建空表La */
   for(j=1;j<=4;j++) /* 在表La中插入4个元素 */
     ListInsert(&La,j,a[j-1]);
   printf("La= "); /* 输出表La的内容 */
   ListTraverse(La,print);
   InitList(&Lb); /* 创建空表Lb */
   for(j=1;j<=7;j++) /* 在表Lb中插入7个元素 */
     ListInsert(&Lb,j,b[j-1]);
   printf("Lb= "); /* 输出表Lb的内容 */
   ListTraverse(Lb,print);
   MergeList(La,Lb,&Lc);
   printf("Lc= "); /* 输出表Lc的内容 */
   ListTraverse(Lc,print);
 }
**********ALGO2-3.c**********
 /* algo2-3.c 实现算法2.7的程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-1.h"
 #include"bo2-1.c"

 void MergeList(SqList La,SqList Lb,SqList *Lc) /* 算法2.7 */
 { /* 已知顺序线性表La和Lb的元素按值非递减排列。 */
   /* 归并La和Lb得到新的顺序线性表Lc,Lc的元素也按值非递减排列 */
   ElemType *pa,*pa_last,*pb,*pb_last,*pc;
   pa=La.elem;
   pb=Lb.elem;
   (*Lc).listsize=(*Lc).length=La.length+Lb.length;/*不用InitList()创建空表Lc */
   pc=(*Lc).elem=(ElemType *)malloc((*Lc).listsize*sizeof(ElemType));
   if(!(*Lc).elem) /* 存储分配失败 */
     exit(OVERFLOW);
   pa_last=La.elem+La.length-1;
   pb_last=Lb.elem+Lb.length-1;
   while(pa<=pa_last&&pb<=pb_last) /* 表La和表Lb均非空 */
   { /* 归并 */
     if(*pa<=*pb)
       *pc++=*pa++;
     else
       *pc++=*pb++;
   }
   while(pa<=pa_last) /* 表La非空且表Lb空 */
     *pc++=*pa++; /* 插入La的剩余元素 */
   while(pb<=pb_last) /* 表Lb非空且表La空 */
     *pc++=*pb++; /* 插入Lb的剩余元素 */
 }

 void print(ElemType *c)
 {
   printf("%d ",*c);
 }

 void main()
 {
   SqList La,Lb,Lc;
   int j;
   InitList(&La); /* 创建空表La */
   for(j=1;j<=5;j++) /* 在表La中插入5个元素 */
     ListInsert(&La,j,j);
   printf("La= "); /* 输出表La的内容 */
   ListTraverse(La,print);
   InitList(&Lb); /* 创建空表Lb */
   for(j=1;j<=5;j++) /* 在表Lb中插入5个元素 */
     ListInsert(&Lb,j,2*j);
   printf("Lb= "); /* 输出表Lb的内容 */
   ListTraverse(Lb,print);
   MergeList(La,Lb,&Lc);
   printf("Lc= "); /* 输出表Lc的内容 */
   ListTraverse(Lc,print);
 }

**********ALGO2-4.c**********
 /* algo2-4.c 修改算法2.7的第一个循环语句中的条件语句为开关语句，且当 */
 /* *pa=*pb时，只将两者中之一插入Lc。此操作的结果和算法2.1相同 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-1.h"
 #include"bo2-1.c"

 int comp(ElemType c1,ElemType c2)
 {
   int i;
   if(c1<c2)
     i=1;
   else if(c1==c2)
     i=0;
   else
     i=-1;
   return i;
 }

 void MergeList(SqList La,SqList Lb,SqList *Lc)
 { /* 另一种合并线性表的方法（根据算法2.7下的要求修改算法2.7） */
   ElemType  *pa,*pa_last,*pb,*pb_last,*pc;
   pa=La.elem;
   pb=Lb.elem;
   (*Lc).listsize=La.length+Lb.length; /* 此句与算法2.7不同 */
   pc=(*Lc).elem=(ElemType *)malloc((*Lc).listsize*sizeof(ElemType));
   if(!(*Lc).elem)
     exit(OVERFLOW);
   pa_last=La.elem+La.length-1;
   pb_last=Lb.elem+Lb.length-1;
   while(pa<=pa_last&&pb<=pb_last) /* 表La和表Lb均非空 */
     switch(comp(*pa,*pb)) /* 此句与算法2.7不同 */
     {
       case  0: pb++;
       case  1: *pc++=*pa++;
                break;
       case -1: *pc++=*pb++;
     }
   while(pa<=pa_last) /* 表La非空且表Lb空 */
     *pc++=*pa++;
   while(pb<=pb_last) /* 表Lb非空且表La空 */
     *pc++=*pb++;
   (*Lc).length=pc-(*Lc).elem; /* 加此句 */
 }

 void print(ElemType *c)
 {
   printf("%d ",*c);
 }

 void main()
 {
   SqList La,Lb,Lc;
   int j;
   InitList(&La); /* 创建空表La */
   for(j=1;j<=5;j++) /* 在表La中插入5个元素 */
     ListInsert(&La,j,j);
   printf("La= "); /* 输出表La的内容 */
   ListTraverse(La,print);
   InitList(&Lb); /* 创建空表Lb */
   for(j=1;j<=5;j++) /* 在表Lb中插入5个元素 */
     ListInsert(&Lb,j,2*j);
   printf("Lb= "); /* 输出表Lb的内容 */
   ListTraverse(Lb,print);
   MergeList(La,Lb,&Lc);
   printf("Lc= "); /* 输出表Lc的内容 */
   ListTraverse(Lc,print);
 }

**********Algo2-5.c**********
 /* algo2-5.c 实现算法2.11、2.12的程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-2.h"
 #include"bo2-2.c"

 void CreateList(LinkList *L,int n) /* 算法2.11 */
 { /* 逆位序(插在表头)输入n个元素的值，建立带表头结构的单链线性表L */
   int i;
   LinkList p;
   *L=(LinkList)malloc(sizeof(struct LNode));
   (*L)->next=NULL; /* 先建立一个带头结点的单链表 */
   printf("请输入%d个数据\n",n);
   for(i=n;i>0;--i)
   {
     p=(LinkList)malloc(sizeof(struct LNode)); /* 生成新结点 */
     scanf("%d",&p->data); /* 输入元素值 */
     p->next=(*L)->next; /* 插入到表头 */
     (*L)->next=p;
   }
 }

 void CreateList2(LinkList *L,int n)
 { /* 正位序(插在表尾)输入n个元素的值，建立带表头结构的单链线性表 */
   int i;
   LinkList p,q;
   *L=(LinkList)malloc(sizeof(struct LNode)); /* 生成头结点 */
   (*L)->next=NULL;
   q=*L;
   printf("请输入%d个数据\n",n);
   for(i=1;i<=n;i++)
   {
     p=(LinkList)malloc(sizeof(struct LNode));
     scanf("%d",&p->data);
     q->next=p;
     q=q->next;
   }
   p->next=NULL;
 }

 void MergeList(LinkList La,LinkList *Lb,LinkList *Lc)/* 算法2.12 */
 { /* 已知单链线性表La和Lb的元素按值非递减排列。 */
   /* 归并La和Lb得到新的单链线性表Lc，Lc的元素也按值非递减排列 */
   LinkList pa=La->next,pb=(*Lb)->next,pc;
   *Lc=pc=La; /* 用La的头结点作为Lc的头结点 */
   while(pa&&pb)
     if(pa->data<=pb->data)
     {
       pc->next=pa;
       pc=pa;
       pa=pa->next;
     }
     else
     {
       pc->next=pb;
       pc=pb;
       pb=pb->next;
     }
   pc->next=pa?pa:pb; /* 插入剩余段 */
   free(*Lb); /* 释放Lb的头结点 */
   Lb=NULL;
 }

 void visit(ElemType c) /* ListTraverse()调用的函数(类型要一致) */
 {
   printf("%d ",c);
 }

 void main()
 {
   int n=5;
   LinkList La,Lb,Lc;
   printf("按非递减顺序, ");
   CreateList2(&La,n); /* 正位序输入n个元素的值 */
   printf("La="); /* 输出链表La的内容 */
   ListTraverse(La,visit);
   printf("按非递增顺序, ");
   CreateList(&Lb,n); /* 逆位序输入n个元素的值 */
   printf("Lb="); /* 输出链表Lb的内容 */
   ListTraverse(Lb,visit);
   MergeList(La,&Lb,&Lc); /* 按非递减顺序归并La和Lb,得到新表Lc */
   printf("Lc="); /* 输出链表Lc的内容 */
   ListTraverse(Lc,visit);
 }

**********algo2-6.c**********
 /* algo2-6.c 利用单链表结构处理教科书图2.1(学生健康登记表) */
 #include"c1.h"
 #define NAMELEN 8 /* 姓名最大长度 */
 #define CLASSLEN 4 /* 班级名最大长度 */
 struct stud /* 记录的结构 */
 {
   char name[NAMELEN+1];
   long num;
   char sex;
   int age;
   char Class[CLASSLEN+1];
   int health;
 };
 typedef struct stud ElemType; /* 链表结点元素类型为结构体 */
 #include"c2-2.h"
 char sta[3][9]={"健康  ","一般  ","神经衰弱"}; /* 健康状况(3类) */
 FILE *fp;

 Status InitList(LinkList *L) /* 拷自bo2-2.c */
 { /* 操作结果：构造一个空的线性表L */
   *L=(LinkList)malloc(sizeof(struct LNode)); /* 产生头结点,并使L指向此头结点 */
   if(!*L) /* 存储分配失败 */
     exit(OVERFLOW);
   (*L)->next=NULL; /* 指针域为空 */
   return OK;
 }

 Status ListTraverse(LinkList L,void(*vi)(ElemType)) /* 拷自bo2-2.c */
 { /* 初始条件：线性表L已存在 */
   /* 操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败 */
   LinkList p=L->next;
   while(p)
   {
     vi(p->data);
     p=p->next;
   }
   printf("\n");
   return OK;
 }

 void InsertAscend(LinkList L,ElemType e) /* 此函数是由bo2-9.c中的同名函数改写 */
 { /* 按学号非降序插入 */
   LinkList q=L,p=L->next;
   while(p&&e.num>p->data.num)
   {
     q=p;
     p=p->next;
   }
   q->next=(LinkList)malloc(sizeof(struct LNode)); /* 插在q后 */
   q->next->data=e;
   q->next->next=p;
 }

 void Print(struct stud e)
 { /* 显示记录e的内容 */
   printf("%-8s %6ld",e.name,e.num);
   if(e.sex=='m')
     printf(" 男");
   else
     printf(" 女");
   printf("%5d  %-4s",e.age,e.Class);
   printf("%9s\n",sta[e.health]);
 }

 void ReadIn(struct stud *e)
 { /* 由键盘输入结点信息 */
   printf("请输入姓名(<=%d个字符): ",NAMELEN);
   scanf("%s",e->name);
   printf("请输入学号: ");
   scanf("%ld",&e->num);
   printf("请输入性别(m:男 f:女): ");
   scanf("%*c%c",&e->sex);
   printf("请输入年龄: ");
   scanf("%d",&e->age);
   printf("请输入班级(<=%d个字符): ",CLASSLEN);
   scanf("%s",e->Class);
   printf("请输入健康状况(0:%s 1:%s 2:%s):",sta[0],sta[1],sta[2]);
   scanf("%d",&e->health);
 }

 void WriteToFile(struct stud e)
 { /* 将结点信息写入fp指定的文件 */
   fwrite(&e,sizeof(struct stud),1,fp);
 }

 Status ReadFromFile(struct stud *e)
 { /* 由fp指定的文件读取结点信息到e */
   int i;
   i=fread(e,sizeof(struct stud),1,fp);
   if(i==1) /* 读取文件成功 */
     return OK;
   else
     return ERROR;
 }

 Status FindFromNum(LinkList L,long num,LinkList *p,LinkList *q)
 { /* 查找表中学号为num的结点,如找到,q指向此结点,p指向q的前驱, */
   /* 并返回TRUE;如无此元素,则返回FALSE */
   *p=L;
   while(*p)
   {
     *q=(*p)->next;
     if(*q&&(*q)->data.num>num) /* 因为是按学号非降序排列 */
       break;
     if(*q&&(*q)->data.num==num) /* 找到该学号 */
       return TRUE;
     *p=*q;
   }
   return FALSE;
 }

 Status FindFromName(LinkList L,char name[],LinkList *p,LinkList *q)
 { /* 查找表中姓名为name的结点,如找到,q指向此结点,p指向q的前驱, */
   /* 并返回TRUE;如无此元素,则返回FALSE */
   *p=L;
   while(*p)
   {
     *q=(*p)->next;
     if(*q&&!strcmp((*q)->data.name,name)) /* 找到该姓名 */
       return TRUE;
     *p=*q;
   }
   return FALSE;
 }

 Status DeleteElemNum(LinkList L,long num)
 { /* 删除表中学号为num的元素，并返回TRUE；如无此元素，则返回FALSE */
   LinkList p,q;
   if(FindFromNum(L,num,&p,&q)) /* 找到此结点,且q指向其,p指向其前驱 */
   {
     p->next=q->next;
     free(q);
     return TRUE;
   }
   return FALSE;
 }

 Status DeleteElemName(LinkList L,char name[])
 { /* 删除表中姓名为name的元素，并返回TRUE；如无此元素，则返回FALSE */
   LinkList p,q;
   if(FindFromName(L,name,&p,&q)) /* 找到此结点,且q指向其,p指向其前驱 */
   {
     p->next=q->next;
     free(q);
     return TRUE;
   }
   return FALSE;
 }

 void Modify(ElemType *e)
 { /* 修改结点内容 */
   char s[80];
   Print(*e); /* 显示原内容 */
   printf("请输入待修改项的内容，不修改的项按回车键保持原值:\n");
   printf("请输入姓名(<=%d个字符): ",NAMELEN);
   gets(s);
   if(strlen(s))
     strcpy(e->name,s);
   printf("请输入学号: ");
   gets(s);
   if(strlen(s))
     e->num=atol(s);
   printf("请输入性别(m:男 f:女): ");
   gets(s);
   if(strlen(s))
     e->sex=s[0];
   printf("请输入年龄: ");
   gets(s);
   if(strlen(s))
     e->age=atoi(s);
   printf("请输入班级(<=%d个字符): ",CLASSLEN);
   gets(s);
   if(strlen(s))
     strcpy(e->Class,s);
   printf("请输入健康状况(0:%s 1:%s 2:%s):",sta[0],sta[1],sta[2]);
   gets(s);
   if(strlen(s))
     e->health=atoi(s); /* 修改完毕 */
 }

 #define N 4 /* student记录的个数 */
 void main()
 {
   struct stud student[N]={{"王小林",790631,'m',18,"计91",0},
                           {"陈红",790632,'f',20,"计91",1},
                           {"刘建平",790633,'m',21,"计91",0},
                           {"张立立",790634,'m',17,"计91",2}}; /* 表的初始记录 */
   int i,j,flag=1;
   long num;
   char filename[13],name[NAMELEN+1];
   ElemType e;
   LinkList T,p,q;
   InitList(&T); /* 初始化链表 */
   while(flag)
   {
     printf("1:将结构体数组student中的记录按学号非降序插入链表\n");
     printf("2:将文件中的记录按学号非降序插入链表\n");
     printf("3:键盘输入新记录，并将其按学号非降序插入链表\n");
     printf("4:删除链表中第一个有给定学号的记录\n");
     printf("5:删除链表中第一个有给定姓名的记录\n");
     printf("6:修改链表中第一个有给定学号的记录\n");
     printf("7:修改链表中第一个有给定姓名的记录\n");
     printf("8:查找链表中第一个有给定学号的记录\n");
     printf("9:查找链表中第一个有给定姓名的记录\n");
     printf("10:显示所有记录 11:将链表中的所有记录存入文件 12:结束\n");
     printf("请选择操作命令: ");
     scanf("%d",&i);
     switch(i)
     {
       case 1: for(j=0;j<N;j++)
                 InsertAscend(T,student[j]);
               break;
       case 2: printf("请输入文件名: ");
               scanf("%s",filename);
               if((fp=fopen(filename,"rb"))==NULL)
                 printf("打开文件失败!\n");
               else
               {
                 while(ReadFromFile(&e))
                   InsertAscend(T,e);
                 fclose(fp);
               }
               break;
       case 3: ReadIn(&e);
               InsertAscend(T,e);
               break;
       case 4: printf("请输入待删除记录的学号: ");
               scanf("%ld",&num);
               if(!DeleteElemNum(T,num))
                 printf("没有学号为%ld的记录\n",num);
               break;
       case 5: printf("请输入待删除记录的姓名: ");
               scanf("%s",name);
               if(!DeleteElemName(T,name))
                 printf("没有姓名为%s的记录\n",name);
               break;
       case 6: printf("请输入待修改记录的学号: ");
               scanf("%ld%*c",&num); /* %*c吃掉回车符 */
               if(!FindFromNum(T,num,&p,&q))
                 printf("没有学号为%ld的记录\n",num);
               else
               {
                 Modify(&q->data);
                 if(q->data.num!=num) /* 学号被修改 */
                 {
                   p->next=q->next; /* 把q所指的结点从L中删除 */
                   InsertAscend(T,q->data); /* 把元素插入L */
                   free(q); /* 删除q */
                 }
               }
               break;
       case 7: printf("请输入待修改记录的姓名: ");
               scanf("%s%*c",name); /* %*c吃掉回车符 */
               if(!FindFromName(T,name,&p,&q))
                 printf("没有姓名为%s的记录\n",name);
               else
               {
                 num=q->data.num; /* 学号存入num */
                 Modify(&q->data);
                 if(q->data.num!=num) /* 学号被修改 */
                 {
                   p->next=q->next; /* 把q所指的结点从L中删除 */
                   InsertAscend(T,q->data); /* 把元素插入L */
                   free(q); /* 删除q */
                 }
               }
               break;
       case 8: printf("请输入待查找记录的学号: ");
               scanf("%ld",&num);
               if(!FindFromNum(T,num,&p,&q))
                 printf("没有学号为%ld的记录\n",num);
               else
                 Print(q->data);
               break;
       case 9: printf("请输入待查找记录的姓名: ");
               scanf("%s",name);
               if(!FindFromName(T,name,&p,&q))
                 printf("没有姓名为%s的记录\n",name);
               else
               Print(q->data);
               break;
       case 10:printf("  姓名    学号 性别 年龄 班级 健康状况\n");
               ListTraverse(T,Print);
               break;
       case 11:printf("请输入文件名: ");
               scanf("%s",filename);
               if((fp=fopen(filename,"wb"))==NULL)
                 printf("打开文件失败!\n");
               else
                 ListTraverse(T,WriteToFile);
               fclose(fp);
               break;
       case 12:flag=0;
     }
   }
 }


**********Algo2-7.c**********
 /* algo2-7.c 教科书中图2.10 静态链表示例 */
 /* 第一个结点的位置在[0].cur中，成员cur的值为0，则到链表尾 */
 #include"c1.h"
 #define N 6 /* 字符串长度 */
 typedef char ElemType[N];
 #include"c2-3.h"

 void main()
 {
   SLinkList s={{"",1},{"ZHAO",2},{"QIAN",3},{"SUN",4},{"LI",5},{"ZHOU",6},{"WU",7},{"ZHENG",8},{"WANG",0}};
   int i;
   i=s[0].cur;
   while(i) /* 输出教科书中图2.10(a)的状态 */
   {
     printf("%s ",s[i].data); /* 输出链表的当前值 */
     i=s[i].cur; /* 找到下一个 */
   }
   printf("\n");
   s[4].cur=9; /* 按教科书中图2.10(b)修改 */
   s[6].cur=8;
   s[9].cur=5;
   strcpy(s[9].data,"SHI");
   i=s[0].cur;
   while(i) /* 输出教科书中图2.10(b)的状态 */
   {
     printf("%s ",s[i].data); /* 输出链表的当前值 */
     i=s[i].cur; /* 找到下一个 */
   }
   printf("\n");
 }
**********Algo2-8.c**********
 /* algo2-8.c 实现算法2.17的程序 */
 #include"c1.h"
 #define N 2
 typedef char ElemType;
 #include"c2-3.h"
 #include"bo2-3.c"
 #include"bo2-32.c"

 void difference(SLinkList space,int *S) /* 算法2.17 */
 { /* 依次输入集合A和B的元素，在一维数组space中建立表示集合(A-B)∪(B-A) */
   /* 的静态链表，S为其头指针。假设备用空间足够大，space[0].cur为备用空间的头指针 */
   int r,p,m,n,i,j,k;
   ElemType b;
   InitSpace(space); /* 初始化备用空间 */
   *S=Malloc(space); /* 生成S的头结点 */
   r=*S; /* r指向S的当前最后结点 */
   printf("请输入集合A和B的元素个数m,n:");
   scanf("%d,%d%*c",&m,&n); /* %*c吃掉回车符 */
   printf("请输入集合A的元素（共%d个）:",m);
   for(j=1;j<=m;j++) /* 建立集合A的链表 */
   {
     i=Malloc(space); /* 分配结点 */
     scanf("%c",&space[i].data); /* 输入A的元素值 */
     space[r].cur=i; /* 插入到表尾 */
     r=i;
   }
   scanf("%*c"); /* %*c吃掉回车符 */
   space[r].cur=0; /* 尾结点的指针为空 */
   printf("请输入集合B的元素（共%d个）:",n);
   for(j=1;j<=n;j++)
   { /* 依次输入B的元素,若不在当前表中,则插入,否则删除 */
     scanf("%c",&b);
     p=*S;
     k=space[*S].cur; /* k指向集合A中的第一个结点 */
     while(k!=space[r].cur&&space[k].data!=b)
     { /* 在当前表中查找 */
       p=k;
       k=space[k].cur;
     }
     if(k==space[r].cur)
     { /* 当前表中不存在该元素，插入在r所指结点之后，且r的位置不变 */
       i=Malloc(space);
       space[i].data=b;
       space[i].cur=space[r].cur;
       space[r].cur=i;
     }
     else /* 该元素已在表中，删除之 */
     {
       space[p].cur=space[k].cur;
       Free(space,k);
       if(r==k)
         r=p; /* 若删除的是尾元素，则需修改尾指针 */
     }
   }
 }

 void visit(ElemType c)
 {
   printf("%c ",c);
 }

 void main()
 {
   int k;
   SLinkList s;
   difference(s,&k);
   ListTraverse(s,k,visit);
 }

**********Algo2-9.c**********
 /* algo2-9.c 尽量采用bo2-32.c中的基本操作实现算法2.17的功能 */
 #include"c1.h"
 #define N 2
 typedef char ElemType;
 #include"c2-3.h"
 #include"bo2-3.c"
 #include"bo2-32.c"

 void visit(ElemType c)
 {
   printf("%c ",c);
 }

 int difference(SLinkList space) /* 改进算法2.17(尽量利用基本操作实现) */
 { /* 依次输入集合A和B的元素，在一维数组space中建立表示集合(A-B)∪(B-A) */
   /* 的静态链表，并返回其头指针。假设备用空间足够大，space[0].cur为备用空间的头指针 */
   int m,n,i,j,k,S;
   ElemType b,c;
   InitSpace(space); /* 初始化备用空间 */
   S=InitList(space); /* 生成链表S的头结点 */
   printf("请输入集合A和B的元素个数m,n:");
   scanf("%d,%d%*c",&m,&n); /* %*c吃掉回车符 */
   printf("请输入集合A的元素（共%d个）:",m);
   for(j=1;j<=m;j++) /* 建立集合A的链表 */
   {
     scanf("%c",&b); /* 输入A的元素值 */
     ListInsert(space,S,j,b); /* 插入到表尾 */
   }
   scanf("%*c"); /* 吃掉回车符 */
   printf("请输入集合B的元素（共%d个）:",n);
   for(j=1;j<=n;j++)
   { /* 依次输入B的元素,若不在当前表中,则插入,否则删除 */
     scanf("%c",&b);
     k=LocateElem(space,S,b); /* k为b的位序 */
     if(k) /* b在当前表中 */
     {
       PriorElem(space,S,b,&c); /* b的前驱为c */
       i=LocateElem(space,S,c); /* i为c的位序 */
       space[i].cur=space[k].cur; /* 将k的指针赋给i的指针 */
       Free(space,k); /* 将下标为k的空闲结点回收到备用链表 */
     }
     else
       ListInsert(space,S,ListLength(space,S)+1,b); /* 在表尾插入b */
   }
   return S;
 }

 void main()
 {
   int k;
   SLinkList s;
   k=difference(s);
   ListTraverse(s,k,visit);
 }

**********bo2-1.c**********
 /* bo2-1.c 顺序表示的线性表(存储结构由c2-1.h定义)的基本操作(12个) */
 Status InitList(SqList *L) /* 算法2.3 */
 { /* 操作结果：构造一个空的顺序线性表 */
   (*L).elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
   if(!(*L).elem)
     exit(OVERFLOW); /* 存储分配失败 */
   (*L).length=0; /* 空表长度为0 */
   (*L).listsize=LIST_INIT_SIZE; /* 初始存储容量 */
   return OK;
 }

 Status DestroyList(SqList *L)
 { /* 初始条件：顺序线性表L已存在。操作结果：销毁顺序线性表L */
   free((*L).elem);
   (*L).elem=NULL;
   (*L).length=0;
   (*L).listsize=0;
   return OK;
 }

 Status ClearList(SqList *L)
 { /* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
   (*L).length=0;
   return OK;
 }

 Status ListEmpty(SqList L)
 { /* 初始条件：顺序线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
   if(L.length==0)
     return TRUE;
   else
     return FALSE;
 }

 int ListLength(SqList L)
 { /* 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数 */
   return L.length;
 }

 Status GetElem(SqList L,int i,ElemType *e)
 { /* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
   /* 操作结果：用e返回L中第i个数据元素的值 */
   if(i<1||i>L.length)
     exit(ERROR);
   *e=*(L.elem+i-1);
   return OK;
 }

 int LocateElem(SqList L,ElemType e,Status(*compare)(ElemType,ElemType))
 { /* 初始条件：顺序线性表L已存在，compare()是数据元素判定函数(满足为1,否则为0) */
   /* 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。 */
   /*           若这样的数据元素不存在，则返回值为0。算法2.6 */
   ElemType *p;
   int i=1; /* i的初值为第1个元素的位序 */
   p=L.elem; /* p的初值为第1个元素的存储位置 */
   while(i<=L.length&&!compare(*p++,e))
     ++i;
   if(i<=L.length)
     return i;
   else
     return 0;
 }

 Status PriorElem(SqList L,ElemType cur_e,ElemType *pre_e)
 { /* 初始条件：顺序线性表L已存在 */
   /* 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱， */
   /*           否则操作失败，pre_e无定义 */
   int i=2;
   ElemType *p=L.elem+1;
   while(i<=L.length&&*p!=cur_e)
   {
     p++;
     i++;
   }
   if(i>L.length)
     return INFEASIBLE;
   else
   {
     *pre_e=*--p;
     return OK;
   }
 }

 Status NextElem(SqList L,ElemType cur_e,ElemType *next_e)
 { /* 初始条件：顺序线性表L已存在 */
   /* 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继， */
   /*           否则操作失败，next_e无定义 */
   int i=1;
   ElemType *p=L.elem;
   while(i<L.length&&*p!=cur_e)
   {
     i++;
     p++;
   }
   if(i==L.length)
     return INFEASIBLE;
   else
   {
     *next_e=*++p;
     return OK;
   }
 }

 Status ListInsert(SqList *L,int i,ElemType e) /* 算法2.4 */
 { /* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L)+1 */
   /* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
   ElemType *newbase,*q,*p;
   if(i<1||i>(*L).length+1) /* i值不合法 */
     return ERROR;
   if((*L).length>=(*L).listsize) /* 当前存储空间已满,增加分配 */
   {
     newbase=(ElemType *)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(ElemType));
     if(!newbase)
       exit(OVERFLOW); /* 存储分配失败 */
     (*L).elem=newbase; /* 新基址 */
     (*L).listsize+=LISTINCREMENT; /* 增加存储容量 */
   }
   q=(*L).elem+i-1; /* q为插入位置 */
   for(p=(*L).elem+(*L).length-1;p>=q;--p) /* 插入位置及之后的元素右移 */
     *(p+1)=*p;
   *q=e; /* 插入e */
   ++(*L).length; /* 表长增1 */
   return OK;
 }

 Status ListDelete(SqList *L,int i,ElemType *e) /* 算法2.5 */
 { /* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
   /* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
   ElemType *p,*q;
   if(i<1||i>(*L).length) /* i值不合法 */
     return ERROR;
   p=(*L).elem+i-1; /* p为被删除元素的位置 */
   *e=*p; /* 被删除元素的值赋给e */
   q=(*L).elem+(*L).length-1; /* 表尾元素的位置 */
   for(++p;p<=q;++p) /* 被删除元素之后的元素左移 */
     *(p-1)=*p;
   (*L).length--; /* 表长减1 */
   return OK;
 }

 Status ListTraverse(SqList L,void(*vi)(ElemType*))
 { /* 初始条件：顺序线性表L已存在 */
   /* 操作结果：依次对L的每个数据元素调用函数vi()。一旦vi()失败，则操作失败 */
   /*           vi()的形参加'&'，表明可通过调用vi()改变元素的值 */
   ElemType *p;
   int i;
   p=L.elem;
   for(i=1;i<=L.length;i++)
     vi(p++);
   printf("\n");
   return OK;
 }

**********BO2-2.C**********
 /* bo2-2.c 单链表线性表(存储结构由c2-2.h定义)的基本操作(12个) */
 Status InitList(LinkList *L)
 { /* 操作结果：构造一个空的线性表L */
   *L=(LinkList)malloc(sizeof(struct LNode)); /* 产生头结点,并使L指向此头结点 */
   if(!*L) /* 存储分配失败 */
     exit(OVERFLOW);
   (*L)->next=NULL; /* 指针域为空 */
   return OK;
 }

 Status DestroyList(LinkList *L)
 { /* 初始条件：线性表L已存在。操作结果：销毁线性表L */
   LinkList q;
   while(*L)
   {
     q=(*L)->next;
     free(*L);
     *L=q;
   }
   return OK;
 }

 Status ClearList(LinkList L) /* 不改变L */
 { /* 初始条件：线性表L已存在。操作结果：将L重置为空表 */
   LinkList p,q;
   p=L->next; /* p指向第一个结点 */
   while(p) /* 没到表尾 */
   {
     q=p->next;
     free(p);
     p=q;
   }
   L->next=NULL; /* 头结点指针域为空 */
   return OK;
 }

 Status ListEmpty(LinkList L)
 { /* 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
   if(L->next) /* 非空 */
     return FALSE;
   else
     return TRUE;
 }

 int ListLength(LinkList L)
 { /* 初始条件：线性表L已存在。操作结果：返回L中数据元素个数 */
   int i=0;
   LinkList p=L->next; /* p指向第一个结点 */
   while(p) /* 没到表尾 */
   {
     i++;
     p=p->next;
   }
   return i;
 }

 Status GetElem(LinkList L,int i,ElemType *e) /* 算法2.8 */
 { /* L为带头结点的单链表的头指针。当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR */
   int j=1; /* j为计数器 */
   LinkList p=L->next; /* p指向第一个结点 */
   while(p&&j<i) /* 顺指针向后查找,直到p指向第i个元素或p为空 */
   {
     p=p->next;
     j++;
   }
   if(!p||j>i) /* 第i个元素不存在 */
     return ERROR;
   *e=p->data; /* 取第i个元素 */
   return OK;
 }

 int LocateElem(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
 { /* 初始条件: 线性表L已存在,compare()是数据元素判定函数(满足为1,否则为0) */
   /* 操作结果: 返回L中第1个与e满足关系compare()的数据元素的位序。 */
   /*           若这样的数据元素不存在,则返回值为0 */
   int i=0;
   LinkList p=L->next;
   while(p)
   {
     i++;
     if(compare(p->data,e)) /* 找到这样的数据元素 */
       return i;
     p=p->next;
   }
   return 0;
 }

 Status PriorElem(LinkList L,ElemType cur_e,ElemType *pre_e)
 { /* 初始条件: 线性表L已存在 */
   /* 操作结果: 若cur_e是L的数据元素,且不是第一个,则用pre_e返回它的前驱, */
   /*           返回OK;否则操作失败,pre_e无定义,返回INFEASIBLE */
   LinkList q,p=L->next; /* p指向第一个结点 */
   while(p->next) /* p所指结点有后继 */
   {
     q=p->next; /* q为p的后继 */
     if(q->data==cur_e)
     {
       *pre_e=p->data;
       return OK;
     }
     p=q; /* p向后移 */
   }
   return INFEASIBLE;
 }

 Status NextElem(LinkList L,ElemType cur_e,ElemType *next_e)
 { /* 初始条件：线性表L已存在 */
   /* 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继， */
   /*           返回OK;否则操作失败，next_e无定义，返回INFEASIBLE */
   LinkList p=L->next; /* p指向第一个结点 */
   while(p->next) /* p所指结点有后继 */
   {
     if(p->data==cur_e)
     {
       *next_e=p->next->data;
       return OK;
     }
     p=p->next;
   }
   return INFEASIBLE;
 }

 Status ListInsert(LinkList L,int i,ElemType e) /* 算法2.9。不改变L */
 { /* 在带头结点的单链线性表L中第i个位置之前插入元素e */
   int j=0;
   LinkList p=L,s;
   while(p&&j<i-1) /* 寻找第i-1个结点 */
   {
     p=p->next;
     j++;
   }
   if(!p||j>i-1) /* i小于1或者大于表长 */
     return ERROR;
   s=(LinkList)malloc(sizeof(struct LNode)); /* 生成新结点 */
   s->data=e; /* 插入L中 */
   s->next=p->next;
   p->next=s;
   return OK;
 }

 Status ListDelete(LinkList L,int i,ElemType *e) /* 算法2.10。不改变L */
 { /* 在带头结点的单链线性表L中，删除第i个元素,并由e返回其值 */
   int j=0;
   LinkList p=L,q;
   while(p->next&&j<i-1) /* 寻找第i个结点,并令p指向其前趋 */
   {
     p=p->next;
     j++;
   }
   if(!p->next||j>i-1) /* 删除位置不合理 */
     return ERROR;
   q=p->next; /* 删除并释放结点 */
   p->next=q->next;
   *e=q->data;
   free(q);
   return OK;
 }

 Status ListTraverse(LinkList L,void(*vi)(ElemType))
 /* vi的形参类型为ElemType，与bo2-1.c中相应函数的形参类型ElemType&不同 */
 { /* 初始条件：线性表L已存在 */
   /* 操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败 */
   LinkList p=L->next;
   while(p)
   {
     vi(p->data);
     p=p->next;
   }
   printf("\n");
   return OK;
 }

**********BO2-3.c**********
 /* bo2-3.c 实现算法2.15、2.16的程序 (数据结构由c2-3.h定义) (3个) */
 int Malloc(SLinkList space) /* 算法2.15 */
 { /* 若备用链表非空,则返回分配的结点下标(备用链表的第一个结点),否则返回0 */
   int i=space[0].cur;
   if(i) /* 备用链表非空 */
     space[0].cur=space[i].cur; /* 备用链表的头结点指向原备用链表的第二个结点 */
   return i; /* 返回新开辟结点的坐标 */
 }

 void Free(SLinkList space,int k) /* 算法2.16 */
 { /* 将下标为k的空闲结点回收到备用链表(成为备用链表的第一个结点) */
   space[k].cur=space[0].cur; /* 回收结点的＂游标＂指向备用链表的第一个结点 */
   space[0].cur=k; /* 备用链表的头结点指向新回收的结点 */
 }

 void DestroyList()
 { /* 静态数组不能被销毁 */
 }

**********BO2-31.c**********
 /* bo2-31.c 一个数组只生成一个静态链表(数据结构由c2-3.h定义)的基本操作(11个) */
 void InitList(SLinkList L)
 { /* 构造一个空的链表，表头为L的最后一个单元L[MAXSIZE-1]，其余单元链成 */
   /* 一个备用链表，表头为L的第一个单元L[0]，“0”表示空指针 */
   int i;
   L[MAXSIZE-1].cur=0; /* L的最后一个单元为空链表的表头 */
   for(i=0;i<MAXSIZE-2;i++) /* 将其余单元链接成以L[0]为表头的备用链表 */
     L[i].cur=i+1;
   L[MAXSIZE-2].cur=0;
 }

 Status ClearList(SLinkList L)
 { /* 初始条件：线性表L已存在。操作结果：将L重置为空表 */
   int i,j,k;
   i=L[MAXSIZE-1].cur; /* 链表第一个结点的位置 */
   L[MAXSIZE-1].cur=0; /* 链表空 */
   k=L[0].cur; /* 备用链表第一个结点的位置 */
   L[0].cur=i; /* 把链表的结点连到备用链表的表头 */
   while(i) /* 没到链表尾 */
   {
     j=i;
     i=L[i].cur; /* 指向下一个元素 */
   }
   L[j].cur=k; /* 备用链表的第一个结点接到链表的尾部 */
   return OK;
 }

 Status ListEmpty(SLinkList L)
 { /* 若L是空表，返回TRUE；否则返回FALSE */
   if(L[MAXSIZE-1].cur==0) /* 空表 */
     return TRUE;
   else
     return FALSE;
 }

 int ListLength(SLinkList L)
 { /* 返回L中数据元素个数 */
   int j=0,i=L[MAXSIZE-1].cur; /* i指向第一个元素 */
   while(i) /* 没到静态链表尾 */
   {
     i=L[i].cur; /* 指向下一个元素 */
     j++;
   }
   return j;
 }

 Status GetElem(SLinkList L,int i,ElemType *e)
 { /* 用e返回L中第i个元素的值 */
   int l,k=MAXSIZE-1; /* k指向表头序号 */
   if(i<1||i>ListLength(L))
     return ERROR;
   for(l=1;l<=i;l++) /* 移动到第i个元素处 */
     k=L[k].cur;
   *e=L[k].data;
   return OK;
 }

 int LocateElem(SLinkList L,ElemType e) /* 算法2.13（有改动） */
 { /* 在静态单链线性表L中查找第1个值为e的元素。若找到，则返回它在L中的 */
   /* 位序，否则返回0。（与其它LocateElem()的定义不同) */
   int i=L[MAXSIZE-1].cur; /* i指示表中第一个结点 */
   while(i&&L[i].data!=e) /* 在表中顺链查找(e不能是字符串) */
     i=L[i].cur;
   return i;
 }

 Status PriorElem(SLinkList L,ElemType cur_e,ElemType *pre_e)
 { /* 初始条件：线性表L已存在 */
   /* 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱， */
   /*           否则操作失败，pre_e无定义 */
   int j,i=L[MAXSIZE-1].cur; /* i指示链表第一个结点的位置 */
   do
   { /* 向后移动结点 */
     j=i;
     i=L[i].cur;
   }while(i&&cur_e!=L[i].data);
   if(i) /* 找到该元素 */
   {
     *pre_e=L[j].data;
     return OK;
   }
   return ERROR;
 }

 Status NextElem(SLinkList L,ElemType cur_e,ElemType *next_e)
 { /* 初始条件：线性表L已存在 */
   /* 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继， */
   /*           否则操作失败，next_e无定义 */
   int j,i=LocateElem(L,cur_e); /* 在L中查找第一个值为cur_e的元素的位置 */
   if(i) /* L中存在元素cur_e */
   {
     j=L[i].cur; /* cur_e的后继的位置 */
     if(j) /* cur_e有后继 */
     {
       *next_e=L[j].data;
       return OK; /* cur_e元素有后继 */
     }
   }
   return ERROR; /* L不存在cur_e元素,cur_e元素无后继 */
 }

 Status ListInsert(SLinkList L,int i,ElemType e)
 { /* 在L中第i个元素之前插入新的数据元素e */
   int l,j,k=MAXSIZE-1; /* k指向表头 */
   if(i<1||i>ListLength(L)+1)
     return ERROR;
   j=Malloc(L); /* 申请新单元 */
   if(j) /* 申请成功 */
   {
     L[j].data=e; /* 赋值给新单元 */
     for(l=1;l<i;l++) /* 移动i-1个元素 */
       k=L[k].cur;
     L[j].cur=L[k].cur;
     L[k].cur=j;
     return OK;
   }
   return ERROR;
 }

 Status ListDelete(SLinkList L,int i,ElemType *e)
 { /* 删除在L中第i个数据元素e，并返回其值 */
   int j,k=MAXSIZE-1; /* k指向表头 */
   if(i<1||i>ListLength(L))
     return ERROR;
   for(j=1;j<i;j++) /* 移动i-1个元素 */
     k=L[k].cur;
   j=L[k].cur;
   L[k].cur=L[j].cur;
   *e=L[j].data;
   Free(L,j);
   return OK;
 }

 Status ListTraverse(SLinkList L,void(*vi)(ElemType))
 { /* 初始条件:线性表L已存在 */
   /* 操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败 */
   int i=L[MAXSIZE-1].cur; /* 指向第一个元素 */
   while(i) /* 没到静态链表尾 */
   {
     vi(L[i].data); /* 调用vi() */
     i=L[i].cur; /* 指向下一个元素 */
   }
   printf("\n");
   return OK;
 }

**********BO2-32.c**********
 /* bo2-32.c 一个数组可生成若干静态链表(数据结构由c2-3.h定义)的基本操作(12个) */
 void InitSpace(SLinkList L) /* 算法2.14。另加 */
 { /* 将一维数组L中各分量链成一个备用链表，L[0].cur为头指针。“0”表示空指针 */
   int i;
   for(i=0;i<MAXSIZE-1;i++)
     L[i].cur=i+1;
   L[MAXSIZE-1].cur=0;
 }

 int InitList(SLinkList L)
 { /* 构造一个空链表，返回值为空表在数组中的位序 */
   int i;
   i=Malloc(L); /* 调用Malloc()，简化程序 */
   L[i].cur=0; /* 空链表的表头指针为空(0) */
   return i;
 }

 Status ClearList(SLinkList L,int n)
 { /* 初始条件：L中表头位序为n的静态链表已存在。操作结果：将此表重置为空表 */
   int j,k,i=L[n].cur; /* 链表第一个结点的位置 */
   L[n].cur=0; /* 链表空 */
   k=L[0].cur; /* 备用链表第一个结点的位置 */
   L[0].cur=i; /* 把链表的结点连到备用链表的表头 */
   while(i) /* 没到链表尾 */
   {
     j=i;
     i=L[i].cur; /* 指向下一个元素 */
   }
   L[j].cur=k; /* 备用链表的第一个结点接到链表的尾部 */
   return OK;
 }

 Status ListEmpty(SLinkList L,int n)
 { /* 判断L中表头位序为n的链表是否空,若是空表返回TRUE;否则返回FALSE */
   if(L[n].cur==0) /* 空表 */
     return TRUE;
   else
     return FALSE;
 }

 int ListLength(SLinkList L,int n)
 { /* 返回L中表头位序为n的链表的数据元素个数 */
   int j=0,i=L[n].cur; /* i指向第一个元素 */
   while(i) /* 没到静态链表尾 */
   {
     i=L[i].cur; /* 指向下一个元素 */
     j++;
   }
   return j;
 }

 Status GetElem(SLinkList L,int n, int i,ElemType *e)
 { /* 用e返回L中表头位序为n的链表的第i个元素的值 */
   int l,k=n; /* k指向表头序号 */
   if(i<1||i>ListLength(L,n)) /* i值不合理 */
     return ERROR;
   for(l=1;l<=i;l++) /* 移动i-1个元素 */
     k=L[k].cur;
   *e=L[k].data;
   return OK;
 }

 int LocateElem(SLinkList L,int n,ElemType e)
 { /* 在L中表头位序为n的静态单链表中查找第1个值为e的元素。 */
   /* 若找到，则返回它在L中的位序，否则返回0 */
   int i=L[n].cur; /* i指示表中第一个结点 */
   while(i&&L[i].data!=e) /* 在表中顺链查找(e不能是字符串) */
     i=L[i].cur;
   return i;
 }

 Status PriorElem(SLinkList L,int n,ElemType cur_e,ElemType *pre_e)
 { /* 初始条件：在L中表头位序为n的静态单链表已存在 */
   /* 操作结果：若cur_e是此单链表的数据元素，且不是第一个， */
   /*           则用pre_e返回它的前驱，否则操作失败，pre_e无定义 */
   int j,i=L[n].cur; /* i为链表第一个结点的位置 */
   do
   { /* 向后移动结点 */
     j=i;
     i=L[i].cur;
   }while(i&&cur_e!=L[i].data);
   if(i) /* 找到该元素 */
   {
     *pre_e=L[j].data;
     return OK;
   }
   return ERROR;
 }

 Status NextElem(SLinkList L,int n,ElemType cur_e,ElemType *next_e)
 { /* 初始条件：在L中表头位序为n的静态单链表已存在 */
   /* 操作结果：若cur_e是此单链表的数据元素，且不是最后一个， */
   /* 则用next_e返回它的后继，否则操作失败，next_e无定义 */
   int i;
   i=LocateElem(L,n,cur_e); /* 在链表中查找第一个值为cur_e的元素的位置 */
   if(i) /* 在静态单链表中存在元素cur_e */
   {
     i=L[i].cur; /* cur_e的后继的位置 */
     if(i) /* cur_e有后继 */
     {
       *next_e=L[i].data;
       return OK; /* cur_e元素有后继 */
     }
   }
   return ERROR; /* L不存在cur_e元素,cur_e元素无后继 */
 }

 Status ListInsert(SLinkList L,int n,int i,ElemType e)
 { /* 在L中表头位序为n的链表的第i个元素之前插入新的数据元素e */
   int l,j,k=n; /* k指向表头 */
   if(i<1||i>ListLength(L,n)+1)
     return ERROR;
   j=Malloc(L); /* 申请新单元 */
   if(j) /* 申请成功 */
   {
     L[j].data=e; /* 赋值给新单元 */
     for(l=1;l<i;l++) /* 移动i-1个元素 */
       k=L[k].cur;
     L[j].cur=L[k].cur;
     L[k].cur=j;
     return OK;
   }
   return ERROR;
 }

 Status ListDelete(SLinkList L,int n,int i,ElemType *e)
 { /* 删除在L中表头位序为n的链表的第i个数据元素e，并返回其值 */
   int j,k=n; /* k指向表头 */
   if(i<1||i>ListLength(L,n))
     return ERROR;
   for(j=1;j<i;j++) /* 移动i-1个元素 */
     k=L[k].cur;
   j=L[k].cur;
   L[k].cur=L[j].cur;
   *e=L[j].data;
   Free(L,j);
   return OK;
 }

 Status ListTraverse(SLinkList L,int n,void(*vi)(ElemType))
 { /* 依次对L中表头位序为n的链表的每个数据元素,调用函数vi()。一旦vi()失败,则操作失败 */
   int i=L[n].cur; /* 指向第一个元素 */
   while(i) /* 没到静态链表尾 */
   {
     vi(L[i].data); /* 调用vi() */
     i=L[i].cur; /* 指向下一个元素 */
   }
   printf("\n");
   return OK;
 }

**********BO2-4.c**********
 /* bo2-4.c 设立尾指针的单循环链表(存储结构由c2-2.h定义)的12个基本操作 */
 Status InitList_CL(LinkList *L)
 { /* 操作结果：构造一个空的线性表L */
   *L=(LinkList)malloc(sizeof(struct LNode)); /* 产生头结点,并使L指向此头结点 */
   if(!*L) /* 存储分配失败 */
     exit(OVERFLOW);
   (*L)->next=*L; /* 指针域指向头结点 */
   return OK;
 }

 Status DestroyList_CL(LinkList *L)
 { /* 操作结果：销毁线性表L */
   LinkList q,p=(*L)->next; /* p指向头结点 */
   while(p!=*L) /* 没到表尾 */
   {
     q=p->next;
     free(p);
     p=q;
   }
   free(*L);
   *L=NULL;
   return OK;
 }

 Status ClearList_CL(LinkList *L) /* 改变L */
 { /* 初始条件：线性表L已存在。操作结果：将L重置为空表 */
   LinkList p,q;
   *L=(*L)->next; /* L指向头结点 */
   p=(*L)->next; /* p指向第一个结点 */
   while(p!=*L) /* 没到表尾 */
   {
     q=p->next;
     free(p);
     p=q;
   }
   (*L)->next=*L; /* 头结点指针域指向自身 */
   return OK;
 }

 Status ListEmpty_CL(LinkList L)
 { /* 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
   if(L->next==L) /* 空 */
     return TRUE;
   else
     return FALSE;
 }

 int ListLength_CL(LinkList L)
 { /* 初始条件：L已存在。操作结果：返回L中数据元素个数 */
   int i=0;
   LinkList p=L->next; /* p指向头结点 */
   while(p!=L) /* 没到表尾 */
   {
     i++;
     p=p->next;
   }
   return i;
 }

 Status GetElem_CL(LinkList L,int i,ElemType *e)
 { /* 当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR */
   int j=1; /* 初始化,j为计数器 */
   LinkList p=L->next->next; /* p指向第一个结点 */
   if(i<=0||i>ListLength_CL(L)) /* 第i个元素不存在 */
     return ERROR;
   while(j<i)
   { /* 顺指针向后查找,直到p指向第i个元素 */
     p=p->next;
     j++;
   }
   *e=p->data; /* 取第i个元素 */
   return OK;
 }

 int LocateElem_CL(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
 { /* 初始条件：线性表L已存在，compare()是数据元素判定函数 */
   /* 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。 */
   /*           若这样的数据元素不存在，则返回值为0 */
   int i=0;
   LinkList p=L->next->next; /* p指向第一个结点 */
   while(p!=L->next)
   {
     i++;
     if(compare(p->data,e)) /* 满足关系 */
       return i;
     p=p->next;
   }
   return 0;
 }

 Status PriorElem_CL(LinkList L,ElemType cur_e,ElemType *pre_e)
 { /* 初始条件：线性表L已存在 */
   /* 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱， */
   /*           否则操作失败，pre_e无定义 */
   LinkList q,p=L->next->next; /* p指向第一个结点 */
   q=p->next;
   while(q!=L->next) /* p没到表尾 */
   {
     if(q->data==cur_e)
     {
       *pre_e=p->data;
       return TRUE;
     }
     p=q;
     q=q->next;
   }
   return FALSE;
 }

 Status NextElem_CL(LinkList L,ElemType cur_e,ElemType *next_e)
 { /* 初始条件：线性表L已存在 */
   /* 操作结果：若cur_e是L的数据元素,且不是最后一个,则用next_e返回它的后继， */
   /*           否则操作失败，next_e无定义 */
   LinkList p=L->next->next; /* p指向第一个结点 */
   while(p!=L) /* p没到表尾 */
   {
     if(p->data==cur_e)
     {
       *next_e=p->next->data;
       return TRUE;
     }
     p=p->next;
   }
   return FALSE;
 }

 Status ListInsert_CL(LinkList *L,int i,ElemType e) /* 改变L */
 { /* 在L的第i个位置之前插入元素e */
   LinkList p=(*L)->next,s; /* p指向头结点 */
   int j=0;
   if(i<=0||i>ListLength_CL(*L)+1) /* 无法在第i个元素之前插入 */
     return ERROR;
   while(j<i-1) /* 寻找第i-1个结点 */
   {
     p=p->next;
     j++;
   }
   s=(LinkList)malloc(sizeof(struct LNode)); /* 生成新结点 */
   s->data=e; /* 插入L中 */
   s->next=p->next;
   p->next=s;
   if(p==*L) /* 改变尾结点 */
     *L=s;
   return OK;
 }

 Status ListDelete_CL(LinkList *L,int i,ElemType *e) /* 改变L */
 { /* 删除L的第i个元素,并由e返回其值 */
   LinkList p=(*L)->next,q; /* p指向头结点 */
   int j=0;
   if(i<=0||i>ListLength_CL(*L)) /* 第i个元素不存在 */
     return ERROR;
   while(j<i-1) /* 寻找第i-1个结点 */
   {
     p=p->next;
     j++;
   }
   q=p->next; /* q指向待删除结点 */
   p->next=q->next;
   *e=q->data;
   if(*L==q) /* 删除的是表尾元素 */
     *L=p;
   free(q); /* 释放待删除结点 */
   return OK;
 }

 Status ListTraverse_CL(LinkList L,void(*vi)(ElemType))
 { /* 初始条件:L已存在。操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败 */
   LinkList p=L->next->next;
   while(p!=L->next)
   {
     vi(p->data);
     p=p->next;
   }
   printf("\n");
   return OK;
 }
**********BO2-5.c**********
 /* bo2-5.c 双链循环线性表(存储结构由c2-4.h定义)的基本操作(14个) */
 Status InitList(DuLinkList *L)
 { /* 产生空的双向循环链表L */
   *L=(DuLinkList)malloc(sizeof(DuLNode));
   if(*L)
   {
     (*L)->next=(*L)->prior=*L;
     return OK;
   }
   else
     return OVERFLOW;
 }

 Status DestroyList(DuLinkList *L)
 { /* 操作结果：销毁双向循环链表L */
   DuLinkList q,p=(*L)->next; /* p指向第一个结点 */
   while(p!=*L) /* p没到表头 */
   {
     q=p->next;
     free(p);
     p=q;
   }
   free(*L);
   *L=NULL;
   return OK;
 }

 Status ClearList(DuLinkList L) /* 不改变L */
 { /* 初始条件：L已存在。操作结果：将L重置为空表 */
   DuLinkList q,p=L->next; /* p指向第一个结点 */
   while(p!=L) /* p没到表头 */
   {
     q=p->next;
     free(p);
     p=q;
   }
   L->next=L->prior=L; /* 头结点的两个指针域均指向自身 */
   return OK;
 }

 Status ListEmpty(DuLinkList L)
 { /* 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
   if(L->next==L&&L->prior==L)
     return TRUE;
   else
     return FALSE;
 }

 int ListLength(DuLinkList L)
 { /* 初始条件：L已存在。操作结果：返回L中数据元素个数 */
   int i=0;
   DuLinkList p=L->next; /* p指向第一个结点 */
   while(p!=L) /* p没到表头 */
   {
     i++;
     p=p->next;
   }
   return i;
 }

 Status GetElem(DuLinkList L,int i,ElemType *e)
 { /* 当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR */
   int j=1; /* j为计数器 */
   DuLinkList p=L->next; /* p指向第一个结点 */
   while(p!=L&&j<i) /* 顺指针向后查找,直到p指向第i个元素或p指向头结点 */
   {
     p=p->next;
     j++;
   }
   if(p==L||j>i) /* 第i个元素不存在 */
     return ERROR;
   *e=p->data; /* 取第i个元素 */
   return OK;
 }

 int LocateElem(DuLinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
 { /* 初始条件：L已存在，compare()是数据元素判定函数 */
   /* 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。 */
   /*           若这样的数据元素不存在，则返回值为0 */
   int i=0;
   DuLinkList p=L->next; /* p指向第1个元素 */
   while(p!=L)
   {
     i++;
     if(compare(p->data,e)) /* 找到这样的数据元素 */
       return i;
     p=p->next;
   }
   return 0;
 }

 Status PriorElem(DuLinkList L,ElemType cur_e,ElemType *pre_e)
 { /* 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱， */
   /*           否则操作失败，pre_e无定义 */
   DuLinkList p=L->next->next; /* p指向第2个元素 */
   while(p!=L) /* p没到表头 */
   {
     if(p->data==cur_e)
     {
       *pre_e=p->prior->data;
       return TRUE;
     }
     p=p->next;
   }
   return FALSE;
 }

 Status NextElem(DuLinkList L,ElemType cur_e,ElemType *next_e)
 { /* 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继， */
   /*           否则操作失败，next_e无定义 */
   DuLinkList p=L->next->next; /* p指向第2个元素 */
   while(p!=L) /* p没到表头 */
   {
     if(p->prior->data==cur_e)
     {
       *next_e=p->data;
       return TRUE;
     }
     p=p->next;
   }
   return FALSE;
 }

 DuLinkList GetElemP(DuLinkList L,int i) /* 另加 */
 { /* 在双向链表L中返回第i个元素的位置指针(算法2.18、2.19要调用的函数) */
   int j;
   DuLinkList p=L;
   for(j=1;j<=i;j++)
     p=p->next;
   return p;
 }

 Status ListInsert(DuLinkList L,int i,ElemType e) /* 改进算法2.18 */
 { /* 在带头结点的双链循环线性表L中第i个位置之前插入元素e，i的合法值为1≤i≤表长+1 */
   DuLinkList p,s;
   if(i<1||i>ListLength(L)+1) /* i值不合法 */
     return ERROR;
   p=GetElemP(L,i-1); /* 在L中确定第i-1个元素的位置指针p */
   if(!p) /* p=NULL,即第i-1个元素不存在 */
     return ERROR;
   s=(DuLinkList)malloc(sizeof(DuLNode));
   if(!s)
     return OVERFLOW;
   s->data=e; /* 在第i-1个元素之后插入 */
   s->prior=p;
   s->next=p->next;
   p->next->prior=s;
   p->next=s;
   return OK;
 }

 Status ListDelete(DuLinkList L,int i,ElemType *e) /* 算法2.19 */
 { /* 删除带头结点的双链循环线性表L的第i个元素,i的合法值为1≤i≤表长+1 */
   DuLinkList p;
   if(i<1||i>ListLength(L)) /* i值不合法 */
     return ERROR;
   p=GetElemP(L,i);  /* 在L中确定第i个元素的位置指针p */
   if(!p) /* p=NULL,即第i个元素不存在 */
     return ERROR;
   *e=p->data;
   p->prior->next=p->next;
   p->next->prior=p->prior;
   free(p);
   return OK;
 }

 void ListTraverse(DuLinkList L,void(*visit)(ElemType))
 { /* 由双链循环线性表L的头结点出发,正序对每个数据元素调用函数visit() */
   DuLinkList p=L->next; /* p指向头结点 */
   while(p!=L)
   {
     visit(p->data);
     p=p->next;
   }
   printf("\n");
 }

 void ListTraverseBack(DuLinkList L,void(*visit)(ElemType))
 { /* 由双链循环线性表L的头结点出发,逆序对每个数据元素调用函数visit()。另加 */
   DuLinkList p=L->prior; /* p指向尾结点 */
   while(p!=L)
   {
     visit(p->data);
     p=p->prior;
   }
   printf("\n");
 }

**********BO2-6.c**********
 /* bo2-6.c 具有实用意义的线性链表(存储结构由c2-5.h定义)的24个基本操作 */
 Status MakeNode(Link *p,ElemType e)
 { /* 分配由p指向的值为e的结点，并返回OK；若分配失败。则返回ERROR */
   *p=(Link)malloc(sizeof(LNode));
   if(!*p)
     return ERROR;
   (*p)->data=e;
   return OK;
 }

 void FreeNode(Link *p)
 { /* 释放p所指结点 */
   free(*p);
   *p=NULL;
 }

 Status InitList(LinkList *L)
 { /* 构造一个空的线性链表 */
   Link p;
   p=(Link)malloc(sizeof(LNode)); /* 生成头结点 */
   if(p)
   {
     p->next=NULL;
     (*L).head=(*L).tail=p;
     (*L).len=0;
     return OK;
   }
   else
     return ERROR;
 }

 Status ClearList(LinkList *L)
 { /* 将线性链表L重置为空表，并释放原链表的结点空间 */
   Link p,q;
   if((*L).head!=(*L).tail)/* 不是空表 */
   {
     p=q=(*L).head->next;
     (*L).head->next=NULL;
     while(p!=(*L).tail)
     {
       p=q->next;
       free(q);
       q=p;
     }
     free(q);
     (*L).tail=(*L).head;
     (*L).len=0;
   }
   return OK;
 }

 Status DestroyList(LinkList *L)
 { /* 销毁线性链表L，L不再存在 */
   ClearList(L); /* 清空链表 */
   FreeNode(&(*L).head);
   (*L).tail=NULL;
   (*L).len=0;
   return OK;
 }

 Status InsFirst(LinkList *L,Link h,Link s) /* 形参增加L,因为需修改L */
 { /* h指向L的一个结点，把h当做头结点，将s所指结点插入在第一个结点之前 */
   s->next=h->next;
   h->next=s;
   if(h==(*L).tail) /* h指向尾结点 */
     (*L).tail=h->next; /* 修改尾指针 */
   (*L).len++;
   return OK;
 }

 Status DelFirst(LinkList *L,Link h,Link *q) /* 形参增加L,因为需修改L */
 { /* h指向L的一个结点，把h当做头结点，删除链表中的第一个结点并以q返回。 */
   /* 若链表为空(h指向尾结点)，q=NULL，返回FALSE */
   *q=h->next;
   if(*q) /* 链表非空 */
   {
     h->next=(*q)->next;
     if(!h->next) /* 删除尾结点 */
       (*L).tail=h; /* 修改尾指针 */
     (*L).len--;
     return OK;
   }
   else
     return FALSE; /* 链表空 */
 }

 Status Append(LinkList *L,Link s)
 { /* 将指针s(s->data为第一个数据元素)所指(彼此以指针相链,以NULL结尾)的 */
   /* 一串结点链接在线性链表L的最后一个结点之后,并改变链表L的尾指针指向新 */
   /* 的尾结点 */
   int i=1;
   (*L).tail->next=s;
   while(s->next)
   {
     s=s->next;
     i++;
   }
   (*L).tail=s;
   (*L).len+=i;
   return OK;
 }

 Position PriorPos(LinkList L,Link p)
 { /* 已知p指向线性链表L中的一个结点，返回p所指结点的直接前驱的位置 */
   /* 若无前驱，则返回NULL */
   Link q;
   q=L.head->next;
   if(q==p) /* 无前驱 */
     return NULL;
   else
   {
     while(q->next!=p) /* q不是p的直接前驱 */
       q=q->next;
     return q;
   }
 }

 Status Remove(LinkList *L,Link *q)
 { /* 删除线性链表L中的尾结点并以q返回，改变链表L的尾指针指向新的尾结点 */
   Link p=(*L).head;
   if((*L).len==0) /* 空表 */
   {
     *q=NULL;
     return FALSE;
   }
   while(p->next!=(*L).tail)
     p=p->next;
   *q=(*L).tail;
   p->next=NULL;
   (*L).tail=p;
   (*L).len--;
   return OK;
 }

 Status InsBefore(LinkList *L,Link *p,Link s)
 { /* 已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之前， */
   /* 并修改指针p指向新插入的结点 */
   Link q;
   q=PriorPos(*L,*p); /* q是p的前驱 */
   if(!q) /* p无前驱 */
     q=(*L).head;
   s->next=*p;
   q->next=s;
   *p=s;
   (*L).len++;
   return OK;
 }

 Status InsAfter(LinkList *L,Link *p,Link s)
 { /* 已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之后， */
   /* 并修改指针p指向新插入的结点 */
   if(*p==(*L).tail) /* 修改尾指针 */
     (*L).tail=s;
   s->next=(*p)->next;
   (*p)->next=s;
   *p=s;
   (*L).len++;
   return OK;
 }

 Status SetCurElem(Link p,ElemType e)
 { /* 已知p指向线性链表中的一个结点，用e更新p所指结点中数据元素的值 */
   p->data=e;
   return OK;
 }

 ElemType GetCurElem(Link p)
 { /* 已知p指向线性链表中的一个结点，返回p所指结点中数据元素的值 */
   return p->data;
 }

 Status ListEmpty(LinkList L)
 { /* 若线性链表L为空表，则返回TRUE，否则返回FALSE */
   if(L.len)
     return FALSE;
   else
     return TRUE;
 }

 int ListLength(LinkList L)
 { /* 返回线性链表L中元素个数 */
   return L.len;
 }

 Position GetHead(LinkList L)
 { /* 返回线性链表L中头结点的位置 */
   return L.head;
 }

 Position GetLast(LinkList L)
 { /* 返回线性链表L中最后一个结点的位置 */
   return L.tail;
 }

 Position NextPos(Link p)
 { /* 已知p指向线性链表L中的一个结点，返回p所指结点的直接后继的位置 */
   /* 若无后继，则返回NULL */
   return p->next;
 }

 Status LocatePos(LinkList L,int i,Link *p)
 { /* 返回p指示线性链表L中第i个结点的位置，并返回OK，i值不合法时返回ERROR */
   /* i=0为头结点 */
   int j;
   if(i<0||i>L.len)
     return ERROR;
   else
   {
     *p=L.head;
     for(j=1;j<=i;j++)
       *p=(*p)->next;
     return OK;
   }
 }

 Position LocateElem(LinkList L,ElemType e,Status (*compare)(ElemType,ElemType))
 { /* 返回线性链表L中第1个与e满足函数compare()判定关系的元素的位置， */
   /* 若不存在这样的元素，则返回NULL */
   Link p=L.head;
   do
     p=p->next;
   while(p&&!(compare(p->data,e))); /* 没到表尾且没找到满足关系的元素 */
   return p;
 }

 Status ListTraverse(LinkList L,void(*visit)(ElemType))
 { /* 依次对L的每个数据元素调用函数visit()。一旦visit()失败，则操作失败 */
   Link p=L.head->next;
   int j;
   for(j=1;j<=L.len;j++)
   {
     visit(p->data);
     p=p->next;
   }
   printf("\n");
   return OK;
 }

 Status OrderInsert(LinkList *L,ElemType e,int (*comp)(ElemType,ElemType))
 { /* 已知L为有序线性链表，将元素e按非降序插入在L中。（用于一元多项式） */
   Link o,p,q;
   q=(*L).head;
   p=q->next;
   while(p!=NULL&&comp(p->data,e)<0) /* p不是表尾且元素值小于e */
   {
     q=p;
     p=p->next;
   }
   o=(Link)malloc(sizeof(LNode)); /* 生成结点 */
   o->data=e; /* 赋值 */
   q->next=o; /* 插入 */
   o->next=p;
   (*L).len++; /* 表长加1 */
   if(!p) /* 插在表尾 */
     (*L).tail=o; /* 修改尾结点 */
   return OK;
 }

 Status LocateElemP(LinkList L,ElemType e,Position *q,int(*compare)(ElemType,ElemType))
 { /* 若升序链表L中存在与e满足判定函数compare()取值为0的元素，则q指示L中 */
   /* 第一个值为e的结点的位置，并返回TRUE；否则q指示第一个与e满足判定函数 */
   /* compare()取值>0的元素的前驱的位置。并返回FALSE。（用于一元多项式） */
   Link p=L.head,pp;
   do
   {
     pp=p;
     p=p->next;
   }while(p&&(compare(p->data,e)<0)); /* 没到表尾且p->data.expn<e.expn */
   if(!p||compare(p->data,e)>0) /* 到表尾或compare(p->data,e)>0 */
   {
     *q=pp;
     return FALSE;
   }
   else /* 找到 */
   {
     *q=p;
     return TRUE;
   }
 }

**********bo2-7.c**********
 /* bo2-7.c 多项式(存储结构由c2-6.h定义)的基本操作及算法2.22、2.23等 */
 #include"c2-5.h"
 #include"bo2-6.c"
 typedef LinkList polynomial;
 #define DestroyPolyn DestroyList /* 与bo2-6.cpp中的函数同义不同名 */
 #define PolynLength ListLength /* 与bo2-6.cpp中的函数同义不同名 */

 Status OrderInsertMerge(LinkList *L,ElemType e,int(* compare)(term,term))
 { /* 按有序判定函数compare()的约定，将值为e的结点插入或合并到升序链表L的适当位置 */
   Position q,s;
   if(LocateElemP(*L,e,&q,compare)) /* L中存在该指数项 */
   {
     q->data.coef+=e.coef; /* 改变当前结点系数的值 */
     if(!q->data.coef) /* 系数为0 */
     { /* 删除多项式L中当前结点 */
       s=PriorPos(*L,q); /* s为当前结点的前驱 */
       if(!s) /* q无前驱 */
         s=(*L).head;
       DelFirst(L,s,&q);
       FreeNode(&q);
     }
     return OK;
   }
   else /* 生成该指数项并插入链表 */
     if(MakeNode(&s,e)) /* 生成结点成功 */
     {
       InsFirst(L,q,s);
       return OK;
     }
     else /* 生成结点失败 */
       return ERROR;
 }

 int cmp(term a,term b) /* CreatPolyn()的实参 */
 { /* 依a的指数值<、=或>b的指数值，分别返回-1、0或+1 */
   if(a.expn==b.expn)
     return 0;
   else
     return (a.expn-b.expn)/abs(a.expn-b.expn);
 }

 void CreatPolyn(polynomial *P,int m) /* 算法2.22 */
 { /* 输入m项的系数和指数，建立表示一元多项式的有序链表P */
   Position q,s;
   term e;
   int i;
   InitList(P);
   printf("请依次输入%d个系数，指数：\n",m);
   for(i=1;i<=m;++i)
   { /* 依次输入m个非零项（可按任意顺序） */
     scanf("%f,%d",&e.coef,&e.expn);
     if(!LocateElemP(*P,e,&q,cmp)) /* 当前链表中不存在该指数项,cmp是实参 */
       if(MakeNode(&s,e)) /* 生成结点并插入链表 */
         InsFirst(P,q,s);
   }
 }

 void PrintPolyn(polynomial P)
 { /* 打印输出一元多项式P */
   Link q;
   q=P.head->next; /* q指向第一个结点 */
   printf("  系数    指数\n");
   while(q)
   {
     printf("%f  %d\n",q->data.coef,q->data.expn);
     q=q->next;
   }
 }

 void AddPolyn(polynomial *Pa,polynomial *Pb) /* 算法2.23 */
 { /* 多项式加法:Pa=Pa+Pb,并销毁一元多项式Pb */
   Position ha,hb,qa,qb;
   term a,b;
   ha=GetHead(*Pa);
   hb=GetHead(*Pb); /* ha和hb分别指向Pa和Pb的头结点 */
   qa=NextPos(ha);
   qb=NextPos(hb); /* qa和qb分别指向Pa和Pb中当前结点（现为第一个结点） */
   while(!ListEmpty(*Pa)&&!ListEmpty(*Pb)&&qa)
   { /* Pa和Pb均非空且ha没指向尾结点(qa!=0) */
     a=GetCurElem(qa);
     b=GetCurElem(qb); /* a和b为两表中当前比较元素 */
     switch(cmp(a,b))
     {
       case -1:ha=qa; /* 多项式Pa中当前结点的指数值小 */
               qa=NextPos(ha); /* ha和qa均向后移一个结点 */
               break;
       case 0: qa->data.coef+=qb->data.coef;
               /* 两者的指数值相等,修改Pa当前结点的系数值 */
               if(qa->data.coef==0) /* 删除多项式Pa中当前结点 */
               {
                 DelFirst(Pa,ha,&qa);
                 FreeNode(&qa);
               }
               else
                 ha=qa;
               DelFirst(Pb,hb,&qb);
               FreeNode(&qb);
               qb=NextPos(hb);
               qa=NextPos(ha);
               break;
       case 1: DelFirst(Pb,hb,&qb); /* 多项式Pb中当前结点的指数值小 */
               InsFirst(Pa,ha,qb);
               ha=ha->next;
               qb=NextPos(hb);
     }
   }
   if(!ListEmpty(*Pb))
   {
     (*Pb).tail=hb;
     Append(Pa,qb); /* 链接Pb中剩余结点 */
   }
   DestroyPolyn(Pb); /* 销毁Pb */
 }

 void AddPolyn1(polynomial *Pa,polynomial *Pb)
 { /* 另一种多项式加法的算法:Pa=Pa+Pb,并销毁一元多项式Pb */
   Position qb;
   term b;
   qb=GetHead(*Pb); /* qb指向Pb的头结点 */
   qb=qb->next; /* qb指向Pb的第一个结点 */
   while(qb)
   {
     b=GetCurElem(qb);
     OrderInsertMerge(Pa,b,cmp);
     qb=qb->next;
   }
   DestroyPolyn(Pb); /* 销毁Pb */
 }

 void Opposite(polynomial Pa)
 { /* 一元多项式系数取反 */
   Position p;
   p=Pa.head;
   while(p->next)
   {
     p=p->next;
     p->data.coef*=-1;
   }
 }

 void SubtractPolyn(polynomial *Pa,polynomial *Pb)
 { /* 多项式减法:Pa=Pa-Pb,并销毁一元多项式Pb */
   Opposite(*Pb);
   AddPolyn(Pa,Pb);
 }

 void MultiplyPolyn(polynomial *Pa,polynomial *Pb)
 { /* 多项式乘法:Pa=PaPb,并销毁一元多项式Pb */
   polynomial Pc;
   Position qa,qb;
   term a,b,c;
   InitList(&Pc);
   qa=GetHead(*Pa);
   qa=qa->next;
   while(qa)
   {
     a=GetCurElem(qa);
     qb=GetHead(*Pb);
     qb=qb->next;
     while(qb)
     {
       b=GetCurElem(qb);
       c.coef=a.coef*b.coef;
       c.expn=a.expn+b.expn;
       OrderInsertMerge(&Pc,c,cmp);
       qb=qb->next;
     }
     qa=qa->next;
   }
   DestroyPolyn(Pb); /* 销毁Pb */
   ClearList(Pa); /* 将Pa重置为空表 */
   (*Pa).head=Pc.head;
   (*Pa).tail=Pc.tail;
   (*Pa).len=Pc.len;
 }

**********BO2-8.C**********
 /* bo2-8.c 顺序表示的线性表(存储结构由c2-1.h定义)的扩展操作(10个) */
 #include"bo2-1.c"
 void InsertAscend(SqList *L,ElemType e)
 { /* 初始条件：按非降序排列的顺序线性表L已存在 */
   /* 操作结果：在L中按非降序插入新的数据元素e，L的长度加1 */
   ElemType *newbase,*p;
   int k;
   if((*L).length>=(*L).listsize) /* 当前存储空间已满,增加分配 */
   {
     newbase=(ElemType *)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(ElemType));
     if(!newbase)
       exit(OVERFLOW); /* 存储分配失败 */
     (*L).elem=newbase; /* 新基址 */
     (*L).listsize+=LISTINCREMENT; /* 增加存储容量 */
   }
   p=(*L).elem;
   for(k=1;k<=(*L).length;k++)
     if(e>*p)
       p++;
     else
       break;
   ListInsert(L,k,e); /* 函数在bo2-1.c中 */
 }

 void InsertDescend(SqList *L,ElemType e)
 { /* 初始条件：按非升序排列的顺序线性表L已存在 */
   /* 操作结果：在L中按非升序插入新的数据元素e，L的长度加1 */
   ElemType *newbase,*p;
   int k;
   if((*L).length>=(*L).listsize) /* 当前存储空间已满,增加分配 */
   {
     newbase=(ElemType *)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(ElemType));
     if(!newbase)
       exit(OVERFLOW); /* 存储分配失败 */
     (*L).elem=newbase; /* 新基址 */
     (*L).listsize+=LISTINCREMENT; /* 增加存储容量 */
   }
   p=(*L).elem;
   for(k=1;k<=(*L).length;k++)
     if(e<*p)
       p++;
     else
       break;
   ListInsert(L,k,e); /* 函数在bo2-1.c中 */
 }

 Status HeadInsert(SqList *L,ElemType e)
 { /* 初始条件：顺序线性表L已存在。操作结果：在L的头部插入新的数据元素e，L的长度加1 */
   ElemType *p,*q,*newbase;
   if((*L).length>=(*L).listsize)
   {
     newbase=(ElemType *)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(ElemType));
     if(!newbase)
       exit(OVERFLOW);
     (*L).elem=newbase;
     (*L).listsize+=LISTINCREMENT;
   }
   q=(*L).elem;
   for(p=(*L).elem+(*L).length-1;p>=q;--p)
     *(p+1)=*p;
   *q=e;
   (*L).length++;
   return OK;
 }

 Status EndInsert(SqList *L,ElemType e)
 { /* 初始条件：顺序线性表L已存在。操作结果：在L的尾部插入新的数据元素e，L的长度加1 */
   ElemType *q,*newbase;
   if((*L).length>=(*L).listsize) /* 当前存储空间已满,增加分配 */
   {
     newbase=(ElemType *)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(ElemType));
     if(!newbase)
       exit(OVERFLOW); /* 存储分配失败 */
     (*L).elem=newbase; /* 新基址 */
     (*L).listsize+=LISTINCREMENT; /* 增加存储容量 */
   }
   q=(*L).elem+(*L).length; /* q为插入位置 */
   *q=e;
   (*L).length++;
   return OK;
 }

 Status DeleteFirst(SqList *L,ElemType *e)
 { /* 初始条件：顺序线性表L已存在，且有不少于1个元素 */
   /* 操作结果：删除L的第一个数据元素，并由e返回其值，L的长度减1 */
   ElemType *p,*q;
   if(ListEmpty(*L)) /* 空表无法删除 */
     return ERROR;
   p=(*L).elem; /* p指向第一个元素 */
   *e=*p;
   q=(*L).elem+(*L).length-1; /* q指向最后一个元素 */
   for(++p;p<=q;++p)
     *(p-1)=*p; /* 从第2个元素起，所有元素向前移动一个位置 */
   (*L).length--; /* 当前长度减1 */
   return OK;
 }

 Status DeleteTail(SqList *L,ElemType *e)
 { /* 初始条件：顺序线性表L已存在，且有不少于1个元素 */
   /* 操作结果：删除L的最后一个数据元素，并用e返回其值，L的长度减1 */
   ElemType *p;
   if(!(*L).length) /* 空表 */
     return ERROR;
   p=(*L).elem+(*L).length-1; /* 最后一个数据元素的位置 */
   *e=*p; /* 被删除元素的值赋给e */
   (*L).length--; /* 表长减1 */
   return OK;
 }

 Status DeleteElem(SqList *L,ElemType e)
 { /* 删除表中值为e的元素，并返回TRUE；如无此元素，则返回FALSE */
   int i=0,j;
   while(i<(*L).length&&e!=*((*L).elem+i))
     i++;
   if(i==(*L).length) /* 没找到 */
     return FALSE;
   else
   {
     for(j=i;j<(*L).length;j++)
       *((*L).elem+j)=*((*L).elem+j+1); /* 后面的元素依次前移 */
     (*L).length--; /* 当前长度减1 */
     return TRUE;
   }
 }

 Status ReplaceElem(SqList L,int i,ElemType e)
 { /* 用e取代表L中第i个元素的值 */
   if(i<1||i>L.length) /* i值不合法 */
     exit(ERROR);
   *(L.elem+i-1)=e;
   return OK;
 }

 Status CreatAscend(SqList *L,int n)
 { /* 按非降序建立n个元素的线性表 */
   int i,j;
   ElemType e;
   InitList(L);
   printf("请输入%d个元素:\n",n);
   scanf("%d",&e);
   ListInsert(L,1,e); /* 在空表中插入第1个元素 */
   for(i=1;i<n;i++)
   {
     scanf("%d",&e);
     for(j=0;j<(*L).length;j++)
       if(e<=*((*L).elem+j))
         break;
     ListInsert(L,j+1,e); /* 插于表中 */
   }
   return TRUE;
 }

 Status CreatDescend(SqList *L,int n)
 { /* 按非升序建立n个元素的线性表 */
   int i,j;
   ElemType e;
   InitList(L);
   printf("请输入%d个元素:\n",n);
   scanf("%d",&e);
   ListInsert(L,1,e); /* 在空表中插入第1个元素 */
   for(i=1;i<n;i++)
   {
     scanf("%d",&e);
     for(j=0;j<(*L).length;j++)
       if(e>=*((*L).elem+j))
         break;
     ListInsert(L,j+1,e); /* 插于表中 */
   }
   return TRUE;
 }


**********Bo2-9.c**********
 /* bo2-9.c 单链表线性表(存储结构由c2-2.h定义)的扩展操作(11个) */
 void InsertAscend(LinkList L,ElemType e)
 { /* 初始条件：按非降序排列的线性表L已存在。操作结果：在L中按非降序插入新的数据元素e */
   LinkList q=L,p=L->next;
   while(p&&e>p->data)
   {
     q=p;
     p=p->next;
   }
   q->next=(LinkList)malloc(sizeof(struct LNode)); /* 插在q后 */
   q->next->data=e;
   q->next->next=p;
 }

 void InsertDescend(LinkList L,ElemType e)
 { /* 初始条件：按非升序排列的线性表L已存在。操作结果：在L中按非升序插入新的数据元素e */
   LinkList q=L,p=L->next;
   while(p&&e<p->data)
   {
     q=p;
     p=p->next;
   }
   q->next=(LinkList)malloc(sizeof(struct LNode)); /* 插在q后 */
   q->next->data=e;
   q->next->next=p;
 }

 Status HeadInsert(LinkList L,ElemType e)
 { /* 初始条件：线性表L已存在。操作结果：在L的头部插入新的数据元素e,作为链表的第一个元素 */
   LinkList s;
   s=(LinkList)malloc(sizeof(struct LNode)); /* 生成新结点 */
   s->data=e; /* 给结点赋值 */
   s->next=L->next; /* 插在表头 */
   L->next=s;
   return OK;
 }

 Status EndInsert(LinkList L,ElemType e)
 { /* 初始条件：线性表L已存在。操作结果：在L的尾部插入新的数据元素e,作为链表的最后一个元素 */
   LinkList p=L;
   while(p->next) /* 使p指向表尾元素 */
     p=p->next;
   p->next=(LinkList)malloc(sizeof(struct LNode)); /* 在表尾生成新结点 */
   p->next->data=e; /* 给新结点赋值 */
   p->next->next=NULL; /* 表尾 */
   return OK;
 }

 Status DeleteFirst(LinkList L,ElemType *e)
 { /* 初始条件：线性表L已存在，且有不少于1个元素 */
   /* 操作结果：删除L的第一个数据元素，并由e返回其值 */
   LinkList p=L->next;
   if(p)
   {
     *e=p->data;
     L->next=p->next;
     free(p);
     return OK;
   }
   else
     return ERROR;
 }

 Status DeleteTail(LinkList L,ElemType *e)
 { /* 初始条件：线性表L已存在，且有不少于1个元素 */
   /* 操作结果：删除L的最后一个数据元素，并用e返回其值 */
   LinkList p=L,q;
   if(!p->next) /* 链表为空 */
     return ERROR;
   while(p->next)
   {
     q=p;
     p=p->next;
   }
   q->next=NULL; /* 新尾结点的next域设为NULL */
   *e=p->data;
   free(p);
   return OK;
 }

 Status DeleteElem(LinkList L,ElemType e)
 { /* 删除表中值为e的元素，并返回TRUE；如无此元素，则返回FALSE */
   LinkList p=L,q;
   while(p)
   {
     q=p->next;
     if(q&&q->data==e)
     {
       p->next=q->next;
       free(q);
       return TRUE;
     }
     p=q;
   }
   return FALSE;
 }

 Status ReplaceElem(LinkList L,int i,ElemType e)
 { /* 用e取代表L中第i个元素的值 */
   LinkList p=L;
   int j=0;
   while(p->next&&j<i)
   {
     j++;
     p=p->next;
   }
   if(j==i)
   {
     p->data=e;
     return OK;
   }
   else /* 表中不存在第i个元素 */
     return ERROR;
 }

 Status CreatAscend(LinkList *L,int n)
 { /* 按非降序建立n个元素的线性表 */
   int j;
   LinkList p,q,s;
   if(n<=0)
     return ERROR;
   InitList(L);
   printf("请输入%d个元素:\n",n);
   s=(LinkList)malloc(sizeof(struct LNode)); /* 第一个结点 */
   scanf("%d",&s->data);
   s->next=NULL;
   (*L)->next=s;
   for(j=1;j<n;j++)
   {
     s=(LinkList)malloc(sizeof(struct LNode)); /* 其余结点 */
     scanf("%d",&s->data);
     q=*L;
     p=(*L)->next;
     while(p&&p->data<s->data) /* p没到表尾，且所指元素值小于新值 */
     {
       q=p;
       p=p->next; /* 指针后移 */
     }
     s->next=q->next; /* 元素插在q的后面 */
     q->next=s;
   }
   return OK;
 }

 Status CreatDescend(LinkList *L,int n)
 { /* 按非升序建立n个元素的线性表 */
   int j;
   LinkList p,q,s;
   if(n<=0)
     return ERROR;
   InitList(L);
   printf("请输入%d个元素:\n",n);
   s=(LinkList)malloc(sizeof(struct LNode)); /* 第一个结点 */
   scanf("%d",&s->data);
   s->next=NULL;
   (*L)->next=s;
   for(j=1;j<n;j++)
   {
     s=(LinkList)malloc(sizeof(struct LNode)); /* 其余结点 */
     scanf("%d",&s->data);
     q=*L;
     p=(*L)->next;
     while(p&&p->data>s->data) /* p没到表尾，且所指元素值大于新值 */
     {
       q=p;
       p=p->next; /* 指针后移 */
     }
     s->next=q->next; /* 元素插在q的后面 */
     q->next=s;
   }
   return OK;
 }

 Status GetFirstElem(LinkList L,ElemType *e)
 { /* 返回表头元素的值 */
   LinkList p=L->next;
   if(!p) /* 空表 */
     return ERROR;
   else /* 非空表 */
     *e=p->data;
   return OK;
 }

**********c1.h**********
 /* c1.h (程序名) */
 #include<string.h>
 #include<ctype.h>
 #include<malloc.h> /* malloc()等 */
 #include<limits.h> /* INT_MAX等 */
 #include<stdio.h> /* EOF(=^Z或F6),NULL */
 #include<stdlib.h> /* atoi() */
 #include<io.h> /* eof() */
 #include<math.h> /* floor(),ceil(),abs() */
 #include<process.h> /* exit() */
 /* 函数结果状态代码 */
 #define TRUE 1
 #define FALSE 0
 #define OK 1
 #define ERROR 0
 #define INFEASIBLE -1
 /* #define OVERFLOW -2 因为在math.h中已定义OVERFLOW的值为3,故去掉此行 */
 typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
 typedef int Boolean; /* Boolean是布尔类型,其值是TRUE或FALSE */

**********C2-1.H**********
 /* c2-1.h 线性表的动态分配顺序存储结构 */
 #define LIST_INIT_SIZE 10 /* 线性表存储空间的初始分配量 */
 #define LISTINCREMENT 2 /* 线性表存储空间的分配增量 */
 typedef struct
 {
   ElemType *elem; /* 存储空间基址 */
   int length; /* 当前长度 */
   int listsize; /* 当前分配的存储容量(以sizeof(ElemType)为单位) */
 }SqList;

**********C2-2.H**********
 /* c2-2.h 线性表的单链表存储结构 */
 struct LNode
 {
   ElemType data;
   struct LNode *next;
 };
 typedef struct LNode *LinkList; /* 另一种定义LinkList的方法 */

**********C2-3.H**********
 /* c2-3.h 线性表的静态单链表存储结构 */
 #define MAXSIZE 100 /* 链表的最大长度 */
 typedef struct
 {
   ElemType data;
   int cur;
 }component,SLinkList[MAXSIZE];

**********C2-4.H**********
 /* c2-4.h 线性表的双向链表存储结构 */
 typedef struct DuLNode
 {
   ElemType data;
   struct DuLNode *prior,*next;
 }DuLNode,*DuLinkList;

**********C2-5.H**********
 /* c2-5.h 带头结点的线性链表类型 */
 typedef struct LNode /* 结点类型 */
 {
   ElemType data;
   struct LNode *next;
 }LNode,*Link,*Position;

 typedef struct LinkList /* 链表类型 */
 {
   Link head,tail; /* 分别指向线性链表中的头结点和最后一个结点 */
   int len; /* 指示线性链表中数据元素的个数 */
 }LinkList;

**********C2-6.H**********
 /* c2-6.h 抽象数据类型Polynomial的实现 */
 typedef struct /* 项的表示,多项式的项作为LinkList的数据元素 */
 {
   float coef; /* 系数 */
   int expn; /* 指数 */
 }term,ElemType;
 /* 两个类型名:term用于本ADT,ElemType为LinkList的数据对象名 */
**********MAIN2-1.c**********
 /* main2-1.c 检验bo2-1.c的主程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-1.h"
 #include"bo2-1.c"

 Status comp(ElemType c1,ElemType c2) /* 数据元素判定函数(平方关系) */
 {
   if(c1==c2*c2)
     return TRUE;
   else
     return FALSE;
 }

 void visit(ElemType *c) /* ListTraverse()调用的函数(类型要一致) */
 {
   printf("%d ",*c);
 }

 void dbl(ElemType *c) /* ListTraverse()调用的另一函数(元素值加倍) */
 {
   *c*=2;
 }

 void main()
 {
   SqList L;
   ElemType e,e0;
   Status i;
   int j,k;
   i=InitList(&L);
   printf("初始化L后：L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
   for(j=1;j<=5;j++)
     i=ListInsert(&L,1,j);
   printf("在L的表头依次插入1～5后：*L.elem=");
   for(j=1;j<=5;j++)
     printf("%d ",*(L.elem+j-1));
   printf("\n");
   printf("L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
   i=ListEmpty(L);
   printf("L是否空：i=%d(1:是 0:否)\n",i);
   i=ClearList(&L);
   printf("清空L后：L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
   i=ListEmpty(L);
   printf("L是否空：i=%d(1:是 0:否)\n",i);
   for(j=1;j<=10;j++)
     ListInsert(&L,j,j);
   printf("在L的表尾依次插入1～10后：*L.elem=");
   for(j=1;j<=10;j++)
     printf("%d ",*(L.elem+j-1));
   printf("\n");
   printf("L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
   ListInsert(&L,1,0);
   printf("在L的表头插入0后：*L.elem=");
   for(j=1;j<=ListLength(L);j++) /* ListLength(L)为元素个数 */
     printf("%d ",*(L.elem+j-1));
   printf("\n");
   printf("L.elem=%u(有可能改变) L.length=%d(改变) L.listsize=%d(改变)\n",L.elem,L.length,L.listsize);
   GetElem(L,5,&e);
   printf("第5个元素的值为：%d\n",e);
   for(j=3;j<=4;j++)
   {
     k=LocateElem(L,j,comp);
     if(k)
       printf("第%d个元素的值为%d的平方\n",k,j);
     else
       printf("没有值为%d的平方的元素\n",j);
   }
   for(j=1;j<=2;j++) /* 测试头两个数据 */
   {
     GetElem(L,j,&e0); /* 把第j个数据赋给e0 */
     i=PriorElem(L,e0,&e); /* 求e0的前驱 */
     if(i==INFEASIBLE)
       printf("元素%d无前驱\n",e0);
     else
       printf("元素%d的前驱为：%d\n",e0,e);
   }
   for(j=ListLength(L)-1;j<=ListLength(L);j++) /* 最后两个数据 */
   {
     GetElem(L,j,&e0); /* 把第j个数据赋给e0 */
     i=NextElem(L,e0,&e); /* 求e0的后继 */
     if(i==INFEASIBLE)
       printf("元素%d无后继\n",e0);
     else
       printf("元素%d的后继为：%d\n",e0,e);
   }
   k=ListLength(L); /* k为表长 */
   for(j=k+1;j>=k;j--)
   {
     i=ListDelete(&L,j,&e); /* 删除第j个数据 */
     if(i==ERROR)
       printf("删除第%d个数据失败\n",j);
     else
       printf("删除的元素值为：%d\n",e);
   }
   printf("依次输出L的元素：");
   ListTraverse(L,visit); /* 依次对元素调用visit()，输出元素的值 */
   printf("L的元素值加倍后：");
   ListTraverse(L,dbl); /* 依次对元素调用dbl()，元素值乘2 */
   ListTraverse(L,visit);
   DestroyList(&L);
   printf("销毁L后：L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
 }
**********MAIN2-2.c**********
 /* main2-2.c 检验bo2-2.c的主程序(与main2-1.c很像) */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-2.h" /* 与main2-1.c不同 */
 #include"bo2-2.c" /* 与main2-1.c不同 */

 Status comp(ElemType c1,ElemType c2)
 { /* 数据元素判定函数(相等为TRUE,否则为FALSE) */
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 void visit(ElemType c) /* 与main2-1.c不同 */
 {
   printf("%d ",c);
 }

 void main() /* 除了几个输出语句外，主程和main2-1.c很像 */
 {
   LinkList L; /* 与main2-1.c不同 */
   ElemType e,e0;
   Status i;
   int j,k;
   i=InitList(&L);
   for(j=1;j<=5;j++)
     i=ListInsert(L,1,j);
   printf("在L的表头依次插入1～5后：L=");
   ListTraverse(L,visit); /* 依次对元素调用visit()，输出元素的值 */
   i=ListEmpty(L);
   printf("L是否空：i=%d(1:是 0:否)\n",i);
   i=ClearList(L);
   printf("清空L后：L=");
   ListTraverse(L,visit);
   i=ListEmpty(L);
   printf("L是否空：i=%d(1:是 0:否)\n",i);
   for(j=1;j<=10;j++)
     ListInsert(L,j,j);
   printf("在L的表尾依次插入1～10后：L=");
   ListTraverse(L,visit);
   GetElem(L,5,&e);
   printf("第5个元素的值为：%d\n",e);
   for(j=0;j<=1;j++)
   {
     k=LocateElem(L,j,comp);
     if(k)
       printf("第%d个元素的值为%d\n",k,j);
     else
       printf("没有值为%d的元素\n",j);
   }
   for(j=1;j<=2;j++) /* 测试头两个数据 */
   {
     GetElem(L,j,&e0); /* 把第j个数据赋给e0 */
     i=PriorElem(L,e0,&e); /* 求e0的前驱 */
     if(i==INFEASIBLE)
       printf("元素%d无前驱\n",e0);
     else
       printf("元素%d的前驱为：%d\n",e0,e);
   }
   for(j=ListLength(L)-1;j<=ListLength(L);j++)/*最后两个数据 */
   {
     GetElem(L,j,&e0); /* 把第j个数据赋给e0 */
     i=NextElem(L,e0,&e); /* 求e0的后继 */
     if(i==INFEASIBLE)
       printf("元素%d无后继\n",e0);
     else
       printf("元素%d的后继为：%d\n",e0,e);
   }
   k=ListLength(L); /* k为表长 */
   for(j=k+1;j>=k;j--)
   {
     i=ListDelete(L,j,&e); /* 删除第j个数据 */
     if(i==ERROR)
       printf("删除第%d个数据失败\n",j);
     else
       printf("删除的元素为：%d\n",e);
   }
   printf("依次输出L的元素：");
   ListTraverse(L,visit);
   DestroyList(&L);
   printf("销毁L后：L=%u\n",L);
 }
**********MAIN2-31.C**********
 /* main2-31.c 检验bo2-3.c和bo2-31.cpp的主程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-3.h"
 #include"bo2-3.c" /* 两种方法都适用的函数在此文件中 */
 #include"bo2-31.c"

 void visit(ElemType c)
 {
   printf("%d ",c);
 }

 void main()
 {
   int j,k;
   Status i;
   ElemType e,e0;
   SLinkList L;
   InitList(L);
   for(j=1;j<=5;j++)
     i=ListInsert(L,1,j);
   printf("在L的表头依次插入1～5后：L=");
   ListTraverse(L,visit);
   i=ListEmpty(L);
   printf("L是否空:i=%d(1:是 0:否)表L的长度=%d\n",i,ListLength(L));
   i=ClearList(L);
   printf("清空L后：L=");
   ListTraverse(L,visit);
   i=ListEmpty(L);
   printf("L是否空:i=%d(1:是 0:否)表L的长度=%d\n",i,ListLength(L));
   for(j=1;j<=10;j++)
     ListInsert(L,j,j);
   printf("在L的表尾依次插入1～10后：L=");
   ListTraverse(L,visit);
   GetElem(L,5,&e);
   printf("第5个元素的值为：%d\n",e);
   for(j=0;j<=1;j++)
   {
     k=LocateElem(L,j);
     if(k)
       printf("值为%d的元素在静态链表中的位序为%d\n",j,k);
     else
       printf("没有值为%d的元素\n",j);
   }
   for(j=1;j<=2;j++) /* 测试头两个数据 */
   {
     GetElem(L,j,&e0); /* 把第j个数据赋给e0 */
     i=PriorElem(L,e0,&e); /* 求e0的前驱 */
     if(!i)
       printf("元素%d无前驱\n",e0);
     else
       printf("元素%d的前驱为：%d\n",e0,e);
   }
   for(j=ListLength(L)-1;j<=ListLength(L);j++) /* 最后两个数据 */
   {
     GetElem(L,j,&e0); /* 把第j个数据赋给e0 */
     i=NextElem(L,e0,&e); /* 求e0的后继 */
     if(!i)
       printf("元素%d无后继\n",e0);
     else
       printf("元素%d的后继为：%d\n",e0,e);
   }
   k=ListLength(L); /* k为表长 */
   for(j=k+1;j>=k;j--)
   {
     i=ListDelete(L,j,&e); /* 删除第j个数据 */
     if(i)
       printf("删除的元素为：%d\n",e);
     else
       printf("删除第%d个数据失败\n",j);
   }
   printf("依次输出L的元素：");
   ListTraverse(L,visit); /* 依次对元素调用visit()，输出元素的值 */
 }

**********MAIN2-32.C**********
 /* main2-32.c 检验bo2-3.c和bo2-32.c的主程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-3.h"
 #include"bo2-3.c" /* 两种方法都适用的函数在此文件中 */
 #include"bo2-32.c"

 void visit(ElemType c)
 {
   printf("%d ",c);
 }

 void main()
 {
   int j,k,La,Lb;
   Status i;
   ElemType e,e0;
   SLinkList L;
   InitSpace(L); /* 建立备用链表 */
   La=InitList(L); /* 初始化链表La */
   Lb=InitList(L); /* 初始化链表Lb */
   printf("La表空否？%d(1:空 0:否) La的表长=%d\n",ListEmpty(L,La),ListLength(L,La));
   for(j=1;j<=5;j++)
     ListInsert(L,La,1,j);
   printf("在空表La的表头依次插入1～5后：La=");
   ListTraverse(L,La,visit);
   for(j=1;j<=5;j++)
     ListInsert(L,Lb,j,j);
   printf("在空表Lb的表尾依次插入1～5后：Lb=");
   ListTraverse(L,Lb,visit);
   printf("La表空否？%d(1:空 0:否) La的表长=%d\n",ListEmpty(L,La),ListLength(L,La));
   ClearList(L,La);
   printf("清空La后：La=");
   ListTraverse(L,La,visit);
   printf("La表空否？%d(1:空 0:否) La的表长=%d\n",ListEmpty(L,La),ListLength(L,La));
   for(j=2;j<8;j+=5)
   {
     i=GetElem(L,Lb,j,&e);
     if(i)
       printf("Lb表的第%d个元素的值为：%d\n",j,e);
     else
       printf("Lb表不存在第%d个元素！\n",j,e);
   }
   for(j=0;j<=1;j++)
   {
     k=LocateElem(L,Lb,j);
     if(k)
       printf("Lb表中值为%d的元素在静态链表中的位序为%d\n",j,k);
     else
       printf("Lb表中没有值为%d的元素\n",j);
   }
   for(j=1;j<=2;j++) /* 测试头两个数据 */
   {
     GetElem(L,Lb,j,&e0); /* 把第j个数据赋给e0 */
     i=PriorElem(L,Lb,e0,&e); /* 求e0的前驱 */
     if(!i)
       printf("Lb表中的元素%d无前驱\n",e0);
     else
       printf("Lb表中元素%d的前驱为：%d\n",e0,e);
   }
   for(j=ListLength(L,Lb)-1;j<=ListLength(L,Lb);j++) /* 最后两个数据 */
   {
     GetElem(L,Lb,j,&e0); /* 把第j个数据赋给e0 */
     i=NextElem(L,Lb,e0,&e); /* 求e0的后继 */
     if(!i)
       printf("Lb表中元素%d无后继\n",e0);
     else
       printf("Lb表中元素%d的后继为：%d\n",e0,e);
   }
   k=ListLength(L,Lb); /* k为表长 */
   for(j=k+1;j>=k;j--)
   {
     i=ListDelete(L,Lb,j,&e); /* 删除第j个数据 */
     if(i)
       printf("Lb表中第%d个元素为%d,已删除。\n",j,e);
     else
       printf("删除Lb表中第%d个数据失败(不存在此元素)。\n",j);
   }
   printf("依次输出Lb的元素：");
   ListTraverse(L,Lb,visit); /* 依次对元素调用visit()，输出元素的值 */
 }

**********MAIN2-4.c**********
 /* main2-4.c 单循环链表,检验bo2-4.c的主程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-2.h"
 #include"bo2-4.c"

 Status compare(ElemType c1,ElemType c2)
 {
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 void visit(ElemType c)
 {
   printf("%d ",c);
 }

 void main()
 {
   LinkList L;
   ElemType e;
   int j;
   Status i;
   i=InitList_CL(&L); /* 初始化单循环链表L */
   printf("初始化单循环链表L i=%d (1:初始化成功)\n",i);
   i=ListEmpty_CL(L);
   printf("L是否空 i=%d(1:空 0:否)\n",i);
   ListInsert_CL(&L,1,3); /* 在L中依次插入3,5 */
   ListInsert_CL(&L,2,5);
   i=GetElem_CL(L,1,&e);
   j=ListLength_CL(L);
   printf("L中数据元素个数=%d,第1个元素的值为%d。\n",j,e);
   printf("L中的数据元素依次为：");
   ListTraverse_CL(L,visit);
   PriorElem_CL(L,5,&e); /* 求元素5的前驱 */
   printf("5前面的元素的值为%d。\n",e);
   NextElem_CL(L,3,&e); /* 求元素3的后继 */
   printf("3后面的元素的值为%d。\n",e);
   printf("L是否空 %d(1:空 0:否)\n",ListEmpty_CL(L));
   j=LocateElem_CL(L,5,compare);
   if(j)
     printf("L的第%d个元素为5。\n",j);
   else
     printf("不存在值为5的元素\n");
   i=ListDelete_CL(&L,2,&e);
   printf("删除L的第2个元素：\n");
   if(i)
   {
     printf("删除的元素值为%d,现在L中的数据元素依次为：",e);
     ListTraverse_CL(L,visit);
   }
   else
     printf("删除不成功！\n");
   printf("清空L：%d(1: 成功)\n",ClearList_CL(&L));
   printf("清空L后，L是否空：%d(1:空 0:否)\n",ListEmpty_CL(L));
   printf("销毁L：%d(1: 成功)\n",DestroyList_CL(&L));
 }

**********MAIN2-5.c**********
 /* main2-5.c 检验bo2-5.c的主程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-4.h"
 #include"bo2-5.c"

 Status compare(ElemType c1,ElemType c2) /* 数据元素判定函数(判定相等) */
 {
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 void vd(ElemType c) /* ListTraverse()调用的函数(类型一致) */
 {
   printf("%d ",c);
 }

 void main()
 {
   DuLinkList L;
   int i,n;
   Status j;
   ElemType e;
   InitList(&L);
   for(i=1;i<=5;i++)
     ListInsert(L,i,i); /* 在第i个结点之前插入i */
   printf("正序输出链表：");
   ListTraverse(L,vd); /* 正序输出 */
   printf("逆序输出链表：");
   ListTraverseBack(L,vd); /* 逆序输出 */
   n=2;
   ListDelete(L,n,&e); /* 删除并释放第n个结点 */
   printf("删除第%d个结点，值为%d，其余结点为：",n,e);
   ListTraverse(L,vd); /* 正序输出 */
   printf("链表的元素个数为%d\n",ListLength(L));
   printf("链表是否空：%d(1:是 0:否)\n",ListEmpty(L));
   ClearList(L); /* 清空链表 */
   printf("清空后，链表是否空：%d(1:是 0:否)\n",ListEmpty(L));
   for(i=1;i<=5;i++)
     ListInsert(L,i,i); /* 重新插入5个结点 */
   ListTraverse(L,vd); /* 正序输出 */
   n=3;
   j=GetElem(L,n,&e); /* 将链表的第n个元素赋值给e */
   if(j)
     printf("链表的第%d个元素值为%d\n",n,e);
   else
     printf("不存在第%d个元素\n",n);
   n=4;
   i=LocateElem(L,n,compare);
   if(i)
     printf("等于%d的元素是第%d个\n",n,i);
   else
     printf("没有等于%d的元素\n",n);
   j=PriorElem(L,n,&e);
   if(j)
     printf("%d的前驱是%d\n",n,e);
   else
     printf("不存在%d的前驱\n",n);
   j=NextElem(L,n,&e);
   if(j)
     printf("%d的后继是%d\n",n,e);
   else
     printf("不存在%d的后继\n",n);
   DestroyList(&L);
 }
**********MAIN2-6.c**********
 /* main2-6.c 检验bo2-6.cpp的主程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-5.h"
 #include"bo2-6.c"
 Status compare(ElemType c1,ElemType c2) /* c1等于c2 */
 {
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 int cmp(ElemType a,ElemType b)
 { /* 根据a<、=或>b,分别返回-1、0或1 */
   if(a==b)
     return 0;
   else
     return (a-b)/abs(a-b);
 }

 void visit(ElemType c)
 {
   printf("%d ",c);
 }

 void main()
 {
   Link p,h;
   LinkList L;
   Status i;
   int j,k;
   i=InitList(&L);
   if(!i) /* 初始化空的线性表L不成功 */
     exit(FALSE); /* 退出程序运行 */
   for(j=1;j<=2;j++)
   {
     MakeNode(&p,j); /* 生成由p指向、值为j的结点 */
     InsFirst(&L,L.tail,p); /* 插在表尾 */
   }
   OrderInsert(&L,0,cmp); /* 按升序插在有序表头 */
   for(j=0;j<=3;j++)
   {
     i=LocateElemP(L,j,&p,cmp);
     if(i)
       printf("链表中有值为%d的元素。\n",p->data);
     else
       printf("链表中没有值为%d的元素。\n",j);
   }
   printf("输出链表：");
   ListTraverse(L,visit); /* 输出L */
   for(j=1;j<=4;j++)
   {
     printf("删除表头结点：");
     DelFirst(&L,L.head,&p); /* 删除L的首结点，并以p返回 */
     if(p)
       printf("%d\n",GetCurElem(p));
     else
       printf("表空，无法删除 p=%u\n",p);
   }
   printf("L中结点个数=%d L是否空 %d(1:空 0:否)\n",ListLength(L),ListEmpty(L));
   MakeNode(&p,10);
   p->next=NULL; /* 尾结点 */
   for(j=4;j>=1;j--)
   {
     MakeNode(&h,j*2);
     h->next=p;
     p=h;
   } /* h指向一串5个结点，其值依次是2 4 6 8 10 */
   Append(&L,h); /* 把结点h链接在线性链表L的最后一个结点之后 */
   OrderInsert(&L,12,cmp); /* 按升序插在有序表尾头 */
   OrderInsert(&L,7,cmp); /* 按升序插在有序表中间 */
   printf("输出链表：");
   ListTraverse(L,visit); /* 输出L */
   for(j=1;j<=2;j++)
   {
     p=LocateElem(L,j*5,compare);
     if(p)
       printf("L中存在值为%d的结点。\n",j*5);
     else
       printf("L中不存在值为%d的结点。\n",j*5);
   }
   for(j=1;j<=2;j++)
   {
     LocatePos(L,j,&p); /* p指向L的第j个结点 */
     h=PriorPos(L,p); /* h指向p的前驱 */
     if(h)
       printf("%d的前驱是%d。\n",p->data,h->data);
     else
       printf("%d没前驱。\n",p->data);
   }
   k=ListLength(L);
   for(j=k-1;j<=k;j++)
   {
     LocatePos(L,j,&p); /* p指向L的第j个结点 */
     h=NextPos(p); /* h指向p的后继 */
     if(h)
       printf("%d的后继是%d。\n",p->data,h->data);
     else
       printf("%d没后继。\n",p->data);
   }
   printf("L中结点个数=%d L是否空 %d(1:空 0:否)\n",ListLength(L),ListEmpty(L));
   p=GetLast(L); /* p指向最后一个结点 */
   SetCurElem(p,15); /* 将最后一个结点的值变为15 */
   printf("第1个元素为%d 最后1个元素为%d\n",GetCurElem(GetHead(L)->next),GetCurElem(p));
   MakeNode(&h,10);
   InsBefore(&L,&p,h); /* 将10插到尾结点之前，p指向新结点 */
   p=p->next; /* p恢复为尾结点 */
   MakeNode(&h,20);
   InsAfter(&L,&p,h); /* 将20插到尾结点之后 */
   k=ListLength(L);
   printf("依次删除表尾结点并输出其值：");
   for(j=0;j<=k;j++)
   {
     i=Remove(&L,&p);
     if(!i) /* 删除不成功 */
       printf("删除不成功 p=%u\n",p);
     else
       printf("%d ",p->data);
   }
   MakeNode(&p,29); /* 重建具有1个结点(29)的链表 */
   InsFirst(&L,L.head,p);
   DestroyList(&L); /* 销毁线性链表L */
   printf("销毁线性链表L之后: L.head=%u L.tail=%u L.len=%d\n",L.head,L.tail,L.len);
 }

**********MAIN2-7.c**********
 /* main2-7.c 检验bo2-7.cpp的主程序 */
 #include"c1.h"
 #include"c2-6.h"
 #include"bo2-7.c"
 void main()
 {
   polynomial p,q;
   int m;
   printf("请输入第一个一元多项式的非零项的个数：");
   scanf("%d",&m);
   CreatPolyn(&p,m);
   printf("请输入第二个一元多项式的非零项的个数：");
   scanf("%d",&m);
   CreatPolyn(&q,m);
   AddPolyn(&p,&q);
   printf("两个一元多项式相加的结果：\n");
   PrintPolyn(p);
   printf("请输入第三个一元多项式的非零项的个数：");
   scanf("%d",&m);
   CreatPolyn(&q,m);
   AddPolyn1(&p,&q);
   printf("两个一元多项式相加的结果(另一种方法)：\n");
   PrintPolyn(p);
   printf("请输入第四个一元多项式的非零项的个数：");
   scanf("%d",&m);
   CreatPolyn(&q,m);
   SubtractPolyn(&p,&q);
   printf("两个一元多项式相减的结果：\n");
   PrintPolyn(p);
   printf("请输入第五个一元多项式的非零项的个数：");
   scanf("%d",&m);
   CreatPolyn(&q,m);
   MultiplyPolyn(&p,&q);
   printf("两个一元多项式相乘的结果：\n");
   PrintPolyn(p);
   DestroyPolyn(&p);
 }

**********MAIN2-8.C**********
 /* main2-8.c 检验bo2-8.c的主程序 */
 #include"c1.h"
 typedef int ElemType; /* 也可以定义ElemType为实型或双精度型 */
 #include"c2-1.h"
 #include"bo2-8.c"

 void visit(ElemType *c) /* ListTraverse()调用的函数(类型要一致) */
 {
   printf("%d ",*c);
 }

 void main()
 {
   SqList L;
   ElemType d,e;
   Status i;
   int n;
   printf("按非降序建立n个元素的线性表L,请输入元素个数n: ");
   scanf("%d",&n);
   CreatAscend(&L,n);
   printf("依次输出L的元素：");
   ListTraverse(L,visit);
   InsertAscend(&L,10); /* 按非降序插入元素10 */
   printf("按非降序插入元素10后，线性表L为：");
   ListTraverse(L,visit);
   HeadInsert(&L,12); /* 在L的头部插入12 */
   EndInsert(&L,9); /* 在L的尾部插入9 */
   printf("在L的头部插入12，尾部插入9后，线性表L为：");
   ListTraverse(L,visit);
   printf("请输入要删除的元素的值: ");
   scanf("%d",&e);
   i=DeleteElem(&L,e);
   if(i)
     printf("成功删除%d\n",e);
   else
     printf("不存在元素%d!\n",e);
   printf("线性表L为：");
   ListTraverse(L,visit);
   printf("请输入要取代的元素的序号 元素的新值: ");
   scanf("%d%d",&n,&e);
   ReplaceElem(L,n,e);
   printf("线性表L为：");
   ListTraverse(L,visit);
   DestroyList(&L);
   printf("销毁L后,按非升序重新建立n个元素的线性表L,请输入元素个数n(>2): ");
   scanf("%d",&n);
   CreatDescend(&L,n);
   printf("依次输出L的元素：");
   ListTraverse(L,visit);
   InsertDescend(&L,10); /* 按非升序插入元素10 */
   printf("按非升序插入元素10后，线性表L为：");
   ListTraverse(L,visit);
   printf("请输入要删除的元素的值: ");
   scanf("%d",&e);
   i=DeleteElem(&L,e);
   if(i)
     printf("成功删除%d\n",e);
   else
     printf("不存在元素%d!\n",e);
   printf("线性表L为：");
   ListTraverse(L,visit);
   DeleteFirst(&L,&e);
   DeleteTail(&L,&d);
   printf("删除表头元素%d和表尾元素%d后,线性表L为：\n",e,d);
   ListTraverse(L,visit);
 }
**********MAIN2-9.C**********
 /* main2-9.c 检验bo2-9.c的主程序(除输出语句外，和main2-8.c很像) */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-2.h" /* 此句和main2-8.c不同 */
 #include"bo2-2.c" /* 加此句 */
 #include"bo2-9.c" /* 此句和main2-8.c不同 */

 void visit(ElemType c) /* ListTraverse()调用的函数(类型要一致) */
 {
   printf("%d ",c);
 }

 void main()
 {
   LinkList L; /* 此句和main2-8.c不同 */
   ElemType d,e;
   Status i;
   int n;
   printf("按非降序建立n个元素的线性表L,请输入元素个数n: ");
   scanf("%d",&n);
   CreatAscend(&L,n);
   printf("依次输出L的元素：");
   ListTraverse(L,visit);
   InsertAscend(L,10); /* 按非降序插入元素10 */
   printf("按非降序插入元素10后，线性表L为：");
   ListTraverse(L,visit);
   HeadInsert(L,12); /* 在L的头部插入12 */
   EndInsert(L,9); /* 在L的尾部插入9 */
   printf("在L的头部插入12，尾部插入9后，线性表L为：");
   ListTraverse(L,visit);
   i=GetFirstElem(L,&e); /* 此句加 */
   printf("第1个元素是: %d\n",e); /* 此句加 */
   printf("请输入要删除的元素的值: ");
   scanf("%d",&e);
   i=DeleteElem(L,e);
   if(i)
     printf("成功删除%d!\n",e);
   else
     printf("不存在元素%d!\n",e);
   printf("线性表L为：");
   ListTraverse(L,visit);
   printf("请输入要取代的元素的序号 元素的新值: ");
   scanf("%d%d",&n,&e);
   ReplaceElem(L,n,e);
   printf("线性表L为：");
   ListTraverse(L,visit);
   DestroyList(&L);
   printf("销毁L后,按非升序重新建立n个元素的线性表L,请输入元素个数n(>2): ");
   scanf("%d",&n);
   CreatDescend(&L,n);
   printf("依次输出L的元素：");
   ListTraverse(L,visit);
   InsertDescend(L,10); /* 按非升序插入元素10 */
   printf("按非升序插入元素10后，线性表L为：");
   ListTraverse(L,visit);
   printf("请输入要删除的元素的值: ");
   scanf("%d",&e);
   i=DeleteElem(L,e);
   if(i)
     printf("成功删除%d!\n",e);
   else
     printf("不存在元素%d!\n",e);
   printf("线性表L为：");
   ListTraverse(L,visit);
   DeleteFirst(L,&e);
   DeleteTail(L,&d);
   printf("删除表头元素%d和表尾元素%d后,线性表L为：",e,d);
   ListTraverse(L,visit);
 }
F:\GitHubCode\Code\Csjjg\严蔚敏《数据结构》的全部代码实现（C语言）\ch2\Debug
F:\GitHubCode\Code\Csjjg\严蔚敏《数据结构》的全部代码实现（C语言）\ch3
**********ALGO3-10.c**********
 /* algo3-10.c Hanoi塔问题,调用算法3.5的程序 */
 #include<stdio.h>

 int c=0; /* 全局变量，搬动次数 */

 void move(char x,int n,char z)
 { /* 第n个圆盘从塔座x搬到塔座z */
   printf("第%i步: 将%i号盘从%c移到%c\n",++c,n,x,z);
 }

 void hanoi(int n,char x,char y,char z) /* 算法3.5 */
 { /* 将塔座x上按直径由小到大且自上而下编号为1至n的n个圆盘 */
   /* 按规则搬到塔座z上。y可用作辅助塔座 */
   if(n==1)
     move(x,1,z); /* 将编号为1的圆盘从x移到z */
   else
   {
     hanoi(n-1,x,z,y); /* 将x上编号为1至n-1的圆盘移到y，z作辅助塔 */
     move(x,n,z); /* 将编号为n的圆盘从x移到z */
     hanoi(n-1,y,x,z); /* 将y上编号为1至n-1的圆盘移到z，x作辅助塔 */
   }
 }

 void main()
 {
   int n;
   printf("3个塔座为a、b、c，圆盘最初在a座，借助b座移到c座。请输入圆盘数：");
   scanf("%d",&n);
   hanoi(n,'a','b','c');
 }
**********ALGO3-11.c**********
 /* algo3-11.c 利用非循环顺序队列采用广度搜索法求解迷宫问题(一条路径) */
 #include"c1.h"
 #define M 5 /* 迷宫行数(包括外墙) */
 #define N 5 /* 迷宫列数(包括外墙) */
 #define D 8 /* 移动方向数,只能取4和8。(8个,可斜行;4个,只可直走) */

 typedef struct /* 定义队列元素和栈元素为同类型的结构体 */
 {
   int x,y; /* 当前点的行值，列值 */
   int pre; /* 前一点在队列中的序号 */
 }QElemType,SElemType; /* 定义栈元素和队列元素 */
 #include"c3-1.h" /* 栈的存储结构 */
 #include"bo3-1.c" /* 栈的基本操作 */
 #include"c3-3.h" /* 队列的存储结构 */
 #include"bo3-4.c" /* 队列的基本操作 */

 struct /* 移动数组,移动方向由正东起顺时针转 */
 {
   int x,y;
 #if D==8
 }move[D]={{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
 #endif
 #if D==4
 }move[D]={{0,1},{1,0},{0,-1},{-1,0}};
 #endif

 Status Path(int maze[M][N]) /* 广度搜索法求一条迷宫路径 */
 {
   SqQueue q; /* 采用非循环顺序队列 */
   QElemType qf,qt; /* 当前点和下一点 */
   SqStack s; /* 采用顺序栈 */
   int i,j,flag=1; /* 当找到出口,flag=0 */
   int x1,y1; /* 终点的坐标 */
   printf("请输入入口的行,列(左上角为1,1)\n");
   scanf("%d,%d",&qf.x,&qf.y);
   printf("请输入出口的行,列(右下角为%d,%d)\n",M-2,N-2);
   scanf("%d,%d",&x1,&y1);
   qf.pre=-1; /* 设入口(第一点)的上一点的序号=-1 */
   maze[qf.x][qf.y]=-1; /* 初始点设为-1(已访问过) */
   InitQueue(&q);
   EnQueue(&q,qf); /* 起点入队 */
   while(!QueueEmpty(q)&&flag)
   { /* 队列中还有没被广度搜索过的点且还没找到出口 */
     DeQueue(&q,&qf); /* 出队qf为当前点 */
     for(i=0;i<D;i++) /* 向各个方向尝试 */
     {
       qt.x=qf.x+move[i].x; /* 下一点的坐标 */
       qt.y=qf.y+move[i].y;
       if(maze[qt.x][qt.y]==1)
       { /* 此点是通道且不曾被访问过 */
         maze[qt.x][qt.y]=-1; /* 已访问过 */
         qt.pre=q.front-1; /* 上一点处于队列中现队头减一的位置(没删除) */
         EnQueue(&q,qt); /* 入队 */
         if(qt.x==x1&&qt.y==y1) /* 到达终点 */
         {
           flag=0;
           break;
         }
       }
     }
   }
   if(flag) /* 搜索完整个队列还没到达终点 */
   {
     printf("没有路径可到达终点！\n");
     return ERROR;
   }
   else
   {
     InitStack(&s); /* 初始化s栈 */
     i=q.rear-1; /* i为待入栈元素在队列中的位置 */
     while(i>=0) /* 没到入口 */
     {
       Push(&s,*(q.base+i));
       i=(*(q.base+i)).pre; /* i为前一元素在队列中的位置 */
     }
     i=0; /* i为走出迷宫的步骤 */
     while(!StackEmpty(s))
     {
       Pop(&s,&qf);
       i++;
       maze[qf.x][qf.y]=i;
     }
     printf("走出迷宫的一个方案：\n");
     for(i=1;i<M-1;i++) /* 输出maze[][],其值是走出迷宫的步骤 */
     {
       for(j=1;j<N-1;j++)
         printf("%3d",maze[i][j]);
       printf("\n");
     }
     return OK;
   }
 }

 void main()
 {
   int i,j;
   int maze[M][N]; /* 迷宫数组 */
   printf("%d行%d列迷宫(不包括外墙)\n",M-2,N-2);
   for(i=0;i<N;i++)
   { /* 0为墙,1为通道 */
     maze[0][i]=0; /* 北墙 */
     maze[M-1][i]=0; /* 南墙 */
   }
   for(i=1;i<M-1;i++)
   {
     maze[i][0]=0; /* 西墙 */
     maze[i][N-1]=0; /* 东墙 */
   }
   printf("请按行输入迷宫结构(不包括周边,0为墙,1为通道),如1 0 0 1\n");
   for(i=1;i<M-1;i++)
     for(j=1;j<N-1;j++)
       scanf("%d",&maze[i][j]);
   printf("迷宫结构(包括外墙):\n");
   for(i=0;i<M;i++)
   {
     for(j=0;j<N;j++)
       printf("%3d",maze[i][j]);
     printf("\n");
   }
   Path(maze);
 }

**********ALGO3-12.c**********
 /* algo3-12.c 银行业务模拟。实现算法3.6、3.7的程序 */
 #define Qu 4 /* 客户队列数 */
 #define Khjg 5 /* 两相邻到达的客户的时间间隔最大值 */
 #define Blsj 30 /* 每个客户办理业务的时间最大值 */
 #include"c1.h"

 typedef struct /* 定义ElemType为结构体类型 */
 {
   int OccurTime; /* 事件发生时刻 */
   int NType; /* 事件类型，Qu表示到达事件,0至Qu-1表示Qu个窗口的离开事件 */
 }Event,ElemType; /* 事件类型，有序链表LinkList的数据元素类型 */

 #include"c2-5.h"
 typedef LinkList EventList; /* 事件链表类型，定义为有序链表 */
 #include"bo2-6.c" /* 使用已有的链表基本操作 */

 typedef struct
 {
   int ArrivalTime; /* 到达时刻 */
   int Duration; /* 办理事务所需时间 */
 }QElemType; /* 定义QElemType(队列的数据元素类型)为结构体类型; */

 #include"c3-2.h"
 #include"bo3-2.c" /* 使用已有的队列基本操作 */

 /* 程序中用到的主要变量(全局)。算法3.7 */
 EventList ev; /* 事件表 */
 Event en; /* 事件 */
 Event et; /* 临时变量 */
 LinkQueue q[Qu]; /* Qu个客户队列 */
 QElemType customer; /* 客户记录 */
 int TotalTime=0,CustomerNum=0; /* 累计客户逗留时间,客户数(初值为0) */
 int CloseTime; /* 银行营业时间(单位是分) */

 int cmp(Event a,Event b)
 { /* 依事件a的发生时刻<、=或>事件b的发生时刻分别返回-1、0或1 */
   if(a.OccurTime==b.OccurTime)
     return 0;
   else
     return (a.OccurTime-b.OccurTime)/abs(a.OccurTime-b.OccurTime);
 }

 void OpenForDay()
 { /* 初始化操作 */
   int i;
   InitList(&ev); /* 初始化事件链表为空 */
   en.OccurTime=0; /* 设定第一个客户到达事件 */
   en.NType=Qu; /* 到达 */
   OrderInsert(&ev,en,cmp); /* 插入事件表 */
   for(i=0;i<Qu;++i) /* 置空队列 */
     InitQueue(&q[i]);
 }

 void Random(int *d,int *i)
 {
   *d=rand()%Blsj+1; /* 1到Blsj之间的随机数 */
   *i=rand()%Khjg+1; /* 1到Khjg之间的随机数 */
 }

 int Minimum(LinkQueue Q[]) /* 返回最短队列的序号 */
 {
   int l[Qu];
   int i,k;
   for(i=0;i<Qu;i++)
     l[i]=QueueLength(Q[i]);
   k=0;
   for(i=1;i<Qu;i++)
     if(l[i]<l[0])
     {
       l[0]=l[i];
       k=i;
     }
   return k;
 }

 void CustomerArrived()
 { /* 处理客户到达事件，en.NType=Qu */
   QElemType f;
   int durtime,intertime,i;
   ++CustomerNum;
   Random(&durtime,&intertime); /* 生成随机数 */
   et.OccurTime=en.OccurTime+intertime; /* 下一客户到达时刻 */
   et.NType=Qu; /* 队列中只有一个客户到达事件 */
   if(et.OccurTime<CloseTime) /* 银行尚未关门，插入事件表 */
     OrderInsert(&ev,et,cmp);
   i=Minimum(q); /* 求长度最短队列的序号,等长为最小的序号 */
   f.ArrivalTime=en.OccurTime;
   f.Duration=durtime;
   EnQueue(&q[i],f);
   if(QueueLength(q[i])==1)
   {
     et.OccurTime=en.OccurTime+durtime;
     et.NType=i;
     OrderInsert(&ev,et,cmp); /* 设定第i队列的一个离开事件并插入事件表 */
   }
 }

 void CustomerDeparture()
 { /* 处理客户离开事件，en.NTyPe<Qu */
   int i;
   i=en.NType;
   DeQueue(&q[i],&customer); /* 删除第i队列的排头客户 */
   TotalTime+=en.OccurTime-customer.ArrivalTime; /* 累计客户逗留时间 */
   if(!QueueEmpty(q[i]))
   { /* 设定第i队列的一个离开事件并插入事件表 */
     GetHead_Q(q[i],&customer);
     et.OccurTime=en.OccurTime+customer.Duration;
     et.NType=i;
     OrderInsert(&ev,et,cmp);
   }
 }

 void Bank_Simulation()
 {
   Link p;
   OpenForDay(); /* 初始化 */
   while(!ListEmpty(ev))
   {
     DelFirst(&ev,GetHead(ev),&p);
     en.OccurTime=GetCurElem(p).OccurTime;
     en.NType=GetCurElem(p).NType;
     if(en.NType==Qu)
       CustomerArrived(); /* 处理客户到达事件 */
     else
       CustomerDeparture(); /* 处理客户离开事件 */
   } /* 计算并输出平均逗留时间 */
   printf("顾客总数:%d, 所有顾客共耗时:%d分钟, 平均每人耗时: %d分钟\n",CustomerNum,TotalTime,TotalTime/CustomerNum);
 }

 void main()
 {
   printf("请输入银行营业时间长度(单位:分)\n");
   scanf("%d",&CloseTime);
   Bank_Simulation();
 }

**********ALGO3-2.c**********
 /* algo3-2.c 改算法3.1，10进制→16进制 */
 typedef int SElemType; /* 定义栈元素类型为整型 */
 #include"c1.h"
 #include"c3-1.h" /* 采用顺序栈 */
 #include"bo3-1.c" /* 利用顺序栈的基本操作 */

 void conversion()
 { /* 对于输入的任意一个非负10进制整数，打印输出与其等值的16进制数 */
   SqStack s;
   unsigned n; /* 非负整数 */
   SElemType e;
   InitStack(&s); /* 初始化栈 */
   printf("n(>=0)=");
   scanf("%u",&n); /* 输入非负十进制整数n */
   while(n) /* 当n不等于0 */
   {
     Push(&s,n%16); /* 入栈n除以16的余数(16进制的低位) */
     n=n/16;
   }
   while(!StackEmpty(s)) /* 当栈不空 */
   {
     Pop(&s,&e); /* 弹出栈顶元素且赋值给e */
     if(e<=9)
       printf("%d",e);
     else
       printf("%c",e+55);
   }
   printf("\n");
 }

 void main()
 {
   conversion();
 }

**********algo3-3.c**********
 /* algo3-3.c 括号匹配的检验，（限于()、[]） */
 typedef char SElemType;
 #include"c1.h"
 #include"c3-1.h"
 #include"bo3-1.c"

 void check()
 { /* 对于输入的任意一个字符串，检验括号是否配对 */
   SqStack s;
   SElemType ch[80],*p,e;
   if(InitStack(&s)) /* 初始化栈成功 */
   {
     printf("请输入表达式\n");
     gets(ch);
     p=ch;
     while(*p) /* 没到串尾 */
       switch(*p)
       {
         case '(':
         case '[':Push(&s,*p++);
                  break; /* 左括号入栈，且p++ */
         case ')':
         case ']':if(!StackEmpty(s)) /* 栈不空 */
                  {
                    Pop(&s,&e); /* 弹出栈顶元素 */
                    if(*p==')'&&e!='('||*p==']'&&e!='[') /* 弹出的栈顶元素与*p不配对 */
                    {
                      printf("左右括号不配对\n");
                      exit(ERROR);
                    }
                    else
                    {
                      p++;
                      break; /* 跳出switch语句 */
                    }
                  }
                  else /* 栈空 */
                  {
                    printf("缺乏左括号\n");
                    exit(ERROR);
                  }
         default: p++; /* 其它字符不处理，指针向后移 */
       }
       if(StackEmpty(s)) /* 字符串结束时栈空 */
         printf("括号匹配\n");
       else
         printf("缺乏右括号\n");
   }
 }

 void main()
 {
   check();
 }


**********algo3-4.c**********
 /* algo3-4.c 行编辑程序,实现算法3.2 */
 typedef char SElemType;
 #include"c1.h"
 #include"c3-1.h"
 #include"bo3-1.c"
 FILE *fp;

 Status copy(SElemType c)
 { /* 将字符c送至fp所指的文件中 */
   fputc(c,fp);
   return OK;
 }

 void LineEdit()
 { /* 利用字符栈s，从终端接收一行并送至调用过程的数据区。算法3.2 */
   SqStack s;
   char ch,c;
   InitStack(&s);
   printf("请输入一个文本文件,^Z结束输入:\n");
   ch=getchar();
   while(ch!=EOF)
   { /* EOF为^Z键，全文结束符 */
     while(ch!=EOF&&ch!='\n')
     {
       switch(ch)
       {
         case '#':Pop(&s,&c);
                  break; /* 仅当栈非空时退栈 */
         case '@':ClearStack(&s);
                  break; /* 重置s为空栈 */
         default :Push(&s,ch); /* 有效字符进栈 */
       }
       ch=getchar(); /* 从终端接收下一个字符 */
     }
     StackTraverse(s,copy); /* 将从栈底到栈顶的栈内字符传送至文件 */
     ClearStack(&s); /* 重置s为空栈 */
     fputc('\n',fp);
     if(ch!=EOF)
       ch=getchar();
   }
   DestroyStack(&s);
 }

 void main()
 {
   fp=fopen("ED.DAT","w"); /* 在当前目录下建立ED.DAT文件，用于写数据， */
   if(fp)                  /* 如已有同名文件则先删除原文件 */
   {
     LineEdit();
     fclose(fp); /* 关闭fp所指的文件 */
   }
   else
     printf("建立文件失败!\n");
 }


**********ALGO3-5.c**********
 /* algo3-5.c 利用栈求解迷宫问题（只输出一个解，算法3.3） */
 typedef struct /* 迷宫坐标位置类型 */
 {
   int x; /* 行值 */
   int y; /* 列值 */
 }PosType;

 #define MAXLENGTH 25 /* 设迷宫的最大行列为25 */
 typedef int MazeType[MAXLENGTH][MAXLENGTH]; /* 迷宫数组[行][列] */

 /* 全局变量 */
 MazeType m; /* 迷宫数组 */
 int curstep=1; /* 当前足迹,初值为1 */

 typedef struct /* 栈的元素类型 */
 {
   int ord; /* 通道块在路径上的＂序号＂ */
   PosType seat; /* 通道块在迷宫中的＂坐标位置＂ */
   int di; /* 从此通道块走向下一通道块的＂方向＂(0～3表示东～北) */
 }SElemType;

 #include"c1.h"
 #include"c3-1.h" /* 采用顺序栈存储结构 */
 #include"bo3-1.c" /* 采用顺序栈的基本操作函数 */

 /* 定义墙元素值为0,可通过路径为1,不能通过路径为-1,通过路径为足迹 */

 Status Pass(PosType b)
 { /* 当迷宫m的b点的序号为1(可通过路径)，return OK; 否则，return ERROR。 */
   if(m[b.x][b.y]==1)
     return OK;
   else
     return ERROR;
 }

 void FootPrint(PosType a)
 { /* 使迷宫m的a点的序号变为足迹(curstep) */
   m[a.x][a.y]=curstep;
 }

 PosType NextPos(PosType c,int di)
 { /* 根据当前位置及移动方向，返回下一位置 */
   PosType direc[4]={{0,1},{1,0},{0,-1},{-1,0}}; /* {行增量,列增量} */
   /* 移动方向,依次为东南西北 */
   c.x+=direc[di].x;
   c.y+=direc[di].y;
   return c;
 }

 void MarkPrint(PosType b)
 { /* 使迷宫m的b点的序号变为-1(不能通过的路径) */
   m[b.x][b.y]=-1;
 }

 Status MazePath(PosType start,PosType end) /* 算法3.3 */
 { /* 若迷宫maze中存在从入口start到出口end的通道，则求得一条 */
   /* 存放在栈中(从栈底到栈顶)，并返回TRUE；否则返回FALSE */
   SqStack S;
   PosType curpos;
   SElemType e;
   InitStack(&S);
   curpos=start;
   do
   {
     if(Pass(curpos))
     { /* 当前位置可以通过，即是未曾走到过的通道块 */
       FootPrint(curpos); /* 留下足迹 */
       e.ord=curstep;
       e.seat.x=curpos.x;
       e.seat.y=curpos.y;
       e.di=0;
       Push(&S,e); /* 入栈当前位置及状态 */
       curstep++; /* 足迹加1 */
       if(curpos.x==end.x&&curpos.y==end.y) /* 到达终点(出口) */
         return TRUE;
       curpos=NextPos(curpos,e.di);
     }
     else
     { /* 当前位置不能通过 */
       if(!StackEmpty(S))
       {
         Pop(&S,&e); /* 退栈到前一位置 */
         curstep--;
         while(e.di==3&&!StackEmpty(S)) /* 前一位置处于最后一个方向(北) */
         {
           MarkPrint(e.seat); /* 留下不能通过的标记(-1) */
           Pop(&S,&e); /* 退回一步 */
           curstep--;
         }
         if(e.di<3) /* 没到最后一个方向(北) */
         {
           e.di++; /* 换下一个方向探索 */
           Push(&S,e);
           curstep++;
           curpos=NextPos(e.seat,e.di); /* 设定当前位置是该新方向上的相邻块 */
         }
       }
     }
   }while(!StackEmpty(S));
   return FALSE;
 }

 void Print(int x,int y)
 { /* 输出迷宫的解 */
   int i,j;
   for(i=0;i<x;i++)
   {
     for(j=0;j<y;j++)
       printf("%3d",m[i][j]);
     printf("\n");
   }
 }

 void main()
 {
   PosType begin,end;
   int i,j,x,y,x1,y1;
   printf("请输入迷宫的行数,列数(包括外墙)：");
   scanf("%d,%d",&x,&y);
   for(i=0;i<x;i++) /* 定义周边值为0(同墙) */
   {
     m[0][i]=0; /* 行周边 */
     m[x-1][i]=0;
   }
   for(j=1;j<y-1;j++)
   {
     m[j][0]=0; /* 列周边 */
     m[j][y-1]=0;
   }
   for(i=1;i<x-1;i++)
     for(j=1;j<y-1;j++)
       m[i][j]=1; /* 定义通道初值为1 */
   printf("请输入迷宫内墙单元数：");
   scanf("%d",&j);
   printf("请依次输入迷宫内墙每个单元的行数,列数：\n");
   for(i=1;i<=j;i++)
   {
     scanf("%d,%d",&x1,&y1);
     m[x1][y1]=0; /* 定义墙的值为0 */
   }
   printf("迷宫结构如下:\n");
   Print(x,y);
   printf("请输入起点的行数,列数：");
   scanf("%d,%d",&begin.x,&begin.y);
   printf("请输入终点的行数,列数：");
   scanf("%d,%d",&end.x,&end.y);
   if(MazePath(begin,end)) /* 求得一条通路 */
   {
     printf("此迷宫从入口到出口的一条路径如下:\n");
     Print(x,y); /* 输出此通路 */
   }
   else
     printf("此迷宫没有从入口到出口的路径\n");
 }

**********ALGO3-6.c**********
 /* algo3-6.c 表达式求值（输入、输出和中间结果均只能是0～9） */
 typedef char SElemType;
 #include"c1.h"
 #include"c3-1.h"
 #include"bo3-1.c"

 SElemType Precede(SElemType t1,SElemType t2)
 { /* 根据教科书表3.1，判断两符号的优先关系 */
   SElemType f;
   switch(t2)
   {
     case '+':
     case '-':if(t1=='('||t1=='#')
                f='<';
              else
                f='>';
              break;
     case '*':
     case '/':if(t1=='*'||t1=='/'||t1==')')
                f='>';
              else
                f='<';
              break;
     case '(':if(t1==')')
              {
                printf("ERROR1\n");
                exit(ERROR);
              }
              else
                f='<';
              break;
     case ')':switch(t1)
              {
                case '(':f='=';
                         break;
                case '#':printf("ERROR2\n");
                         exit(ERROR);
                default: f='>';
              }
              break;
     case '#':switch(t1)
              {
                case '#':f='=';
                         break;
                case '(':printf("ERROR3\n");
                         exit(ERROR);
                default: f='>';
              }
   }
   return f;
 }

 Status In(SElemType c)
 { /* 判断c是否为运算符 */
   switch(c)
   {
     case'+':
     case'-':
     case'*':
     case'/':
     case'(':
     case')':
     case'#':return TRUE;
     default:return FALSE;
   }
 }

 SElemType Operate(SElemType a,SElemType theta,SElemType b)
 {
   SElemType c;
   a=a-48;
   b=b-48;
   switch(theta)
   {
     case'+':c=a+b+48;
             break;
     case'-':c=a-b+48;
             break;
     case'*':c=a*b+48;
             break;
     case'/':c=a/b+48;
   }
   return c;
 }

 SElemType EvaluateExpression() /* 算法3.4 */
 { /* 算术表达式求值的算符优先算法。设OPTR和OPND分别为运算符栈和运算数栈 */
   SqStack OPTR,OPND;
   SElemType a,b,c,x,theta;
   InitStack(&OPTR);
   Push(&OPTR,'#');
   InitStack(&OPND);
   c=getchar();
   GetTop(OPTR,&x);
   while(c!='#'||x!='#')
   {
     if(In(c)) /* 是7种运算符之一 */
       switch(Precede(x,c))
       {
         case'<':Push(&OPTR,c); /* 栈顶元素优先权低 */
                 c=getchar();
                 break;
         case'=':Pop(&OPTR,&x); /* 脱括号并接收下一字符 */
                 c=getchar();
                 break;
         case'>':Pop(&OPTR,&theta); /* 退栈并将运算结果入栈 */
		 Pop(&OPND,&b);
                 Pop(&OPND,&a);
                 Push(&OPND,Operate(a,theta,b));
                 break;
       }
     else if(c>='0'&&c<='9') /* c是操作数 */
     {
       Push(&OPND,c);
       c=getchar();
     }
     else /* c是非法字符 */
     {
       printf("ERROR4\n");
       exit(ERROR);
     }
     GetTop(OPTR,&x);
   }
   GetTop(OPND,&x);
   return x;
 }

 void main()
 {
   printf("请输入算术表达式（中间值及最终结果要在0～9之间），并以#结束\n");
   printf("%c\n",EvaluateExpression());
 }


**********Algo3-7.c**********
 /* algo3-7.c 表达式求值(范围为int类型,输入负数要用(0-正数)表示) */
 typedef int SElemType; /* 栈元素类型为整型,改进算法3.4 */
 #include"c1.h"
 #include"c3-1.h"
 #include"bo3-1.c"

 SElemType Precede(SElemType t1,SElemType t2) /* 同algo3-6.c */
 { /* 根据教科书表3.1，判断两符号的优先关系 */
   SElemType f;
   switch(t2)
   {
     case '+':
     case '-':if(t1=='('||t1=='=')
                f='<';
              else
                f='>';
              break;
     case '*':
     case '/':if(t1=='*'||t1=='/'||t1==')')
                f='>';
              else
                f='<';
              break;
     case '(':if(t1==')')
              {
                printf("ERROR1\n");
                exit(ERROR);
              }
              else
                f='<';
              break;
     case ')':switch(t1)
              {
                case '(':f='=';
                         break;
                case '=':printf("ERROR2\n");
                         exit(ERROR);
                default: f='>';
              }
              break;
     case '=':switch(t1)
              {
                case '=':f='=';
                         break;
                case '(':printf("ERROR2\n");
                         exit(ERROR);
                default: f='>';
              }
   }
   return f;
 }

 Status In(SElemType c) /* 几乎与algo3-6.c相同 */
 { /* 判断c是否为运算符 */
   switch(c)
   {
     case'+':
     case'-':
     case'*':
     case'/':
     case'(':
     case')':
     case'=':return TRUE; /* 此句不同于algo3-6.c */
     default:return FALSE;
   }
 }

 SElemType Operate(SElemType a,SElemType theta,SElemType b) /* 有改动 */
 {
   SElemType c;
   switch(theta)
   {
     case'+':c=a+b;
             break;
     case'-':c=a-b;
             break;
     case'*':c=a*b;
             break;
     case'/':c=a/b;
   }
   return c;
 }

 SElemType EvaluateExpression() /* 有改动 */
 { /* 算术表达式求值的算符优先算法。设OPTR和OPND分别为运算符栈和运算数栈 */
   SqStack OPTR,OPND;
   SElemType a,b,d,x,theta;
   char c; /* 存放由键盘接收的字符串 */
   char z[6]; /* 存放整数字符串 */
   int i;
   InitStack(&OPTR); /* 初始化运算符栈 */
   Push(&OPTR,'='); /* =是表达式结束标志 */
   InitStack(&OPND); /* 初始化运算数栈 */
   c=getchar();
   GetTop(OPTR,&x);
   while(c!='='||x!='=')
   {
     if(In(c)) /* 是7种运算符之一 */
       switch(Precede(x,c))
       {
         case'<':Push(&OPTR,c); /* 栈顶元素优先权低 */
                 c=getchar();
                 break;
         case'=':Pop(&OPTR,&x); /* 脱括号并接收下一字符 */
                 c=getchar();
                 break;
         case'>':Pop(&OPTR,&theta); /* 退栈并将运算结果入栈 */
                 Pop(&OPND,&b);
                 Pop(&OPND,&a);
                 Push(&OPND,Operate(a,theta,b));
       }
     else if(c>='0'&&c<='9') /* c是操作数 */
     {
       i=0;
       do
       {
         z[i]=c;
         i++;
         c=getchar();
       }while(c>='0'&&c<='9');
       z[i]=0;
       d=atoi(z); /* 将字符串数组转为整型存于d */
       Push(&OPND,d);
     }
     else /* c是非法字符 */
     {
       printf("ERROR3\n");
       exit(ERROR);
     }
     GetTop(OPTR,&x);
   }
   GetTop(OPND,&x);
   return x;
 }

 void main() /* 有改动 */
 {
   printf("请输入算术表达式,负数要用(0-正数)表示,并以=结束\n");
   printf("%d\n",EvaluateExpression());
 }


**********ALGO3-8.c**********
 /* algo3-8.c 用递归调用求Ackerman(m,n)的值 */
 #include<stdio.h>
 int ack(int m,int n)
 {
   int z;
   if(m==0)
     z=n+1;
   else if(n==0)
     z=ack(m-1,1);
   else
     z=ack(m-1,ack(m,n-1));
   return z;
 }

 void main()
 {
   int m,n;
   printf("Please input m,n:");
   scanf("%d,%d",&m,&n);
   printf("Ack(%d,%d)=%d\n",m,n,ack(m,n));
 }

**********ALGO3-9.c**********
 /* algo3-9.c 用递归函数求解迷宫问题(求出所有解) */
 #include<stdio.h> /* 根据《PASCAL程序设计》(郑启华编著)中的程序改编 */
 struct PosType /* 迷宫坐标位置类型 */
 {
   int x; /* 行值 */
   int y; /* 列值 */
 };

 #define MAXLENGTH 25 /* 设迷宫的最大行列为25 */
 typedef int MazeType[MAXLENGTH][MAXLENGTH]; /* [行][列] */

 /* 全局变量 */
 struct PosType end; /* 迷宫终点位置 */
 MazeType m; /* 迷宫数组 */
 int x,y; /* 迷宫行数，列数 */

 /* 定义墙元素值为0,可通过路径为-1,通过路径为足迹 */

 void Print(int x,int y)
 { /* 输出解 */
   int i,j;
   for(i=0;i<x;i++)
   {
     for(j=0;j<y;j++)
       printf("%3d",m[i][j]);
     printf("\n");
   }
   printf("\n");
 }

 void Try(struct PosType cur,int curstep)
 { /* 由当前位置cur、当前步骤curstep试探下一点 */
   int i;
   struct PosType next; /* 下一个位置 */
   struct PosType direc[4]={{0,1},{1,0},{0,-1},{-1,0}}; /* {行增量,列增量} */
   /* 移动方向,依次为东南西北 */
   for(i=0;i<=3;i++) /* 依次试探东南西北四个方向 */
   {
     next.x=cur.x+direc[i].x;
     next.y=cur.y+direc[i].y;
     if(m[next.x][next.y]==-1) /* 是通路 */
     {
       m[next.x][next.y]=++curstep;
       if(next.x!=end.x||next.y!=end.y) /* 没到终点 */
         Try(next,curstep); /* 试探下一点(递归调用) */
       else
         Print(x,y); /* 输出结果 */
       m[next.x][next.y]=-1; /* 恢复为通路，试探下一条路 */
       curstep--;
     }
   }
 }

 void main()
 {
   struct PosType begin;
   int i,j,x1,y1;
   printf("请输入迷宫的行数,列数(包括外墙)：");
   scanf("%d,%d",&x,&y);
   for(i=0;i<x;i++) /* 定义周边值为0(同墙) */
   {
     m[0][i]=0; /* 行周边 */
     m[x-1][i]=0;
   }
   for(j=1;j<y-1;j++)
   {
     m[j][0]=0; /* 列周边 */
     m[j][y-1]=0;
   }
   for(i=1;i<x-1;i++)
     for(j=1;j<y-1;j++)
       m[i][j]=-1; /* 定义通道初值为-1 */
   printf("请输入迷宫内墙单元数：");
   scanf("%d",&j);
   if(j)
     printf("请依次输入迷宫内墙每个单元的行数,列数：\n");
   for(i=1;i<=j;i++)
   {
     scanf("%d,%d",&x1,&y1);
     m[x1][y1]=0;
   }
   printf("迷宫结构如下:\n");
   Print(x,y);
   printf("请输入起点的行数,列数：");
   scanf("%d,%d",&begin.x,&begin.y);
   printf("请输入终点的行数,列数：");
   scanf("%d,%d",&end.x,&end.y);
   m[begin.x][begin.y]=1;
   Try(begin,1); /* 由第一步起点试探起 */
 }

**********BO3-1.c**********
 /* bo3-1.c 顺序栈（存储结构由c3-1.h定义）的基本操作（9个） */
 Status InitStack(SqStack *S)
 { /* 构造一个空栈S */
   (*S).base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
   if(!(*S).base)
     exit(OVERFLOW); /* 存储分配失败 */
   (*S).top=(*S).base;
   (*S).stacksize=STACK_INIT_SIZE;
   return OK;
 }

 Status DestroyStack(SqStack *S)
 { /* 销毁栈S，S不再存在 */
   free((*S).base);
   (*S).base=NULL;
   (*S).top=NULL;
   (*S).stacksize=0;
   return OK;
 }

 Status ClearStack(SqStack *S)
 { /* 把S置为空栈 */
   (*S).top=(*S).base;
   return OK;
 }

 Status StackEmpty(SqStack S)
 { /* 若栈S为空栈，则返回TRUE，否则返回FALSE */
   if(S.top==S.base)
     return TRUE;
   else
     return FALSE;
 }

 int StackLength(SqStack S)
 { /* 返回S的元素个数，即栈的长度 */
   return S.top-S.base;
 }

 Status GetTop(SqStack S,SElemType *e)
 { /* 若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR */
   if(S.top>S.base)
   {
     *e=*(S.top-1);
     return OK;
   }
   else
     return ERROR;
 }

 Status Push(SqStack *S,SElemType e)
 { /* 插入元素e为新的栈顶元素 */
   if((*S).top-(*S).base>=(*S).stacksize) /* 栈满，追加存储空间 */
   {
     (*S).base=(SElemType *)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));
     if(!(*S).base)
       exit(OVERFLOW); /* 存储分配失败 */
     (*S).top=(*S).base+(*S).stacksize;
     (*S).stacksize+=STACKINCREMENT;
   }
   *((*S).top)++=e;
   return OK;
 }

 Status Pop(SqStack *S,SElemType *e)
 { /* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
   if((*S).top==(*S).base)
     return ERROR;
   *e=*--(*S).top;
   return OK;
 }

 Status StackTraverse(SqStack S,Status(*visit)(SElemType))
 { /* 从栈底到栈顶依次对栈中每个元素调用函数visit()。 */
   /* 一旦visit()失败，则操作失败 */
   while(S.top>S.base)
     visit(*S.base++);
   printf("\n");
   return OK;
 }
**********BO3-2.c**********
 /* bo3-2.c 链队列(存储结构由c3-2.h定义)的基本操作(9个) */
 Status InitQueue(LinkQueue *Q)
 { /* 构造一个空队列Q */
   (*Q).front=(*Q).rear=(QueuePtr)malloc(sizeof(QNode));
   if(!(*Q).front)
     exit(OVERFLOW);
   (*Q).front->next=NULL;
   return OK;
 }

 Status DestroyQueue(LinkQueue *Q)
 { /* 销毁队列Q(无论空否均可) */
   while((*Q).front)
   {
     (*Q).rear=(*Q).front->next;
     free((*Q).front);
     (*Q).front=(*Q).rear;
   }
   return OK;
 }

 Status ClearQueue(LinkQueue *Q)
 { /* 将Q清为空队列 */
   QueuePtr p,q;
   (*Q).rear=(*Q).front;
   p=(*Q).front->next;
   (*Q).front->next=NULL;
   while(p)
   {
     q=p;
     p=p->next;
     free(q);
   }
   return OK;
 }

 Status QueueEmpty(LinkQueue Q)
 { /* 若Q为空队列,则返回TRUE,否则返回FALSE */
   if(Q.front==Q.rear)
     return TRUE;
   else
     return FALSE;
 }

 int QueueLength(LinkQueue Q)
 { /* 求队列的长度 */
   int i=0;
   QueuePtr p;
   p=Q.front;
   while(Q.rear!=p)
   {
     i++;
     p=p->next;
   }
   return i;
 }

 Status GetHead_Q(LinkQueue Q,QElemType *e) /* 避免与bo2-6.c重名 */
 { /* 若队列不空,则用e返回Q的队头元素,并返回OK,否则返回ERROR */
   QueuePtr p;
   if(Q.front==Q.rear)
     return ERROR;
   p=Q.front->next;
   *e=p->data;
   return OK;
 }

 Status EnQueue(LinkQueue *Q,QElemType e)
 { /* 插入元素e为Q的新的队尾元素 */
   QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
   if(!p) /* 存储分配失败 */
     exit(OVERFLOW);
   p->data=e;
   p->next=NULL;
   (*Q).rear->next=p;
   (*Q).rear=p;
   return OK;
 }

 Status DeQueue(LinkQueue *Q,QElemType *e)
 { /* 若队列不空,删除Q的队头元素,用e返回其值,并返回OK,否则返回ERROR */
   QueuePtr p;
   if((*Q).front==(*Q).rear)
     return ERROR;
   p=(*Q).front->next;
   *e=p->data;
   (*Q).front->next=p->next;
   if((*Q).rear==p)
     (*Q).rear=(*Q).front;
   free(p);
   return OK;
 }

 Status QueueTraverse(LinkQueue Q,void(*vi)(QElemType))
 { /* 从队头到队尾依次对队列Q中每个元素调用函数vi()。一旦vi失败,则操作失败 */
   QueuePtr p;
   p=Q.front->next;
   while(p)
   {
     vi(p->data);
     p=p->next;
   }
   printf("\n");
   return OK;
 }
**********BO3-3.c**********
 /* bo3-3.c 循环队列(存储结构由c3-3.h定义)的基本操作(9个) */
 Status InitQueue(SqQueue *Q)
 { /* 构造一个空队列Q */
   (*Q).base=(QElemType *)malloc(MAXQSIZE*sizeof(QElemType));
   if(!(*Q).base) /* 存储分配失败 */
     exit(OVERFLOW);
   (*Q).front=(*Q).rear=0;
   return OK;
 }

 Status DestroyQueue(SqQueue *Q)
 { /* 销毁队列Q,Q不再存在 */
   if((*Q).base)
     free((*Q).base);
   (*Q).base=NULL;
   (*Q).front=(*Q).rear=0;
   return OK;
 }

 Status ClearQueue(SqQueue *Q)
 { /* 将Q清为空队列 */
   (*Q).front=(*Q).rear=0;
   return OK;
 }

 Status QueueEmpty(SqQueue Q)
 { /* 若队列Q为空队列,则返回TRUE,否则返回FALSE */
   if(Q.front==Q.rear) /* 队列空的标志 */
     return TRUE;
   else
     return FALSE;
 }

 int QueueLength(SqQueue Q)
 { /* 返回Q的元素个数,即队列的长度 */
   return(Q.rear-Q.front+MAXQSIZE)%MAXQSIZE;
 }

 Status GetHead(SqQueue Q,QElemType *e)
 { /* 若队列不空,则用e返回Q的队头元素,并返回OK,否则返回ERROR */
   if(Q.front==Q.rear) /* 队列空 */
     return ERROR;
   *e=*(Q.base+Q.front);
   return OK;
 }

 Status EnQueue(SqQueue *Q,QElemType e)
 { /* 插入元素e为Q的新的队尾元素 */
   if(((*Q).rear+1)%MAXQSIZE==(*Q).front) /* 队列满 */
     return ERROR;
   (*Q).base[(*Q).rear]=e;
   (*Q).rear=((*Q).rear+1)%MAXQSIZE;
   return OK;
 }

 Status DeQueue(SqQueue *Q,QElemType *e)
 { /* 若队列不空,则删除Q的队头元素,用e返回其值,并返回OK;否则返回ERROR */
   if((*Q).front==(*Q).rear) /* 队列空 */
     return ERROR;
   *e=(*Q).base[(*Q).front];
   (*Q).front=((*Q).front+1)%MAXQSIZE;
   return OK;
 }

 Status QueueTraverse(SqQueue Q,void(*vi)(QElemType))
 { /* 从队头到队尾依次对队列Q中每个元素调用函数vi().一旦vi失败,则操作失败 */
   int i;
   i=Q.front;
   while(i!=Q.rear)
   {
     vi(*(Q.base+i));
     i=(i+1)%MAXQSIZE;
   }
   printf("\n");
   return OK;
 }
**********BO3-4.c**********
 /* bo3-4.c 顺序队列(非循环,存储结构由c3-3.h定义)的基本操作(9个) */
 Status InitQueue(SqQueue *Q)
 { /* 构造一个空队列Q */
   (*Q).base=(QElemType *)malloc(MAXQSIZE*sizeof(QElemType));
   if(!(*Q).base) /* 存储分配失败 */
     exit(OVERFLOW);
   (*Q).front=(*Q).rear=0;
   return OK;
 }

 Status DestroyQueue(SqQueue *Q)
 { /* 销毁队列Q,Q不再存在 */
   if((*Q).base)
     free((*Q).base);
   (*Q).base=NULL;
   (*Q).front=(*Q).rear=0;
   return OK;
 }

 Status ClearQueue(SqQueue *Q)
 { /* 将Q清为空队列 */
   (*Q).front=(*Q).rear=0;
   return OK;
 }

 Status QueueEmpty(SqQueue Q)
 { /* 若队列Q为空队列,则返回TRUE,否则返回FALSE */
   if(Q.front==Q.rear) /* 队列空的标志 */
     return TRUE;
   else
     return FALSE;
 }

 int QueueLength(SqQueue Q)
 { /* 返回Q的元素个数,即队列的长度 */
   return(Q.rear-Q.front);
 }

 Status GetHead(SqQueue Q,QElemType *e)
 { /* 若队列不空,则用e返回Q的队头元素,并返回OK,否则返回ERROR */
   if(Q.front==Q.rear) /* 队列空 */
     return ERROR;
   *e=*(Q.base+Q.front);
   return OK;
 }

 Status EnQueue(SqQueue *Q,QElemType e)
 { /* 插入元素e为Q的新的队尾元素 */
   if((*Q).rear>=MAXQSIZE)
   { /* 队列满，增加1个存储单元 */
     (*Q).base=(QElemType *)realloc((*Q).base,((*Q).rear+1)*sizeof(QElemType));
     if(!(*Q).base) /* 增加单元失败 */
       return ERROR;
   }
   *((*Q).base+(*Q).rear)=e;
   (*Q).rear++;
   return OK;
 }

 Status DeQueue(SqQueue *Q,QElemType *e)
 { /* 若队列不空,则删除Q的队头元素,用e返回其值,并返回OK,否则返回ERROR */
   if((*Q).front==(*Q).rear) /* 队列空 */
     return ERROR;
   *e=(*Q).base[(*Q).front];
   (*Q).front=(*Q).front+1;
   return OK;
 }

 Status QueueTraverse(SqQueue Q,void(*vi)(QElemType))
 { /* 从队头到队尾依次对队列Q中每个元素调用函数vi()。一旦vi失败,则操作失败 */
   int i;
   i=Q.front;
   while(i!=Q.rear)
   {
     vi(*(Q.base+i));
     i++;
   }
   printf("\n");
   return OK;
 }

**********BO3-5.c**********
 /* bo3-5.c 链栈(存储结构由c2-2.h定义)的基本操作(9个) */
 /* 大部分基本操作是由bo2-2.c和bo2-9.cpp中的函数改名得来 */
 typedef SElemType ElemType; /* 栈结点类型和链表结点类型一致 */
 #include"c2-2.h"
 typedef LinkList LinkStack; /* LinkStack是指向栈结点的指针类型 */
 #define InitStack InitList /* InitStack()与InitList()作用相同，下同 */
 #define DestroyStack DestroyList
 #define ClearStack ClearList
 #define StackEmpty ListEmpty
 #define StackLength ListLength
 #define GetTop GetFirstElem
 #define Push HeadInsert
 #define Pop DeleteFirst
 #include"bo2-2.c"
 #include"bo2-9.c"
 Status StackTraverse(LinkStack S,void(*visit)(SElemType))
 { /* 从栈底到栈顶依次对栈中每个元素调用函数visit()。 */
   SElemType e;
   LinkStack temp,p=S;
   InitStack(&temp); /* 初始化temp栈 */
   while(p->next)
   {
     GetTop(p,&e);
     Push(temp,e);
     p=p->next;
   }
   ListTraverse(temp,visit);
   return OK;
 }
**********C3-1.H**********
 /* c3-1.h 栈的顺序存储表示 */
 #define STACK_INIT_SIZE 10 /* 存储空间初始分配量 */
 #define STACKINCREMENT 2 /* 存储空间分配增量 */
 typedef struct SqStack
 {
   SElemType *base; /* 在栈构造之前和销毁之后，base的值为NULL */
   SElemType *top; /* 栈顶指针 */
   int stacksize; /* 当前已分配的存储空间，以元素为单位 */
 }SqStack; /* 顺序栈 */
**********C3-2.H**********
 /* c3-2.h 单链队列－－队列的链式存储结构 */
 typedef struct QNode
 {
   QElemType data;
   struct QNode *next;
 }QNode,*QueuePtr;

 typedef struct
 {
   QueuePtr front,rear; /* 队头、队尾指针 */
 }LinkQueue;

**********C3-3.H**********
 /* c3-3.h 队列的顺序存储结构(可用于循环队列和非循环队列) */
 #define MAXQSIZE 5 /* 最大队列长度(对于循环队列，最大队列长度要减1) */
 typedef struct
 {
   QElemType *base; /* 初始化的动态分配存储空间 */
   int front; /* 头指针,若队列不空,指向队列头元素 */
   int rear; /* 尾指针,若队列不空,指向队列尾元素的下一个位置 */
 }SqQueue;
**********MAIN3-1.c**********
 /* main3-1.c 检验bo3-1.cpp的主程序 */
 #include"c1.h"
 typedef int SElemType; /* 定义栈元素类型，此句要在c3-1.h的前面 */
 #include"c3-1.h"
 #include"bo3-1.c"

 Status visit(SElemType c)
 {
   printf("%d ",c);
   return OK;
 }

 void main()
 {
   int j;
   SqStack s;
   SElemType e;
   if(InitStack(&s)==OK)
     for(j=1;j<=12;j++)
       Push(&s,j);
   printf("栈中元素依次为：");
   StackTraverse(s,visit);
   Pop(&s,&e);
   printf("弹出的栈顶元素 e=%d\n",e);
   printf("栈空否：%d(1:空 0:否)\n",StackEmpty(s));
   GetTop(s,&e);
   printf("栈顶元素 e=%d 栈的长度为%d\n",e,StackLength(s));
   ClearStack(&s);
   printf("清空栈后，栈空否：%d(1:空 0:否)\n",StackEmpty(s));
   DestroyStack(&s);
   printf("销毁栈后，s.top=%u s.base=%u s.stacksize=%d\n",s.top,s.base, s.stacksize);
 }

**********MAIN3-2.c**********
 /* main3-2.c 检验bo3-2.c的主程序 */
 #include"c1.h"
 typedef int QElemType;
 #include"c3-2.h"
 #include"bo3-2.c"

 void visit(QElemType i)
 {
   printf("%d ",i);
 }

 void main()
 {
   int i;
   QElemType d;
   LinkQueue q;
   i=InitQueue(&q);
   if(i)
     printf("成功地构造了一个空队列!\n");
   printf("是否空队列？%d(1:空 0:否)  ",QueueEmpty(q));
   printf("队列的长度为%d\n",QueueLength(q));
   EnQueue(&q,-5);
   EnQueue(&q,5);
   EnQueue(&q,10);
   printf("插入3个元素(-5,5,10)后,队列的长度为%d\n",QueueLength(q));
   printf("是否空队列？%d(1:空 0:否)  ",QueueEmpty(q));
   printf("队列的元素依次为：");
   QueueTraverse(q,visit);
   i=GetHead_Q(q,&d);
   if(i==OK)
     printf("队头元素是：%d\n",d);
   DeQueue(&q,&d);
   printf("删除了队头元素%d\n",d);
   i=GetHead_Q(q,&d);
   if(i==OK)
     printf("新的队头元素是：%d\n",d);
   ClearQueue(&q);
   printf("清空队列后,q.front=%u q.rear=%u q.front->next=%u\n",q.front,q.rear,q.front->next);
   DestroyQueue(&q);
   printf("销毁队列后,q.front=%u q.rear=%u\n",q.front, q.rear);
 }
**********MAIN3-3.c**********
 /* main3-3.c 循环队列 检验bo3-3.c的主程序 */
 #include"c1.h"
 typedef int QElemType;
 #include"c3-3.h"
 #include"bo3-3.c"

 void visit(QElemType i)
 {
   printf("%d ",i);
 }

 void main()
 {
   Status j;
   int i=0,l;
   QElemType d;
   SqQueue Q;
   InitQueue(&Q);
   printf("初始化队列后，队列空否？%u(1:空 0:否)\n",QueueEmpty(Q));
   printf("请输入整型队列元素(不超过%d个),-1为提前结束符: ",MAXQSIZE-1);
   do
   {
     scanf("%d",&d);
     if(d==-1)
       break;
     i++;
     EnQueue(&Q,d);
   }while(i<MAXQSIZE-1);
   printf("队列长度为: %d\n",QueueLength(Q));
   printf("现在队列空否？%u(1:空 0:否)\n",QueueEmpty(Q));
   printf("连续%d次由队头删除元素,队尾插入元素:\n",MAXQSIZE);
   for(l=1;l<=MAXQSIZE;l++)
   {
     DeQueue(&Q,&d);
     printf("删除的元素是%d,请输入待插入的元素: ",d);
     scanf("%d",&d);
     EnQueue(&Q,d);
   }
   l=QueueLength(Q);
   printf("现在队列中的元素为: \n");
   QueueTraverse(Q,visit);
   printf("共向队尾插入了%d个元素\n",i+MAXQSIZE);
   if(l-2>0)
     printf("现在由队头删除%d个元素:\n",l-2);
   while(QueueLength(Q)>2)
   {
     DeQueue(&Q,&d);
     printf("删除的元素值为%d\n",d);
   }
   j=GetHead(Q,&d);
   if(j)
     printf("现在队头元素为: %d\n",d);
   ClearQueue(&Q);
   printf("清空队列后, 队列空否？%u(1:空 0:否)\n",QueueEmpty(Q));
   DestroyQueue(&Q);
 }
**********MAIN3-4.c**********
 /* main3-4.c 顺序队列(非循环),检验bo3-4.c的主程序 */
 #include"c1.h"
 typedef int QElemType;
 #include"c3-3.h"
 #include"bo3-4.c"

 void visit(QElemType i)
 {
   printf("%d ",i);
 }

 void main()
 {
   Status j;
   int i,n;
   QElemType d;
   SqQueue Q;
   InitQueue(&Q);
   printf("初始化队列后，队列空否？%u(1:空 0:否)\n",QueueEmpty(Q));
   printf("队列长度为：%d\n",QueueLength(Q));
   printf("请输入队列元素个数n: ");
   scanf("%d",&n);
   printf("请输入%d个整型队列元素:\n",n);
   for(i=0;i<n;i++)
   {
     scanf("%d",&d);
     EnQueue(&Q,d);
   }
   printf("队列长度为：%d\n",QueueLength(Q));
   printf("现在队列空否？%u(1:空 0:否)\n",QueueEmpty(Q));
   printf("现在队列中的元素为: \n");
   QueueTraverse(Q,visit);
   DeQueue(&Q,&d);
   printf("删除队头元素%d\n",d);
   printf("队列中的元素为: \n");
   QueueTraverse(Q,visit);
   j=GetHead(Q,&d);
   if(j)
     printf("队头元素为: %d\n",d);
   else
     printf("无队头元素(空队列)\n");
   ClearQueue(&Q);
   printf("清空队列后, 队列空否？%u(1:空 0:否)\n",QueueEmpty(Q));
   j=GetHead(Q,&d);
   if(j)
     printf("队头元素为: %d\n",d);
   else
     printf("无队头元素(空队列)\n");
   DestroyQueue(&Q);
 }
**********MAIN3-5.c**********
 /* main3-5.c 检验bo3-5.cpp的主程序 */
 #include"c1.h"
 typedef int SElemType; /* 定义栈元素的类型 */
 #include"bo3-5.c"

 void print(SElemType c)
 {
   printf("%d ",c);
 }

 void main()
 {
   int j;
   LinkStack s;
   SElemType e;
   if(InitStack(&s))
     for(j=1;j<=5;j++)
       Push(s,2*j);
   printf("栈中的元素从栈底到栈顶依次为: ");
   StackTraverse(s,print);
   Pop(s,&e);
   printf("弹出的栈顶元素为%d\n",e);
   printf("栈空否: %d(1:空 0:否)\n",StackEmpty(s));
   GetTop(s,&e);
   printf("当前栈顶元素为%d，栈的长度为%d\n",e,StackLength(s));
   ClearStack(s);
   printf("清空栈后，栈空否: %d(1:空 0:否)，栈的长度为%d\n",StackEmpty(s),StackLength(s));
   printf("是否销毁栈了: %d(1:是 0:否)\n",DestroyStack(&s));
 }

F:\GitHubCode\Code\Csjjg\严蔚敏《数据结构》的全部代码实现（C语言）\ch3\Debug
F:\GitHubCode\Code\Csjjg\严蔚敏《数据结构》的全部代码实现（C语言）\ch4
**********ALGO4-2.c**********
 /* algo4-2.c 实现算法4.6、4.8的程序 */
 #include"c1.h"
 #include"c4-1.h"
 #include"bo4-1.c"

 void get_nextval(SString T,int nextval[])
 { /* 求模式串T的next函数修正值并存入数组nextval。算法4.8 */
   int i=1,j=0;
   nextval[1]=0;
   while(i<T[0])
     if(j==0||T[i]==T[j])
     {
       ++i;
       ++j;
       if(T[i]!=T[j])
	 nextval[i]=j;
       else
	 nextval[i]=nextval[j];
     }
     else
       j=nextval[j];
 }

 int Index_KMP(SString S,SString T,int pos,int next[])
 { /* 利用模式串T的next函数求T在主串S中第pos个字符之后的位置的KMP算法。 */
   /* 其中,T非空,1≤pos≤StrLength(S)。算法 4.6 同algo4-1.c */
   int i=pos,j=1;
   while(i<=S[0]&&j<=T[0])
     if(j==0||S[i]==T[j]) /* 继续比较后继字符 */
     {
       ++i;
       ++j;
     }
     else /* 模式串向右移动 */
       j=next[j];
   if(j>T[0]) /* 匹配成功 */
     return i-T[0];
   else
     return 0;
 }

 void main()
 {
   int i,j,*p;
   SString s1,s2; /* 以教科书算法4.8之上的数据为例 */
   StrAssign(s1,"aaabaaaab");
   printf("主串为: ");
   StrPrint(s1);
   StrAssign(s2,"aaaab");
   printf("子串为: ");
   StrPrint(s2);
   i=StrLength(s2);
   p=(int*)malloc((i+1)*sizeof(int)); /* 生成s2的next数组 */
   get_nextval(s2,p);
   printf("子串的nextval函数为: ");
   for(j=1;j<=i;j++)
     printf("%d ",*(p+j));
   printf("\n");
   printf("主串和子串在第%d个字符处首次匹配\n",Index_KMP(s1,s2,1,p));
 }

**********algo4-3.c**********
 /* algo4-3.c 文本行编辑 */
 #include"c1.h"
 #include"c4-2.h" /* 采用串的堆分配存储结构 */
 #include"bo4-2.c" /* 串的堆分配基本操作 */

 #define MAX_LEN 25 /* 文件最大行数 */
 #define LINE_LEN 75 /* 每行字符数最大值+1 */
 #define NAME_LEN 20 /* 文件名最大长度(包括盘符、路径)+1 */

 /* 全局变量 */
 HString T[MAX_LEN];
 char str[LINE_LEN],filename[NAME_LEN]="";
 FILE *fp;
 int n=0; /* 文件行数 */

 void Open()
 { /* 打开文件(新或旧) */
   int i;
   if(filename[0]) /* 文件已打开 */
     printf("已存在打开的文件\n");
   else
   {
     printf("请输入文件名(可包括盘符、路径，不超过%d个字符): ",NAME_LEN-1);
     scanf("%s%*c",filename);
     fp=fopen(filename,"r");
     if(fp) /* 已存在此文件 */
     {
       do
       {
         fgets(str,LINE_LEN,fp);
         i=strlen(str);
         str[i-1]=0; /* 将10强制改为0 */
         i--;
         if(i>0)
         {
           StrAssign(&T[n],str);
           n++;
           if(n>MAX_LEN)
           {
             printf("文件太大\n");
             return;
           }
         }
       }while(i>0);
       fclose(fp);
     }
     else
       printf("新文件\n");
   }
 }

 void List()
 { /* 显示文件内容 */
   int i;
   for(i=0;i<n;i++)
   {
     printf("%d: ",i+1);
     StrPrint(T[i]);
   }
   getchar();
 }

 void Insert()
 { /* 插入行 */
   int i,l,m;
   printf("在第l行前插m行,请输入l m: ");
   scanf("%d%d%*c",&l,&m);
   if(n+m>MAX_LEN)
   {
     printf("插入行太多\n");
     return;
   }
   if(n>=l-1&&l>0)
   {
     for(i=n-1;i>=l-1;i--)
       T[i+m]=T[i];
     n+=m;
     printf("请顺序输入待插入内容:\n");
     for(i=l-1;i<l-1+m;i++)
     {
       gets(str);
       InitString(&T[i]);
       StrAssign(&T[i],str);
     }
   }
   else
     printf("行超出范围\n");
 }

 void Delete()
 { /* 删除行 */
   int i,l,m;
   printf("从第l行起删除m行,请输入l m: ");
   scanf("%d%d%*c",&l,&m);
   if(n>=l+m-1&&l>0)
   {
     for(i=l-1+m;i<n;i++)
       T[i-m]=T[i];
     for(i=n-m;i<n;i++)
       InitString(&T[i]);
     n-=m;
   }
   else
     printf("行超出范围\n");
 }

 void Copy()
 { /* 拷贝行 */
   int i,l,m,k;
   printf("把第l行开始的m行插在原k行之前,请输入l m k: ");
   scanf("%d%d%d%*c",&l,&m,&k);
   if(n+m>MAX_LEN)
   {
     printf("拷贝行太多\n");
     return;
   }
   if(n>=k-1&&n>=l-1+m&&(k>=l+m||k<=l))
   {
     for(i=n-1;i>=k-1;i--)
       T[i+m]=T[i];
     n+=m;
     if(k<=l)
       l+=m;
     for(i=l-1;i<l-1+m;i++)
     {
       InitString(&T[i+k-l]);
       StrCopy(&T[i+k-l],T[i]);
     }
   }
   else
     printf("行超出范围\n");
 }

 void Modify()
 { /* 修改行 */
   int i;
   printf("请输入待修改的行号: ");
   scanf("%d%*c",&i);
   if(i>0&&i<=n) /* 行号合法 */
   {
     printf("%d: ",i);
     StrPrint(T[i-1]);
     printf("请输入新内容: ");
     gets(str);
     StrAssign(&T[i-1],str);
   }
   else
     printf("行号超出范围\n");
 }

 void Search()
 { /* 查找字符串 */
   int i,k,f=1; /* f为继续查找标志 */
   char b;
   HString s;
   printf("请输入待查找的字符串: ");
   scanf("%s%*c",str);
   InitString(&s);
   StrAssign(&s,str);
   for(i=0;i<n&&f;i++) /* 逐行查找 */
   {
     k=1; /* 由每行第1个字符起查找 */
     while(k)
     {
       k=Index(T[i],s,k); /* 由本行的第k个字符开始查找 */
       if(k) /* 找到 */
       {
         printf("第%d行: ",i+1);
         StrPrint(T[i]);
         printf("第%d个字符处找到。继续查找吗(Y/N)? ",k);
         b=getchar();
         getchar();
         if(b!='Y'&&b!='y') /* 中断查找 */
         {
           f=0;
           break;
         }
         else
           k++;
       }
     }
   }
   if(f)
     printf("没找到\n");
 }

 void Replace1()
 { /* 替换字符串 */
   int i,k,f=1; /* f为继续替换标志 */
   char b;
   HString s,t;
   printf("请输入待替换的字符串: ");
   scanf("%s%*c",str);
   InitString(&s);
   StrAssign(&s,str);
   printf("替换为: ");
   scanf("%s%*c",str);
   InitString(&t);
   StrAssign(&t,str);
   for(i=0;i<n&&f;i++) /* 逐行查找、替换 */
   {
     k=1; /* 由每行第1个字符起查找 */
     while(k)
     {
       k=Index(T[i],s,k); /* 由本行的第k个字符开始查找 */
       if(k) /* 找到 */
       {
         printf("第%d行: ",i+1);
         StrPrint(T[i]);
         printf("第%d个字符处找到。是否替换(Y/N)? ",k);
         b=getchar();
         getchar();
         if(b=='Y'||b=='y')
         {
           StrDelete(&T[i],k,StrLength(s));
           StrInsert(&T[i],k,t);
         }
         printf("继续替换吗(Y/N)?");
         b=getchar();
         getchar();
         if(b!='Y'&&b!='y') /* 中断查找、替换 */
         {
           f=0;
           break;
         }
         else
           k+=StrLength(t);
       }
     }
   }
   if(f)
     printf("没找到\n");
 }

 void Save()
 { /* 存盘 */
   int i;
   getchar();
   fp=fopen(filename,"w");
   if(fp)
   {
     for(i=0;i<n;i++)
     {
       T[i].ch[T[i].length]=0;
       fputs(T[i].ch,fp);
       fputc(10,fp);
     }
     fputc(10,fp);
     fclose(fp);
   }
   else
     printf("存盘失败\n");
 }

 void main()
 {
   Status s=TRUE;
   int i,k;
   for(i=0;i<MAX_LEN;i++) /* 初始化串 */
     InitString(&T[i]);
   while(s)
   {
     printf("请选择: 1.打开文件(新或旧)  2.显示文件内容\n");
     printf("        3.插入行  4.删除行  5.拷贝行  6.修改行\n");
     printf("        7.查找字符串        8.替换字符串\n");
     printf("        9.存盘退出          0.放弃编辑\n");
     scanf("%d",&k);
     switch(k)
     {
       case 1: Open();
               break;
       case 2: List();
               break;
       case 3: Insert();
               break;
       case 4: Delete();
               break;
       case 5: Copy();
               break;
       case 6: Modify();
               break;
       case 7: Search();
               break;
       case 8: Replace1();
               break;
       case 9: Save();
       case 0: s=FALSE;
     }
   }
 }

**********ALGO4-4.c**********
 /* algo4-4.c 生成书名关键词索引文件bookidx.txt，算法4.9～4.14 */
 /* 为运行algo4-5.c做准备 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-5.h"
 #include"bo2-6.c"
 #include"c4-2.h"
 #include"bo4-2.c"

 #define MaxKeyNum 25 /* 索引表的最大容量(关键词的最大数) */
 #define MaxLineLen 51 /* 书目串(书名+书号)buf的最大长度 */
 #define MaxWordNum 10 /* 词表(一本书的关键词)的最大容量 */
 #define MaxNoIdx 10 /* 常用词(仅指大写)的最大数 */
 typedef struct
 {
   char *item[MaxWordNum]; /* 词表(字符串)指针数组 */
   int last; /* 词的数量 */
 }WordListType; /* 词表类型(顺序表) */

 typedef struct
 {
   HString key; /* 关键词(堆分配类型,c4-2.h) */
   LinkList bnolist; /* 存放书号索引的链表(c2-5.h) */
 }IdxTermType; /* 索引项类型 */

 typedef struct
 {
   IdxTermType item[MaxKeyNum+1];
   int last; /* 关键词的个数 */
 }IdxListType; /* 索引表类型(有序表) */

 typedef struct
 {
   char *item[MaxNoIdx]; /* 常用词表指针数组 */
   int last; /* 常用词的数量 */
 }NoIdxType; /* 常用词表类型(有序表) */

 /* 全局变量 */
 char buf[MaxLineLen+1]; /* 当前书目串(包括'\0') */
 WordListType wdlist; /* 暂存一本书的词表 */
 NoIdxType noidx; /* 常用词表 */

 void InitIdxList(IdxListType *idxlist)
 { /* 初始化操作，置索引表idxlist为空表，且在idxliat.item[0]设一空串 */
   (*idxlist).last=0;
   InitString(&(*idxlist).item[0].key); /* bo4-2.c */
   InitList(&(*idxlist).item[0].bnolist); /* bo2-6.c */
 }

 void ExtractKeyWord(int *BookNo)
 { /* 从buf中提取书名关键词到词表wdlist，书号存入BookNo */
   int i,l,f=1; /* f是字符串结束标志 0: 结束 1: 未结束 */
   char *s1,*s2;
   if(buf[0]<'0'||buf[0]>'9') /* buf的首字母不是数字 */
     exit(OVERFLOW);
   for(i=1;i<=wdlist.last;i++) /* 释放上一个书目在词表wdlist的存储空间 */
   {
     free(wdlist.item[i]);
     wdlist.item[i]=NULL;
   }
   wdlist.last=0;
   *BookNo=(buf[0]-'0')*100+(buf[1]-'0')*10+(buf[2]-'0'); /* 前三位为书号 */
   s2=&buf[2]; /* s1指向书号的尾字符 */
   do
   { /* 提取书名关键词到词表wdlist */
     s1=s2+1; /* s1向后移动一个单词 */
     s2=strchr(s1,' '); /* s2指向s1的第一个空格,如没有,返回NULL */
     if(!s2) /* 到串尾 */
     {
       s2=strchr(s1,'\12'); /* s2指向buf的最后一个字符(回车符) */
       f=0;
     }
     l=s2-s1; /* 单词长度 */
     if(s1[0]>='A'&&s1[0]<='Z') /* 单词首字母为大写 */
     { /* 写入词表 */
       wdlist.item[wdlist.last]=(char *)malloc((l+1)*sizeof(char));
       /* 生成串空间(包括'\0') */
       for(i=0;i<l;i++)
         wdlist.item[wdlist.last][i]=s1[i]; /* 写入词表 */
       wdlist.item[wdlist.last][l]=0;
       for(i=0;i<noidx.last;i++) /* 查找是否为常用词 */
         if(!strcmp(wdlist.item[wdlist.last],noidx.item[i]))
           break;
       if(i!=noidx.last) /* 是常用词 */
       {
         free(wdlist.item[wdlist.last]); /* 从词表中删除该词 */
         wdlist.item[wdlist.last]=NULL;
       }
       else
         wdlist.last++; /* 词表长度+1 */
     }
   }while(f);
 }

 void GetWord(int i,HString *wd)
 { /* 用wd返回词表wdlist中第i个关键词 */
   StrAssign(wd,wdlist.item[i]); /* 生成关键字字符串 bo4-2.c */
 }

 int Locate(IdxListType *idxlist,HString wd,Status *b)
 { /* 在索引表idxlist中查询是否存在与wd相等的关键词。若存在,则返回其 */
   /* 在索引表中的位置,且b取值TRUE;否则返回插入位置,且b取值FALSE */
   int i,m;
   for(i=(*idxlist).last;(m=StrCompare((*idxlist).item[i].key,wd))>0;--i); /* bo4-2.c */
   if(m==0) /* 找到 */
   {
     *b=TRUE;
     return i;
   }
   else
   {
     *b=FALSE;
     return i+1;
   }
 }

 void InsertNewKey(IdxListType *idxlist,int i,HString wd)
 { /* 在索引表idxlist的第i项上插入新关键词wd,并初始化书号索引的链表为空表 */
   int j;
   InitList(&(*idxlist).item[(*idxlist).last+1].bnolist); /* bo2-6.c */
   for(j=(*idxlist).last;j>=i;--j) /* 后移索引项 */
     (*idxlist).item[j+1]=(*idxlist).item[j];
   InitString(&(*idxlist).item[i].key); /* bo4-2.c */
   StrCopy(&(*idxlist).item[i].key,wd); /* 串拷贝插入新的索引项 bo4-2.c */
   InitList(&(*idxlist).item[i].bnolist); /* 初始化书号索引表为空表 bo2-6.c */
   (*idxlist).last++;
 }

 void InsertBook(IdxListType *idxlist,int i,int bno)
 { /* 在索引表idxlist的第i项中插入书号为bno的索引 */
   Link p;
   if(!MakeNode(&p,bno)) /* 分配失败 bo2-6.c */
     exit(OVERFLOW);
   p->next=NULL;
   Append(&(*idxlist).item[i].bnolist,p); /* 插入新的书号索引 bo2-6.c */
 }

 void InsIdxList(IdxListType *idxlist,int bno)
 { /* 将书号为bno的关键词插入索引表 */
   int i,j;
   Status b;
   HString wd;
   InitString(&wd); /* bo4-2.c */
   for(i=0;i<wdlist.last;i++)
   {
     GetWord(i,&wd);
     j=Locate(idxlist,wd,&b);
     if(!b)
       InsertNewKey(idxlist,j,wd); /* 插入新的索引项 */
     InsertBook(idxlist,j,bno); /* 插入书号索引 */
   }
 }

 void PutText(FILE *f,IdxListType idxlist)
 { /* 将生成的索引表idxlist输出到文件f */
   int i,j;
   Link p;
   fprintf(f,"%d\n",idxlist.last);
   for(i=1;i<=idxlist.last;i++)
   {
     for(j=0;j<idxlist.item[i].key.length;j++)
       fprintf(f,"%c",idxlist.item[i].key.ch[j]);
     fprintf(f,"\n%d\n",idxlist.item[i].bnolist.len);
     p=idxlist.item[i].bnolist.head;
     for(j=1;j<=idxlist.item[i].bnolist.len;j++)
     {
       p=p->next;
       fprintf(f,"%d ",p->data);
     }
     fprintf(f,"\n");
   }
 }

 void main()
 {
   FILE *f; /* 任何时间最多打开一个文件 */
   IdxListType idxlist; /* 索引表 */
   int BookNo; /* 书号变量 */
   int k,l;
   f=fopen("NoIdx.txt","r"); /* 打开常用词文件 */
   if(!f)
     exit(OVERFLOW);
   fscanf(f,"%d",&noidx.last); /* 常用词个数 */
   for(k=0;k<noidx.last;k++) /* 把常用词文件的内容拷到noidx中 */
   {
     fscanf(f,"%s",buf);
     l=strlen(buf);
     noidx.item[k]=(char*)malloc(l*sizeof(char));
     strcpy(noidx.item[k],buf);
   }
   fclose(f);
   f=fopen("BookInfo.txt","r"); /* 打开书目文件 */
   if(!f)
     exit(FALSE);
   InitIdxList(&idxlist); /* 初始化索引表idxlist为空 */
   wdlist.last=0; /* 词表长度初值为0 */
   while(!feof(f))
   {
     fgets(buf,MaxLineLen,f);
     l=strlen(buf);
     if(l<=1)
       break;
     ExtractKeyWord(&BookNo); /* 从buf中提取关键词到词表，书号存入BookNo */
     InsIdxList(&idxlist,BookNo);
   }
   fclose(f);
   f=fopen("BookIdx.txt","w");
   if(!f)
     exit(INFEASIBLE);
   PutText(f,idxlist); /* 将生成的索引表idxlist输出到文件f */
   fclose(f);
 }

**********ALGO4-5.c**********
 /* algo4-5.c 根据algo4-4.c产生的文件,索引查询图书 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-5.h"
 #include"bo2-6.c"
 #include"c4-2.h"
 #include"bo4-2.c"

 #define MaxBookNum 10 /* 假设只对10本书建索引表 */
 #define MaxKeyNum 25 /* 索引表的最大容量(关键词的最大数) */
 #define MaxLineLen 51 /* 书目串(书名+书号)buf的最大长度 */

 typedef struct
 {
   HString key; /* 关键词(堆分配类型,c4-2.h) */
   LinkList bnolist; /* 存放书号索引的链表(c2-5.h) */
 }IdxTermType; /* 索引项类型 */

 typedef struct
 {
   IdxTermType item[MaxKeyNum+1];
   int last; /* 关键词的个数 */
 }IdxListType; /* 索引表类型(有序表) */

 typedef struct
 {
   char bookname[MaxLineLen]; /* 书目串 */
   int bookno; /* 书号 */
 }BookTermType; /* 书目项类型 */

 typedef struct BookListType /* 书目表类型(有序表) */
 {
   BookTermType item[MaxBookNum];
   int last; /* 书目的数量 */
 }BookListType; /* 书目表类型(有序表) */

 void main()
 {
   FILE *f; /* 任何时间最多打开一个文件 */
   IdxListType idxlist; /* 索引表 */
   BookListType booklist; /* 书目表 */
   char buf[MaxLineLen+1]; /* 当前书目串(包括'\0') */
   HString ch; /* 索引字符串 */
   int BookNo; /* 书号变量 */
   int i,k,l;
   Link p;
   InitString(&ch); /* 初始化HString类型的变量 */
   f=fopen("BookIdx.txt","r"); /* 打开书名关键词索引表文件 */
   if(!f)
     exit(OVERFLOW);
   fscanf(f,"%d",&idxlist.last); /* 书名关键词个数 */
   for(k=0;k<idxlist.last;k++) /* 把关键词文件的内容拷到idxlist中 */
   {
     fscanf(f,"%s",buf);
     i=0;
     while(buf[i])
       buf[i++]=tolower(buf[i]); /* 字母转为小写 */
     InitString(&idxlist.item[k].key);
     StrAssign(&idxlist.item[k].key,buf);
     InitList(&idxlist.item[k].bnolist); /* 初始化书号链表 bo2-6.c */
     fscanf(f,"%d",&i);
     for(l=0;l<i;l++)
     {
       fscanf(f,"%d",&BookNo);
       if(!MakeNode(&p,BookNo)) /* 分配失败 bo2-6.c */
         exit(OVERFLOW);
       p->next=NULL;
       Append(&idxlist.item[k].bnolist,p); /* 插入新的书号索引 bo2-6.c */
     }
   }
   fclose(f);
   f=fopen("BookInfo.txt","r"); /* 打开书目文件 */
   if(!f)
     exit(FALSE);
   i=0;
   while(!feof(f)) /* 把书目文件的内容拷到booklist中 */
   {
     fgets(buf,MaxLineLen,f);
     booklist.item[i].bookno=(buf[0]-'0')*100+(buf[1]-'0')*10+(buf[2]-'0'); /* 前三位为书号 */
     strcpy(booklist.item[i].bookname,buf);
     i++;
   }
   booklist.last=i;
   printf("请输入书目的关键词(一个)");
   scanf("%s",buf);
   i=0;
   while(buf[i])
     buf[i++]=tolower(buf[i]); /* 字母转为小写 */
   StrAssign(&ch,buf);
   i=0;
   do
   {
     k=StrCompare(ch,idxlist.item[i].key); /* bo4-2.c */
     i++;
   }while(k&&i<=idxlist.last);
   if(!k) /* 索引表中有此关键词 */
   {
     p=idxlist.item[i-1].bnolist.head->next;
     while(p)
     {
       l=0;
       while(l<booklist.last&&p->data!=booklist.item[l].bookno)
         l++;
       if(l<booklist.last)
         printf("%s",booklist.item[l].bookname);
       p=p->next;
     }
   }
   else
     printf("没找到\n");
 }

**********BO4-1.C**********
 /* bo4-1.c 串采用定长顺序存储结构(由c4-1.h定义)的基本操作(14个) */
 /* SString是数组，故不需引用类型。此基本操作包括算法4.2,4.3,4.5 */
 Status StrAssign(SString T,char *chars)
 { /* 生成一个其值等于chars的串T */
   int i;
   if(strlen(chars)>MAXSTRLEN)
     return ERROR;
   else
   {
     T[0]=strlen(chars);
     for(i=1;i<=T[0];i++)
       T[i]=*(chars+i-1);
     return OK;
   }
 }

 Status StrCopy(SString T,SString S)
 { /* 由串S复制得串T */
   int i;
   for(i=0;i<=S[0];i++)
     T[i]=S[i];
   return OK;
 }

 Status StrEmpty(SString S)
 { /* 若S为空串,则返回TRUE,否则返回FALSE */
   if(S[0]==0)
     return TRUE;
   else
     return FALSE;
 }

 int StrCompare(SString S,SString T)
 { /* 初始条件: 串S和T存在 */
   /* 操作结果: 若S>T,则返回值>0;若S=T,则返回值=0;若S<T,则返回值<0 */
   int i;
   for(i=1;i<=S[0]&&i<=T[0];++i)
     if(S[i]!=T[i])
       return S[i]-T[i];
   return S[0]-T[0];
 }

 int StrLength(SString S)
 { /* 返回串的元素个数 */
   return S[0];
 }

 Status ClearString(SString S)
 { /* 初始条件:串S存在。操作结果:将S清为空串 */
   S[0]=0;/* 令串长为零 */
   return OK;
 }

 Status Concat(SString T,SString S1,SString S2) /* 算法4.2改 */
 { /* 用T返回S1和S2联接而成的新串。若未截断，则返回TRUE，否则FALSE */
   int i;
   if(S1[0]+S2[0]<=MAXSTRLEN)
   { /* 未截断 */
     for(i=1;i<=S1[0];i++)
       T[i]=S1[i];
     for(i=1;i<=S2[0];i++)
       T[S1[0]+i]=S2[i];
     T[0]=S1[0]+S2[0];
     return TRUE;
   }
   else
   { /* 截断S2 */
     for(i=1;i<=S1[0];i++)
       T[i]=S1[i];
     for(i=1;i<=MAXSTRLEN-S1[0];i++)
       T[S1[0]+i]=S2[i];
     T[0]=MAXSTRLEN;
     return FALSE;
   }
 }

 Status SubString(SString Sub,SString S,int pos,int len)
 { /* 用Sub返回串S的第pos个字符起长度为len的子串。算法4.3 */
   int i;
   if(pos<1||pos>S[0]||len<0||len>S[0]-pos+1)
     return ERROR;
   for(i=1;i<=len;i++)
     Sub[i]=S[pos+i-1];
   Sub[0]=len;
   return OK;
 }

 int Index(SString S,SString T,int pos)
 { /* 返回子串T在主串S中第pos个字符之后的位置。若不存在,则函数值为0。 */
   /* 其中,T非空,1≤pos≤StrLength(S)。算法4.5 */
   int i,j;
   if(1<=pos&&pos<=S[0])
   {
     i=pos;
     j=1;
     while(i<=S[0]&&j<=T[0])
       if(S[i]==T[j]) /* 继续比较后继字符 */
       {
         ++i;
         ++j;
       }
       else /* 指针后退重新开始匹配 */
       {
         i=i-j+2;
         j=1;
       }
     if(j>T[0])
       return i-T[0];
     else
       return 0;
   }
   else
     return 0;
 }

 Status StrInsert(SString S,int pos,SString T)
 { /* 初始条件: 串S和T存在,1≤pos≤StrLength(S)+1 */
   /* 操作结果: 在串S的第pos个字符之前插入串T。完全插入返回TRUE,部分插入返回FALSE */
   int i;
   if(pos<1||pos>S[0]+1)
     return ERROR;
   if(S[0]+T[0]<=MAXSTRLEN)
   { /* 完全插入 */
     for(i=S[0];i>=pos;i--)
       S[i+T[0]]=S[i];
     for(i=pos;i<pos+T[0];i++)
       S[i]=T[i-pos+1];
     S[0]=S[0]+T[0];
     return TRUE;
   }
   else
   { /* 部分插入 */
     for(i=MAXSTRLEN;i<=pos;i--)
       S[i]=S[i-T[0]];
     for(i=pos;i<pos+T[0];i++)
       S[i]=T[i-pos+1];
     S[0]=MAXSTRLEN;
     return FALSE;
   }
 }

 Status StrDelete(SString S,int pos,int len)
 { /* 初始条件: 串S存在,1≤pos≤StrLength(S)-len+1 */
   /* 操作结果: 从串S中删除第pos个字符起长度为len的子串 */
   int i;
   if(pos<1||pos>S[0]-len+1||len<0)
     return ERROR;
   for(i=pos+len;i<=S[0];i++)
     S[i-len]=S[i];
   S[0]-=len;
   return OK;
 }

 Status Replace(SString S,SString T,SString V)
 { /* 初始条件: 串S,T和V存在,T是非空串（此函数与串的存储结构无关） */
   /* 操作结果: 用V替换主串S中出现的所有与T相等的不重叠的子串 */
   int i=1; /* 从串S的第一个字符起查找串T */
   if(StrEmpty(T)) /* T是空串 */
     return ERROR;
   do
   {
     i=Index(S,T,i); /* 结果i为从上一个i之后找到的子串T的位置 */
     if(i) /* 串S中存在串T */
     {
       StrDelete(S,i,StrLength(T)); /* 删除该串T */
       StrInsert(S,i,V); /* 在原串T的位置插入串V */
       i+=StrLength(V); /* 在插入的串V后面继续查找串T */
     }
   }while(i);
   return OK;
 }

 void DestroyString()
 { /* 由于SString是定长类型,无法销毁 */
 }

 void StrPrint(SString T)
 { /* 输出字符串T。另加 */
   int i;
   for(i=1;i<=T[0];i++)
     printf("%c",T[i]);
   printf("\n");
 }

**********Bo4-2.c**********
 /* bo4-2.c 串采用堆分配存储结构(由c4-2.h定义)的基本操作(15个) */
 /* 包括算法4.1、4.4 */
 Status StrAssign(HString *T,char *chars)
 { /* 生成一个其值等于串常量chars的串T */
   int i,j;
   if((*T).ch)
     free((*T).ch); /* 释放T原有空间 */
   i=strlen(chars); /* 求chars的长度i */
   if(!i)
   { /* chars的长度为0 */
     (*T).ch=NULL;
     (*T).length=0;
   }
   else
   { /* chars的长度不为0 */
     (*T).ch=(char*)malloc(i*sizeof(char)); /* 分配串空间 */
     if(!(*T).ch) /* 分配串空间失败 */
       exit(OVERFLOW);
     for(j=0;j<i;j++) /* 拷贝串 */
       (*T).ch[j]=chars[j];
     (*T).length=i;
   }
   return OK;
 }

 Status StrCopy(HString *T,HString S)
 { /* 初始条件:串S存在。操作结果: 由串S复制得串T */
   int i;
   if((*T).ch)
     free((*T).ch); /* 释放T原有空间 */
   (*T).ch=(char*)malloc(S.length*sizeof(char)); /* 分配串空间 */
   if(!(*T).ch) /* 分配串空间失败 */
     exit(OVERFLOW);
   for(i=0;i<S.length;i++) /* 拷贝串 */
     (*T).ch[i]=S.ch[i];
   (*T).length=S.length;
   return OK;
 }

 Status StrEmpty(HString S)
 { /* 初始条件: 串S存在。操作结果: 若S为空串,则返回TRUE,否则返回FALSE */
   if(S.length==0&&S.ch==NULL)
     return TRUE;
   else
     return FALSE;
 }

 int StrCompare(HString S,HString T)
 { /* 若S>T,则返回值>0;若S=T,则返回值=0;若S<T,则返回值<0 */
   int i;
   for(i=0;i<S.length&&i<T.length;++i)
     if(S.ch[i]!=T.ch[i])
       return S.ch[i]-T.ch[i];
   return S.length-T.length;
 }

 int StrLength(HString S)
 { /* 返回S的元素个数,称为串的长度 */
   return S.length;
 }

 Status ClearString(HString *S)
 { /* 将S清为空串 */
   if((*S).ch)
   {
     free((*S).ch);
     (*S).ch=NULL;
   }
   (*S).length=0;
   return OK;
 }

 Status Concat(HString *T,HString S1,HString S2)
 { /* 用T返回由S1和S2联接而成的新串 */
   int i;
   if((*T).ch)
     free((*T).ch); /* 释放旧空间 */
   (*T).length=S1.length+S2.length;
   (*T).ch=(char *)malloc((*T).length*sizeof(char));
   if(!(*T).ch)
     exit(OVERFLOW);
   for(i=0;i<S1.length;i++)
     (*T).ch[i]=S1.ch[i];
   for(i=0;i<S2.length;i++)
     (*T).ch[S1.length+i]=S2.ch[i];
   return OK;
 }

 Status SubString(HString *Sub, HString S,int pos,int len)
 { /* 用Sub返回串S的第pos个字符起长度为len的子串。 */
   /* 其中,1≤pos≤StrLength(S)且0≤len≤StrLength(S)-pos+1 */
   int i;
   if(pos<1||pos>S.length||len<0||len>S.length-pos+1)
     return ERROR;
   if((*Sub).ch)
     free((*Sub).ch); /* 释放旧空间 */
   if(!len) /* 空子串 */
   {
     (*Sub).ch=NULL;
     (*Sub).length=0;
   }
   else
   { /* 完整子串 */
     (*Sub).ch=(char*)malloc(len*sizeof(char));
     if(!(*Sub).ch)
       exit(OVERFLOW);
     for(i=0;i<=len-1;i++)
       (*Sub).ch[i]=S.ch[pos-1+i];
     (*Sub).length=len;
   }
   return OK;
 }

 void InitString(HString *T)
 { /* 初始化(产生空串)字符串T。另加 */
   (*T).length=0;
   (*T).ch=NULL;
 }

 int Index(HString S,HString T,int pos) /* 算法4.1 */
 { /* T为非空串。若主串S中第pos个字符之后存在与T相等的子串, */
   /* 则返回第一个这样的子串在S中的位置,否则返回0 */
   int n,m,i;
   HString sub;
   InitString(&sub);
   if(pos>0)
   {
     n=StrLength(S);
     m=StrLength(T);
     i=pos;
     while(i<=n-m+1)
     {
       SubString(&sub,S,i,m);
       if(StrCompare(sub,T)!=0)
	 ++i;
       else
	 return i;
     }
   }
   return 0;
  }

 Status StrInsert(HString *S,int pos,HString T) /* 算法4.4 */
 { /* 1≤pos≤StrLength(S)+1。在串S的第pos个字符之前插入串T */
   int i;
   if(pos<1||pos>(*S).length+1) /* pos不合法 */
     return ERROR;
   if(T.length) /* T非空,则重新分配空间,插入T */
   {
     (*S).ch=(char*)realloc((*S).ch,((*S).length+T.length)*sizeof(char));
     if(!(*S).ch)
       exit(OVERFLOW);
     for(i=(*S).length-1;i>=pos-1;--i) /* 为插入T而腾出位置 */
       (*S).ch[i+T.length]=(*S).ch[i];
     for(i=0;i<T.length;i++)
       (*S).ch[pos-1+i]=T.ch[i]; /* 插入T */
     (*S).length+=T.length;
   }
   return OK;
 }

 Status StrDelete(HString *S,int pos,int len)
 { /* 从串S中删除第pos个字符起长度为len的子串 */
   int i;
   if((*S).length<pos+len-1)
     exit(ERROR);
   for(i=pos-1;i<=(*S).length-len;i++)
     (*S).ch[i]=(*S).ch[i+len];
   (*S).length-=len;
   (*S).ch=(char*)realloc((*S).ch,(*S).length*sizeof(char));
   return OK;
 }

 Status Replace(HString *S,HString T,HString V)
 { /* 初始条件: 串S,T和V存在,T是非空串（此函数与串的存储结构无关） */
   /* 操作结果: 用V替换主串S中出现的所有与T相等的不重叠的子串 */
   int i=1; /* 从串S的第一个字符起查找串T */
   if(StrEmpty(T)) /* T是空串 */
     return ERROR;
   do
   {
     i=Index(*S,T,i); /* 结果i为从上一个i之后找到的子串T的位置 */
     if(i) /* 串S中存在串T */
     {
       StrDelete(S,i,StrLength(T)); /* 删除该串T */
       StrInsert(S,i,V); /* 在原串T的位置插入串V */
       i+=StrLength(V); /* 在插入的串V后面继续查找串T */
     }
   }while(i);
   return OK;
 }

 void DestroyString()
 { /* 堆分配类型的字符串无法销毁 */
 }

 void StrPrint(HString T)
 { /* 输出T字符串。另加 */
   int i;
   for(i=0;i<T.length;i++)
     printf("%c",T.ch[i]);
   printf("\n");
 }

**********BO4-3.c**********
 /* bo4-3.c 串采用块链存储结构(由c4-3.h定义)的基本操作(16个) */
 void InitString(LString *T)
 { /* 初始化(产生空串)字符串T。另加 */
   (*T).curlen=0;
   (*T).head=NULL;
   (*T).tail=NULL;
 }

 Status StrAssign(LString *T,char *chars)
 { /* 生成一个其值等于chars的串T(要求chars中不包含填补空余的字符) */
   /* 成功返回OK，否则返回ERROR */
   int i,j,k,l;
   Chunk *p,*q;
   i=strlen(chars); /* i为串的长度 */
   if(!i||strchr(chars,blank)) /* 串长为0或chars中包含填补空余的字符 */
     return ERROR;
   (*T).curlen=i;
   j=i/CHUNKSIZE; /* j为块链的结点数 */
   if(i%CHUNKSIZE)
     j++;
   for(k=0;k<j;k++)
   {
     p=(Chunk*)malloc(sizeof(Chunk));
     if(!p)
       return ERROR;
     if(k==0) /* 第一个链块 */
       (*T).head=q=p;
     else
     {
       q->next=p;
       q=p;
     }
     for(l=0;l<CHUNKSIZE&&*chars;l++)
       *(q->ch+l)=*chars++;
     if(!*chars) /* 最后一个链块 */
     {
       (*T).tail=q;
       q->next=NULL;
       for(;l<CHUNKSIZE;l++) /* 用填补空余的字符填满链表 */
         *(q->ch+l)=blank;
     }
   }
   return OK;
 }

 Status StrCopy(LString *T,LString S)
 { /* 初始条件:串S存在。操作结果:由串S复制得串T(连填补空余的字符一块拷贝) */
   Chunk *h=S.head,*p,*q;
   (*T).curlen=S.curlen;
   if(h)
   {
     p=(*T).head=(Chunk*)malloc(sizeof(Chunk));
     *p=*h; /* 复制1个结点 */
     h=h->next;
     while(h)
     {
       q=p;
       p=(Chunk*)malloc(sizeof(Chunk));
       q->next=p;
       *p=*h;
       h=h->next;
     }
     p->next=NULL;
     (*T).tail=p;
     return OK;
   }
   else
    return ERROR;
 }

 Status StrEmpty(LString S)
 { /* 初始条件:串S存在。操作结果:若S为空串,则返回TRUE,否则返回FALSE */
   if(S.curlen) /* 非空 */
     return FALSE;
   else
     return TRUE;
 }

 int StrCompare(LString S,LString T)
 { /* 若S>T,则返回值>0;若S=T,则返回值=0;若S<T,则返回值<0 */
   int i=0; /* i为当前待比较字符在S,T串中的位置 */
   Chunk *ps=S.head,*pt=T.head; /* ps,pt分别指向S和T的待比较块 */
   int js=0,jt=0; /* js,jt分别指示S和T的待比较字符在块中的位序 */
   while(i<S.curlen&&i<T.curlen)
   {
     i++; /* 分别找S和T的第i个字符 */
     while(*(ps->ch+js)==blank) /* 跳过填补空余的字符 */
     {
       js++;
       if(js==CHUNKSIZE)
       {
         ps=ps->next;
         js=0;
       }
     }; /* *(ps->ch+js)为S的第i个有效字符 */
     while(*(pt->ch+jt)==blank) /* 跳过填补空余的字符 */
     {
       jt++;
       if(jt==CHUNKSIZE)
       {
         pt=pt->next;
         jt=0;
       }
     }; /* *(pt->ch+jt)为T的第i个有效字符 */
     if(*(ps->ch+js)!=*(pt->ch+jt))
       return *(ps->ch+js)-*(pt->ch+jt);
     else /* 继续比较下一个字符 */
     {
       js++;
       if(js==CHUNKSIZE)
       {
         ps=ps->next;
         js=0;
       }
       jt++;
       if(jt==CHUNKSIZE)
       {
         pt=pt->next;
         jt=0;
       }
     }
   }
   return S.curlen-T.curlen;
 }

 int StrLength(LString S)
 { /* 返回S的元素个数,称为串的长度 */
   return S.curlen;
 }

 Status ClearString(LString *S)
 { /* 初始条件: 串S存在。操作结果: 将S清为空串 */
   Chunk *p,*q;
   p=(*S).head;
   while(p)
   {
     q=p->next;
     free(p);
     p=q;
   }
   (*S).head=NULL;
   (*S).tail=NULL;
   (*S).curlen=0;
   return OK;
 }

 Status Concat(LString *T,LString S1,LString S2)
 { /* 用T返回由S1和S2联接而成的新串 */
   LString a1,a2;
   InitString(&a1);
   InitString(&a2);
   StrCopy(&a1,S1);
   StrCopy(&a2,S2);
   (*T).curlen=S1.curlen+S2.curlen;
   (*T).head=a1.head;
   a1.tail->next=a2.head;
   (*T).tail=a2.tail;
   return OK;
 }

 Status SubString(LString *Sub, LString S,int pos,int len)
 { /* 用Sub返回串S的第pos个字符起长度为len的子串。 */
   /* 其中,1≤pos≤StrLength(S)且0≤len≤StrLength(S)-pos+1 */
   Chunk *p,*q;
   int i,k,n,flag=1;
   if(pos<1||pos>S.curlen||len<0||len>S.curlen-pos+1)
     return ERROR;
   n=len/CHUNKSIZE; /* 生成空的Sub串 */
   if(len%CHUNKSIZE)
     n++; /* n为块的个数 */
   p=(Chunk*)malloc(sizeof(Chunk));
   (*Sub).head=p;
   for(i=1;i<n;i++)
   {
     q=(Chunk*)malloc(sizeof(Chunk));
     p->next=q;
     p=q;
   }
   p->next=NULL;
   (*Sub).tail=p;
   (*Sub).curlen=len;
   for(i=len%CHUNKSIZE;i<CHUNKSIZE;i++)
     *(p->ch+i)=blank; /* 填充Sub尾部的多余空间 */
   q=(*Sub).head; /* q指向Sub串即将复制的块 */
   i=0; /* i指示即将复制的字符在块中的位置 */
   p=S.head; /* p指向S串的当前块 */
   n=0; /* n指示当前字符在串中的序号 */
   while(flag)
   {
     for(k=0;k<CHUNKSIZE;k++) /* k指示当前字符在块中的位置 */
       if(*(p->ch+k)!=blank)
       {
         n++;
         if(n>=pos&&n<=pos+len-1) /* 复制 */
         {
           if(i==CHUNKSIZE)
           { /* 到下一块 */
             q=q->next;
             i=0;
           }
           *(q->ch+i)=*(p->ch+k);
           i++;
           if(n==pos+len-1) /* 复制结束 */
           {
             flag=0;
             break;
           }
         }
       }
     p=p->next;
   }
   return OK;
 }

 int Index(LString S,LString T,int pos)
 { /* T为非空串。若主串S中第pos个字符之后存在与T相等的子串, */
   /* 则返回第一个这样的子串在S中的位置,否则返回0 */
   int i,n,m;
   LString sub;
   if(pos>=1&&pos<=StrLength(S)) /* pos满足条件 */
   {
     n=StrLength(S); /* 主串长度 */
     m=StrLength(T); /* T串长度 */
     i=pos;
     while(i<=n-m+1)
     {
       SubString(&sub,S,i,m); /* sub为从S的第i个字符起,长度为m的子串 */
       if(StrCompare(sub,T)!=0) /* sub不等于T */
         ++i;
       else
         return i;
     }
   }
   return 0;
 }

 void Zip(LString *S)
 { /* 压缩串(清除块中不必要的填补空余的字符)。加 */
   int j,n=0;
   Chunk *h=(*S).head;
   char *q;
   q=(char*)malloc(((*S).curlen+1)*sizeof(char));
   while(h) /* 将LString类型的字符串转换为char[]类型的字符串 */
   {
     for(j=0;j<CHUNKSIZE;j++)
       if(*(h->ch+j)!=blank)
       {
         *(q+n)=*(h->ch+j);
         n++;
       }
     h=h->next;
   }
   *(q+n)=0; /* 串结束符 */
   ClearString(S); /* 清空S */
   StrAssign(S,q); /* 重新生成S */
 }

 Status StrInsert(LString *S,int pos,LString T)
 { /* 1≤pos≤StrLength(S)+1。在串S的第pos个字符之前插入串T */
   int i,j,k;
   Chunk *p,*q;
   LString t;
   if(pos<1||pos>StrLength(*S)+1) /* pos超出范围 */
     return ERROR;
   StrCopy(&t,T); /* 复制T为t */
   Zip(S); /* 去掉S中多余的填补空余的字符 */
   i=(pos-1)/CHUNKSIZE; /* 到达插入点要移动的块数 */
   j=(pos-1)%CHUNKSIZE; /* 到达插入点在最后一块上要移动的字符数 */
   p=(*S).head;
   if(pos==1) /* 插在S串前 */
   {
     t.tail->next=(*S).head;
     (*S).head=t.head;
   }
   else if(j==0) /* 插在块之间 */
   {
     for(k=1;k<i;k++)
       p=p->next; /* p指向插入点的左块 */
     q=p->next; /* q指向插入点的右块 */
     p->next=t.head; /* 插入t */
     t.tail->next=q;
     if(q==NULL) /* 插在S串后 */
       (*S).tail=t.tail; /* 改变尾指针 */
   }
   else /* 插在一块内的两个字符之间 */
   {
     for(k=1;k<=i;k++)
       p=p->next; /* p指向插入点所在块 */
     q=(Chunk*)malloc(sizeof(Chunk)); /* 生成新块 */
     for(i=0;i<j;i++)
       *(q->ch+i)=blank; /* 块q的前j个字符为填补空余的字符 */
     for(i=j;i<CHUNKSIZE;i++)
     {
       *(q->ch+i)=*(p->ch+i); /* 复制插入点后的字符到q */
       *(p->ch+i)=blank; /* p的该字符为填补空余的字符 */
     }
     q->next=p->next;
     p->next=t.head;
     t.tail->next=q;
   }
   (*S).curlen+=t.curlen;
   Zip(S);
   return OK;
 }

 Status StrDelete(LString *S,int pos,int len)
 { /* 从串S中删除第pos个字符起长度为len的子串 */
   int i=1; /* 当前字符是S串的第i个字符(1～S.curlen) */
   Chunk *p=(*S).head; /* p指向S的当前块 */
   int j=0; /* 当前字符在当前块中的位序(0～CHUNKSIZE-1) */
   if(pos<1||pos>(*S).curlen-len+1||len<0) /* pos,len的值超出范围 */
     return ERROR;
   while(i<pos) /* 找第pos个字符 */
   {
     while(*(p->ch+j)==blank) /* 跳过填补空余的字符 */
     {
       j++;
       if(j==CHUNKSIZE) /* 应转向下一块 */
       {
         p=p->next;
         j=0;
       }
     }
     i++; /* 当前字符是S的第i个字符 */
     j++;
     if(j==CHUNKSIZE) /* 应转向下一块 */
     {
       p=p->next;
       j=0;
     }
   }; /* i=pos,*(p->ch+j)为S的第pos个有效字符 */
   while(i<pos+len) /* 删除从第pos个字符起到第pos+len-1个字符 */
   {
     while(*(p->ch+j)==blank) /* 跳过填补空余的字符 */
     {
       j++;
       if(j==CHUNKSIZE) /* 应转向下一块 */
       {
         p=p->next;
         j=0;
       }
     }
     *(p->ch+j)=blank; /* 把字符改成填补空余的字符来＂删除＂第i个字符 */
     i++; /* 到下一个字符 */
     j++;
     if(j==CHUNKSIZE) /* 应转向下一块 */
     {
       p=p->next;
       j=0;
     }
   };
   (*S).curlen-=len; /* 串的当前长度 */
   return OK;
 }

 Status Replace(LString *S,LString T,LString V)
 { /* 初始条件: 串S,T和V存在,T是非空串（此函数与串的存储结构无关） */
   /* 操作结果: 用V替换主串S中出现的所有与T相等的不重叠的子串 */
   int i=1; /* 从串S的第一个字符起查找串T */
   if(StrEmpty(T)) /* T是空串 */
     return ERROR;
   do
   {
     i=Index(*S,T,i); /* 结果i为从上一个i之后找到的子串T的位置 */
     if(i) /* 串S中存在串T */
     {
       StrDelete(S,i,StrLength(T)); /* 删除该串T */
       StrInsert(S,i,V); /* 在原串T的位置插入串V */
       i+=StrLength(V); /* 在插入的串V后面继续查找串T */
     }
   }while(i);
   return OK;
 }

 void StrPrint(LString T)
 { /* 输出字符串T。另加 */
   int i=0,j;
   Chunk *h;
   h=T.head;
   while(i<T.curlen)
   {
     for(j=0;j<CHUNKSIZE;j++)
       if(*(h->ch+j)!=blank) /* 不是填补空余的字符 */
       {
         printf("%c",*(h->ch+j));
         i++;
       }
     h=h->next;
   }
   printf("\n");
 }

 void DestroyString()
 { /* 块链类型的字符串无法销毁 */
 }

**********C4-1.H**********
 /* c4-1.h 串的定长顺序存储表示 */
 #define MAXSTRLEN 40 /* 用户可在255以内定义最大串长（1个字节） */
 typedef char SString[MAXSTRLEN+1]; /* 0号单元存放串的长度 */

**********C4-2.H**********
 /* c4-2.h 串的堆分配存储 */
 typedef struct
 {
   char *ch; /* 若是非空串,则按串长分配存储区,否则ch为NULL */
   int length; /* 串长度 */
 }HString;
**********C4-3.H**********
 /* c4-3.h 串的块链存储表示 */
 #define CHUNKSIZE 4 /* 可由用户定义的块大小 */
 typedef struct Chunk
 {
   char ch[CHUNKSIZE];
   struct Chunk *next;
 }Chunk;
 typedef struct
 {
   Chunk *head,*tail; /* 串的头和尾指针 */
   int curlen; /* 串的当前长度 */
 }LString;
**********MAIN4-1.c**********
 /* main4-1.c 检验bo4-1.c的主程序 */
 #include"c1.h"
 #include"c4-1.h"
 #include"bo4-1.c"
 void main()
 {
   int i,j;
   Status k;
   char s,c[MAXSTRLEN+1];
   SString t,s1,s2;
   printf("请输入串s1: ");
   gets(c);
   k=StrAssign(s1,c);
   if(!k)
   {
     printf("串长超过MAXSTRLEN(=%d)\n",MAXSTRLEN);
     exit(0);
   }
   printf("串长为%d 串空否？%d(1:是 0:否)\n",StrLength(s1),StrEmpty(s1));
   StrCopy(s2,s1);
   printf("拷贝s1生成的串为: ");
   StrPrint(s2);
   printf("请输入串s2: ");
   gets(c);
   k=StrAssign(s2,c);
   if(!k)
   {
     printf("串长超过MAXSTRLEN(%d)\n",MAXSTRLEN);
     exit(0);
   }
   i=StrCompare(s1,s2);
   if(i<0)
     s='<';
   else if(i==0)
     s='=';
   else
     s='>';
   printf("串s1%c串s2\n",s);
   k=Concat(t,s1,s2);
   printf("串s1联接串s2得到的串t为: ");
   StrPrint(t);
   if(k==FALSE)
     printf("串t有截断\n");
   ClearString(s1);
   printf("清为空串后,串s1为: ");
   StrPrint(s1);
   printf("串长为%d 串空否？%d(1:是 0:否)\n",StrLength(s1),StrEmpty(s1));
   printf("求串t的子串,请输入子串的起始位置,子串长度: ");
   scanf("%d,%d",&i,&j);
   k=SubString(s2,t,i,j);
   if(k)
   {
     printf("子串s2为: ");
     StrPrint(s2);
   }
   printf("从串t的第pos个字符起,删除len个字符，请输入pos,len: ");
   scanf("%d,%d",&i,&j);
   StrDelete(t,i,j);
   printf("删除后的串t为: ");
   StrPrint(t);
   i=StrLength(s2)/2;
   StrInsert(s2,i,t);
   printf("在串s2的第%d个字符之前插入串t后,串s2为:\n",i);
   StrPrint(s2);
   i=Index(s2,t,1);
   printf("s2的第%d个字母起和t第一次匹配\n",i);
   SubString(t,s2,1,1);
   printf("串t为：");
   StrPrint(t);
   Concat(s1,t,t);
   printf("串s1为：");
   StrPrint(s1);
   Replace(s2,t,s1);
   printf("用串s1取代串s2中和串t相同的不重叠的串后,串s2为: ");
   StrPrint(s2);
 }
**********MAIN4-2.c**********
 /* main4-2.c 检验bo4-2.c的主程序 */
 #include"c1.h"
 #include"c4-2.h"
 #include"bo4-2.c"
 void main()
 {
   int i;
   char c,*p="God bye!",*q="God luck!";
   HString t,s,r;
   InitString(&t); /* HString类型必需初始化 */
   InitString(&s);
   InitString(&r);
   StrAssign(&t,p);
   printf("串t为: ");
   StrPrint(t);
   printf("串长为%d 串空否？%d(1:空 0:否)\n",StrLength(t),StrEmpty(t));
   StrAssign(&s,q);
   printf("串s为: ");
   StrPrint(s);
   i=StrCompare(s,t);
   if(i<0)
     c='<';
   else if(i==0)
     c='=';
   else
     c='>';
   printf("串s%c串t\n",c);
   Concat(&r,t,s);
   printf("串t联接串s产生的串r为: ");
   StrPrint(r);
   StrAssign(&s,"oo");
   printf("串s为: ");
   StrPrint(s);
   StrAssign(&t,"o");
   printf("串t为: ");
   StrPrint(t);
   Replace(&r,t,s);
   printf("把串r中和串t相同的子串用串s代替后，串r为:\n");
   StrPrint(r);
   ClearString(&s);
   printf("串s清空后，串长为%d 空否？%d(1:空 0:否)\n",StrLength(s),StrEmpty(s));
   SubString(&s,r,6,4);
   printf("串s为从串r的第6个字符起的4个字符，长度为%d 串s为: ",s.length);
   StrPrint(s);
   StrCopy(&t,r);
   printf("复制串t为串r,串t为: ");
   StrPrint(t);
   StrInsert(&t,6,s);
   printf("在串t的第6个字符前插入串s后，串t为: ");
   StrPrint(t);
   StrDelete(&t,1,5);
   printf("从串t的第1个字符起删除5个字符后,串t为: ");
   StrPrint(t);
   printf("%d是从串t的第1个字符起，和串s相同的第1个子串的位置\n",Index(t,s,1));
   printf("%d是从串t的第2个字符起，和串s相同的第1个子串的位置\n",Index(t,s,2));
 }

**********Main4-3.c**********
 /* main4-3.c 检验bo4-3.c的主程序 */
 char blank='#'; /* 全局变量,用于填补空余 */
 #include"c1.h"
 #include"c4-3.h"
 #include"bo4-3.c"
 void main()
 {
   char *s1="ABCDEFGHI",*s2="12345",*s3="",*s4="asd#tr",*s5="ABCD";
   Status k;
   int pos,len;
   LString t1,t2,t3,t4;
   InitString(&t1);
   InitString(&t2);
   printf("初始化串t1后，串t1空否？%d(1:空 0:否) 串长=%d\n",StrEmpty(t1),StrLength(t1));
   k=StrAssign(&t1,s3);
   if(k==OK)
   {
     printf("串t1为: ");
     StrPrint(t1);
   }
   else
     printf("出错\n"); /* 不能生成空串 */
   k=StrAssign(&t1,s4);
   if(k==OK)
   {
     printf("串t1为: ");
     StrPrint(t1);
   }
   else
     printf("出错\n"); /* 不能生成含有变量blank所代表的字符的串 */
   k=StrAssign(&t1,s1);
   if(k==OK)
   {
     printf("串t1为: ");
     StrPrint(t1);
   }
   else
     printf("出错\n");
   printf("串t1空否？%d(1:空 0:否) 串长=%d\n",StrEmpty(t1),StrLength(t1));
   StrAssign(&t2,s2);
   printf("串t2为: ");
   StrPrint(t2);
   StrCopy(&t3,t1);
   printf("由串t1拷贝得到串t3,串t3为: ");
   StrPrint(t3);
   InitString(&t4);
   StrAssign(&t4,s5);
   printf("串t4为: ");
   StrPrint(t4);
   Replace(&t3,t4,t2);
   printf("用t2取代串t3中的t4串后，串t3为: ");
   StrPrint(t3);
   ClearString(&t1);
   printf("清空串t1后，串t1空否？%d(1:空 0:否) 串长=%d\n",StrEmpty(t1),StrLength(t1));
   Concat(&t1,t2,t3);
   printf("串t1(=t2+t3)为: ");
   StrPrint(t1);
   Zip(&t1);
   printf("去除不必要的占位符后，串t1为: ");
   StrPrint(t1);
   pos=Index(t1,t3,1);
   printf("pos=%d\n",pos);
   printf("在串t1的第pos个字符之前插入串t2，请输入pos: ");
   scanf("%d",&pos);
   k=StrInsert(&t1,pos,t2);
   if(k)
   {
     printf("插入串t2后，串t1为: ");
     StrPrint(t1);
   }
   else
     printf("插入失败！\n");
   printf("求从t1的第pos个字符起,长度为len的子串t2,请输入pos,len: ");
   scanf("%d,%d",&pos,&len);
   SubString(&t2,t1,pos,len);
   printf("串t2为: ");
   StrPrint(t2);
   printf("StrCompare(t1,t2)=%d\n",StrCompare(t1,t2));
   printf("删除串t1中的子字符串：从第pos个字符起删除len个字符。请输入pos,len：");
   scanf("%d,%d",&pos,&len);
   k=StrDelete(&t1,pos,len);
   if(k)
   {
     printf("从第%d位置起删除%d个元素后串t1为:",pos,len);
     StrPrint(t1);
   }
 }
F:\GitHubCode\Code\Csjjg\严蔚敏《数据结构》的全部代码实现（C语言）\ch5
**********BO5-1.C**********
 /* bo5-1.c 顺序存储数组(存储结构由c5-1.h定义)的基本操作(5个) */
 Status InitArray(Array *A,int dim,...)
 { /* 若维数dim和各维长度合法，则构造相应的数组A，并返回OK */
   int elemtotal=1,i; /* elemtotal是元素总值 */
   va_list ap;
   if(dim<1||dim>MAX_ARRAY_DIM)
     return ERROR;
   (*A).dim=dim;
   (*A).bounds=(int *)malloc(dim*sizeof(int));
   if(!(*A).bounds)
     exit(OVERFLOW);
   va_start(ap,dim);
   for(i=0;i<dim;++i)
   {
     (*A).bounds[i]=va_arg(ap,int);
     if((*A).bounds[i]<0)
       return UNDERFLOW; /* 在math.h中定义为4 */
     elemtotal*=(*A).bounds[i];
   }
   va_end(ap);
   (*A).base=(ElemType *)malloc(elemtotal*sizeof(ElemType));
   if(!(*A).base)
     exit(OVERFLOW);
   (*A).constants=(int *)malloc(dim*sizeof(int));
   if(!(*A).constants)
     exit(OVERFLOW);
   (*A).constants[dim-1]=1;
   for(i=dim-2;i>=0;--i)
     (*A).constants[i]=(*A).bounds[i+1]*(*A).constants[i+1];
   return OK;
 }

 Status DestroyArray(Array *A)
 { /* 销毁数组A */
   if((*A).base)
   {
     free((*A).base);
     (*A).base=NULL;
   }
   else
     return ERROR;
   if((*A).bounds)
   {
     free((*A).bounds);
     (*A).bounds=NULL;
   }
   else
     return ERROR;
   if((*A).constants)
   {
     free((*A).constants);
     (*A).constants=NULL;
   }
   else
     return ERROR;
   return OK;
 }

 Status Locate(Array A,va_list ap,int *off) /* Value()、Assign()调用此函数 */
 { /* 若ap指示的各下标值合法，则求出该元素在A中的相对地址off */
   int i,ind;
   *off=0;
   for(i=0;i<A.dim;i++)
   {
     ind=va_arg(ap,int);
     if(ind<0||ind>=A.bounds[i])
       return OVERFLOW;
     *off+=A.constants[i]*ind;
   }
   return OK;
 }

 Status Value(ElemType *e,Array A,...) /* 在VC++中，...之前的形参不能是引用类型 */
 { /* ...依次为各维的下标值，若各下标合法，则e被赋值为A的相应的元素值 */
   va_list ap;
   Status result;
   int off;
   va_start(ap,A);
   if((result=Locate(A,ap,&off))==OVERFLOW) /* 调用Locate() */
     return result;
   *e=*(A.base+off);
   return OK;
 }

 Status Assign(Array *A,ElemType e,...)
 { /* ...依次为各维的下标值，若各下标合法，则将e的值赋给A的指定的元素 */
   va_list ap;
   Status result;
   int off;
   va_start(ap,e);
   if((result=Locate(*A,ap,&off))==OVERFLOW) /* 调用Locate() */
     return result;
   *((*A).base+off)=e;
   return OK;
 }

**********BO5-2.c**********
 /* bo5-2.c 三元组稀疏矩阵的基本操作,包括算法5.1(9个) */
 Status CreateSMatrix(TSMatrix *M)
 { /* 创建稀疏矩阵M */
   int i,m,n;
   ElemType e;
   Status k;
   printf("请输入矩阵的行数,列数,非零元素数：");
   scanf("%d,%d,%d",&(*M).mu,&(*M).nu,&(*M).tu);
   (*M).data[0].i=0; /* 为以下比较顺序做准备 */
   for(i=1;i<=(*M).tu;i++)
   {
     do
     {
       printf("请按行序顺序输入第%d个非零元素所在的行(1～%d),列(1～%d),元素值：",i,(*M).mu,(*M).nu);
       scanf("%d,%d,%d",&m,&n,&e);
       k=0;
       if(m<1||m>(*M).mu||n<1||n>(*M).nu) /* 行或列超出范围 */
         k=1;
       if(m<(*M).data[i-1].i||m==(*M).data[i-1].i&&n<=(*M).data[i-1].j) /* 行或列的顺序有错 */
         k=1;
     }while(k);
     (*M).data[i].i=m;
     (*M).data[i].j=n;
     (*M).data[i].e=e;
   }
   return OK;
 }

 void DestroySMatrix(TSMatrix *M)
 { /* 销毁稀疏矩阵M */
   (*M).mu=0;
   (*M).nu=0;
   (*M).tu=0;
 }

 void PrintSMatrix(TSMatrix M)
 { /* 输出稀疏矩阵M */
   int i;
   printf("%d行%d列%d个非零元素。\n",M.mu,M.nu,M.tu);
   printf("行  列  元素值\n");
   for(i=1;i<=M.tu;i++)
     printf("%2d%4d%8d\n",M.data[i].i,M.data[i].j,M.data[i].e);
 }

 Status CopySMatrix(TSMatrix M,TSMatrix *T)
 { /* 由稀疏矩阵M复制得到T */
   (*T)=M;
   return OK;
 }

 int comp(int c1,int c2) /* 另加 */
 { /* AddSMatrix函数要用到 */
   int i;
   if(c1<c2)
     i=1;
   else if(c1==c2)
     i=0;
   else
     i=-1;
   return i;
 }

 Status AddSMatrix(TSMatrix M,TSMatrix N,TSMatrix *Q)
 { /* 求稀疏矩阵的和Q=M+N */
   Triple *Mp,*Me,*Np,*Ne,*Qh,*Qe;
   if(M.mu!=N.mu)
     return ERROR;
   if(M.nu!=N.nu)
     return ERROR;
   (*Q).mu=M.mu;
   (*Q).nu=M.nu;
   Mp=&M.data[1]; /* Mp的初值指向矩阵M的非零元素首地址 */
   Np=&N.data[1]; /* Np的初值指向矩阵N的非零元素首地址 */
   Me=&M.data[M.tu]; /* Me指向矩阵M的非零元素尾地址 */
   Ne=&N.data[N.tu]; /* Ne指向矩阵N的非零元素尾地址 */
   Qh=Qe=(*Q).data; /* Qh、Qe的初值指向矩阵Q的非零元素首地址的前一地址 */
   while(Mp<=Me&&Np<=Ne)
   {
     Qe++;
     switch(comp(Mp->i,Np->i))
     {
       case  1: *Qe=*Mp;
                Mp++;
                break;
       case  0: switch(comp(Mp->j,Np->j)) /* M、N矩阵当前非零元素的行相等,继续比较列 */
                {
                  case  1: *Qe=*Mp;
                           Mp++;
                           break;
                  case  0: *Qe=*Mp;
                           Qe->e+=Np->e;
                           if(!Qe->e) /* 元素值为0，不存入压缩矩阵 */
                             Qe--;
                           Mp++;
                           Np++;
                           break;
                  case -1: *Qe=*Np;
                           Np++;
                }
                break;
       case -1: *Qe=*Np;
                Np++;
     }
   }
   if(Mp>Me) /* 矩阵M的元素全部处理完毕 */
     while(Np<=Ne)
     {
       Qe++;
       *Qe=*Np;
       Np++;
     }
   if(Np>Ne) /* 矩阵N的元素全部处理完毕 */
     while(Mp<=Me)
     {
       Qe++;
       *Qe=*Mp;
       Mp++;
     }
   (*Q).tu=Qe-Qh; /* 矩阵Q的非零元素个数 */
   return OK;
 }

 Status SubtSMatrix(TSMatrix M,TSMatrix N,TSMatrix *Q)
 { /* 求稀疏矩阵的差Q=M-N */
   int i;
   for(i=1;i<=N.tu;i++)
     N.data[i].e*=-1;
   AddSMatrix(M,N,Q);
   return OK;
 }

 Status MultSMatrix(TSMatrix M,TSMatrix N,TSMatrix *Q)
 { /* 求稀疏矩阵的乘积Q=M*N */
   int i,j,h=M.mu,l=N.nu,Qn=0;
   /* h,l分别为矩阵Q的行、列值,Qn为矩阵Q的非零元素个数，初值为0 */
   ElemType *Qe;
   if(M.nu!=N.mu)
     return ERROR;
   (*Q).mu=M.mu;
   (*Q).nu=N.nu;
   Qe=(ElemType *)malloc(h*l*sizeof(ElemType)); /* Qe为矩阵Q的临时数组 */
   /* 矩阵Q的第i行j列的元素值存于*(Qe+(i-1)*l+j-1)中，初值为0 */
   for(i=0;i<h*l;i++)
     *(Qe+i)=0; /* 赋初值0 */
   for(i=1;i<=M.tu;i++) /* 矩阵元素相乘，结果累加到Qe */
     for(j=1;j<=N.tu;j++)
       if(M.data[i].j==N.data[j].i)
         *(Qe+(M.data[i].i-1)*l+N.data[j].j-1)+=M.data[i].e*N.data[j].e;
   for(i=1;i<=M.mu;i++)
     for(j=1;j<=N.nu;j++)
       if(*(Qe+(i-1)*l+j-1)!=0)
       {
         Qn++;
         (*Q).data[Qn].e=*(Qe+(i-1)*l+j-1);
         (*Q).data[Qn].i=i;
         (*Q).data[Qn].j=j;
       }
   free(Qe);
   (*Q).tu=Qn;
   return OK;
 }

 Status TransposeSMatrix(TSMatrix M,TSMatrix *T)
 { /* 求稀疏矩阵M的转置矩阵T。算法5.1 */
   int p,q,col;
   (*T).mu=M.nu;
   (*T).nu=M.mu;
   (*T).tu=M.tu;
   if((*T).tu)
   {
     q=1;
     for(col=1;col<=M.nu;++col)
       for(p=1;p<=M.tu;++p)
         if(M.data[p].j==col)
         {
           (*T).data[q].i=M.data[p].j;
           (*T).data[q].j=M.data[p].i;
           (*T).data[q].e=M.data[p].e;
           ++q;
         }
   }
   return OK;
 }

**********BO5-3.c**********
 /* bo5-3.c 行逻辑链接稀疏矩阵(存储结构由c5-3.h定义)的基本操作(8个) */
 Status CreateSMatrix(RLSMatrix *M)
 { /* 创建稀疏矩阵M */
   int i;
   Triple T;
   Status k;
   printf("请输入矩阵的行数,列数,非零元素数：");
   scanf("%d,%d,%d",&(*M).mu,&(*M).nu,&(*M).tu);
   (*M).data[0].i=0; /* 为以下比较做准备 */
   for(i=1;i<=(*M).tu;i++)
   {
     do
     {
       printf("请按行序顺序输入第%d个非零元素所在的行(1～%d),列(1～%d),元素值：",i,(*M).mu,(*M).nu);
       scanf("%d,%d,%d",&T.i,&T.j,&T.e);
       k=0;
       if(T.i<1||T.i>(*M).mu||T.j<1||T.j>(*M).nu) /* 行、列超出范围 */
         k=1;
       if(T.i<(*M).data[i-1].i||T.i==(*M).data[i-1].i&&T.j<=(*M).data[i-1].j) /* 没有按顺序输入非零元素 */
         k=1;
     }while(k); /* 当输入有误,重新输入 */
     (*M).data[i]=T;
   }
   for(i=1;i<=(*M).tu;i++) /* 计算rpos[] */
     if((*M).data[i].i>(*M).data[i-1].i)
       for(T.i=0;T.i<(*M).data[i].i-(*M).data[i-1].i;T.i++)
         (*M).rpos[(*M).data[i].i-T.i]=i;
   for(i=(*M).data[(*M).tu].i+1;i<=(*M).mu;i++) /* 给最后没有非零元素的几行赋值 */
     (*M).rpos[i]=(*M).tu+1;
   return OK;
 }

 void DestroySMatrix(RLSMatrix *M)
 { /* 销毁稀疏矩阵M(使M为0行0列0个非零元素的矩阵) */
   (*M).mu=0;
   (*M).nu=0;
   (*M).tu=0;
 }

 void PrintSMatrix(RLSMatrix M)
 { /* 输出稀疏矩阵M */
   int i;
   printf("%d行%d列%d个非零元素。\n",M.mu,M.nu,M.tu);
   printf("行  列  元素值\n");
   for(i=1;i<=M.tu;i++)
     printf("%2d%4d%8d\n",M.data[i].i,M.data[i].j,M.data[i].e);
   for(i=1;i<=M.mu;i++)
     printf("第%d行的第一个非零元素是本矩阵第%d个元素\n",i,M.rpos[i]);
 }

 Status CopySMatrix(RLSMatrix M,RLSMatrix *T)
 { /* 由稀疏矩阵M复制得到T */
   *T=M;
   return OK;
 }

 Status AddSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix *Q)
 { /* 求稀疏矩阵的和Q=M+N */
   int k,p,q;
   if(M.mu!=N.mu||M.nu!=N.nu)
     return ERROR;
   (*Q).mu=M.mu;
   (*Q).nu=M.nu;
   (*Q).tu=0;
   M.rpos[M.mu+1]=M.tu+1; /* 为方便后面的while循环临时设置 */
   N.rpos[N.mu+1]=N.tu+1;
   for(k=1;k<=M.mu;++k) /* 对于每一行，k指示行号 */
   {
     (*Q).rpos[k]=(*Q).tu+1;
     p=M.rpos[k]; /* p指示M矩阵第k行当前元素的序号 */
     q=N.rpos[k]; /* q指示N矩阵第k行当前元素的序号 */
     while(p<M.rpos[k+1]&&q<N.rpos[k+1])
     { /* M,N矩阵均有第k行元素未处理 */
       if(M.data[p].j==N.data[q].j) /* M矩阵当前元素和N矩阵当前元素的列相同 */
       {
         (*Q).data[(*Q).tu+1].e=M.data[p].e+N.data[q].e;
         if((*Q).data[(*Q).tu+1].e!=0)
         {
           ++(*Q).tu;
           (*Q).data[(*Q).tu].i=k;
           (*Q).data[(*Q).tu].j=M.data[p].j;
         }
         ++p;
         ++q;
       }
       else if(M.data[p].j<N.data[q].j)
       { /* M矩阵当前元素的列<N矩阵当前元素的列 */
         ++(*Q).tu;
         (*Q).data[(*Q).tu].e=M.data[p].e;
         (*Q).data[(*Q).tu].i=k;
         (*Q).data[(*Q).tu].j=M.data[p].j;
         ++p;
       }
       else /* M矩阵当前元素的列>N矩阵当前元素的列 */
       {
         ++(*Q).tu;
         (*Q).data[(*Q).tu].e=N.data[q].e;
         (*Q).data[(*Q).tu].i=k;
         (*Q).data[(*Q).tu].j=N.data[q].j;
         ++q;
       }
     }
     while(p<M.rpos[k+1]) /* M矩阵还有k行的元素未处理 */
     {
       ++(*Q).tu;
       (*Q).data[(*Q).tu].e=M.data[p].e;
       (*Q).data[(*Q).tu].i=k;
       (*Q).data[(*Q).tu].j=M.data[p].j;
       ++p;
     }
     while(q<N.rpos[k+1]) /* N矩阵还有k行的元素未处理 */
     {
       ++(*Q).tu;
       (*Q).data[(*Q).tu].e=N.data[q].e;
       (*Q).data[(*Q).tu].i=k;
       (*Q).data[(*Q).tu].j=N.data[q].j;
       ++q;
     }
   }
   return OK;
 }

 Status SubtSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix *Q)
 { /* 求稀疏矩阵的差Q=M-N */
   int i;
   if(M.mu!=N.mu||M.nu!=N.nu)
     return ERROR;
   for(i=1;i<=N.tu;++i) /* 对于N的每一元素,其值乘以-1 */
     N.data[i].e*=-1;
   AddSMatrix(M,N,Q); /* Q=M+(-N) */
   return OK;
 }

 Status MultSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix *Q)
 { /* 求稀疏矩阵乘积Q=M＊N。算法5.3 */
   int arow,brow,p,q,ccol,ctemp[MAXRC+1];
   if(M.nu!=N.mu) /* 矩阵M的列数应和矩阵N的行数相等 */
     return ERROR;
   (*Q).mu=M.mu; /* Q初始化 */
   (*Q).nu=N.nu;
   (*Q).tu=0;
   M.rpos[M.mu+1]=M.tu+1; /* 为方便后面的while循环临时设置 */
   N.rpos[N.mu+1]=N.tu+1;
   if(M.tu*N.tu!=0) /* M和N都是非零矩阵 */
   {
     for(arow=1;arow<=M.mu;++arow)
     { /* 从M的第一行开始，到最后一行，arow是M的当前行 */
       for(ccol=1;ccol<=(*Q).nu;++ccol)
         ctemp[ccol]=0; /* Q的当前行的各列元素累加器清零 */
       (*Q).rpos[arow]=(*Q).tu+1; /* Q当前行的第1个元素位于上1行最后1个元素之后 */
       for(p=M.rpos[arow];p<M.rpos[arow+1];++p)
       { /* 对M当前行中每一个非零元 */
         brow=M.data[p].j; /* 找到对应元在N中的行号(M当前元的列号) */
         for(q=N.rpos[brow];q<N.rpos[brow+1];++q)
	 {
           ccol=N.data[q].j; /* 乘积元素在Q中列号 */
           ctemp[ccol]+=M.data[p].e*N.data[q].e;
         }
       } /* 求得Q中第arow行的非零元 */
       for(ccol=1;ccol<=(*Q).nu;++ccol) /* 压缩存储该行非零元 */
         if(ctemp[ccol])
         {
           if(++(*Q).tu>MAXSIZE)
             return ERROR;
           (*Q).data[(*Q).tu].i=arow;
           (*Q).data[(*Q).tu].j=ccol;
           (*Q).data[(*Q).tu].e=ctemp[ccol];
         }
     }
   }
   return OK;
 }

 Status TransposeSMatrix(RLSMatrix M,RLSMatrix *T)
 { /* 求稀疏矩阵M的转置矩阵T */
   int p,q,t,col,*num;
   num=(int *)malloc((M.nu+1)*sizeof(int));
   (*T).mu=M.nu;
   (*T).nu=M.mu;
   (*T).tu=M.tu;
   if((*T).tu)
   {
     for(col=1;col<=M.nu;++col)
       num[col]=0;  /* 设初值 */
     for(t=1;t<=M.tu;++t) /* 求M中每一列非零元个数 */
       ++num[M.data[t].j];
     (*T).rpos[1]=1;
     for(col=2;col<=M.nu;++col) /* 求M中第col中第一个非零元在(*T).data中的序号 */
       (*T).rpos[col]=(*T).rpos[col-1]+num[col-1];
     for(col=1;col<=M.nu;++col)
       num[col]=(*T).rpos[col];
     for(p=1;p<=M.tu;++p)
     {
       col=M.data[p].j;
       q=num[col];
       (*T).data[q].i=M.data[p].j;
       (*T).data[q].j=M.data[p].i;
       (*T).data[q].e=M.data[p].e;
       ++num[col];
     }
   }
   free(num);
   return OK;
 }

**********BO5-4.c**********
 /* bo5-4.c 稀疏矩阵的十字链表存储(存储结构由c5-4.h定义)的基本操作(9个) */
 Status InitSMatrix(CrossList *M) /* 加 */
 { /* 初始化M(CrossList类型的变量必须初始化,否则创建、复制矩阵将出错) */
   (*M).rhead=(*M).chead=NULL;
   (*M).mu=(*M).nu=(*M).tu=0;
   return OK;
 }

 Status DestroySMatrix(CrossList *M)
 { /* 初始条件: 稀疏矩阵M存在。操作结果: 销毁稀疏矩阵M */
   int i;
   OLNode *p,*q;
   for(i=1;i<=(*M).mu;i++) /* 按行释放结点 */
   {
     p=*((*M).rhead+i);
     while(p)
     {
       q=p;
       p=p->right;
       free(q);
     }
   }
   free((*M).rhead);
   free((*M).chead);
   (*M).rhead=(*M).chead=NULL;
   (*M).mu=(*M).nu=(*M).tu=0;
   return OK;
 }

 Status CreateSMatrix(CrossList *M)
 { /* 创建稀疏矩阵M,采用十字链表存储表示。算法5.4 */
   int i,j,k,m,n,t;
   ElemType e;
   OLNode *p,*q;
   if((*M).rhead)
     DestroySMatrix(M);
   printf("请输入稀疏矩阵的行数 列数 非零元个数: ");
   scanf("%d%d%d",&m,&n,&t);
   (*M).mu=m;
   (*M).nu=n;
   (*M).tu=t;
   (*M).rhead=(OLink*)malloc((m+1)*sizeof(OLink));
   if(!(*M).rhead)
     exit(OVERFLOW);
   (*M).chead=(OLink*)malloc((n+1)*sizeof(OLink));
   if(!(*M).chead)
     exit(OVERFLOW);
   for(k=1;k<=m;k++) /* 初始化行头指针向量;各行链表为空链表 */
     (*M).rhead[k]=NULL;
   for(k=1;k<=n;k++) /* 初始化列头指针向量;各列链表为空链表 */
     (*M).chead[k]=NULL;
   printf("请按任意次序输入%d个非零元的行 列 元素值:\n",(*M).tu);
   for(k=0;k<t;k++)
   {
     scanf("%d%d%d",&i,&j,&e);
     p=(OLNode*)malloc(sizeof(OLNode));
     if(!p)
       exit(OVERFLOW);
     p->i=i; /* 生成结点 */
     p->j=j;
     p->e=e;
     if((*M).rhead[i]==NULL||(*M).rhead[i]->j>j) /* p插在该行的第一个结点处 */
     {
       p->right=(*M).rhead[i];
       (*M).rhead[i]=p;
     }
     else /* 寻查在行表中的插入位置 */
     {
       for(q=(*M).rhead[i];q->right&&q->right->j<j;q=q->right);
       p->right=q->right; /* 完成行插入 */
       q->right=p;
     }
     if((*M).chead[j]==NULL||(*M).chead[j]->i>i) /* p插在该列的第一个结点处 */
     {
       p->down=(*M).chead[j];
       (*M).chead[j]=p;
     }
     else /* 寻查在列表中的插入位置 */
     {
       for(q=(*M).chead[j];q->down&&q->down->i<i;q=q->down);
       p->down=q->down; /* 完成列插入 */
       q->down=p;
     }
   }
   return OK;
 }

 Status PrintSMatrix(CrossList M)
 { /* 初始条件: 稀疏矩阵M存在。操作结果: 按行或按列输出稀疏矩阵M */
   int i,j;
   OLink p;
   printf("%d行%d列%d个非零元素\n",M.mu,M.nu,M.tu);
   printf("请输入选择(1.按行输出 2.按列输出): ");
   scanf("%d",&i);
   switch(i)
   {
     case 1: for(j=1;j<=M.mu;j++)
             {
               p=M.rhead[j];
               while(p)
               {
                 printf("%d行%d列值为%d\n",p->i,p->j,p->e);
                 p=p->right;
               }
             }
             break;
     case 2: for(j=1;j<=M.nu;j++)
             {
               p=M.chead[j];
               while(p)
               {
                 printf("%d行%d列值为%d\n",p->i,p->j,p->e);
                 p=p->down;
               }
             }
   }
   return OK;
 }

 Status CopySMatrix(CrossList M,CrossList *T)
 { /* 初始条件: 稀疏矩阵M存在。操作结果: 由稀疏矩阵M复制得到T */
   int i;
   OLink p,q,q1,q2;
   if((*T).rhead)
     DestroySMatrix(T);
   (*T).mu=M.mu;
   (*T).nu=M.nu;
   (*T).tu=M.tu;
   (*T).rhead=(OLink*)malloc((M.mu+1)*sizeof(OLink));
   if(!(*T).rhead)
     exit(OVERFLOW);
   (*T).chead=(OLink*)malloc((M.nu+1)*sizeof(OLink));
   if(!(*T).chead)
     exit(OVERFLOW);
   for(i=1;i<=M.mu;i++) /* 初始化矩阵T的行头指针向量;各行链表为空链表 */
     (*T).rhead[i]=NULL;
   for(i=1;i<=M.nu;i++) /* 初始化矩阵T的列头指针向量;各列链表为空链表 */
     (*T).chead[i]=NULL;
   for(i=1;i<=M.mu;i++) /* 按行复制 */
   {
     p=M.rhead[i];
     while(p) /* 没到行尾 */
     {
       q=(OLNode*)malloc(sizeof(OLNode)); /* 生成结点 */
       if(!q)
         exit(OVERFLOW);
       q->i=p->i; /* 给结点赋值 */
       q->j=p->j;
       q->e=p->e;
       if(!(*T).rhead[i]) /* 插在行表头 */
         (*T).rhead[i]=q1=q;
       else /* 插在行表尾 */
         q1=q1->right=q;
       if(!(*T).chead[q->j]) /* 插在列表头 */
       {
         (*T).chead[q->j]=q;
         q->down=NULL;
       }
       else /* 插在列表尾 */
       {
         q2=(*T).chead[q->j];
         while(q2->down)
           q2=q2->down;
         q2->down=q;
         q->down=NULL;
       }
       p=p->right;
     }
     q->right=NULL;
   }
   return OK;
 }

 Status AddSMatrix(CrossList M,CrossList N,CrossList *Q)
 { /* 初始条件: 稀疏矩阵M与N的行数和列数对应相等。 */
   /* 操作结果: 求稀疏矩阵的和Q=M+N */
   int i,k;
   OLink p,pq,pm,pn;
   OLink *col;
   if(M.mu!=N.mu||M.nu!=N.nu)
   {
     printf("两个矩阵不是同类型的,不能相加\n");
     exit(OVERFLOW);
   }
   (*Q).mu=M.mu; /* 初始化Q矩阵 */
   (*Q).nu=M.nu;
   (*Q).tu=0; /* 元素个数的初值 */
   (*Q).rhead=(OLink*)malloc(((*Q).mu+1)*sizeof(OLink));
   if(!(*Q).rhead)
     exit(OVERFLOW);
   (*Q).chead=(OLink*)malloc(((*Q).nu+1)*sizeof(OLink));
   if(!(*Q).chead)
     exit(OVERFLOW);
   for(k=1;k<=(*Q).mu;k++) /* 初始化Q的行头指针向量;各行链表为空链表 */
     (*Q).rhead[k]=NULL;
   for(k=1;k<=(*Q).nu;k++) /* 初始化Q的列头指针向量;各列链表为空链表 */
     (*Q).chead[k]=NULL;
   col=(OLink*)malloc(((*Q).nu+1)*sizeof(OLink)); /* 生成指向列的最后结点的数组 */
   if(!col)
     exit(OVERFLOW);
   for(k=1;k<=(*Q).nu;k++) /* 赋初值 */
     col[k]=NULL;
   for(i=1;i<=M.mu;i++) /* 按行的顺序相加 */
   {
     pm=M.rhead[i]; /* pm指向矩阵M的第i行的第1个结点 */
     pn=N.rhead[i]; /* pn指向矩阵N的第i行的第1个结点 */
     while(pm&&pn) /* pm和pn均不空 */
     {
       if(pm->j<pn->j) /* 矩阵M当前结点的列小于矩阵N当前结点的列 */
       {
         p=(OLink)malloc(sizeof(OLNode)); /* 生成矩阵Q的结点 */
         if(!p)
           exit(OVERFLOW);
         (*Q).tu++; /* 非零元素数加1 */
         p->i=i; /* 给结点赋值 */
         p->j=pm->j;
         p->e=pm->e;
         p->right=NULL;
         pm=pm->right; /* pm指针向右移 */
       }
       else if(pm->j>pn->j) /* 矩阵M当前结点的列大于矩阵N当前结点的列 */
       {
         p=(OLink)malloc(sizeof(OLNode)); /* 生成矩阵Q的结点 */
         if(!p)
           exit(OVERFLOW);
         (*Q).tu++; /* 非零元素数加1 */
         p->i=i; /* 给结点赋值 */
         p->j=pn->j;
         p->e=pn->e;
         p->right=NULL;
         pn=pn->right; /* pn指针向右移 */
       }
       else if(pm->e+pn->e) /* 矩阵M、N当前结点的列相等且两元素之和不为0 */
       {
         p=(OLink)malloc(sizeof(OLNode)); /* 生成矩阵Q的结点 */
         if(!p)
           exit(OVERFLOW);
         (*Q).tu++; /* 非零元素数加1 */
         p->i=i; /* 给结点赋值 */
         p->j=pn->j;
         p->e=pm->e+pn->e;
         p->right=NULL;
         pm=pm->right; /* pm指针向右移 */
         pn=pn->right; /* pn指针向右移 */
       }
       else /* 矩阵M、N当前结点的列相等且两元素之和为0 */
       {
         pm=pm->right; /* pm指针向右移 */
         pn=pn->right; /* pn指针向右移 */
         continue;
       }
       if((*Q).rhead[i]==NULL) /* p为该行的第1个结点 */
         (*Q).rhead[i]=pq=p; /* p插在该行的表头且pq指向p(该行的最后一个结点) */
       else /* 插在pq所指结点之后 */
       {
         pq->right=p; /* 完成行插入 */
         pq=pq->right; /* pq指向该行的最后一个结点 */
       }
       if((*Q).chead[p->j]==NULL) /* p为该列的第1个结点 */
         (*Q).chead[p->j]=col[p->j]=p; /* p插在该列的表头且col[p->j]指向p */
       else /* 插在col[p->]所指结点之后 */
       {
         col[p->j]->down=p; /* 完成列插入 */
         col[p->j]=col[p->j]->down; /* col[p->j]指向该列的最后一个结点 */
       }
     }
     while(pm) /* 将矩阵M该行的剩余元素插入矩阵Q */
     {
       p=(OLink)malloc(sizeof(OLNode)); /* 生成矩阵Q的结点 */
       if(!p)
         exit(OVERFLOW);
       (*Q).tu++; /* 非零元素数加1 */
       p->i=i; /* 给结点赋值 */
       p->j=pm->j;
       p->e=pm->e;
       p->right=NULL;
       pm=pm->right; /* pm指针向右移 */
       if((*Q).rhead[i]==NULL) /* p为该行的第1个结点 */
         (*Q).rhead[i]=pq=p; /* p插在该行的表头且pq指向p(该行的最后一个结点) */
       else /* 插在pq所指结点之后 */
       {
         pq->right=p; /* 完成行插入 */
         pq=pq->right; /* pq指向该行的最后一个结点 */
       }
       if((*Q).chead[p->j]==NULL) /* p为该列的第1个结点 */
         (*Q).chead[p->j]=col[p->j]=p; /* p插在该列的表头且col[p->j]指向p */
       else /* 插在col[p->j]所指结点之后 */
       {
         col[p->j]->down=p; /* 完成列插入 */
         col[p->j]=col[p->j]->down; /* col[p->j]指向该列的最后一个结点 */
       }
     }
     while(pn) /* 将矩阵N该行的剩余元素插入矩阵Q */
     {
       p=(OLink)malloc(sizeof(OLNode)); /* 生成矩阵Q的结点 */
       if(!p)
         exit(OVERFLOW);
       (*Q).tu++; /* 非零元素数加1 */
       p->i=i; /* 给结点赋值 */
       p->j=pn->j;
       p->e=pn->e;
       p->right=NULL;
       pn=pn->right; /* pm指针向右移 */
       if((*Q).rhead[i]==NULL) /* p为该行的第1个结点 */
         (*Q).rhead[i]=pq=p; /* p插在该行的表头且pq指向p(该行的最后一个结点) */
       else /* 插在pq所指结点之后 */
       {
         pq->right=p; /* 完成行插入 */
         pq=pq->right; /* pq指向该行的最后一个结点 */
       }
       if((*Q).chead[p->j]==NULL) /* p为该列的第1个结点 */
         (*Q).chead[p->j]=col[p->j]=p; /* p插在该列的表头且col[p->j]指向p */
       else /* 插在col[p->j]所指结点之后 */
       {
         col[p->j]->down=p; /* 完成列插入 */
         col[p->j]=col[p->j]->down; /* col[p->j]指向该列的最后一个结点 */
       }
     }
   }
   for(k=1;k<=(*Q).nu;k++)
     if(col[k]) /* k列有结点 */
       col[k]->down=NULL; /*  令该列最后一个结点的down指针为空 */
   free(col);
   return OK;
 }

 Status SubtSMatrix(CrossList M,CrossList N,CrossList *Q)
 { /* 初始条件: 稀疏矩阵M与N的行数和列数对应相等。 */
   /* 操作结果: 求稀疏矩阵的差Q=M-N */
   int i,k;
   OLink p,pq,pm,pn;
   OLink *col;
   if(M.mu!=N.mu||M.nu!=N.nu)
   {
     printf("两个矩阵不是同类型的,不能相加\n");
     exit(OVERFLOW);
   }
   (*Q).mu=M.mu; /* 初始化Q矩阵 */
   (*Q).nu=M.nu;
   (*Q).tu=0; /* 元素个数的初值 */
   (*Q).rhead=(OLink*)malloc(((*Q).mu+1)*sizeof(OLink));
   if(!(*Q).rhead)
     exit(OVERFLOW);
   (*Q).chead=(OLink*)malloc(((*Q).nu+1)*sizeof(OLink));
   if(!(*Q).chead)
     exit(OVERFLOW);
   for(k=1;k<=(*Q).mu;k++) /* 初始化Q的行头指针向量;各行链表为空链表 */
     (*Q).rhead[k]=NULL;
   for(k=1;k<=(*Q).nu;k++) /* 初始化Q的列头指针向量;各列链表为空链表 */
     (*Q).chead[k]=NULL;
   col=(OLink*)malloc(((*Q).nu+1)*sizeof(OLink)); /* 生成指向列的最后结点的数组 */
   if(!col)
     exit(OVERFLOW);
   for(k=1;k<=(*Q).nu;k++) /* 赋初值 */
     col[k]=NULL;
   for(i=1;i<=M.mu;i++) /* 按行的顺序相加 */
   {
     pm=M.rhead[i]; /* pm指向矩阵M的第i行的第1个结点 */
     pn=N.rhead[i]; /* pn指向矩阵N的第i行的第1个结点 */
     while(pm&&pn) /* pm和pn均不空 */
     {
       if(pm->j<pn->j) /* 矩阵M当前结点的列小于矩阵N当前结点的列 */
       {
         p=(OLink)malloc(sizeof(OLNode)); /* 生成矩阵Q的结点 */
         if(!p)
           exit(OVERFLOW);
         (*Q).tu++; /* 非零元素数加1 */
         p->i=i; /* 给结点赋值 */
         p->j=pm->j;
         p->e=pm->e;
         p->right=NULL;
         pm=pm->right; /* pm指针向右移 */
       }
       else if(pm->j>pn->j) /* 矩阵M当前结点的列大于矩阵N当前结点的列 */
       {
         p=(OLink)malloc(sizeof(OLNode)); /* 生成矩阵Q的结点 */
         if(!p)
           exit(OVERFLOW);
         (*Q).tu++; /* 非零元素数加1 */
         p->i=i; /* 给结点赋值 */
         p->j=pn->j;
         p->e=-pn->e;
         p->right=NULL;
         pn=pn->right; /* pn指针向右移 */
       }
       else if(pm->e-pn->e) /* 矩阵M、N当前结点的列相等且两元素之差不为0 */
       {
         p=(OLink)malloc(sizeof(OLNode)); /* 生成矩阵Q的结点 */
         if(!p)
           exit(OVERFLOW);
         (*Q).tu++; /* 非零元素数加1 */
         p->i=i; /* 给结点赋值 */
         p->j=pn->j;
         p->e=pm->e-pn->e;
         p->right=NULL;
         pm=pm->right; /* pm指针向右移 */
         pn=pn->right; /* pn指针向右移 */
       }
       else /* 矩阵M、N当前结点的列相等且两元素之差为0 */
       {
         pm=pm->right; /* pm指针向右移 */
         pn=pn->right; /* pn指针向右移 */
         continue;
       }
       if((*Q).rhead[i]==NULL) /* p为该行的第1个结点 */
         (*Q).rhead[i]=pq=p; /* p插在该行的表头且pq指向p(该行的最后一个结点) */
       else /* 插在pq所指结点之后 */
       {
         pq->right=p; /* 完成行插入 */
         pq=pq->right; /* pq指向该行的最后一个结点 */
       }
       if((*Q).chead[p->j]==NULL) /* p为该列的第1个结点 */
         (*Q).chead[p->j]=col[p->j]=p; /* p插在该列的表头且col[p->j]指向p */
       else /* 插在col[p->]所指结点之后 */
       {
         col[p->j]->down=p; /* 完成列插入 */
         col[p->j]=col[p->j]->down; /* col[p->j]指向该列的最后一个结点 */
       }
     }
     while(pm) /* 将矩阵M该行的剩余元素插入矩阵Q */
     {
       p=(OLink)malloc(sizeof(OLNode)); /* 生成矩阵Q的结点 */
       if(!p)
         exit(OVERFLOW);
       (*Q).tu++; /* 非零元素数加1 */
       p->i=i; /* 给结点赋值 */
       p->j=pm->j;
       p->e=pm->e;
       p->right=NULL;
       pm=pm->right; /* pm指针向右移 */
       if((*Q).rhead[i]==NULL) /* p为该行的第1个结点 */
         (*Q).rhead[i]=pq=p; /* p插在该行的表头且pq指向p(该行的最后一个结点) */
       else /* 插在pq所指结点之后 */
       {
         pq->right=p; /* 完成行插入 */
         pq=pq->right; /* pq指向该行的最后一个结点 */
       }
       if((*Q).chead[p->j]==NULL) /* p为该列的第1个结点 */
         (*Q).chead[p->j]=col[p->j]=p; /* p插在该列的表头且col[p->j]指向p */
       else /* 插在col[p->j]所指结点之后 */
       {
         col[p->j]->down=p; /* 完成列插入 */
         col[p->j]=col[p->j]->down; /* col[p->j]指向该列的最后一个结点 */
       }
     }
     while(pn) /* 将矩阵N该行的剩余元素插入矩阵Q */
     {
       p=(OLink)malloc(sizeof(OLNode)); /* 生成矩阵Q的结点 */
       if(!p)
         exit(OVERFLOW);
       (*Q).tu++; /* 非零元素数加1 */
       p->i=i; /* 给结点赋值 */
       p->j=pn->j;
       p->e=-pn->e;
       p->right=NULL;
       pn=pn->right; /* pm指针向右移 */
       if((*Q).rhead[i]==NULL) /* p为该行的第1个结点 */
         (*Q).rhead[i]=pq=p; /* p插在该行的表头且pq指向p(该行的最后一个结点) */
       else /* 插在pq所指结点之后 */
       {
         pq->right=p; /* 完成行插入 */
         pq=pq->right; /* pq指向该行的最后一个结点 */
       }
       if((*Q).chead[p->j]==NULL) /* p为该列的第1个结点 */
         (*Q).chead[p->j]=col[p->j]=p; /* p插在该列的表头且col[p->j]指向p */
       else /* 插在col[p->j]所指结点之后 */
       {
         col[p->j]->down=p; /* 完成列插入 */
         col[p->j]=col[p->j]->down; /* col[p->j]指向该列的最后一个结点 */
       }
     }
   }
   for(k=1;k<=(*Q).nu;k++)
     if(col[k]) /* k列有结点 */
       col[k]->down=NULL; /* 令该列最后一个结点的down指针为空 */
   free(col);
   return OK;
 }

 Status MultSMatrix(CrossList M,CrossList N,CrossList *Q)
 { /* 初始条件: 稀疏矩阵M的列数等于N的行数。操作结果: 求稀疏矩阵乘积Q=M*N */
   int i,j,e;
   OLink q,p0,q0,q1,q2;
   InitSMatrix(Q);
   (*Q).mu=M.mu;
   (*Q).nu=N.nu;
   (*Q).tu=0;
   (*Q).rhead=(OLink*)malloc(((*Q).mu+1)*sizeof(OLink));
   if(!(*Q).rhead)
     exit(OVERFLOW);
   (*Q).chead=(OLink*)malloc(((*Q).nu+1)*sizeof(OLink));
   if(!(*Q).chead)
     exit(OVERFLOW);
   for(i=1;i<=(*Q).mu;i++) /* 初始化矩阵Q的行头指针向量;各行链表为空链表 */
     (*Q).rhead[i]=NULL;
   for(i=1;i<=(*Q).nu;i++) /* 初始化矩阵Q的列头指针向量;各列链表为空链表 */
     (*Q).chead[i]=NULL;
   for(i=1;i<=(*Q).mu;i++)
     for(j=1;j<=(*Q).nu;j++)
     {
       p0=M.rhead[i];
       q0=N.chead[j];
       e=0;
       while(p0&&q0)
       {
         if(q0->i<p0->j)
           q0=q0->down; /* 列指针后移 */
         else if(q0->i>p0->j)
           p0=p0->right; /* 行指针后移 */
         else /* q0->i==p0->j */
         {
           e+=p0->e*q0->e; /* 乘积累加 */
           q0=q0->down; /* 行列指针均后移 */
           p0=p0->right;
         }
       }
       if(e) /* 值不为0 */
       {
	 (*Q).tu++; /* 非零元素数加1 */
	 q=(OLink)malloc(sizeof(OLNode)); /* 生成结点 */
	 if(!q) /* 生成结点失败 */
	   exit(OVERFLOW);
	 q->i=i; /* 给结点赋值 */
	 q->j=j;
	 q->e=e;
	 q->right=NULL;
	 q->down=NULL;
	 if(!(*Q).rhead[i]) /* 行表空时插在行表头 */
	   (*Q).rhead[i]=q1=q;
	 else /* 否则插在行表尾 */
	   q1=q1->right=q;
	 if(!(*Q).chead[j]) /* 列表空时插在列表头 */
	   (*Q).chead[j]=q;
	 else /* 否则插在列表尾 */
	 {
	   q2=(*Q).chead[j]; /* q2指向j行第1个结点 */
	   while(q2->down)
             q2=q2->down; /* q2指向j行最后1个结点 */
           q2->down=q;
         }
       }
     }
   return OK;
 }

 Status TransposeSMatrix(CrossList M,CrossList *T)
 { /* 初始条件: 稀疏矩阵M存在。操作结果: 求稀疏矩阵M的转置矩阵T */
   int u,i;
   OLink *head,p,q,r;
   if((*T).rhead)
     DestroySMatrix(T);
   CopySMatrix(M,T); /* T=M */
   u=(*T).mu; /* 交换(*T).mu和(*T).nu */
   (*T).mu=(*T).nu;
   (*T).nu=u;
   head=(*T).rhead; /* 交换(*T).rhead和(*T).chead */
   (*T).rhead=(*T).chead;
   (*T).chead=head;
   for(u=1;u<=(*T).mu;u++) /* 对T的每一行 */
   {
     p=(*T).rhead[u]; /* p为行表头 */
     while(p) /* 没到表尾,对T的每一结点 */
     {
       q=p->down; /* q指向下一个结点 */
       i=p->i; /* 交换.i和.j */
       p->i=p->j;
       p->j=i;
       r=p->down; /* 交换.down.和right */
       p->down=p->right;
       p->right=r;
       p=q; /* p指向下一个结点 */
     }
   }
   return OK;
 }

**********BO5-5.c**********
 /* bo5-5.c 广义表的头尾链表存储(存储结构由c5-5.h定义)的基本操作(11个) */
 Status InitGList(GList *L)
 { /* 创建空的广义表L */
   *L=NULL;
   return OK;
 }

 void DestroyGList(GList *L) /* 广义表的头尾链表存储的销毁操作 */
 { /* 销毁广义表L */
   GList q1,q2;
   if(*L)
   {
     if((*L)->tag==ATOM)
     {
       free(*L); /* 删除原子结点 */
       *L=NULL;
     }
     else /* 删除表结点 */
     {
       q1=(*L)->a.ptr.hp;
       q2=(*L)->a.ptr.tp;
       free(*L);
       *L=NULL;
       DestroyGList(&q1);
       DestroyGList(&q2);
     }
   }
 }

 Status CopyGList(GList *T,GList L)
 { /* 采用头尾链表存储结构,由广义表L复制得到广义表T。算法5.6 */
   if(!L) /* 复制空表 */
     *T=NULL;
   else
   {
     *T=(GList)malloc(sizeof(GLNode)); /* 建表结点 */
     if(!*T)
       exit(OVERFLOW);
     (*T)->tag=L->tag;
     if(L->tag==ATOM)
       (*T)->a.atom=L->a.atom; /* 复制单原子 */
     else
     {
       CopyGList(&((*T)->a.ptr.hp),L->a.ptr.hp);
       /* 复制广义表L->ptr.hp的一个副本T->ptr.hp */
       CopyGList(&((*T)->a.ptr.tp),L->a.ptr.tp);
       /* 复制广义表L->ptr.tp的一个副本T->ptr.tp */
     }
   }
   return OK;
 }

 int GListLength(GList L)
 { /* 返回广义表的长度,即元素个数 */
   int len=0;
   if(!L)
     return 0;
   if(L->tag==ATOM)
     return 1;
   while(L)
   {
     L=L->a.ptr.tp;
     len++;
   }
   return len;
 }

 int GListDepth(GList L)
 { /* 采用头尾链表存储结构,求广义表L的深度。算法5.5 */
   int max,dep;
   GList pp;
   if(!L)
     return 1; /* 空表深度为1 */
   if(L->tag==ATOM)
     return 0; /* 原子深度为0 */
   for(max=0,pp=L;pp;pp=pp->a.ptr.tp)
   {
     dep=GListDepth(pp->a.ptr.hp); /* 求以pp->a.ptr.hp为头指针的子表深度 */
     if(dep>max)
       max=dep;
   }
   return max+1; /* 非空表的深度是各元素的深度的最大值加1 */
 }

 Status GListEmpty(GList L)
 { /* 判定广义表是否为空 */
   if(!L)
     return TRUE;
   else
     return FALSE;
 }

 GList GetHead(GList L)
 { /* 取广义表L的头 */
   GList h,p;
   if(!L)
   {
     printf("空表无表头!\n");
     exit(0);
   }
   p=L->a.ptr.tp;
   L->a.ptr.tp=NULL;
   CopyGList(&h,L);
   L->a.ptr.tp=p;
   return h;
 }

 GList GetTail(GList L)
 { /* 取广义表L的尾 */
   GList t;
   if(!L)
   {
     printf("空表无表尾!\n");
     exit(0);
   }
   CopyGList(&t,L->a.ptr.tp);
   return t;
 }

 Status InsertFirst_GL(GList *L,GList e)
 { /* 初始条件: 广义表存在 */
   /* 操作结果: 插入元素e作为广义表L的第一元素(表头,也可能是子表) */
   GList p=(GList)malloc(sizeof(GLNode));
   if(!p)
     exit(OVERFLOW);
   p->tag=LIST;
   p->a.ptr.hp=e;
   p->a.ptr.tp=*L;
   *L=p;
   return OK;
 }

 Status DeleteFirst_GL(GList *L,GList *e)
 { /* 初始条件: 广义表L存在 */
   /* 操作结果: 删除广义表L的第一元素,并用e返回其值 */
   GList p;
   *e=(*L)->a.ptr.hp;
   p=*L;
   *L=(*L)->a.ptr.tp;
   free(p);
   return OK;
 }

 void Traverse_GL(GList L,void(*v)(AtomType))
 { /* 利用递归算法遍历广义表L */
   if(L) /* L不空 */
     if(L->tag==ATOM) /* L为单原子 */
       v(L->a.atom);
     else /* L为广义表 */
     {
       Traverse_GL(L->a.ptr.hp,v);
       Traverse_GL(L->a.ptr.tp,v);
     }
 }

**********BO5-51.c**********
 /* bo5-51.c 广义表的书写形式串为SString类型 */
 #include"c4-1.h" /* 定义SString类型 */
 #include"bo4-1.c" /* SString类型的基本操作 */
 void sever(SString str,SString hstr) /* 算法5.8  SString是数组，不需引用类型 */
 { /* 将非空串str分割成两部分:hsub为第一个','之前的子串,str为之后的子串 */
   int n,k,i; /* k记尚未配对的左括号个数 */
   SString ch,c1,c2,c3;
   n=StrLength(str);
   StrAssign(c1,",");
   StrAssign(c2,"(");
   StrAssign(c3,")");
   SubString(ch,str,1,1);
   for(i=1,k=0;i<=n&&StrCompare(ch,c1)||k!=0;++i)
   { /* 搜索最外层的第一个逗号 */
     SubString(ch,str,i,1);
     if(!StrCompare(ch,c2))
       ++k;
     else if(!StrCompare(ch,c3))
       --k;
   }
   if(i<=n)
   {
     SubString(hstr,str,1,i-2);
     SubString(str,str,i,n-i+1);
   }
   else
   {
     StrCopy(hstr,str);
     ClearString(str);
   }
 }

 Status CreateGList(GList *L,SString S) /* 算法5.7 */
 { /* 采用头尾链表存储结构,由广义表的书写形式串S创建广义表L。设emp="()" */
   SString sub,hsub,emp;
   GList p,q;
   StrAssign(emp,"()");
   if(!StrCompare(S,emp))
     *L=NULL; /* 创建空表 */
   else
   {
     *L=(GList)malloc(sizeof(GLNode));
     if(!*L) /* 建表结点 */
       exit(OVERFLOW);
     if(StrLength(S)==1) /* S为单原子 */
     {
       (*L)->tag=ATOM;
       (*L)->a.atom=S[1]; /* 创建单原子广义表 */
     }
     else
     {
       (*L)->tag=LIST;
       p=*L;
       SubString(sub,S,2,StrLength(S)-2); /* 脱外层括号 */
       do
       { /* 重复建n个子表 */
         sever(sub,hsub); /* 从sub中分离出表头串hsub */
         CreateGList(&p->a.ptr.hp,hsub);
         q=p;
         if(!StrEmpty(sub)) /* 表尾不空 */
         {
           p=(GLNode *)malloc(sizeof(GLNode));
           if(!p)
             exit(OVERFLOW);
           p->tag=LIST;
           q->a.ptr.tp=p;
         }
       }while(!StrEmpty(sub));
       q->a.ptr.tp=NULL;
     }
   }
   return OK;
 }


**********BO5-52.c**********
 /* bo5-52.c 广义表的书写形式串为HString类型 */
 #include"c4-2.h" /* 定义HString类型 */
 #include"bo4-2.c" /* HString类型的基本操作 */
 Status sever(HString *str,HString *hstr)
 { /* 将非空串str分割成两部分:hstr为第一个','之前的子串,str为之后的子串 */
   int n,i=1,k=0; /* k记尚未配对的左括号个数 */
   HString ch,c1,c2,c3;
   InitString(&ch); /* 初始化HString类型的变量 */
   InitString(&c1);
   InitString(&c2);
   InitString(&c3);
   StrAssign(&c1,",");
   StrAssign(&c2,"(");
   StrAssign(&c3,")");
   n=StrLength(*str);
   do
   {
     SubString(&ch,*str,i,1);
     if(!StrCompare(ch,c2))
       ++k;
     else if(!StrCompare(ch,c3))
       --k;
     ++i;
   }while(i<=n&&StrCompare(ch,c1)||k!=0);
   if(i<=n)
   {
     StrCopy(&ch,*str);
     SubString(hstr,ch,1,i-2);
     SubString(str,ch,i,n-i+1);
   }
   else
   {
     StrCopy(hstr,*str);
     ClearString(str);
   }
   return OK;
 }

 Status CreateGList(GList *L,HString S)
 { /* 采用头尾链表存储结构,由广义表的书写形式串S创建广义表L。设emp="()" */
   HString emp,sub,hsub;
   GList p,q;
   InitString(&emp);
   InitString(&sub);
   InitString(&hsub);
   StrAssign(&emp,"()");
   if(!StrCompare(S,emp)) /* 创建空表 */
     *L=NULL;
   else
   {
     *L=(GList)malloc(sizeof(GLNode));
     if(!*L) /* 建表结点不成功 */
       exit(OVERFLOW);
     if(StrLength(S)==1) /* 创建单原子广义表 */
     {
       (*L)->tag=ATOM;
       (*L)->a.atom=S.ch[0];
     }
     else
     {
       (*L)->tag=LIST;
       p=*L;
       SubString(&sub,S,2,StrLength(S)-2); /* 脱外层括号 */
       do /* 重复建n个子表 */
       {
         sever(&sub,&hsub); /* 从sub中分离出表头串hsub */
         CreateGList(&p->a.ptr.hp,hsub);
         q=p;
         if(!StrEmpty(sub)) /* 表尾不空 */
         {
           p=(GList)malloc(sizeof(GLNode));
           if(!p)
             exit(OVERFLOW);
           p->tag=LIST;
           q->a.ptr.tp=p;
         }
       }while(!StrEmpty(sub));
       q->a.ptr.tp=NULL;
     }
   }
   return OK;
 }


**********Bo5-6.c**********
 /* bo5-6.c 广义表的扩展线性链表存储(存储结构由c5-6.h定义)的基本操作(13个) */
 #include"c4-2.h" /* 定义HString类型 */
 #include"bo4-2.c" /* HString类型的基本操作 */
 /* 广义表的书写形式串为HString类型 */
 Status InitGList(GList *L)
 { /* 创建空的广义表L */
   *L=NULL;
   return OK;
 }

 Status sever(HString *str,HString *hstr) /* 同bo5-52.c */
 { /* 将非空串str分割成两部分:hstr为第一个','之前的子串,str为之后的子串 */
   int n,i=1,k=0; /* k记尚未配对的左括号个数 */
   HString ch,c1,c2,c3;
   InitString(&ch); /* 初始化HString类型的变量 */
   InitString(&c1);
   InitString(&c2);
   InitString(&c3);
   StrAssign(&c1,",");
   StrAssign(&c2,"(");
   StrAssign(&c3,")");
   n=StrLength(*str);
   do
   {
     SubString(&ch,*str,i,1);
     if(!StrCompare(ch,c2))
       ++k;
     else if(!StrCompare(ch,c3))
       --k;
     ++i;
   }while(i<=n&&StrCompare(ch,c1)||k!=0);
   if(i<=n)
   {
     StrCopy(&ch,*str);
     SubString(hstr,ch,1,i-2);
     SubString(str,ch,i,n-i+1);
   }
   else
   {
     StrCopy(hstr,*str);
     ClearString(str);
   }
   return OK;
 }

 Status CreateGList(GList *L,HString S)
 { /* 初始条件: S是广义表的书写形式串。操作结果: 由S创建广义表L */
   HString emp,sub,hsub;
   GList p;
   InitString(&emp);
   InitString(&sub);
   InitString(&hsub);
   StrAssign(&emp,"()"); /* 设emp="()" */
   *L=(GList)malloc(sizeof(GLNode));
   if(!*L) /* 建表结点不成功 */
     exit(OVERFLOW);
   if(!StrCompare(S,emp)) /* 创建空表 */
   {
     (*L)->tag=LIST;
     (*L)->a.hp=NULL;
     (*L)->tp=NULL;
   }
   else if(StrLength(S)==1) /* 创建单原子广义表 */
   {
     (*L)->tag=ATOM;
     (*L)->a.atom=S.ch[0];
     (*L)->tp=NULL;
   }
   else /* 创建一般表 */
   {
     (*L)->tag=LIST;
     (*L)->tp=NULL;
     SubString(&sub,S,2,StrLength(S)-2); /* 脱外层括号 */
     sever(&sub,&hsub); /* 从sub中分离出表头串hsub */
     CreateGList(&(*L)->a.hp,hsub);
     p=(*L)->a.hp;
     while(!StrEmpty(sub)) /* 表尾不空,则重复建n个子表 */
     {
       sever(&sub,&hsub); /* 从sub中分离出表头串hsub */
       CreateGList(&p->tp,hsub);
       p=p->tp;
     };
   }
   return OK;
 }

 void DestroyGList(GList *L)
 { /* 初始条件: 广义表L存在。操作结果: 销毁广义表L */
   GList ph,pt;
   if(*L) /* L不为空表 */
   { /* 由ph和pt接替L的两个指针 */
     if((*L)->tag) /* 是子表 */
       ph=(*L)->a.hp;
     else /* 是原子 */
       ph=NULL;
     pt=(*L)->tp;
     free(*L); /* 释放L所指结点 */
     *L=NULL; /* 令L为空 */
     DestroyGList(&ph); /* 递归销毁表ph */
     DestroyGList(&pt); /* 递归销毁表pt */
   }
 }

 Status CopyGList(GList *T,GList L)
 { /* 初始条件: 广义表L存在。操作结果: 由广义表L复制得到广义表T */
   if(!L) /* L空 */
   {
     *T=NULL;
     return OK;
   }
   *T=(GList)malloc(sizeof(GLNode));
   if(!*T)
     exit(OVERFLOW);
   (*T)->tag=L->tag; /* 复制枚举变量 */
   if(L->tag==ATOM) /* 复制共用体部分 */
     (*T)->a.atom=L->a.atom; /* 复制单原子 */
   else
     CopyGList(&(*T)->a.hp,L->a.hp); /* 复制子表 */
   if(L->tp==NULL) /* 到表尾 */
     (*T)->tp=L->tp;
   else
     CopyGList(&(*T)->tp,L->tp); /* 复制子表 */
   return OK;
 }

 int GListLength(GList L)
 { /* 初始条件: 广义表L存在。操作结果: 求广义表L的长度,即元素个数 */
   int len=0;
   GList p;
   if(L->tag==LIST&&!L->a.hp) /* 空表 */
     return 0; /* 空表返回0 */
   else if(L->tag==ATOM) /* 单原子表 */
     return 1;
   else /* 一般表 */
   {
     p=L->a.hp;
     do
     {
       len++;
       p=p->tp;
     }while(p);
     return len;
   }
 }

 int GListDepth(GList L)
 { /* 初始条件: 广义表L存在。操作结果: 求广义表L的深度 */
   int max,dep;
   GList pp;
   if(L==NULL||L->tag==LIST&&!L->a.hp)
     return 1; /* 空表深度为1 */
   else if(L->tag==ATOM)
     return 0; /* 单原子表深度为0 */
   else /* 求一般表的深度 */
     for(max=0,pp=L->a.hp;pp;pp=pp->tp)
     {
       dep=GListDepth(pp); /* 求以pp为头指针的子表深度 */
       if(dep>max)
         max=dep;
     }
   return max+1; /* 非空表的深度是各元素的深度的最大值加1 */
 }

 Status GListEmpty(GList L)
 { /* 初始条件: 广义表L存在。操作结果: 判定广义表L是否为空 */
   if(!L||L->tag==LIST&&!L->a.hp)
     return OK;
   else
     return ERROR;
 }

 GList GetHead(GList L)
 { /* 初始条件: 广义表L存在。操作结果: 取广义表L的头 */
   GList h;
   InitGList(&h);
   if(!L||L->tag==LIST&&!L->a.hp)
   {
     printf("\n空表无表头!");
     exit(0);
   }
   h=(GList)malloc(sizeof(GLNode));
   if(!h)
     exit(OVERFLOW);
   h->tag=L->a.hp->tag;
   h->tp=NULL;
   if(h->tag==ATOM)
     h->a.atom=L->a.hp->a.atom;
   else
     CopyGList(&h->a.hp,L->a.hp->a.hp);
   return h;
 }

 GList GetTail(GList L)
 { /* 初始条件: 广义表L存在。操作结果: 取广义表L的尾 */
   GList T;
   if(!L)
   {
     printf("\n空表无表尾!");
     exit(0);
   }
   T=(GList)malloc(sizeof(GLNode));
   if(!T)
     exit(OVERFLOW);
   T->tag=LIST;
   T->tp=NULL;
   CopyGList(&T->a.hp,L->a.hp->tp);
   return T;
 }

 Status InsertFirst_GL(GList *L,GList e)
 { /* 初始条件: 广义表存在 */
   /* 操作结果: 插入元素e作为广义表L的第一元素(表头,也可能是子表) */
   GList p=(*L)->a.hp;
   (*L)->a.hp=e;
   e->tp=p;
   return OK;
 }

 Status DeleteFirst_GL(GList *L,GList *e)
 { /* 初始条件:广义表L存在。操作结果:删除广义表L的第一元素,并用e返回其值 */
   if(*L)
   {
     *e=(*L)->a.hp;
     (*L)->a.hp=(*e)->tp;
     (*e)->tp=NULL;
   }
   else
     *e=*L;
   return OK;
 }

 void Traverse_GL(GList L,void(*v)(AtomType))
 { /* 利用递归算法遍历广义表L */
   GList hp;
   if(L) /* L不空 */
   {
     if(L->tag==ATOM) /* L为单原子 */
     {
       v(L->a.atom);
       hp=NULL;
     }
     else /* L为子表 */
       hp=L->a.hp;
     Traverse_GL(hp,v);
     Traverse_GL(L->tp,v);
   }
 }


**********C5-1.H**********
 /* c5-1.h 数组的顺序存储表示 */
 #include<stdarg.h> /* 标准头文件，提供宏va_start，va_arg和va_end， */
                    /* 用于存取变长参数表 */
 #define MAX_ARRAY_DIM 8 /* 假设数组维数的最大值为8 */
 typedef struct
 {
   ElemType *base; /* 数组元素基址，由InitArray分配 */
   int dim; /* 数组维数 */
   int *bounds; /* 数组维界基址，由InitArray分配 */
   int *constants; /* 数组映象函数常量基址，由InitArray分配 */
 }Array;

**********C5-2.H**********
 /* c5-2.h 稀疏矩阵的三元组顺序表存储表示 */
 #define MAXSIZE 100 /* 非零元个数的最大值 */
 typedef struct
 {
   int i,j; /* 行下标,列下标 */
   ElemType e; /* 非零元素值 */
 }Triple;
 typedef struct
 {
   Triple data[MAXSIZE+1]; /* 非零元三元组表,data[0]未用 */
   int mu,nu,tu; /* 矩阵的行数、列数和非零元个数 */
 }TSMatrix;

**********C5-3.H**********
 /* c5-3.h 稀疏矩阵的三元组行逻辑链接的顺序表存储表示 */
 #define MAXSIZE 100 /* 非零元个数的最大值 */
 #define MAXRC 20 /* 最大行列数 */
 typedef struct
 {
   int i,j; /* 行下标,列下标 */
   ElemType e; /* 非零元素值 */
 }Triple; /* 同c5-2.h */
 typedef struct
 {
   Triple data[MAXSIZE+1]; /* 非零元三元组表,data[0]未用 */
   int rpos[MAXRC+1]; /* 各行第一个非零元素的位置表,比c5-2.h增加的项 */
   int mu,nu,tu; /* 矩阵的行数、列数和非零元个数 */
 }RLSMatrix;

**********C5-4.H**********
 /* c5-4.h 稀疏矩阵的十字链表存储表示 */
 typedef struct OLNode
 {
   int i,j; /* 该非零元的行和列下标 */
   ElemType e; /* 非零元素值 */
   struct OLNode *right,*down; /* 该非零元所在行表和列表的后继链域 */
 }OLNode,*OLink;
 typedef struct
 {
   OLink *rhead,*chead; /* 行和列链表头指针向量基址,由CreatSMatrix_OL()分配 */
   int mu,nu,tu; /* 稀疏矩阵的行数、列数和非零元个数 */
 }CrossList;

**********C5-5.H**********
 /* c5-5.h 广义表的头尾链表存储表示 */
 typedef enum{ATOM,LIST}ElemTag; /* ATOM==0:原子,LIST==1:子表 */
 typedef struct GLNode
 {
   ElemTag tag; /* 公共部分,用于区分原子结点和表结点 */
   union /* 原子结点和表结点的联合部分 */
   {
     AtomType atom; /* atom是原子结点的值域,AtomType由用户定义 */
     struct
     {
       struct GLNode *hp,*tp;
     }ptr; /* ptr是表结点的指针域,prt.hp和ptr.tp分别指向表头和表尾 */
   }a;
 }*GList,GLNode; /* 广义表类型 */

**********C5-6.H**********
 /* c5-6.h 广义表的扩展线性链表存储表示 */
 typedef enum{ATOM,LIST}ElemTag; /* ATOM==0:原子,LIST==1:子表 */
 typedef struct GLNode
 {
   ElemTag tag; /* 公共部分,用于区分原子结点和表结点 */
   union /* 原子结点和表结点的联合部分 */
   {
     AtomType atom; /* 原子结点的值域 */
     struct GLNode *hp; /* 表结点的表头指针 */
   }a;
   struct GLNode *tp; /* 相当于线性链表的next,指向下一个元素结点 */
 }*GList,GLNode; /* 广义表类型GList是一种扩展的线性链表 */

**********MAIN5-1.C**********
 /* main5-1.c 检验bo5-1.c的主程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c5-1.h"
 #include"bo5-1.c"

 void main()
 {
   Array A;
   int i,j,k,*p,dim=3,bound1=3,bound2=4,bound3=2; /* a[3][4][2]数组 */
   ElemType e,*p1;
   InitArray(&A,dim,bound1,bound2,bound3); /* 构造3＊4＊2的3维数组A */
   p=A.bounds;
   printf("A.bounds=");
   for(i=0;i<dim;i++) /* 顺序输出A.bounds */
     printf("%d ",*(p+i));
   p=A.constants;
   printf("\nA.constants=");
   for(i=0;i<dim;i++) /* 顺序输出A.constants */
     printf("%d ",*(p+i));
   printf("\n%d页%d行%d列矩阵元素如下:\n",bound1,bound2,bound3);
   for(i=0;i<bound1;i++)
   {
     for(j=0;j<bound2;j++)
     {
       for(k=0;k<bound3;k++)
       {
         Assign(&A,i*100+j*10+k,i,j,k); /* 将i*100+j*10+k赋值给A[i][j][k] */
         Value(&e,A,i,j,k); /* 将A[i][j][k]的值赋给e */
         printf("A[%d][%d][%d]=%2d ",i,j,k,e); /* 输出A[i][j][k] */
       }
       printf("\n");
     }
     printf("\n");
   }
   p1=A.base;
   printf("A.base=\n");
   for(i=0;i<bound1*bound2*bound3;i++) /* 顺序输出A.base */
   {
     printf("%4d",*(p1+i));
     if(i%(bound2*bound3)==bound2*bound3-1)
       printf("\n");
   }
   DestroyArray(&A);
 }

**********MAIN5-2.c**********
 /* main5-2.c 检验bo5-2.c的主程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c5-2.h"
 #include"bo5-2.c"
 void main()
 {
   TSMatrix A,B,C;
   printf("创建矩阵A: ");
   CreateSMatrix(&A);
   PrintSMatrix(A);
   printf("由矩阵A复制矩阵B: ");
   CopySMatrix(A,&B);
   PrintSMatrix(B);
   DestroySMatrix(&B);
   printf("销毁矩阵B后:\n");
   PrintSMatrix(B);
   printf("创建矩阵B2:(与矩阵A的行、列数相同，行、列分别为%d,%d)\n",A.mu,A.nu);
   CreateSMatrix(&B);
   PrintSMatrix(B);
   printf("矩阵C1(A+B): ");
   AddSMatrix(A,B,&C);
   PrintSMatrix(C);
   DestroySMatrix(&C);
   printf("矩阵C2(A-B): ");
   SubtSMatrix(A,B,&C);
   PrintSMatrix(C);
   DestroySMatrix(&C);
   printf("矩阵C3(A的转置): ");
   TransposeSMatrix(A,&C);
   PrintSMatrix(C);
   DestroySMatrix(&A);
   DestroySMatrix(&B);
   DestroySMatrix(&C);
   printf("创建矩阵A2: ");
   CreateSMatrix(&A);
   PrintSMatrix(A);
   printf("创建矩阵B3:(行数应与矩阵A2的列数相同=%d)\n",A.nu);
   CreateSMatrix(&B);
   PrintSMatrix(B);
   printf("矩阵C5(A*B): ");
   MultSMatrix(A,B,&C);
   PrintSMatrix(C);
   DestroySMatrix(&A);
   DestroySMatrix(&B);
   DestroySMatrix(&C);
 }
**********MAIN5-3.c**********
 /* main5-3.c 检验bo5-3.c的主程序(与main5-2.c很相像) */
 #include"c1.h"
 typedef int ElemType;
 #include"c5-3.h" /* 此行与main5-2.c不同 */
 #include"bo5-3.c" /* 此行与main5-2.c不同 */
 void main()
 {
   RLSMatrix A,B,C; /* 此行与main5-2.c不同 */
   printf("创建矩阵A: ");
   CreateSMatrix(&A);
   PrintSMatrix(A);
   printf("由矩阵A复制矩阵B: ");
   CopySMatrix(A,&B);
   PrintSMatrix(B);
   DestroySMatrix(&B);
   printf("销毁矩阵B后:\n");
   PrintSMatrix(B);
   printf("创建矩阵B2:(与矩阵A的行、列数相同，行、列分别为%d,%d)\n",A.mu,A.nu);
   CreateSMatrix(&B);
   PrintSMatrix(B);
   printf("矩阵C1(A+B): ");
   AddSMatrix(A,B,&C);
   PrintSMatrix(C);
   DestroySMatrix(&C);
   printf("矩阵C2(A-B): ");
   SubtSMatrix(A,B,&C);
   PrintSMatrix(C);
   DestroySMatrix(&C);
   printf("矩阵C3(A的转置): ");
   TransposeSMatrix(A,&C);
   PrintSMatrix(C);
   DestroySMatrix(&A);
   DestroySMatrix(&B);
   DestroySMatrix(&C);
   printf("创建矩阵A2: ");
   CreateSMatrix(&A);
   PrintSMatrix(A);
   printf("创建矩阵B3:(行数应与矩阵A2的列数相同=%d)\n",A.nu);
   CreateSMatrix(&B);
   PrintSMatrix(B);
   printf("矩阵C5(A*B): ");
   MultSMatrix(A,B,&C);
   PrintSMatrix(C);
   DestroySMatrix(&A);
   DestroySMatrix(&B);
   DestroySMatrix(&C);
 }
**********MAIN5-4.c**********
 /* main5-4.c 检验bo5-4.c的主程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c5-4.h"
 #include"bo5-4.c"
 void main()
 {
   CrossList A,B,C;
   InitSMatrix(&A); /* CrossList类型的变量在初次使用之前必须初始化 */
   InitSMatrix(&B);
   printf("创建矩阵A: ");
   CreateSMatrix(&A);
   PrintSMatrix(A);
   printf("由矩阵A复制矩阵B: ");
   CopySMatrix(A,&B);
   PrintSMatrix(B);
   DestroySMatrix(&B); /* CrossList类型的变量在再次使用之前必须先销毁 */
   printf("销毁矩阵B后:\n");
   PrintSMatrix(B);
   printf("创建矩阵B2:(与矩阵A的行、列数相同，行、列分别为%d,%d)\n",A.mu,A.nu);
   CreateSMatrix(&B);
   PrintSMatrix(B);
   printf("矩阵C1(A+B): ");
   AddSMatrix(A,B,&C);
   PrintSMatrix(C);
   DestroySMatrix(&C);
   printf("矩阵C2(A-B): ");
   SubtSMatrix(A,B,&C);
   PrintSMatrix(C);
   DestroySMatrix(&C);
   printf("矩阵C3(A的转置): ");
   TransposeSMatrix(A,&C);
   PrintSMatrix(C);
   DestroySMatrix(&A);
   DestroySMatrix(&B);
   DestroySMatrix(&C);
   printf("创建矩阵A2: ");
   CreateSMatrix(&A);
   PrintSMatrix(A);
   printf("创建矩阵B3:(行数应与矩阵A2的列数相同=%d)\n",A.nu);
   CreateSMatrix(&B);
   PrintSMatrix(B);
   printf("矩阵C5(A*B): ");
   MultSMatrix(A,B,&C);
   PrintSMatrix(C);
   DestroySMatrix(&A);
   DestroySMatrix(&B);
   DestroySMatrix(&C);
 }

**********MAIN5-51.c**********
 /* main5-51.c 检验bo5-5.c和bo5-51.c(字符串为SString类型)的主程序 */
 #include"c1.h"
 typedef char AtomType; /* 定义原子类型为字符型 */
 #include"c5-5.h" /* 定义广义表的头尾链表存储 */
 #include"bo5-5.c"
 #include"bo5-51.c"

 void visit(AtomType e)
 {
   printf("%c ", e);
 }

 void main()
 {
   char p[80];
   SString t;
   GList l,m;
   InitGList(&l);
   InitGList(&m);
   printf("空广义表l的深度=%d l是否空？%d(1:是 0:否)\n",GListDepth(l),GListEmpty(l));
   printf("请输入广义表l(书写形式：空表:(),单原子:a,其它:(a,(b),b)):\n");
   gets(p);
   StrAssign(t,p);
   CreateGList(&l,t);
   printf("广义表l的长度=%d\n",GListLength(l));
   printf("广义表l的深度=%d l是否空？%d(1:是 0:否)\n",GListDepth(l),GListEmpty(l));
   printf("遍历广义表l：\n");
   Traverse_GL(l,visit);
   printf("\n复制广义表m=l\n");
   CopyGList(&m,l);
   printf("广义表m的长度=%d\n",GListLength(m));
   printf("广义表m的深度=%d\n",GListDepth(m));
   printf("遍历广义表m：\n");
   Traverse_GL(m,visit);
   DestroyGList(&m);
   m=GetHead(l);
   printf("\nm是l的表头，遍历广义表m：\n");
   Traverse_GL(m,visit);
   DestroyGList(&m);
   m=GetTail(l);
   printf("\nm是l的表尾，遍历广义表m：\n");
   Traverse_GL(m,visit);
   InsertFirst_GL(&m,l);
   printf("\n插入l为m的表头，遍历广义表m：\n");
   Traverse_GL(m,visit);
   printf("\n删除m的表头，遍历广义表m：\n");
   DestroyGList(&l);
   DeleteFirst_GL(&m,&l);
   Traverse_GL(m,visit);
   printf("\n");
   DestroyGList(&m);
 }

**********MAIN5-52.c**********
 /* main5-52.c 检验bo5-5.c和bo5-52.c(字符串为HString类型)的主程序 */
 #include"c1.h" /* 此程序与main5-51.c基本相同 */
 typedef char AtomType; /* 定义原子类型为字符型 */
 #include"c5-5.h" /* 定义广义表的头尾链表存储 */
 #include"bo5-5.c"
 #include"bo5-52.c" /* 与main5-51.c不同 */

 void visit(AtomType e)
 {
   printf("%c ", e);
 }

 void main()
 {
   char p[80];
   GList l,m;
   HString t; /* 与main5-51.c不同 */
   InitString(&t); /* 增加此句 */
   InitGList(&l);
   InitGList(&m);
   printf("空广义表l的深度=%d l是否空？%d(1:是 0:否)\n",GListDepth(l),GListEmpty(l));
   printf("请输入广义表l(书写形式：空表:(),单原子:a,其它:(a,(b),b)):\n");
   gets(p);
   StrAssign(&t,p);
   CreateGList(&l,t);
   printf("广义表l的长度=%d\n",GListLength(l));
   printf("广义表l的深度=%d l是否空？%d(1:是 0:否)\n",GListDepth(l),GListEmpty(l));
   printf("遍历广义表l：\n");
   Traverse_GL(l,visit);
   printf("\n复制广义表m=l\n");
   CopyGList(&m,l);
   printf("广义表m的长度=%d\n",GListLength(m));
   printf("广义表m的深度=%d\n",GListDepth(m));
   printf("遍历广义表m：\n");
   Traverse_GL(m,visit);
   DestroyGList(&m);
   m=GetHead(l);
   printf("\nm是l的表头，遍历广义表m：\n");
   Traverse_GL(m,visit);
   DestroyGList(&m);
   m=GetTail(l);
   printf("\nm是l的表尾，遍历广义表m：\n");
   Traverse_GL(m,visit);
   InsertFirst_GL(&m,l);
   printf("\n插入l为m的表头，遍历广义表m：\n");
   Traverse_GL(m,visit);
   printf("\n删除m的表头，遍历广义表m：\n");
   DestroyGList(&l);
   DeleteFirst_GL(&m,&l);
   Traverse_GL(m,visit);
   printf("\n");
   DestroyGList(&m);
 }

**********Main5-6.c**********
 /* main5-6.c 检验bo5-6.c(字符串为HString类型)的主程序 */
 #include"c1.h" /* 此程序与main5-52.c只有两句不同 */
 typedef char AtomType; /* 定义原子类型为字符型 */
 #include"c5-6.h" /* 定义广义表的扩展线性链表存储,与main5-52.c不同 */
 #include"bo5-6.c" /* 与main5-52.c不同 */

 void visit(AtomType e)
 {
   printf("%c ", e);
 }

 void main()
 {
   char p[80];
   GList l,m;
   HString t;
   InitString(&t);
   InitGList(&l);
   InitGList(&m);
   printf("空广义表l的深度=%d l是否空？%d(1:是 0:否)\n",GListDepth(l),GListEmpty(l));
   printf("请输入广义表l(书写形式：空表:(),单原子:a,其它:(a,(b),b)):\n");
   gets(p);
   StrAssign(&t,p);
   CreateGList(&l,t);
   printf("广义表l的长度=%d\n",GListLength(l));
   printf("广义表l的深度=%d l是否空？%d(1:是 0:否)\n",GListDepth(l),GListEmpty(l));
   printf("遍历广义表l：\n");
   Traverse_GL(l,visit);
   printf("\n复制广义表m=l\n");
   CopyGList(&m,l);
   printf("广义表m的长度=%d\n",GListLength(m));
   printf("广义表m的深度=%d\n",GListDepth(m));
   printf("遍历广义表m：\n");
   Traverse_GL(m,visit);
   DestroyGList(&m);
   m=GetHead(l);
   printf("\nm是l的表头，遍历广义表m：\n");
   Traverse_GL(m,visit);
   DestroyGList(&m);
   m=GetTail(l);
   printf("\nm是l的表尾，遍历广义表m：\n");
   Traverse_GL(m,visit);
   InsertFirst_GL(&m,l);
   printf("\n插入l为m的表头，遍历广义表m：\n");
   Traverse_GL(m,visit);
   DeleteFirst_GL(&m,&l);
   printf("\n删除m的表头，遍历广义表m：\n");
   Traverse_GL(m,visit);
   printf("\n");
   DestroyGList(&m);
 }

F:\GitHubCode\Code\Csjjg\严蔚敏《数据结构》的全部代码实现（C语言）\ch6
**********algo6-2.c**********
 /* algo6-2.cpp 实现算法6.13的程序，前半部分与algo6-1.cpp同 */
 #include"c1.h"
 #include"c6-7.h"

 int min1(HuffmanTree t,int i)
 { /* 函数void select()调用 */
   int j,flag;
   unsigned int k=UINT_MAX; /* 取k为不小于可能的值 */
   for(j=1;j<=i;j++)
     if(t[j].weight<k&&t[j].parent==0)
       k=t[j].weight,flag=j;
   t[flag].parent=1;
   return flag;
 }

 void select(HuffmanTree t,int i,int *s1,int *s2)
 { /* s1为最小的两个值中序号小的那个 */
   int j;
   *s1=min1(t,i);
   *s2=min1(t,i);
   if(*s1>*s2)
   {
     j=*s1;
     *s1=*s2;
     *s2=j;
   }
 } /* 以上同algo6-1.c */

 void HuffmanCoding(HuffmanTree *HT,HuffmanCode *HC,int *w,int n) /* 前半部分为算法6.12 */
 { /* w存放n个字符的权值(均>0),构造赫夫曼树HT,并求出n个字符的赫夫曼编码HC */
   int m,i,s1,s2; /* 此句与algo6-1.c不同 */
   unsigned c,cdlen; /* 此句与algo6-1.c不同 */
   HuffmanTree p;
   char *cd;
   if(n<=1)
     return;
   m=2*n-1;
   *HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode)); /* 0号单元未用 */
   for(p=*HT+1,i=1;i<=n;++i,++p,++w)
   {
     (*p).weight=*w;
     (*p).parent=0;
     (*p).lchild=0;
     (*p).rchild=0;
   }
   for(;i<=m;++i,++p)
     (*p).parent=0;
   for(i=n+1;i<=m;++i) /* 建赫夫曼树 */
   { /* 在HT[1~i-1]中选择parent为0且weight最小的两个结点,其序号分别为s1和s2 */
     select(*HT,i-1,&s1,&s2);
     (*HT)[s1].parent=(*HT)[s2].parent=i;
     (*HT)[i].lchild=s1;
     (*HT)[i].rchild=s2;
     (*HT)[i].weight=(*HT)[s1].weight+(*HT)[s2].weight;
   }
   /* 以下为算法6.13，无栈非递归遍历赫夫曼树,求赫夫曼编码，以上同算法6.12 */
   *HC=(HuffmanCode)malloc((n+1)*sizeof(char*));
   /* 分配n个字符编码的头指针向量([0]不用) */
   cd=(char*)malloc(n*sizeof(char)); /* 分配求编码的工作空间 */
   c=m;
   cdlen=0;
   for(i=1;i<=m;++i)
     (*HT)[i].weight=0; /* 遍历赫夫曼树时用作结点状态标志 */
   while(c)
   {
     if((*HT)[c].weight==0)
     { /* 向左 */
       (*HT)[c].weight=1;
       if((*HT)[c].lchild!=0)
       {
         c=(*HT)[c].lchild;
         cd[cdlen++]='0';
       }
       else if((*HT)[c].rchild==0)
       { /* 登记叶子结点的字符的编码 */
         (*HC)[c]=(char *)malloc((cdlen+1)*sizeof(char));
         cd[cdlen]='\0';
         strcpy((*HC)[c],cd); /* 复制编码(串) */
       }
     }
     else if((*HT)[c].weight==1)
     { /* 向右 */
       (*HT)[c].weight=2;
       if((*HT)[c].rchild!=0)
       {
         c=(*HT)[c].rchild;
         cd[cdlen++]='1';
       }
     }
     else
     { /* HT[c].weight==2,退回 */
       (*HT)[c].weight=0;
       c=(*HT)[c].parent;
       --cdlen; /* 退到父结点,编码长度减1 */
     }
   }
   free(cd);
 }

 void main()
 { /* 主程序同algo6-1.c */
   HuffmanTree HT;
   HuffmanCode HC;
   int *w,n,i;
   printf("请输入权值的个数(>1)：");
   scanf("%d",&n);
   w=(int *)malloc(n*sizeof(int));
   printf("请依次输入%d个权值(整型)：\n",n);
   for(i=0;i<=n-1;i++)
     scanf("%d",w+i);
   HuffmanCoding(&HT,&HC,w,n);
   for(i=1;i<=n;i++)
     puts(HC[i]);
 }

**********BO6-1.c**********
 /* bo6-1.c 二叉树的顺序存储(存储结构由c6-1.h定义)的基本操作(23个) */
 Status InitBiTree(SqBiTree T)
 { /* 构造空二叉树T。因为T是固定数组，不会改变，故不需要& */
   int i;
   for(i=0;i<MAX_TREE_SIZE;i++)
     T[i]=Nil; /* 初值为空 */
   return OK;
 }

 void DestroyBiTree()
 { /* 由于SqBiTree是定长类型,无法销毁 */
 }

 Status CreateBiTree(SqBiTree T)
 { /* 按层序次序输入二叉树中结点的值(字符型或整型), 构造顺序存储的二叉树T */
   int i=0;
 #if CHAR
   int l;
   char s[MAX_TREE_SIZE];
   printf("请按层序输入结点的值(字符)，空格表示空结点，结点数≤%d:\n",MAX_TREE_SIZE);
   gets(s); /* 输入字符串 */
   l=strlen(s); /* 求字符串的长度 */
   for(;i<l;i++) /* 将字符串赋值给T */
   {
     T[i]=s[i];
     if(i!=0&&T[(i+1)/2-1]==Nil&&T[i]!=Nil) /* 此结点(不空)无双亲且不是根 */
     {
       printf("出现无双亲的非根结点%c\n",T[i]);
       exit(ERROR);
     }
   }
   for(i=l;i<MAX_TREE_SIZE;i++) /* 将空赋值给T的后面的结点 */
     T[i]=Nil;
 #else
   printf("请按层序输入结点的值(整型)，0表示空结点，输999结束。结点数≤%d:\n",MAX_TREE_SIZE);
   while(1)
   {
     scanf("%d",&T[i]);
     if(T[i]==999)
       break;
     if(i!=0&&T[(i+1)/2-1]==Nil&&T[i]!=Nil) /* 此结点(不空)无双亲且不是根 */
     {
       printf("出现无双亲的非根结点%d\n",T[i]);
       exit(ERROR);
     }
     i++;
   }
   while(i<MAX_TREE_SIZE)
   {
     T[i]=Nil; /* 将空赋值给T的后面的结点 */
     i++;
   }
 #endif
   return OK;
 }

 #define ClearBiTree InitBiTree /* 在顺序存储结构中，两函数完全一样 */

 Status BiTreeEmpty(SqBiTree T)
 { /* 初始条件: 二叉树T存在 */
   /* 操作结果: 若T为空二叉树,则返回TRUE,否则FALSE */
   if(T[0]==Nil) /* 根结点为空,则树空 */
     return TRUE;
   else
     return FALSE;
 }

 int BiTreeDepth(SqBiTree T)
 { /* 初始条件: 二叉树T存在。操作结果: 返回T的深度 */
   int i,j=-1;
   for(i=MAX_TREE_SIZE-1;i>=0;i--) /* 找到最后一个结点 */
     if(T[i]!=Nil)
       break;
   i++; /* 为了便于计算 */
   do
     j++;
   while(i>=pow(2,j));
   return j;
 }

 Status Root(SqBiTree T,TElemType *e)
 { /* 初始条件: 二叉树T存在 */
   /* 操作结果:  当T不空,用e返回T的根,返回OK;否则返回ERROR,e无定义 */
   if(BiTreeEmpty(T)) /* T空 */
     return ERROR;
   else
   {
     *e=T[0];
     return OK;
   }
 }

 TElemType Value(SqBiTree T,position e)
 { /* 初始条件: 二叉树T存在,e是T中某个结点(的位置) */
   /* 操作结果: 返回处于位置e(层,本层序号)的结点的值 */
   return T[(int)pow(2,e.level-1)+e.order-2];
 }

 Status Assign(SqBiTree T,position e,TElemType value)
 { /* 初始条件: 二叉树T存在,e是T中某个结点(的位置) */
   /* 操作结果: 给处于位置e(层,本层序号)的结点赋新值value */
   int i=(int)pow(2,e.level-1)+e.order-2; /* 将层、本层序号转为矩阵的序号 */
   if(value!=Nil&&T[(i+1)/2-1]==Nil) /* 给叶子赋非空值但双亲为空 */
     return ERROR;
   else if(value==Nil&&(T[i*2+1]!=Nil||T[i*2+2]!=Nil)) /*  给双亲赋空值但有叶子（不空） */
     return ERROR;
   T[i]=value;
   return OK;
 }

 TElemType Parent(SqBiTree T,TElemType e)
 { /* 初始条件: 二叉树T存在,e是T中某个结点 */
   /* 操作结果: 若e是T的非根结点,则返回它的双亲,否则返回＂空＂ */
   int i;
   if(T[0]==Nil) /* 空树 */
     return Nil;
   for(i=1;i<=MAX_TREE_SIZE-1;i++)
     if(T[i]==e) /* 找到e */
       return T[(i+1)/2-1];
   return Nil; /* 没找到e */
 }

 TElemType LeftChild(SqBiTree T,TElemType e)
 { /* 初始条件: 二叉树T存在,e是T中某个结点 */
   /* 操作结果: 返回e的左孩子。若e无左孩子,则返回＂空＂ */
   int i;
   if(T[0]==Nil) /* 空树 */
     return Nil;
   for(i=0;i<=MAX_TREE_SIZE-1;i++)
     if(T[i]==e) /* 找到e */
       return T[i*2+1];
   return Nil; /* 没找到e */
 }

 TElemType RightChild(SqBiTree T,TElemType e)
 { /* 初始条件: 二叉树T存在,e是T中某个结点 */
   /* 操作结果: 返回e的右孩子。若e无右孩子,则返回＂空＂ */
   int i;
   if(T[0]==Nil) /* 空树 */
     return Nil;
   for(i=0;i<=MAX_TREE_SIZE-1;i++)
     if(T[i]==e) /* 找到e */
       return T[i*2+2];
   return Nil; /* 没找到e */
 }

 TElemType LeftSibling(SqBiTree T,TElemType e)
 { /* 初始条件: 二叉树T存在,e是T中某个结点 */
   /* 操作结果: 返回e的左兄弟。若e是T的左孩子或无左兄弟,则返回＂空＂ */
   int i;
   if(T[0]==Nil) /* 空树 */
     return Nil;
   for(i=1;i<=MAX_TREE_SIZE-1;i++)
     if(T[i]==e&&i%2==0) /* 找到e且其序号为偶数(是右孩子) */
       return T[i-1];
   return Nil; /* 没找到e */
 }

 TElemType RightSibling(SqBiTree T,TElemType e)
 { /* 初始条件: 二叉树T存在,e是T中某个结点 */
   /* 操作结果: 返回e的右兄弟。若e是T的右孩子或无右兄弟,则返回＂空＂ */
   int i;
   if(T[0]==Nil) /* 空树 */
     return Nil;
   for(i=1;i<=MAX_TREE_SIZE-1;i++)
     if(T[i]==e&&i%2) /* 找到e且其序号为奇数(是左孩子) */
       return T[i+1];
   return Nil; /* 没找到e */
 }

 void Move(SqBiTree q,int j,SqBiTree T,int i) /* InsertChild()用到。加 */
 { /* 把从q的j结点开始的子树移为从T的i结点开始的子树 */
   if(q[2*j+1]!=Nil) /* q的左子树不空 */
     Move(q,(2*j+1),T,(2*i+1)); /* 把q的j结点的左子树移为T的i结点的左子树 */
   if(q[2*j+2]!=Nil) /* q的右子树不空 */
     Move(q,(2*j+2),T,(2*i+2)); /* 把q的j结点的右子树移为T的i结点的右子树 */
   T[i]=q[j]; /* 把q的j结点移为T的i结点 */
   q[j]=Nil; /* 把q的j结点置空 */
 }

 Status InsertChild(SqBiTree T,TElemType p,Status LR,SqBiTree c)
 { /* 初始条件: 二叉树T存在,p是T中某个结点的值,LR为0或1,非空二叉树c与T */
   /*           不相交且右子树为空 */
   /* 操作结果: 根据LR为0或1,插入c为T中p结点的左或右子树。p结点的原有左或 */
   /*           右子树则成为c的右子树 */
   int j,k,i=0;
   for(j=0;j<(int)pow(2,BiTreeDepth(T))-1;j++) /* 查找p的序号 */
     if(T[j]==p) /* j为p的序号 */
       break;
   k=2*j+1+LR; /* k为p的左或右孩子的序号 */
   if(T[k]!=Nil) /* p原来的左或右孩子不空 */
     Move(T,k,T,2*k+2); /* 把从T的k结点开始的子树移为从k结点的右子树开始的子树 */
   Move(c,i,T,k); /* 把从c的i结点开始的子树移为从T的k结点开始的子树 */
   return OK;
 }

 typedef int QElemType; /* 设队列元素类型为整型(序号) */
 #include "c3-3.h" /* 顺序非循环队列 */
 #include "bo3-4.c" /* 顺序非循环队列的基本操作 */
 Status DeleteChild(SqBiTree T,position p,int LR)
 { /* 初始条件: 二叉树T存在,p指向T中某个结点,LR为1或0 */
   /* 操作结果: 根据LR为1或0,删除T中p所指结点的左或右子树 */
   int i;
   Status k=OK; /* 队列不空的标志 */
   SqQueue q;
   InitQueue(&q); /* 初始化队列，用于存放待删除的结点 */
   i=(int)pow(2,p.level-1)+p.order-2; /* 将层、本层序号转为矩阵的序号 */
   if(T[i]==Nil) /* 此结点空 */
     return ERROR;
   i=i*2+1+LR; /* 待删除子树的根结点在矩阵中的序号 */
   while(k)
   {
     if(T[2*i+1]!=Nil) /* 左结点不空 */
       EnQueue(&q,2*i+1); /* 入队左结点的序号 */
     if(T[2*i+2]!=Nil) /* 右结点不空 */
       EnQueue(&q,2*i+2); /* 入队右结点的序号 */
     T[i]=Nil; /* 删除此结点 */
     k=DeQueue(&q,&i); /* 队列不空 */
   }
   return OK;
 }

 Status(*VisitFunc)(TElemType); /* 函数变量 */
 void PreTraverse(SqBiTree T,int e)
 { /* PreOrderTraverse()调用 */
   VisitFunc(T[e]);
   if(T[2*e+1]!=Nil) /* 左子树不空 */
     PreTraverse(T,2*e+1);
   if(T[2*e+2]!=Nil) /* 右子树不空 */
     PreTraverse(T,2*e+2);
 }

 Status PreOrderTraverse(SqBiTree T,Status(*Visit)(TElemType))
 { /* 初始条件: 二叉树存在,Visit是对结点操作的应用函数 */
   /* 操作结果: 先序遍历T,对每个结点调用函数Visit一次且仅一次。 */
   /*           一旦Visit()失败,则操作失败 */
   VisitFunc=Visit;
   if(!BiTreeEmpty(T)) /* 树不空 */
     PreTraverse(T,0);
   printf("\n");
   return OK;
 }

 void InTraverse(SqBiTree T,int e)
 { /* InOrderTraverse()调用 */
   if(T[2*e+1]!=Nil) /* 左子树不空 */
     InTraverse(T,2*e+1);
   VisitFunc(T[e]);
   if(T[2*e+2]!=Nil) /* 右子树不空 */
     InTraverse(T,2*e+2);
 }

 Status InOrderTraverse(SqBiTree T,Status(*Visit)(TElemType))
 { /* 初始条件: 二叉树存在,Visit是对结点操作的应用函数 */
   /* 操作结果: 中序遍历T,对每个结点调用函数Visit一次且仅一次。 */
   /*           一旦Visit()失败,则操作失败 */
   VisitFunc=Visit;
   if(!BiTreeEmpty(T)) /* 树不空 */
     InTraverse(T,0);
   printf("\n");
   return OK;
 }

 void PostTraverse(SqBiTree T,int e)
 { /* PostOrderTraverse()调用 */
   if(T[2*e+1]!=Nil) /* 左子树不空 */
     PostTraverse(T,2*e+1);
   if(T[2*e+2]!=Nil) /* 右子树不空 */
     PostTraverse(T,2*e+2);
   VisitFunc(T[e]);
 }

 Status PostOrderTraverse(SqBiTree T,Status(*Visit)(TElemType))
 { /* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
   /* 操作结果: 后序遍历T,对每个结点调用函数Visit一次且仅一次。 */
   /*           一旦Visit()失败,则操作失败 */
   VisitFunc=Visit;
   if(!BiTreeEmpty(T)) /* 树不空 */
     PostTraverse(T,0);
   printf("\n");
   return OK;
 }

 void LevelOrderTraverse(SqBiTree T,Status(*Visit)(TElemType))
 { /* 层序遍历二叉树 */
   int i=MAX_TREE_SIZE-1,j;
   while(T[i]==Nil)
     i--; /* 找到最后一个非空结点的序号 */
   for(j=0;j<=i;j++)  /* 从根结点起,按层序遍历二叉树 */
     if(T[j]!=Nil)
       Visit(T[j]); /* 只遍历非空的结点 */
   printf("\n");
 }

 void Print(SqBiTree T)
 { /* 逐层、按本层序号输出二叉树 */
   int j,k;
   position p;
   TElemType e;
   for(j=1;j<=BiTreeDepth(T);j++)
   {
     printf("第%d层: ",j);
     for(k=1;k<=pow(2,j-1);k++)
     {
       p.level=j;
       p.order=k;
       e=Value(T,p);
       if(e!=Nil)
         printf("%d:%d ",k,e);
     }
     printf("\n");
   }
 }

**********bo6-2.c**********
 /* bo6-2.c 二叉树的二叉链表存储(存储结构由c6-2.h定义)的基本操作(22个) */
 Status InitBiTree(BiTree *T)
 { /* 操作结果: 构造空二叉树T */
   *T=NULL;
   return OK;
 }

 void DestroyBiTree(BiTree *T)
 { /* 初始条件: 二叉树T存在。操作结果: 销毁二叉树T */
   if(*T) /* 非空树 */
   {
     if((*T)->lchild) /* 有左孩子 */
       DestroyBiTree(&(*T)->lchild); /* 销毁左孩子子树 */
     if((*T)->rchild) /* 有右孩子 */
       DestroyBiTree(&(*T)->rchild); /* 销毁右孩子子树 */
     free(*T); /* 释放根结点 */
     *T=NULL; /* 空指针赋0 */
   }
 }

 void CreateBiTree(BiTree *T)
 { /* 算法6.4:按先序次序输入二叉树中结点的值（可为字符型或整型，在主程中 */
   /* 定义），构造二叉链表表示的二叉树T。变量Nil表示空（子）树。有改动 */
   TElemType ch;
 #ifdef CHAR
   scanf("%c",&ch);
 #endif
 #ifdef INT
   scanf("%d",&ch);
 #endif
   if(ch==Nil) /* 空 */
     *T=NULL;
   else
   {
     *T=(BiTree)malloc(sizeof(BiTNode));
     if(!*T)
       exit(OVERFLOW);
     (*T)->data=ch; /* 生成根结点 */
     CreateBiTree(&(*T)->lchild); /* 构造左子树 */
     CreateBiTree(&(*T)->rchild); /* 构造右子树 */
   }
 }

 Status BiTreeEmpty(BiTree T)
 { /* 初始条件: 二叉树T存在 */
   /* 操作结果: 若T为空二叉树,则返回TRUE,否则FALSE */
   if(T)
     return FALSE;
   else
     return TRUE;
 }

 #define ClearBiTree DestroyBiTree

 int BiTreeDepth(BiTree T)
 { /* 初始条件: 二叉树T存在。操作结果: 返回T的深度 */
   int i,j;
   if(!T)
     return 0;
   if(T->lchild)
     i=BiTreeDepth(T->lchild);
   else
     i=0;
   if(T->rchild)
     j=BiTreeDepth(T->rchild);
   else
     j=0;
   return i>j?i+1:j+1;
 }

 TElemType Root(BiTree T)
 { /* 初始条件: 二叉树T存在。操作结果: 返回T的根 */
   if(BiTreeEmpty(T))
     return Nil;
   else
     return T->data;
 }

 TElemType Value(BiTree p)
 { /* 初始条件: 二叉树T存在，p指向T中某个结点 */
   /* 操作结果: 返回p所指结点的值 */
   return p->data;
 }

 void Assign(BiTree p,TElemType value)
 { /* 给p所指结点赋值为value */
   p->data=value;
 }

 typedef BiTree QElemType; /* 设队列元素为二叉树的指针类型 */
 #include"c3-2.h"
 #include"bo3-2.c"
 TElemType Parent(BiTree T,TElemType e)
 { /* 初始条件: 二叉树T存在,e是T中某个结点 */
   /* 操作结果: 若e是T的非根结点,则返回它的双亲,否则返回＂空＂ */
   LinkQueue q;
   QElemType a;
   if(T) /* 非空树 */
   {
     InitQueue(&q); /* 初始化队列 */
     EnQueue(&q,T); /* 树根入队 */
     while(!QueueEmpty(q)) /* 队不空 */
     {
       DeQueue(&q,&a); /* 出队,队列元素赋给a */
       if(a->lchild&&a->lchild->data==e||a->rchild&&a->rchild->data==e)
       /* 找到e(是其左或右孩子) */
         return a->data; /* 返回e的双亲的值 */
       else /* 没找到e,则入队其左右孩子指针(如果非空) */
       {
         if(a->lchild)
           EnQueue(&q,a->lchild);
         if(a->rchild)
           EnQueue(&q,a->rchild);
       }
     }
   }
   return Nil; /* 树空或没找到e */
 }

 BiTree Point(BiTree T,TElemType s)
 { /* 返回二叉树T中指向元素值为s的结点的指针。另加 */
   LinkQueue q;
   QElemType a;
   if(T) /* 非空树 */
   {
     InitQueue(&q); /* 初始化队列 */
     EnQueue(&q,T); /* 根结点入队 */
     while(!QueueEmpty(q)) /* 队不空 */
     {
       DeQueue(&q,&a); /* 出队,队列元素赋给a */
       if(a->data==s)
         return a;
       if(a->lchild) /* 有左孩子 */
         EnQueue(&q,a->lchild); /* 入队左孩子 */
       if(a->rchild) /* 有右孩子 */
         EnQueue(&q,a->rchild); /* 入队右孩子 */
     }
   }
   return NULL;
 }

 TElemType LeftChild(BiTree T,TElemType e)
 { /* 初始条件: 二叉树T存在,e是T中某个结点 */
   /* 操作结果: 返回e的左孩子。若e无左孩子,则返回＂空＂ */
   BiTree a;
   if(T) /* 非空树 */
   {
     a=Point(T,e); /* a是结点e的指针 */
     if(a&&a->lchild) /* T中存在结点e且e存在左孩子 */
       return a->lchild->data; /* 返回e的左孩子的值 */
   }
   return Nil; /* 其余情况返回空 */
 }

 TElemType RightChild(BiTree T,TElemType e)
 { /* 初始条件: 二叉树T存在,e是T中某个结点 */
   /* 操作结果: 返回e的右孩子。若e无右孩子,则返回＂空＂ */
   BiTree a;
   if(T) /* 非空树 */
   {
     a=Point(T,e); /* a是结点e的指针 */
     if(a&&a->rchild) /* T中存在结点e且e存在右孩子 */
       return a->rchild->data; /* 返回e的右孩子的值 */
   }
   return Nil; /* 其余情况返回空 */
 }

 TElemType LeftSibling(BiTree T,TElemType e)
 { /* 初始条件: 二叉树T存在,e是T中某个结点 */
   /* 操作结果: 返回e的左兄弟。若e是T的左孩子或无左兄弟,则返回＂空＂ */
   TElemType a;
   BiTree p;
   if(T) /* 非空树 */
   {
     a=Parent(T,e); /* a为e的双亲 */
     p=Point(T,a); /* p为指向结点a的指针 */
     if(p->lchild&&p->rchild&&p->rchild->data==e) /* p存在左右孩子且右孩子是e */
       return p->lchild->data; /* 返回p的左孩子(e的左兄弟) */
   }
   return Nil; /* 树空或没找到e的左兄弟 */
 }

 TElemType RightSibling(BiTree T,TElemType e)
 { /* 初始条件: 二叉树T存在,e是T中某个结点 */
   /* 操作结果: 返回e的右兄弟。若e是T的右孩子或无右兄弟,则返回＂空＂ */
   TElemType a;
   BiTree p;
   if(T) /* 非空树 */
   {
     a=Parent(T,e); /* a为e的双亲 */
     p=Point(T,a); /* p为指向结点a的指针 */
     if(p->lchild&&p->rchild&&p->lchild->data==e) /* p存在左右孩子且左孩子是e */
       return p->rchild->data; /* 返回p的右孩子(e的右兄弟) */
   }
   return Nil; /* 树空或没找到e的右兄弟 */
 }

 Status InsertChild(BiTree p,int LR,BiTree c) /* 形参T无用 */
 { /* 初始条件: 二叉树T存在,p指向T中某个结点,LR为0或1,非空二叉树c与T */
   /*           不相交且右子树为空 */
   /* 操作结果: 根据LR为0或1,插入c为T中p所指结点的左或右子树。p所指结点的 */
   /*           原有左或右子树则成为c的右子树 */
   if(p) /* p不空 */
   {
     if(LR==0)
     {
       c->rchild=p->lchild;
       p->lchild=c;
     }
     else /* LR==1 */
     {
       c->rchild=p->rchild;
       p->rchild=c;
     }
     return OK;
   }
   return ERROR; /* p空 */
 }

 Status DeleteChild(BiTree p,int LR) /* 形参T无用 */
 { /* 初始条件: 二叉树T存在,p指向T中某个结点,LR为0或1 */
   /* 操作结果: 根据LR为0或1,删除T中p所指结点的左或右子树 */
   if(p) /* p不空 */
   {
     if(LR==0) /* 删除左子树 */
       ClearBiTree(&p->lchild);
     else /* 删除右子树 */
       ClearBiTree(&p->rchild);
     return OK;
   }
   return ERROR; /* p空 */
 }

 void PreOrderTraverse(BiTree T,Status(*Visit)(TElemType))
 { /* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数。算法6.1，有改动 */
   /* 操作结果: 先序递归遍历T,对每个结点调用函数Visit一次且仅一次 */
   if(T) /* T不空 */
   {
     Visit(T->data); /* 先访问根结点 */
     PreOrderTraverse(T->lchild,Visit); /* 再先序遍历左子树 */
     PreOrderTraverse(T->rchild,Visit); /* 最后先序遍历右子树 */
   }
 }

 void InOrderTraverse(BiTree T,Status(*Visit)(TElemType))
 { /* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
   /* 操作结果: 中序递归遍历T,对每个结点调用函数Visit一次且仅一次 */
   if(T)
   {
     InOrderTraverse(T->lchild,Visit); /* 先中序遍历左子树 */
     Visit(T->data); /* 再访问根结点 */
     InOrderTraverse(T->rchild,Visit); /* 最后中序遍历右子树 */
   }
 }

 typedef BiTree SElemType; /* 设栈元素为二叉树的指针类型 */
 #include"c3-1.h"
 #include"bo3-1.c"
 Status InOrderTraverse1(BiTree T,Status(*Visit)(TElemType))
 { /* 采用二叉链表存储结构，Visit是对数据元素操作的应用函数。算法6.3 */
   /* 中序遍历二叉树T的非递归算法(利用栈)，对每个数据元素调用函数Visit */
   SqStack S;
   InitStack(&S);
   while(T||!StackEmpty(S))
   {
     if(T)
     { /* 根指针进栈,遍历左子树 */
       Push(&S,T);
       T=T->lchild;
     }
     else
     { /* 根指针退栈,访问根结点,遍历右子树 */
       Pop(&S,&T);
       if(!Visit(T->data))
         return ERROR;
       T=T->rchild;
     }
   }
   printf("\n");
   return OK;
 }

 Status InOrderTraverse2(BiTree T,Status(*Visit)(TElemType))
 { /* 采用二叉链表存储结构，Visit是对数据元素操作的应用函数。算法6.2 */
   /* 中序遍历二叉树T的非递归算法(利用栈)，对每个数据元素调用函数Visit */
   SqStack S;
   BiTree p;
   InitStack(&S);
   Push(&S,T); /* 根指针进栈 */
   while(!StackEmpty(S))
   {
     while(GetTop(S,&p)&&p)
       Push(&S,p->lchild); /* 向左走到尽头 */
     Pop(&S,&p); /* 空指针退栈 */
     if(!StackEmpty(S))
     { /* 访问结点,向右一步 */
       Pop(&S,&p);
       if(!Visit(p->data))
         return ERROR;
       Push(&S,p->rchild);
     }
   }
   printf("\n");
   return OK;
 }

 void PostOrderTraverse(BiTree T,Status(*Visit)(TElemType))
 { /* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
   /* 操作结果: 后序递归遍历T,对每个结点调用函数Visit一次且仅一次 */
   if(T) /* T不空 */
   {
     PostOrderTraverse(T->lchild,Visit); /* 先后序遍历左子树 */
     PostOrderTraverse(T->rchild,Visit); /* 再后序遍历右子树 */
     Visit(T->data); /* 最后访问根结点 */
   }
 }

 void LevelOrderTraverse(BiTree T,Status(*Visit)(TElemType))
 { /* 初始条件：二叉树T存在,Visit是对结点操作的应用函数 */
   /* 操作结果：层序递归遍历T(利用队列),对每个结点调用函数Visit一次且仅一次 */
   LinkQueue q;
   QElemType a;
   if(T)
   {
     InitQueue(&q);
     EnQueue(&q,T);
     while(!QueueEmpty(q))
     {
       DeQueue(&q,&a);
       Visit(a->data);
       if(a->lchild!=NULL)
         EnQueue(&q,a->lchild);
       if(a->rchild!=NULL)
         EnQueue(&q,a->rchild);
     }
     printf("\n");
   }
 }

**********BO6-3.c**********
 /* bo6-3.c 二叉树的二叉线索存储(存储结构由c6-3.h定义)的基本操作 */
 Status CreateBiThrTree(BiThrTree *T)
 { /* 按先序输入二叉线索树中结点的值,构造二叉线索树T */
   /* 0(整型)/空格(字符型)表示空结点 */
   TElemType h;
 #if CHAR
   scanf("%c",&h);
 #else
   scanf("%d",&h);
 #endif
   if(h==Nil)
     *T=NULL;
   else
   {
     *T=(BiThrTree)malloc(sizeof(BiThrNode));
     if(!*T)
       exit(OVERFLOW);
     (*T)->data=h; /* 生成根结点(先序) */
     CreateBiThrTree(&(*T)->lchild); /* 递归构造左子树 */
     if((*T)->lchild) /* 有左孩子 */
       (*T)->LTag=Link;
     CreateBiThrTree(&(*T)->rchild); /* 递归构造右子树 */
     if((*T)->rchild) /* 有右孩子 */
       (*T)->RTag=Link;
   }
   return OK;
 }

 BiThrTree pre; /* 全局变量,始终指向刚刚访问过的结点 */
 void InThreading(BiThrTree p)
 { /* 中序遍历进行中序线索化。算法6.7 */
   if(p)
   {
     InThreading(p->lchild); /* 递归左子树线索化 */
     if(!p->lchild) /* 没有左孩子 */
     {
       p->LTag=Thread; /* 前驱线索 */
       p->lchild=pre; /* 左孩子指针指向前驱 */
     }
     if(!pre->rchild) /* 前驱没有右孩子 */
     {
       pre->RTag=Thread; /* 后继线索 */
       pre->rchild=p; /* 前驱右孩子指针指向后继(当前结点p) */
     }
     pre=p; /* 保持pre指向p的前驱 */
     InThreading(p->rchild); /* 递归右子树线索化 */
   }
 }

 Status InOrderThreading(BiThrTree *Thrt,BiThrTree T)
 { /* 中序遍历二叉树T,并将其中序线索化,Thrt指向头结点。算法6.6 */
   *Thrt=(BiThrTree)malloc(sizeof(BiThrNode));
   if(!*Thrt)
     exit(OVERFLOW);
   (*Thrt)->LTag=Link; /* 建头结点 */
   (*Thrt)->RTag=Thread;
   (*Thrt)->rchild=*Thrt; /* 右指针回指 */
   if(!T) /* 若二叉树空，则左指针回指 */
     (*Thrt)->lchild=*Thrt;
   else
   {
     (*Thrt)->lchild=T;
     pre=*Thrt;
     InThreading(T); /* 中序遍历进行中序线索化 */
     pre->rchild=*Thrt;
     pre->RTag=Thread; /* 最后一个结点线索化 */
     (*Thrt)->rchild=pre;
   }
   return OK;
 }

 Status InOrderTraverse_Thr(BiThrTree T,Status(*Visit)(TElemType))
 { /* 中序遍历二叉线索树T(头结点)的非递归算法。算法6.5 */
   BiThrTree p;
   p=T->lchild; /* p指向根结点 */
   while(p!=T)
   { /* 空树或遍历结束时,p==T */
     while(p->LTag==Link)
       p=p->lchild;
     if(!Visit(p->data)) /* 访问其左子树为空的结点 */
       return ERROR;
     while(p->RTag==Thread&&p->rchild!=T)
     {
       p=p->rchild;
       Visit(p->data); /* 访问后继结点 */
     }
     p=p->rchild;
   }
   return OK;
 }

**********Bo6-4.c**********
 /* bo6-4.c 树的双亲表存储(存储结构由c6-4.h定义)的基本操作(14个) */
 Status InitTree(PTree *T)
 { /* 操作结果: 构造空树T */
   (*T).n=0;
   return OK;
 }

 void DestroyTree()
 { /* 由于PTree是定长类型,无法销毁 */
 }

 typedef struct
 {
   int num;
   TElemType name;
 }QElemType; /* 定义队列元素类型 */
 #include"c3-2.h" /* 定义LinkQueue类型 */
 #include"bo3-2.c" /* LinkQueue类型的基本操作 */
 Status CreateTree(PTree *T)
 { /* 操作结果: 构造树T */
   LinkQueue q;
   QElemType p,qq;
   int i=1,j,l;
   char c[MAX_TREE_SIZE]; /* 临时存放孩子结点数组 */
   InitQueue(&q); /* 初始化队列 */
   printf("请输入根结点(字符型,空格为空): ");
   scanf("%c%*c",&(*T).nodes[0].data); /* 根结点序号为0,%*c吃掉回车符 */
   if((*T).nodes[0].data!=Nil) /* 非空树 */
   {
     (*T).nodes[0].parent=-1; /* 根结点无双亲 */
     qq.name=(*T).nodes[0].data;
     qq.num=0;
     EnQueue(&q,qq); /* 入队此结点 */
     while(i<MAX_TREE_SIZE&&!QueueEmpty(q)) /* 数组未满且队不空 */
     {
       DeQueue(&q,&qq); /* 出队一个结点 */
       printf("请按长幼顺序输入结点%c的所有孩子: ",qq.name);
       gets(c);
       l=strlen(c);
       for(j=0;j<l;j++)
       {
         (*T).nodes[i].data=c[j];
         (*T).nodes[i].parent=qq.num;
         p.name=c[j];
         p.num=i;
         EnQueue(&q,p); /* 入队此结点 */
         i++;
       }
     }
     if(i>MAX_TREE_SIZE)
     {
       printf("结点数超过数组容量\n");
       exit(OVERFLOW);
     }
     (*T).n=i;
   }
   else
     (*T).n=0;
   return OK;
 }

 #define ClearTree InitTree /* 二者操作相同 */

 Status TreeEmpty(PTree T)
 { /* 初始条件: 树T存在。操作结果: 若T为空树,则返回TRUE,否则返回FALSE */
   if(T.n)
     return FALSE;
   else
     return TRUE;
 }

 int TreeDepth(PTree T)
 { /* 初始条件: 树T存在。操作结果: 返回T的深度 */
   int k,m,def,max=0;
   for(k=0;k<T.n;++k)
   {
     def=1; /* 初始化本际点的深度 */
     m=T.nodes[k].parent;
     while(m!=-1)
     {
       m=T.nodes[m].parent;
       def++;
     }
     if(max<def)
       max=def;
   }
   return max; /* 最大深度 */
 }

 TElemType Root(PTree T)
 { /* 初始条件: 树T存在。操作结果: 返回T的根 */
   int i;
   for(i=0;i<T.n;i++)
     if(T.nodes[i].parent<0)
       return T.nodes[i].data;
   return Nil;
 }

 TElemType Value(PTree T,int i)
 { /* 初始条件: 树T存在,i是树T中结点的序号。操作结果: 返回第i个结点的值 */
   if(i<T.n)
     return T.nodes[i].data;
   else
     return Nil;
 }

 Status Assign(PTree *T,TElemType cur_e,TElemType value)
 { /* 初始条件: 树T存在,cur_e是树T中结点的值。操作结果: 改cur_e为value */
   int j;
   for(j=0;j<(*T).n;j++)
   {
     if((*T).nodes[j].data==cur_e)
     {
       (*T).nodes[j].data=value;
       return OK;
     }
   }
   return ERROR;
 }

 TElemType Parent(PTree T,TElemType cur_e)
 { /* 初始条件: 树T存在,cur_e是T中某个结点 */
   /* 操作结果: 若cur_e是T的非根结点,则返回它的双亲,否则函数值为＂空＂ */
   int j;
   for(j=1;j<T.n;j++) /* 根结点序号为0 */
     if(T.nodes[j].data==cur_e)
       return T.nodes[T.nodes[j].parent].data;
   return Nil;
 }

 TElemType LeftChild(PTree T,TElemType cur_e)
 { /* 初始条件: 树T存在,cur_e是T中某个结点 */
   /* 操作结果: 若cur_e是T的非叶子结点,则返回它的最左孩子,否则返回＂空＂ */
   int i,j;
   for(i=0;i<T.n;i++)
     if(T.nodes[i].data==cur_e) /* 找到cur_e,其序号为i */
       break;
   for(j=i+1;j<T.n;j++) /* 根据树的构造函数,孩子的序号＞其双亲的序号 */
     if(T.nodes[j].parent==i) /* 根据树的构造函数,最左孩子(长子)的序号＜其它孩子的序号 */
       return T.nodes[j].data;
   return Nil;
 }

 TElemType RightSibling(PTree T,TElemType cur_e)
 { /* 初始条件: 树T存在,cur_e是T中某个结点 */
   /* 操作结果: 若cur_e有右(下一个)兄弟,则返回它的右兄弟,否则返回＂空＂ */
   int i;
   for(i=0;i<T.n;i++)
     if(T.nodes[i].data==cur_e) /* 找到cur_e,其序号为i */
       break;
   if(T.nodes[i+1].parent==T.nodes[i].parent)
   /* 根据树的构造函数,若cur_e有右兄弟的话则右兄弟紧接其后 */
     return T.nodes[i+1].data;
   return Nil;
 }

 Status Print(PTree T)
 { /* 输出树T。加 */
   int i;
   printf("结点个数=%d\n",T.n);
   printf(" 结点 双亲\n");
   for(i=0;i<T.n;i++)
   {
     printf("    %c",Value(T,i)); /* 结点 */
     if(T.nodes[i].parent>=0) /* 有双亲 */
       printf("    %c",Value(T,T.nodes[i].parent)); /* 双亲 */
     printf("\n");
   }
   return OK;
 }

 Status InsertChild(PTree *T,TElemType p,int i,PTree c)
 { /* 初始条件: 树T存在,p是T中某个结点,1≤i≤p所指结点的度+1,非空树c与T不相交 */
   /* 操作结果: 插入c为T中p结点的第i棵子树 */
   int j,k,l,f=1,n=0; /* 设交换标志f的初值为1,p的孩子数n的初值为0 */
   PTNode t;
   if(!TreeEmpty(*T)) /* T不空 */
   {
     for(j=0;j<(*T).n;j++) /* 在T中找p的序号 */
       if((*T).nodes[j].data==p) /* p的序号为j */
         break;
     l=j+1; /* 如果c是p的第1棵子树,则插在j+1处 */
     if(i>1) /* c不是p的第1棵子树 */
     {
       for(k=j+1;k<(*T).n;k++) /* 从j+1开始找p的前i-1个孩子 */
         if((*T).nodes[k].parent==j) /* 当前结点是p的孩子 */
         {
           n++; /* 孩子数加1 */
           if(n==i-1) /* 找到p的第i-1个孩子,其序号为k1 */
             break;
         }
       l=k+1; /* c插在k+1处 */
     } /* p的序号为j,c插在l处 */
     if(l<(*T).n) /* 插入点l不在最后 */
       for(k=(*T).n-1;k>=l;k--) /* 依次将序号l以后的结点向后移c.n个位置 */
       {
         (*T).nodes[k+c.n]=(*T).nodes[k];
         if((*T).nodes[k].parent>=l)
           (*T).nodes[k+c.n].parent+=c.n;
       }
     for(k=0;k<c.n;k++)
     {
       (*T).nodes[l+k].data=c.nodes[k].data; /* 依次将树c的所有结点插于此处 */
       (*T).nodes[l+k].parent=c.nodes[k].parent+l;
     }
     (*T).nodes[l].parent=j; /* 树c的根结点的双亲为p */
     (*T).n+=c.n; /* 树T的结点数加c.n个 */
     while(f)
     { /* 从插入点之后,将结点仍按层序排列 */
       f=0; /* 交换标志置0 */
       for(j=l;j<(*T).n-1;j++)
         if((*T).nodes[j].parent>(*T).nodes[j+1].parent)
         {/* 如果结点j的双亲排在结点j+1的双亲之后(树没有按层序排列),交换两结点*/
           t=(*T).nodes[j];
           (*T).nodes[j]=(*T).nodes[j+1];
           (*T).nodes[j+1]=t;
           f=1; /* 交换标志置1 */
           for(k=j;k<(*T).n;k++) /* 改变双亲序号 */
             if((*T).nodes[k].parent==j)
               (*T).nodes[k].parent++; /* 双亲序号改为j+1 */
             else if((*T).nodes[k].parent==j+1)
               (*T).nodes[k].parent--; /* 双亲序号改为j */
         }
     }
     return OK;
   }
   else /* 树T不存在 */
     return ERROR;
 }

 Status deleted[MAX_TREE_SIZE+1]; /* 删除标志数组(全局量) */
 void DeleteChild(PTree *T,TElemType p,int i)
 { /* 初始条件: 树T存在,p是T中某个结点,1≤i≤p所指结点的度 */
   /* 操作结果: 删除T中结点p的第i棵子树 */
   int j,k,n=0;
   LinkQueue q;
   QElemType pq,qq;
   for(j=0;j<=(*T).n;j++)
     deleted[j]=0; /* 置初值为0(不删除标记) */
   pq.name='a'; /* 此成员不用 */
   InitQueue(&q); /* 初始化队列 */
   for(j=0;j<(*T).n;j++)
     if((*T).nodes[j].data==p)
       break; /* j为结点p的序号 */
   for(k=j+1;k<(*T).n;k++)
   {
     if((*T).nodes[k].parent==j)
       n++;
     if(n==i)
       break; /* k为p的第i棵子树结点的序号 */
   }
   if(k<(*T).n) /* p的第i棵子树结点存在 */
   {
     n=0;
     pq.num=k;
     deleted[k]=1; /* 置删除标记 */
     n++;
     EnQueue(&q,pq);
     while(!QueueEmpty(q))
     {
       DeQueue(&q,&qq);
       for(j=qq.num+1;j<(*T).n;j++)
         if((*T).nodes[j].parent==qq.num)
         {
           pq.num=j;
           deleted[j]=1; /* 置删除标记 */
           n++;
           EnQueue(&q,pq);
         }
     }
     for(j=0;j<(*T).n;j++)
       if(deleted[j]==1)
       {
         for(k=j+1;k<=(*T).n;k++)
         {
           deleted[k-1]=deleted[k];
           (*T).nodes[k-1]=(*T).nodes[k];
           if((*T).nodes[k].parent>j)
             (*T).nodes[k-1].parent--;
         }
         j--;
       }
     (*T).n-=n; /* n为待删除结点数 */
   }
 }

 void TraverseTree(PTree T,void(*Visit)(TElemType))
 { /* 初始条件:二叉树T存在,Visit是对结点操作的应用函数 */
   /* 操作结果:层序遍历树T,对每个结点调用函数Visit一次且仅一次 */
   int i;
   for(i=0;i<T.n;i++)
     Visit(T.nodes[i].data);
   printf("\n");
 }

**********Bo6-5.c**********
 /* bo6-5.c 树的二叉链表(孩子－兄弟)存储(存储结构由c6-5.h定义)的基本操作(17个) */
 Status InitTree(CSTree *T)
 { /* 操作结果: 构造空树T */
   *T=NULL;
   return OK;
 }

 void DestroyTree(CSTree *T)
 { /* 初始条件: 树T存在。操作结果: 销毁树T */
   if(*T)
   {
     if((*T)->firstchild) /* T有长子 */
       DestroyTree(&(*T)->firstchild); /* 销毁T的长子为根结点的子树 */
     if((*T)->nextsibling) /* T有下一个兄弟 */
       DestroyTree(&(*T)->nextsibling); /* 销毁T的下一个兄弟为根结点的子树 */
     free(*T); /* 释放根结点 */
     *T=NULL;
   }
 }

 typedef CSTree QElemType; /* 定义队列元素类型 */
 #include"c3-2.h" /* 定义LinkQueue类型 */
 #include"bo3-2.c" /* LinkQueue类型的基本操作 */
 Status CreateTree(CSTree *T)
 { /* 构造树T */
   char c[20]; /* 临时存放孩子结点(设不超过20个)的值 */
   CSTree p,p1;
   LinkQueue q;
   int i,l;
   InitQueue(&q);
   printf("请输入根结点(字符型,空格为空): ");
   scanf("%c%*c",&c[0]);
   if(c[0]!=Nil) /* 非空树 */
   {
     *T=(CSTree)malloc(sizeof(CSNode)); /* 建立根结点 */
     (*T)->data=c[0];
     (*T)->nextsibling=NULL;
     EnQueue(&q,*T); /* 入队根结点的指针 */
     while(!QueueEmpty(q)) /* 队不空 */
     {
       DeQueue(&q,&p); /* 出队一个结点的指针 */
       printf("请按长幼顺序输入结点%c的所有孩子: ",p->data);
       gets(c);
       l=strlen(c);
       if(l>0) /* 有孩子 */
       {
         p1=p->firstchild=(CSTree)malloc(sizeof(CSNode)); /* 建立长子结点 */
         p1->data=c[0];
         for(i=1;i<l;i++)
         {
           p1->nextsibling=(CSTree)malloc(sizeof(CSNode)); /* 建立下一个兄弟结点 */
           EnQueue(&q,p1); /* 入队上一个结点 */
           p1=p1->nextsibling;
           p1->data=c[i];
         }
         p1->nextsibling=NULL;
         EnQueue(&q,p1); /* 入队最后一个结点 */
       }
       else
         p->firstchild=NULL;
     }
   }
   else
     *T=NULL;
   return OK;
 }

 #define ClearTree DestroyTree /* 二者操作相同 */

 Status TreeEmpty(CSTree T)
 { /* 初始条件: 树T存在。操作结果: 若T为空树,则返回TURE,否则返回FALSE */
   if(T) /* T不空 */
     return FALSE;
   else
     return TRUE;
 }

 int TreeDepth(CSTree T)
 { /* 初始条件: 树T存在。操作结果: 返回T的深度 */
   CSTree p;
   int depth,max=0;
   if(!T) /* 树空 */
     return 0;
   if(!T->firstchild) /* 树无长子 */
     return 1;
   for(p=T->firstchild;p;p=p->nextsibling)
   {
     depth=TreeDepth(p);
     if(depth>max)
       max=depth;
   }
   return max+1;
 }

 TElemType Value(CSTree p)
 { /* 返回p所指结点的值 */
   return p->data;
 }

 TElemType Root(CSTree T)
 { /* 初始条件: 树T存在。操作结果: 返回T的根 */
   if(T)
     return Value(T);
   else
     return Nil;
 }

 CSTree Point(CSTree T,TElemType s)
 { /* 返回二叉链表(孩子－兄弟)树T中指向元素值为s的结点的指针。另加 */
   LinkQueue q;
   QElemType a;
   if(T) /* 非空树 */
   {
     InitQueue(&q); /* 初始化队列 */
     EnQueue(&q,T); /* 根结点入队 */
     while(!QueueEmpty(q)) /* 队不空 */
     {
       DeQueue(&q,&a); /* 出队,队列元素赋给a */
       if(a->data==s)
	 return a;
       if(a->firstchild) /* 有长子 */
         EnQueue(&q,a->firstchild); /* 入队长子 */
       if(a->nextsibling) /* 有下一个兄弟 */
         EnQueue(&q,a->nextsibling); /* 入队下一个兄弟 */
     }
   }
   return NULL;
 }

 Status Assign(CSTree *T,TElemType cur_e,TElemType value)
 { /* 初始条件: 树T存在,cur_e是树T中结点的值。操作结果: 改cur_e为value */
   CSTree p;
   if(*T) /* 非空树 */
   {
     p=Point(*T,cur_e); /* p为cur_e的指针 */
     if(p) /* 找到cur_e */
     {
       p->data=value; /* 赋新值 */
       return OK;
     }
   }
   return Nil; /* 树空或没找到 */
 }

 TElemType Parent(CSTree T,TElemType cur_e)
 { /* 初始条件: 树T存在,cur_e是T中某个结点 */
   /* 操作结果: 若cur_e是T的非根结点,则返回它的双亲,否则函数值为＂空＂ */
   CSTree p,t;
   LinkQueue q;
   InitQueue(&q);
   if(T) /* 树非空 */
   {
     if(Value(T)==cur_e) /* 根结点值为cur_e */
       return Nil;
     EnQueue(&q,T); /* 根结点入队 */
     while(!QueueEmpty(q))
     {
       DeQueue(&q,&p);
       if(p->firstchild) /* p有长子 */
       {
         if(p->firstchild->data==cur_e) /* 长子为cur_e */
           return Value(p); /* 返回双亲 */
         t=p; /* 双亲指针赋给t */
         p=p->firstchild; /* p指向长子 */
         EnQueue(&q,p); /* 入队长子 */
         while(p->nextsibling) /* 有下一个兄弟 */
         {
           p=p->nextsibling; /* p指向下一个兄弟 */
	   if(Value(p)==cur_e) /* 下一个兄弟为cur_e */
	     return Value(t); /* 返回双亲 */
	   EnQueue(&q,p); /* 入队下一个兄弟 */
	 }
       }
     }
   }
   return Nil; /* 树空或没找到cur_e */
 }

 TElemType LeftChild(CSTree T,TElemType cur_e)
 { /* 初始条件: 树T存在,cur_e是T中某个结点 */
   /* 操作结果: 若cur_e是T的非叶子结点,则返回它的最左孩子,否则返回＂空＂ */
   CSTree f;
   f=Point(T,cur_e); /* f指向结点cur_e */
   if(f&&f->firstchild) /* 找到结点cur_e且结点cur_e有长子 */
     return f->firstchild->data;
   else
     return Nil;
 }

 TElemType RightSibling(CSTree T,TElemType cur_e)
 { /* 初始条件: 树T存在,cur_e是T中某个结点 */
   /* 操作结果: 若cur_e有右兄弟,则返回它的右兄弟,否则返回＂空＂ */
   CSTree f;
   f=Point(T,cur_e); /* f指向结点cur_e */
   if(f&&f->nextsibling) /* 找到结点cur_e且结点cur_e有右兄弟 */
     return f->nextsibling->data;
   else
     return Nil; /* 树空 */
 }

 Status InsertChild(CSTree *T,CSTree p,int i,CSTree c)
 { /* 初始条件: 树T存在,p指向T中某个结点,1≤i≤p所指结点的度+1,非空树c与T不相交 */
   /* 操作结果: 插入c为T中p结点的第i棵子树 */
   /* 因为p所指结点的地址不会改变，故p不需是引用类型 */
   int j;
   if(*T) /* T不空 */
   {
     if(i==1) /* 插入c为p的长子 */
     {
       c->nextsibling=p->firstchild; /* p的原长子现是c的下一个兄弟(c本无兄弟) */
       p->firstchild=c;
     }
     else /* 找插入点 */
     {
       p=p->firstchild; /* 指向p的长子 */
       j=2;
       while(p&&j<i)
       {
         p=p->nextsibling;
         j++;
       }
       if(j==i) /* 找到插入位置 */
       {
         c->nextsibling=p->nextsibling;
         p->nextsibling=c;
       }
       else /* p原有孩子数小于i-1 */
         return ERROR;
     }
     return OK;
   }
   else /* T空 */
     return ERROR;
 }

 Status DeleteChild(CSTree *T,CSTree p,int i)
 { /* 初始条件: 树T存在,p指向T中某个结点,1≤i≤p所指结点的度 */
   /* 操作结果: 删除T中p所指结点的第i棵子树 */
   /* 因为p所指结点的地址不会改变，故p不需是引用类型 */
   CSTree b;
   int j;
   if(*T) /* T不空 */
   {
     if(i==1) /* 删除长子 */
     {
       b=p->firstchild;
       p->firstchild=b->nextsibling; /* p的原次子现是长子 */
       b->nextsibling=NULL;
       DestroyTree(&b);
     }
     else /* 删除非长子 */
     {
       p=p->firstchild; /* p指向长子 */
       j=2;
       while(p&&j<i)
       {
         p=p->nextsibling;
         j++;
       }
       if(j==i) /* 找到第i棵子树 */
       {
         b=p->nextsibling;
         p->nextsibling=b->nextsibling;
         b->nextsibling=NULL;
         DestroyTree(&b);
       }
       else /* p原有孩子数小于i */
         return ERROR;
     }
     return OK;
   }
   else
     return ERROR;
 }

 void PreOrderTraverse(CSTree T,void(*Visit)(TElemType))
 { /* 先根遍历孩子－兄弟二叉链表结构的树T */
   if(T)
   {
     Visit(Value(T)); /* 先访问根结点 */
     PreOrderTraverse(T->firstchild,Visit); /* 再先根遍历长子子树 */
     PreOrderTraverse(T->nextsibling,Visit); /* 最后先根遍历下一个兄弟子树 */
   }
 }

 void PostOrderTraverse(CSTree T,void(*Visit)(TElemType))
 { /* 后根遍历孩子－兄弟二叉链表结构的树T */
   CSTree p;
   if(T)
   {
     if(T->firstchild) /* 有长子 */
     {
       PostOrderTraverse(T->firstchild,Visit); /* 后根遍历长子子树 */
       p=T->firstchild->nextsibling; /* p指向长子的下一个兄弟 */
       while(p)
       {
         PostOrderTraverse(p,Visit); /* 后根遍历下一个兄弟子树 */
         p=p->nextsibling; /* p指向再下一个兄弟 */
       }
     }
     Visit(Value(T)); /* 最后访问根结点 */
   }
 }

 void LevelOrderTraverse(CSTree T,void(*Visit)(TElemType))
 { /* 层序遍历孩子－兄弟二叉链表结构的树T */
   CSTree p;
   LinkQueue q;
   InitQueue(&q);
   if(T)
   {
     Visit(Value(T)); /* 先访问根结点 */
     EnQueue(&q,T); /* 入队根结点的指针 */
     while(!QueueEmpty(q)) /* 队不空 */
     {
       DeQueue(&q,&p); /* 出队一个结点的指针 */
       if(p->firstchild) /* 有长子 */
       {
         p=p->firstchild;
         Visit(Value(p)); /* 访问长子结点 */
         EnQueue(&q,p); /* 入队长子结点的指针 */
         while(p->nextsibling) /* 有下一个兄弟 */
         {
           p=p->nextsibling;
           Visit(Value(p)); /* 访问下一个兄弟 */
           EnQueue(&q,p); /* 入队兄弟结点的指针 */
         }
       }
     }
   }
 }

**********bo6-6.c**********
 /* bo6-6.c 二叉树的三叉链表存储(存储结构由c6-7.h定义)的基本操作(21个) */
 Status InitBiTree(BiPTree *T)
 { /* 操作结果: 构造空二叉树T */
   *T=NULL;
   return OK;
 }

 void DestroyBiTree(BiPTree *T)
 { /* 初始条件: 二叉树T存在。操作结果: 销毁二叉树T */
   if(*T) /* 非空树 */
   {
     if((*T)->lchild) /* 有左孩子 */
       DestroyBiTree(&(*T)->lchild); /* 销毁左孩子子树 */
     if((*T)->rchild) /* 有右孩子 */
       DestroyBiTree(&(*T)->rchild); /* 销毁右孩子子树 */
     free(*T); /* 释放根结点 */
     *T=NULL; /* 空指针赋0 */
   }
 }

 void Create(BiPTree *T) /* CreateBiTree()调用 */
 { /* 按先序次序输入二叉树中结点的值（可为字符型或整型，在主程中定义）， */
   /* 构造仅缺双亲指针的三叉链表表示的二叉树T。变量Nil表示空（子）树 */
   TElemType ch;
 #ifdef CHAR
   scanf("%c",&ch);
 #endif
 #ifdef INT
   scanf("%d",&ch);
 #endif
   if(ch==Nil) /* 空 */
     *T=NULL;
   else
   {
     *T=(BiPTree)malloc(sizeof(BiTPNode));
     if(!*T)
       exit(OVERFLOW);
     (*T)->data=ch; /* 生成根结点 */
     Create(&(*T)->lchild); /* 构造左子树 */
     Create(&(*T)->rchild); /* 构造右子树 */
   }
 }

 typedef BiPTree QElemType; /* 设队列元素为二叉树的指针类型 */
 #include"c3-2.h"
 #include"bo3-2.c"
 Status CreateBiTree(BiPTree *T)
 { /* 按先序次序输入二叉树中结点的值（可为字符型或整型，在主程中定义）， */
   /* 构造三叉链表表示的二叉树T */
   LinkQueue q;
   QElemType a;
   Create(T); /* 构造二叉树(缺双亲指针) */
   if(*T) /* 非空树 */
   {
     (*T)->parent=NULL; /* 根结点的双亲为＂空＂ */
     InitQueue(&q); /* 初始化队列 */
     EnQueue(&q,*T); /* 根指针入队 */
     while(!QueueEmpty(q)) /* 队不空 */
     {
       DeQueue(&q,&a); /* 出队,队列元素赋给a */
       if(a->lchild) /* 有左孩子 */
       {
         a->lchild->parent=a; /* 给左孩子的双亲指针赋值 */
         EnQueue(&q,a->lchild); /* 左孩子入队 */
       }
       if(a->rchild) /* 有右孩子 */
       {
	 a->rchild->parent=a; /* 给右孩子的双亲指针赋值 */
         EnQueue(&q,a->rchild); /* 右孩子入队 */
       }
     }
   }
   return OK;
 }

 #define ClearBiTree DestroyBiTree

 Status BiTreeEmpty(BiPTree T)
 { /* 初始条件: 二叉树T存在。操作结果: 若T为空二叉树,则返回TRUE,否则FALSE */
   if(T)
     return FALSE;
   else
     return TRUE;
 }

 int BiTreeDepth(BiPTree T)
 { /* 初始条件: 二叉树T存在。操作结果: 返回T的深度 */
   int i,j;
   if(!T)
     return 0;
   if(T->lchild)
     i=BiTreeDepth(T->lchild);
   else
     i=0;
   if(T->rchild)
     j=BiTreeDepth(T->rchild);
   else
     j=0;
   return i>j?i+1:j+1;
 }

 TElemType Root(BiPTree T)
 { /* 初始条件: 二叉树T存在。操作结果: 返回T的根 */
   if(T)
     return T->data;
   else
     return Nil;
 }

 TElemType Value(BiPTree p)
 { /* 初始条件: 二叉树T存在，p指向T中某个结点 */
   /* 操作结果: 返回p所指结点的值 */
   return p->data;
 }

 void Assign(BiPTree p,TElemType value)
 { /* 给p所指结点赋值为value */
   p->data=value;
 }

 BiPTree Point(BiPTree T,TElemType e)
 { /* 返回二叉树T中指向元素值为e的结点的指针。加 */
   LinkQueue q;
   QElemType a;
   if(T) /* 非空树 */
   {
     InitQueue(&q); /* 初始化队列 */
     EnQueue(&q,T); /* 根结点入队 */
     while(!QueueEmpty(q)) /* 队不空 */
     {
       DeQueue(&q,&a); /* 出队,队列元素赋给a */
       if(a->data==e)
         return a;
       if(a->lchild) /* 有左孩子 */
         EnQueue(&q,a->lchild); /* 入队左孩子 */
       if(a->rchild) /* 有右孩子 */
         EnQueue(&q,a->rchild); /* 入队右孩子 */
     }
   }
   return NULL;
 }

 TElemType Parent(BiPTree T,TElemType e)
 { /* 初始条件: 二叉树T存在,e是T中某个结点 */
   /* 操作结果: 若e是T的非根结点,则返回它的双亲,否则返回＂空＂ */
   BiPTree a;
   if(T) /* 非空树 */
   {
     a=Point(T,e); /* a是结点e的指针 */
     if(a&&a!=T) /* T中存在结点e且e是非根结点 */
       return a->parent->data; /* 返回e的双亲的值 */
   }
   return Nil; /* 其余情况返回空 */
 }

 TElemType LeftChild(BiPTree T,TElemType e)
 { /* 初始条件: 二叉树T存在,e是T中某个结点 */
   /* 操作结果: 返回e的左孩子。若e无左孩子,则返回＂空＂ */
   BiPTree a;
   if(T) /* 非空树 */
   {
     a=Point(T,e); /* a是结点e的指针 */
     if(a&&a->lchild) /* T中存在结点e且e存在左孩子 */
       return a->lchild->data; /* 返回e的左孩子的值 */
   }
   return Nil; /* 其余情况返回空 */
 }

 TElemType RightChild(BiPTree T,TElemType e)
 { /* 初始条件: 二叉树T存在,e是T中某个结点 */
   /* 操作结果: 返回e的右孩子。若e无右孩子,则返回＂空＂ */
   BiPTree a;
   if(T) /* 非空树 */
   {
     a=Point(T,e); /* a是结点e的指针 */
     if(a&&a->rchild) /* T中存在结点e且e存在右孩子 */
       return a->rchild->data; /* 返回e的右孩子的值 */
   }
   return Nil; /* 其余情况返回空 */
 }

 TElemType LeftSibling(BiPTree T,TElemType e)
 { /* 初始条件: 二叉树T存在,e是T中某个结点 */
   /* 操作结果: 返回e的左兄弟。若e是T的左孩子或无左兄弟,则返回＂空＂ */
   BiPTree a;
   if(T) /* 非空树 */
   {
     a=Point(T,e); /* a是结点e的指针 */
     if(a&&a!=T&&a->parent->lchild&&a->parent->lchild!=a) /* T中存在结点e且e存在左兄弟 */
       return a->parent->lchild->data; /* 返回e的左兄弟的值 */
   }
   return Nil; /* 其余情况返回空 */
 }

 TElemType RightSibling(BiPTree T,TElemType e)
 { /* 初始条件: 二叉树T存在,e是T中某个结点 */
   /* 操作结果: 返回e的右兄弟。若e是T的右孩子或无右兄弟,则返回＂空＂ */
   BiPTree a;
   if(T) /* 非空树 */
   {
     a=Point(T,e); /* a是结点e的指针 */
     if(a&&a!=T&&a->parent->rchild&&a->parent->rchild!=a) /* T中存在结点e且e存在右兄弟 */
       return a->parent->rchild->data; /* 返回e的右兄弟的值 */
   }
   return Nil; /* 其余情况返回空 */
 }

 Status InsertChild(BiPTree p,int LR,BiPTree c) /* 形参T无用 */
 { /* 初始条件: 二叉树T存在,p指向T中某个结点,LR为0或1,非空二叉树c与T */
   /*           不相交且右子树为空 */
   /* 操作结果: 根据LR为0或1,插入c为T中p所指结点的左或右子树。p所指结点 */
   /*           的原有左或右子树则成为c的右子树。 */
   if(p) /* p不空 */
   {
     if(LR==0)
     {
       c->rchild=p->lchild;
       if(c->rchild) /* c有右孩子(p原有左孩子) */
         c->rchild->parent=c;
       p->lchild=c;
       c->parent=p;
     }
     else /* LR==1 */
     {
       c->rchild=p->rchild;
       if(c->rchild) /* c有右孩子(p原有右孩子) */
         c->rchild->parent=c;
       p->rchild=c;
       c->parent=p;
     }
     return OK;
   }
   return ERROR; /* p空 */
 }

 Status DeleteChild(BiPTree p,int LR) /* 形参T无用 */
 { /* 初始条件: 二叉树T存在,p指向T中某个结点,LR为0或1 */
   /* 操作结果: 根据LR为0或1,删除T中p所指结点的左或右子树 */
   if(p) /* p不空 */
   {
     if(LR==0) /* 删除左子树 */
       ClearBiTree(&p->lchild);
     else /* 删除右子树 */
       ClearBiTree(&p->rchild);
     return OK;
   }
   return ERROR; /* p空 */
 }

 void PreOrderTraverse(BiPTree T,Status(*Visit)(BiPTree))
 { /* 先序递归遍历二叉树T */
   if(T)
   {
     Visit(T); /* 先访问根结点 */
     PreOrderTraverse(T->lchild,Visit); /* 再先序遍历左子树 */
     PreOrderTraverse(T->rchild,Visit); /* 最后先序遍历右子树 */
   }
 }

 void InOrderTraverse(BiPTree T,Status(*Visit)(BiPTree))
 { /* 中序递归遍历二叉树T */
   if(T)
   {
     InOrderTraverse(T->lchild,Visit); /* 中序遍历左子树 */
     Visit(T); /* 再访问根结点 */
     InOrderTraverse(T->rchild,Visit); /* 最后中序遍历右子树 */
   }
 }

 void PostOrderTraverse(BiPTree T,Status(*Visit)(BiPTree))
 { /* 后序递归遍历二叉树T */
   if(T)
   {
     PostOrderTraverse(T->lchild,Visit); /* 后序遍历左子树 */
     PostOrderTraverse(T->rchild,Visit); /* 后序遍历右子树 */
     Visit(T); /* 最后访问根结点 */
   }
 }

 void LevelOrderTraverse(BiPTree T,Status(*Visit)(BiPTree))
 { /* 层序遍历二叉树T(利用队列) */
   LinkQueue q;
   QElemType a;
   if(T)
   {
     InitQueue(&q);
     EnQueue(&q,T);
     while(!QueueEmpty(q))
     {
       DeQueue(&q,&a);
       Visit(a);
       if(a->lchild!=NULL)
         EnQueue(&q,a->lchild);
       if(a->rchild!=NULL)
         EnQueue(&q,a->rchild);
     }
   }
 }

**********C6-1.H**********
 /* c6-1.h 二叉树的顺序存储表示 */
 #define MAX_TREE_SIZE 100 /* 二叉树的最大结点数 */
 typedef TElemType SqBiTree[MAX_TREE_SIZE]; /* 0号单元存储根结点 */

 typedef struct
 {
   int level,order; /* 结点的层,本层序号(按满二叉树计算) */
 }position;

**********C6-2.H**********
 /* c6-2.h 二叉树的二叉链表存储表示 */
 typedef struct BiTNode
 {
   TElemType data;
   struct BiTNode *lchild,*rchild; /* 左右孩子指针 */
 }BiTNode,*BiTree;

**********C6-3.H**********
 /* c6-3.h 二叉树的二叉线索存储表示 */
 typedef enum{Link,Thread}PointerTag; /* Link(0):指针,Thread(1):线索 */
 typedef struct BiThrNode
 {
   TElemType data;
   struct BiThrNode *lchild,*rchild; /* 左右孩子指针 */
   PointerTag LTag,RTag; /* 左右标志 */
 }BiThrNode,*BiThrTree;
**********C6-4.H**********
 /* c6-4.h 树的双亲表存储表示 */
 #define MAX_TREE_SIZE 100
 typedef struct
 {
   TElemType data;
   int parent; /* 双亲位置域 */
 } PTNode;
 typedef struct
 {
   PTNode nodes[MAX_TREE_SIZE];
   int n; /* 结点数 */
 } PTree;

**********C6-5.H**********
 /* c6-5.h 树的二叉链表(孩子－兄弟)存储表示 */
 typedef struct CSNode
 {
   TElemType data;
   struct CSNode *firstchild,*nextsibling;
 }CSNode,*CSTree;

**********c6-6.h**********
 /* c6-6.h 二叉树的三叉链表存储表示 */
 typedef struct BiTPNode
 {
   TElemType data;
   struct BiTPNode *parent,*lchild,*rchild; /* 双亲、左右孩子指针 */
 }BiTPNode,*BiPTree;

**********c6-7.h**********
 /* c6-7.h 赫夫曼树和赫夫曼编码的存储表示 */
 typedef struct
 {
   unsigned int weight;
   unsigned int parent,lchild,rchild;
 }HTNode,*HuffmanTree; /* 动态分配数组存储赫夫曼树 */
 typedef char **HuffmanCode; /* 动态分配数组存储赫夫曼编码表 */

**********Main6-1.c**********
 /* main6-1.c 检验bo6-1.c的主程序，利用条件编译选择数据类型为char或int */
 /*#define CHAR 1 /* 字符型 */
 #define CHAR 0 /* 整型(二者选一) */
 #include"c1.h"
 #if CHAR
   typedef char TElemType;
   TElemType Nil=' '; /* 设字符型以空格符为空 */
 #else
   typedef int TElemType;
   TElemType Nil=0; /* 设整型以0为空 */
 #endif
 #include"c6-1.h"
 #include"bo6-1.c"

 Status visit(TElemType e)
 {
   printf("%d ",e);
   return OK;
 }

 void main()
 {
   Status i;
   int j;
   position p;
   TElemType e;
   SqBiTree T,s;
   InitBiTree(T);
   CreateBiTree(T);
   printf("建立二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
   i=Root(T,&e);
   if(i)
     printf("二叉树的根为：%d\n",e);
   else
     printf("树空，无根\n");
   printf("层序遍历二叉树:\n");
   LevelOrderTraverse(T,visit);
   printf("中序遍历二叉树:\n");
   InOrderTraverse(T,visit);
   printf("后序遍历二叉树:\n");
   PostOrderTraverse(T,visit);
   printf("请输入待修改结点的层号 本层序号: ");
   scanf("%d%d",&p.level,&p.order);
   e=Value(T,p);
   printf("待修改结点的原值为%d请输入新值: ",e);
   scanf("%d",&e);
   Assign(T,p,e);
   printf("先序遍历二叉树:\n");
   PreOrderTraverse(T,visit);
   printf("结点%d的双亲为%d,左右孩子分别为",e,Parent(T,e));
   printf("%d,%d,左右兄弟分别为",LeftChild(T,e),RightChild(T,e));
   printf("%d,%d\n",LeftSibling(T,e),RightSibling(T,e));
   InitBiTree(s);
   printf("建立右子树为空的树s:\n");
   CreateBiTree(s);
   printf("树s插到树T中,请输入树T中树s的双亲结点 s为左(0)或右(1)子树: ");
   scanf("%d%d",&e,&j);
   InsertChild(T,e,j,s);
   Print(T);
   printf("删除子树,请输入待删除子树根结点的层号 本层序号 左(0)或右(1)子树: ");
   scanf("%d%d%d",&p.level,&p.order,&j);
   DeleteChild(T,p,j);
   Print(T);
   ClearBiTree(T);
   printf("清除二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
   i=Root(T,&e);
   if(i)
     printf("二叉树的根为：%d\n",e);
   else
     printf("树空，无根\n");
 }
**********Main6-2.c**********
 /* main6-2.c 检验bo6-2.c的主程序,利用条件编译选择数据类型(另一种方法) */
 #define CHAR /* 字符型 */
 /* #define INT /* 整型（二者选一） */
 #include"c1.h"
 #ifdef CHAR
   typedef char TElemType;
   TElemType Nil=' '; /* 字符型以空格符为空 */
 #endif
 #ifdef INT
   typedef int TElemType;
   TElemType Nil=0; /* 整型以0为空 */
 #endif
 #include"c6-2.h"
 #include"bo6-2.c"

 Status visitT(TElemType e)
 {
 #ifdef CHAR
   printf("%c ",e);
 #endif
 #ifdef INT
   printf("%d ",e);
 #endif
   return OK;
 }

 void main()
 {
   int i;
   BiTree T,p,c;
   TElemType e1,e2;
   InitBiTree(&T);
   printf("构造空二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
   e1=Root(T);
   if(e1!=Nil)
 #ifdef CHAR
     printf("二叉树的根为: %c\n",e1);
 #endif
 #ifdef INT
     printf("二叉树的根为: %d\n",e1);
 #endif
   else
     printf("树空，无根\n");
 #ifdef CHAR
   printf("请先序输入二叉树(如:ab三个空格表示a为根结点,b为左子树的二叉树)\n");
 #endif
 #ifdef INT
   printf("请先序输入二叉树(如:1 2 0 0 0表示1为根结点,2为左子树的二叉树)\n");
 #endif
   CreateBiTree(&T);
   printf("建立二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
   e1=Root(T);
   if(e1!=Nil)
 #ifdef CHAR
     printf("二叉树的根为: %c\n",e1);
 #endif
 #ifdef INT
     printf("二叉树的根为: %d\n",e1);
 #endif
   else
     printf("树空，无根\n");
   printf("中序递归遍历二叉树:\n");
   InOrderTraverse(T,visitT);
   printf("\n中序非递归遍历二叉树:\n");
   InOrderTraverse1(T,visitT);
   printf("中序非递归遍历二叉树(另一种方法):\n");
   InOrderTraverse2(T,visitT);
   printf("后序递归遍历二叉树:\n");
   PostOrderTraverse(T,visitT);
   printf("\n层序遍历二叉树:\n");
   LevelOrderTraverse(T,visitT);
   printf("请输入一个结点的值: ");
 #ifdef CHAR
   scanf("%*c%c",&e1);
 #endif
 #ifdef INT
   scanf("%d",&e1);
 #endif
   p=Point(T,e1); /* p为e1的指针 */
 #ifdef CHAR
   printf("结点的值为%c\n",Value(p));
 #endif
 #ifdef INT
   printf("结点的值为%d\n",Value(p));
 #endif
   printf("欲改变此结点的值，请输入新值: ");
 #ifdef CHAR
   scanf("%*c%c%*c",&e2);
 #endif
 #ifdef INT
   scanf("%d",&e2);
 #endif
   Assign(p,e2);
   printf("层序遍历二叉树:\n");
   LevelOrderTraverse(T,visitT);
   e1=Parent(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c的双亲是%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d的双亲是%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%c没有双亲\n",e2);
 #endif
 #ifdef INT
     printf("%d没有双亲\n",e2);
 #endif
   e1=LeftChild(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c的左孩子是%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d的左孩子是%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%c没有左孩子\n",e2);
 #endif
 #ifdef INT
     printf("%d没有左孩子\n",e2);
 #endif
   e1=RightChild(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c的右孩子是%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d的右孩子是%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%c没有右孩子\n",e2);
 #endif
 #ifdef INT
     printf("%d没有右孩子\n",e2);
 #endif
   e1=LeftSibling(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c的左兄弟是%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d的左兄弟是%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%c没有左兄弟\n",e2);
 #endif
 #ifdef INT
     printf("%d没有左兄弟\n",e2);
 #endif
   e1=RightSibling(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c的右兄弟是%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d的右兄弟是%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%c没有右兄弟\n",e2);
 #endif
 #ifdef INT
     printf("%d没有右兄弟\n",e2);
 #endif
   InitBiTree(&c);
   printf("构造一个右子树为空的二叉树c:\n");
 #ifdef CHAR
   printf("请先序输入二叉树(如:ab三个空格表示a为根结点,b为左子树的二叉树)\n");
 #endif
 #ifdef INT
   printf("请先序输入二叉树(如:1 2 0 0 0表示1为根结点,2为左子树的二叉树)\n");
 #endif
   CreateBiTree(&c);
   printf("先序递归遍历二叉树c:\n");
   PreOrderTraverse(c,visitT);
   printf("\n树c插到树T中,请输入树T中树c的双亲结点 c为左(0)或右(1)子树: ");
 #ifdef CHAR
   scanf("%*c%c%d",&e1,&i);
 #endif
 #ifdef INT
   scanf("%d%d",&e1,&i);
 #endif
   p=Point(T,e1); /* p是T中树c的双亲结点指针 */
   InsertChild(p,i,c);
   printf("先序递归遍历二叉树:\n");
   PreOrderTraverse(T,visitT);
   printf("\n删除子树,请输入待删除子树的双亲结点  左(0)或右(1)子树: ");
 #ifdef CHAR
   scanf("%*c%c%d",&e1,&i);
 #endif
 #ifdef INT
   scanf("%d%d",&e1,&i);
 #endif
   p=Point(T,e1);
   DeleteChild(p,i);
   printf("先序递归遍历二叉树:\n");
   PreOrderTraverse(T,visitT);
   printf("\n");
   DestroyBiTree(&T);
 }
**********MAIN6-3.c**********
 /* main6-3.c 检验bo6-3.c的主程序 */
 #define CHAR 1 /* 字符型 */
 /*#define CHAR 0 /* 整型(二者选一) */
 #if CHAR
   typedef char TElemType;
   TElemType Nil=' '; /* 字符型以空格符为空 */
 #else
   typedef int TElemType;
   TElemType Nil=0; /* 整型以0为空 */
 #endif
 #include"c1.h"
 #include"c6-3.h"
 #include"bo6-3.c"

 Status vi(TElemType c)
 {
 #if CHAR
   printf("%c ",c);
 #else
   printf("%d ",c);
 #endif
   return OK;
 }

 void main()
 {
   BiThrTree H,T;
 #if CHAR
   printf("请按先序输入二叉树(如:ab三个空格表示a为根结点,b为左子树的二叉树)\n");
 #else
   printf("请按先序输入二叉树(如:1 2 0 0 0表示1为根结点,2为左子树的二叉树)\n");
 #endif
   CreateBiThrTree(&T); /* 按先序产生二叉树 */
   InOrderThreading(&H,T); /* 中序遍历，并中序线索化二叉树 */
   printf("中序遍历(输出)二叉线索树:\n");
   InOrderTraverse_Thr(H,vi); /* 中序遍历(输出)二叉线索树 */
   printf("\n");
 }

**********MAIN6-4.c**********
 /* main6-4.c 检验bo6-4.c的主程序 */
 #include"c1.h"
 typedef char TElemType;
 TElemType Nil=' '; /* 以空格符为空 */
 #include"c6-4.h"
 #include"bo6-4.c"

 void vi(TElemType c)
 {
   printf("%c ",c);
 }

 void main()
 {
   int i;
   PTree T,p;
   TElemType e,e1;
   InitTree(&T);
   printf("构造空树后,树空否? %d(1:是 0:否) 树根为%c 树的深度为%d\n",TreeEmpty(T),Root(T),TreeDepth(T));
   CreateTree(&T);
   printf("构造树T后,树空否? %d(1:是 0:否) 树根为%c 树的深度为%d\n",TreeEmpty(T),Root(T),TreeDepth(T));
   printf("层序遍历树T:\n");
   TraverseTree(T,vi);
   printf("请输入待修改的结点的值 新值: ");
   scanf("%c%*c%c%*c",&e,&e1);
   Assign(&T,e,e1);
   printf("层序遍历修改后的树T:\n");
   TraverseTree(T,vi);
   printf("%c的双亲是%c,长子是%c,下一个兄弟是%c\n",e1,Parent(T,e1),LeftChild(T,e1),RightSibling(T,e1));
   printf("建立树p:\n");
   InitTree(&p);
   CreateTree(&p);
   printf("层序遍历树p:\n");
   TraverseTree(p,vi);
   printf("将树p插到树T中，请输入T中p的双亲结点 子树序号: ");
   scanf("%c%d%*c",&e,&i);
   InsertChild(&T,e,i,p);
   Print(T);
   printf("删除树T中结点e的第i棵子树，请输入e i: ");
   scanf("%c%d",&e,&i);
   DeleteChild(&T,e,i);
   Print(T);
 }
**********MAIN6-5.c**********
 /* main6-5.c 检验bo6-5.c的主程序 */
 #include"c1.h"
 typedef char TElemType;
 TElemType Nil=' '; /* 以空格符为空 */
 #include"c6-5.h"
 #include"bo6-5.c"

 void vi(TElemType c)
 {
   printf("%c ",c);
 }

 void main()
 {
   int i;
   CSTree T,p,q;
   TElemType e,e1;
   InitTree(&T);
   printf("构造空树后,树空否? %d(1:是 0:否) 树根为%c 树的深度为%d\n",TreeEmpty(T),Root(T),TreeDepth(T));
   CreateTree(&T);
   printf("构造树T后,树空否? %d(1:是 0:否) 树根为%c 树的深度为%d\n",TreeEmpty(T),Root(T),TreeDepth(T));
   printf("先根遍历树T:\n");
   PreOrderTraverse(T,vi);
   printf("\n请输入待修改的结点的值 新值: ");
   scanf("%c%*c%c%*c",&e,&e1);
   Assign(&T,e,e1);
   printf("后根遍历修改后的树T:\n");
   PostOrderTraverse(T,vi);
   printf("\n%c的双亲是%c,长子是%c,下一个兄弟是%c\n",e1,Parent(T,e1),LeftChild(T,e1),RightSibling(T,e1));
   printf("建立树p:\n");
   InitTree(&p);
   CreateTree(&p);
   printf("层序遍历树p:\n");
   LevelOrderTraverse(p,vi);
   printf("\n将树p插到树T中，请输入T中p的双亲结点 子树序号: ");
   scanf("%c%d%*c",&e,&i);
   q=Point(T,e);
   InsertChild(&T,q,i,p);
   printf("层序遍历树T:\n");
   LevelOrderTraverse(T,vi);
   printf("\n删除树T中结点e的第i棵子树，请输入e i: ");
   scanf("%c%d",&e,&i);
   q=Point(T,e);
   DeleteChild(&T,q,i);
   printf("层序遍历树T:\n",e,i);
   LevelOrderTraverse(T,vi);
   printf("\n");
   DestroyTree(&T);
 }
**********main6-6.c**********
 /* main6-6.c 检验bo6-6.c的主程序 */
 #define CHAR /* 字符型 */
 /*#define INT /* 整型（二者选一） */
 #include"c1.h"
 #ifdef CHAR
   typedef char TElemType;
   TElemType Nil=' '; /* 字符型以空格符为空 */
 #endif
 #ifdef INT
   typedef int TElemType;
   TElemType Nil=0; /* 整型以0为空 */
 #endif
 #include"c6-6.h"
 #include"bo6-6.c"

 Status visitT(BiPTree T)
 {
   if(T) /* T非空 */
 #ifdef CHAR
     printf("%c是",T->data);
   if(T->parent) /* T有双亲 */
   {
     printf("%c",T->parent->data);
 #endif
 #ifdef INT
     printf("%d是",T->data);
   if(T->parent) /* T有双亲 */
   {
     printf("%d",T->parent->data);
 #endif
     if(T->parent->lchild==T)
       printf("的左孩子\n");
     else
       printf("的右孩子\n");
   }
   else
     printf("根结点\n");
   return OK;
 }

 void main()
 {
   int i;
   BiPTree T,c,q;
   TElemType e1,e2;
   InitBiTree(&T);
   printf("构造空二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
   e1=Root(T);
   if(e1!=Nil)
 #ifdef CHAR
     printf("二叉树的根为: %c\n",e1);
 #endif
 #ifdef INT
     printf("二叉树的根为: %d\n",e1);
 #endif
   else
     printf("树空，无根\n");
 #ifdef CHAR
   printf("请按先序输入二叉树(如:ab三个空格表示a为根结点,b为左子树的二叉树)\n");
 #endif
 #ifdef INT
   printf("请按先序输入二叉树(如:1 2 0 0 0表示1为根结点,2为左子树的二叉树)\n");
 #endif
   CreateBiTree(&T);
   printf("建立二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
   e1=Root(T);
   if(e1!=Nil)
 #ifdef CHAR
     printf("二叉树的根为: %c\n",e1);
 #endif
 #ifdef INT
     printf("二叉树的根为: %d\n",e1);
 #endif
   else
     printf("树空，无根\n");
   printf("中序递归遍历二叉树:\n");
   InOrderTraverse(T,visitT);
   printf("后序递归遍历二叉树:\n");
   PostOrderTraverse(T,visitT);
   scanf("%*c"); /* 吃掉回车符 */
   printf("按回车键继续:");
   getchar(); /* 暂停输出 */
   printf("层序遍历二叉树:\n");
   LevelOrderTraverse(T,visitT);
   printf("请输入一个结点的值: ");
 #ifdef CHAR
   scanf("%c",&e1);
 #endif
 #ifdef INT
   scanf("%d",&e1);
 #endif
   c=Point(T,e1); /* c为e1的指针 */
 #ifdef CHAR
   printf("结点的值为%c\n",Value(c));
 #endif
 #ifdef INT
   printf("结点的值为%d\n",Value(c));
 #endif
   printf("欲改变此结点的值，请输入新值: ");
 #ifdef CHAR
   scanf("%*c%c%*c",&e2);
 #endif
 #ifdef INT
   scanf("%d",&e2);
 #endif
   Assign(c,e2);
   printf("层序遍历二叉树:\n");
   LevelOrderTraverse(T,visitT);
   e1=Parent(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c的双亲是%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d的双亲是%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%c没有双亲\n",e2);
 #endif
 #ifdef INT
     printf("%d没有双亲\n",e2);
 #endif
   e1=LeftChild(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c的左孩子是%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d的左孩子是%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%c没有左孩子\n",e2);
 #endif
 #ifdef INT
     printf("%d没有左孩子\n",e2);
 #endif
   e1=RightChild(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c的右孩子是%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d的右孩子是%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%c没有右孩子\n",e2);
 #endif
 #ifdef INT
     printf("%d没有右孩子\n",e2);
 #endif
   e1=LeftSibling(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c的左兄弟是%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d的左兄弟是%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%c没有左兄弟\n",e2);
 #endif
 #ifdef INT
     printf("%d没有左兄弟\n",e2);
 #endif
   e1=RightSibling(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c的右兄弟是%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d的右兄弟是%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%c没有右兄弟\n",e2);
 #endif
 #ifdef INT
     printf("%d没有右兄弟\n",e2);
 #endif 
   InitBiTree(&c);
   printf("构造一个右子树为空的二叉树c:\n");
 #ifdef CHAR
   printf("请先序输入二叉树(如:ab三个空格表示a为根结点,b为左子树的二叉树)\n");
 #endif
 #ifdef INT
   printf("请先序输入二叉树(如:1 2 0 0 0表示1为根结点,2为左子树的二叉树)\n");
 #endif
   CreateBiTree(&c);
   printf("先序递归遍历二叉树c:\n");
   PreOrderTraverse(c,visitT);
   printf("树c插到树T中,请输入树T中树c的双亲结点 c为左(0)或右(1)子树: ");
 #ifdef CHAR
   scanf("%*c%c%d",&e1,&i);
 #endif
 #ifdef INT
   scanf("%d%d",&e1,&i);
 #endif
   q=Point(T,e1);
   InsertChild(q,i,c);
   printf("先序递归遍历二叉树:\n");
   PreOrderTraverse(T,visitT);
   printf("删除子树,请输入待删除子树的双亲结点  左(0)或右(1)子树: ");
 #ifdef CHAR
   scanf("%*c%c%d",&e1,&i);
 #endif
 #ifdef INT
   scanf("%d%d",&e1,&i);
 #endif
   q=Point(T,e1);
   DeleteChild(q,i);
   printf("先序递归遍历二叉树:\n");
   PreOrderTraverse(T,visitT);
   DestroyBiTree(&T);
 }

F:\GitHubCode\Code\Csjjg\严蔚敏《数据结构》的全部代码实现（C语言）\ch6\Debug
F:\GitHubCode\Code\Csjjg\严蔚敏《数据结构》的全部代码实现（C语言）\ch7
**********Algo7-2.c**********
 /* algo7-2.c 实现算法7.9的程序 */
 #include"c1.h"
 typedef int VRType;
 typedef char InfoType;
 #define MAX_NAME 3 /* 顶点字符串的最大长度+1 */
 #define MAX_INFO 20 /* 相关信息字符串的最大长度+1 */
 typedef char VertexType[MAX_NAME];
 #include"c7-1.h"
 #include"bo7-1.c"

 typedef struct
 { /* 记录从顶点集U到V-U的代价最小的边的辅助数组定义 */
   VertexType adjvex;
   VRType lowcost;
 }minside[MAX_VERTEX_NUM];

 int minimum(minside SZ,MGraph G)
 { /* 求closedge.lowcost的最小正值 */
   int i=0,j,k,min;
   while(!SZ[i].lowcost)
     i++;
   min=SZ[i].lowcost; /* 第一个不为0的值 */
   k=i;
   for(j=i+1;j<G.vexnum;j++)
     if(SZ[j].lowcost>0)
       if(min>SZ[j].lowcost)
       {
         min=SZ[j].lowcost;
         k=j;
       }
   return k;
 }

 void MiniSpanTree_PRIM(MGraph G,VertexType u)
 { /* 用普里姆算法从第u个顶点出发构造网G的最小生成树T,输出T的各条边 算法7.9 */
   int i,j,k;
   minside closedge;
   k=LocateVex(G,u);
   for(j=0;j<G.vexnum;++j) /* 辅助数组初始化 */
   {
     if(j!=k)
     {
       strcpy(closedge[j].adjvex,u);
       closedge[j].lowcost=G.arcs[k][j].adj;
     }
   }
   closedge[k].lowcost=0; /* 初始,U={u} */
   printf("最小代价生成树的各条边为:\n");
   for(i=1;i<G.vexnum;++i)
   { /* 选择其余G.vexnum-1个顶点 */
     k=minimum(closedge,G); /* 求出T的下一个结点：第K顶点 */
     printf("(%s-%s)\n",closedge[k].adjvex,G.vexs[k]); /* 输出生成树的边 */
     closedge[k].lowcost=0; /* 第K顶点并入U集 */
     for(j=0;j<G.vexnum;++j)
       if(G.arcs[k][j].adj<closedge[j].lowcost)
       { /* 新顶点并入U集后重新选择最小边 */
         strcpy(closedge[j].adjvex,G.vexs[k]);
         closedge[j].lowcost=G.arcs[k][j].adj;
       }
   }
 }

 void main()
 {
   MGraph G;
   CreateAN(&G);
   MiniSpanTree_PRIM(G,G.vexs[0]);
 }


**********Algo7-3.c**********
 /* algo7-3.c 实现算法7.10、7.11的程序 */
 #include"c1.h"
 #define MAX_NAME 2 /* 顶点字符串的最大长度+1 */
 typedef int InfoType;
 typedef char VertexType[MAX_NAME]; /* 字符串类型 */
 #include"c7-2.h"
 #include"bo7-2.c"

 int count; /* 全局量count对访问计数 */
 int low[MAX_VERTEX_NUM];

 void DFSArticul(ALGraph G,int v0)
 { /* 从第v0个顶点出发深度优先遍历图G，查找并输出关节点。算法7.11 */
   int min,w;
   ArcNode *p;
   visited[v0]=min=++count; /* v0是第count个访问的顶点 */
   for(p=G.vertices[v0].firstarc;p;p=p->nextarc) /* 对v0的每个邻接顶点检查 */
   {
     w=p->adjvex; /* w为v0的邻接顶点 */
     if(visited[w]==0) /* w未曾访问，是v0的孩子 */
     {
       DFSArticul(G,w); /* 返回前求得low[w] */
       if(low[w]<min)
         min=low[w];
       if(low[w]>=visited[v0])
         printf("%d %s\n",v0,G.vertices[v0].data); /* 关节点 */
     }
     else if(visited[w]<min)
       min=visited[w]; /* w已访问，w是v0在生成树上的祖先 */
   }
   low[v0]=min;
 }

 void FindArticul(ALGraph G)
 { /* 连通图G以邻接表作存储结构，查找并输出G上全部关节点。算法7.10 */
   /* 全局量count对访问计数。 */
   int i,v;
   ArcNode *p;
   count=1;
   low[0]=visited[0]=1; /* 设定邻接表上0号顶点为生成树的根 */
   for(i=1;i<G.vexnum;++i)
     visited[i]=0; /* 其余顶点尚未访问 */
   p=G.vertices[0].firstarc;
   v=p->adjvex;
   DFSArticul(G,v); /* 从第v顶点出发深度优先查找关节点 */
   if(count<G.vexnum) /* 生成树的根有至少两棵子树 */
   {
     printf("%d %s\n",0,G.vertices[0].data); /* 根是关节点，输出 */
     while(p->nextarc)
     {
       p=p->nextarc;
       v=p->adjvex;
       if(visited[v]==0)
         DFSArticul(G,v);
     }
   }
 }

 void main()
 {
   int i;
   ALGraph g;
   printf("请选择无向图\n");
   CreateGraph(&g);
   printf("输出关节点：\n");
   FindArticul(g);
   printf(" i G.vertices[i].data visited[i] low[i]\n");
   for(i=0;i<g.vexnum;++i)
     printf("%2d %9s %14d %8d\n",i,g.vertices[i].data,visited[i],low[i]);
 }

**********Algo7-4.c**********
 /* algo7-4.c 输出有向图的一个拓扑序列。实现算法7.12的程序 */
 #include"c1.h"
 #define MAX_NAME 5 /* 顶点字符串的最大长度 */
 typedef int InfoType;
 typedef char VertexType[MAX_NAME]; /* 字符串类型 */
 #include"c7-2.h"
 #include"bo7-2.c"

 void FindInDegree(ALGraph G,int indegree[])
 { /* 求顶点的入度，算法7.12、7.13调用 */
   int i;
   ArcNode *p;
   for(i=0;i<G.vexnum;i++)
     indegree[i]=0; /* 赋初值 */
   for(i=0;i<G.vexnum;i++)
   {
     p=G.vertices[i].firstarc;
     while(p)
     {
       indegree[p->adjvex]++;
       p=p->nextarc;
     }
   }
 }

 typedef int SElemType; /* 栈类型 */
 #include"c3-1.h"
 #include"bo3-1.c"
 Status TopologicalSort(ALGraph G)
 { /* 有向图G采用邻接表存储结构。若G无回路,则输出G的顶点的一个拓扑序列并返回OK, */
   /* 否则返回ERROR。算法7.12 */
   int i,k,count,indegree[MAX_VERTEX_NUM];
   SqStack S;
   ArcNode *p;
   FindInDegree(G,indegree); /* 对各顶点求入度indegree[0..vernum-1] */
   InitStack(&S); /* 初始化栈 */
   for(i=0;i<G.vexnum;++i) /* 建零入度顶点栈S */
     if(!indegree[i])
       Push(&S,i); /* 入度为0者进栈 */
   count=0; /* 对输出顶点计数 */
   while(!StackEmpty(S))
   { /* 栈不空 */
     Pop(&S,&i);
     printf("%s ",G.vertices[i].data); /* 输出i号顶点并计数 */
     ++count;
     for(p=G.vertices[i].firstarc;p;p=p->nextarc)
     { /* 对i号顶点的每个邻接点的入度减1 */
       k=p->adjvex;
       if(!(--indegree[k])) /* 若入度减为0,则入栈 */
         Push(&S,k);
     }
   }
   if(count<G.vexnum)
   {
     printf("此有向图有回路\n");
     return ERROR;
   }
   else
   {
     printf("为一个拓扑序列。\n");
     return OK;
   }
 }

 void main()
 {
   ALGraph f;
   printf("请选择有向图\n");
   CreateGraph(&f);
   Display(f);
   TopologicalSort(f);
 }

**********Algo7-5.c**********
 /* algo7-5.c 求关键路径。实现算法7.13、7.14的程序 */
 #include"c1.h"
 #define MAX_NAME 5 /* 顶点字符串的最大长度+1 */
 typedef int InfoType;
 typedef char VertexType[MAX_NAME]; /* 字符串类型 */
 #include"c7-2.h"
 #include"bo7-2.c"

 int ve[MAX_VERTEX_NUM]; /* 全局变量(用于算法7.13和算法7.14) */

 void FindInDegree(ALGraph G,int indegree[])
 { /* 求顶点的入度，算法7.12、7.13调用 */
   int i;
   ArcNode *p;
   for(i=0;i<G.vexnum;i++)
     indegree[i]=0; /* 赋初值 */
   for(i=0;i<G.vexnum;i++)
   {
     p=G.vertices[i].firstarc;
     while(p)
     {
       indegree[p->adjvex]++;
       p=p->nextarc;
     }
   }
 }

 typedef int SElemType; /* 栈类型 */
 #include"c3-1.h"
 #include"bo3-1.c"
 Status TopologicalOrder(ALGraph G,SqStack *T)
 { /* 算法7.13  有向网G采用邻接表存储结构,求各顶点事件的最早发生时间ve */
   /* (全局变量)。T为拓扑序列顶点栈,S为零入度顶点栈。若G无回路,则用栈T */
   /* 返回G的一个拓扑序列,且函数值为OK,否则为ERROR */
   int j,k,count,indegree[MAX_VERTEX_NUM];
   SqStack S;
   ArcNode *p;
   FindInDegree(G,indegree);/*对各顶点求入度indegree[0..vernum-1] */
   InitStack(&S); /* 初始化栈 */
   for(j=0;j<G.vexnum;++j) /* 建零入度顶点栈S */
     if(!indegree[j])
       Push(&S,j); /* 入度为0者进栈 */
   InitStack(T); /* 初始化拓扑序列顶点栈 */
   count=0; /* 对输出顶点计数 */
   for(j=0;j<G.vexnum;++j) /* 初始化ve[]=0 (最小值) */
     ve[j]=0;
   while(!StackEmpty(S))
   { /* 栈不空 */
     Pop(&S,&j);
     Push(T,j); /* j号顶点入T栈并计数 */
     ++count;
     for(p=G.vertices[j].firstarc;p;p=p->nextarc)
     { /* 对j号顶点的每个邻接点的入度减1 */
       k=p->adjvex;
       if(--indegree[k]==0) /* 若入度减为0,则入栈 */
         Push(&S,k);
       if(ve[j]+*(p->info)>ve[k])
         ve[k]=ve[j]+*(p->info);
     }
   }
   if(count<G.vexnum)
   {
     printf("此有向网有回路\n");
     return ERROR;
   }
   else
     return OK;
 }

 Status CriticalPath(ALGraph G)
 { /* 算法7.14 G为有向网,输出G的各项关键活动 */
   int vl[MAX_VERTEX_NUM];
   SqStack T;
   int i,j,k,ee,el;
   ArcNode *p;
   char dut,tag;
   if(!TopologicalOrder(G,&T)) /* 产生有向环 */
     return ERROR;
   j=ve[0];
   for(i=1;i<G.vexnum;i++) /* j=Max(ve[]) 完成点的值 */
     if(ve[i]>j)
       j=ve[i];
   for(i=0;i<G.vexnum;i++) /* 初始化顶点事件的最迟发生时间(最大值) */
     vl[i]=j; /* 完成点的最早发生时间 */
   while(!StackEmpty(T)) /* 按拓扑逆序求各顶点的vl值 */
     for(Pop(&T,&j),p=G.vertices[j].firstarc;p;p=p->nextarc)
     {
       k=p->adjvex;
       dut=*(p->info); /* dut<j,k> */
       if(vl[k]-dut<vl[j])
         vl[j]=vl[k]-dut;
     }
   printf(" j  k  dut  ee  el  tag\n");
   for(j=0;j<G.vexnum;++j) /* 求ee,el和关键活动 */
     for(p=G.vertices[j].firstarc;p;p=p->nextarc)
     {
       k=p->adjvex;
       dut=*(p->info);
       ee=ve[j];
       el=vl[k]-dut;
       tag=(ee==el)?'*':' ';
       printf("%2d %2d %3d %3d %3d    %c\n",j,k,dut,ee,el,tag); /* 输出关键活动 */
     }
   printf("关键活动为:\n");
   for(j=0;j<G.vexnum;++j) /* 同上 */
     for(p=G.vertices[j].firstarc;p;p=p->nextarc)
     {
       k=p->adjvex;
       dut=*(p->info);
       if(ve[j]==vl[k]-dut)
         printf("%s→%s\n",G.vertices[j].data,G.vertices[k].data); /* 输出关键活动 */
     }
   return OK;
 }

 void main()
 {
   ALGraph h;
   printf("请选择有向网\n");
   CreateGraph(&h);
   Display(h);
   CriticalPath(h);
 }

**********Algo7-6.c**********
 /* algo7-6.c 实现算法7.15的程序。迪杰斯特拉算法的实现 */
 #include"c1.h"
 #define MAX_NAME 5 /* 顶点字符串的最大长度+1 */
 #define MAX_INFO 20 /* 相关信息字符串的最大长度+1 */
 typedef int VRType;
 typedef char InfoType;
 typedef char VertexType[MAX_NAME];
 #include"c7-1.h"
 typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
 typedef int ShortPathTable[MAX_VERTEX_NUM];
 #include"bo7-1.c"

 void ShortestPath_DIJ(MGraph G,int v0,PathMatrix *P,ShortPathTable *D)
 { /* 用Dijkstra算法求有向网G的v0顶点到其余顶点v的最短路径P[v]及带权长度 */
   /* D[v]。若P[v][w]为TRUE,则w是从v0到v当前求得最短路径上的顶点。 */
   /* final[v]为TRUE当且仅当v∈S,即已经求得从v0到v的最短路径 算法7.15 */
   int v,w,i,j,min;
   Status final[MAX_VERTEX_NUM];
   for(v=0;v<G.vexnum;++v)
   {
     final[v]=FALSE;
     (*D)[v]=G.arcs[v0][v].adj;
     for(w=0;w<G.vexnum;++w)
       (*P)[v][w]=FALSE; /* 设空路径 */
     if((*D)[v]<INFINITY)
     {
       (*P)[v][v0]=TRUE;
       (*P)[v][v]=TRUE;
     }
   }
   (*D)[v0]=0;
   final[v0]=TRUE; /* 初始化,v0顶点属于S集 */
   for(i=1;i<G.vexnum;++i) /* 其余G.vexnum-1个顶点 */
   { /* 开始主循环,每次求得v0到某个v顶点的最短路径,并加v到S集 */
     min=INFINITY; /* 当前所知离v0顶点的最近距离 */
     for(w=0;w<G.vexnum;++w)
       if(!final[w]) /* w顶点在V-S中 */
	 if((*D)[w]<min)
	 {
	   v=w;
	   min=(*D)[w];
	 } /* w顶点离v0顶点更近 */
     final[v]=TRUE; /* 离v0顶点最近的v加入S集 */
     for(w=0;w<G.vexnum;++w) /* 更新当前最短路径及距离 */
     {
       if(!final[w]&&min<INFINITY&&G.arcs[v][w].adj<INFINITY&&(min+G.arcs[v][w].adj<(*D)[w]))
       { /* 修改D[w]和P[w],w∈V-S */
         (*D)[w]=min+G.arcs[v][w].adj;
         for(j=0;j<G.vexnum;++j)
           (*P)[w][j]=(*P)[v][j];
         (*P)[w][w]=TRUE;
       }
     }
   }
 }

 void main()
 {
   int i,j,v0=0; /* v0为源点 */
   MGraph g;
   PathMatrix p;
   ShortPathTable d;
   CreateDN(&g);
   ShortestPath_DIJ(g,v0,&p,&d);
   printf("最短路径数组p[i][j]如下:\n");
   for(i=0;i<g.vexnum;++i)
   {
     for(j=0;j<g.vexnum;++j)
       printf("%2d",p[i][j]);
     printf("\n");
   }
   printf("%s到各顶点的最短路径长度为：\n",g.vexs[0]);
   for(i=1;i<g.vexnum;++i)
     printf("%s-%s:%d\n",g.vexs[0],g.vexs[i],d[i]);
 }

**********Algo7-7.c**********
 /* algo7-7.c 实现算法7.16的程序 */
 #define MAX_NAME 5 /* 顶点字符串的最大长度+1 */
 #define MAX_INFO 20 /* 相关信息字符串的最大长度+1 */
 typedef int VRType;
 typedef char VertexType[MAX_NAME];
 typedef char InfoType;
 #include"c1.h"
 #include"c7-1.h"
 #include"bo7-1.c"
 typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
 typedef int DistancMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

 void ShortestPath_FLOYD(MGraph G,PathMatrix *P,DistancMatrix *D)
 { /* 用Floyd算法求有向网G中各对顶点v和w之间的最短路径P[v][w]及其 */
   /* 带权长度D[v][w]。若P[v][w][u]为TRUE,则u是从v到w当前求得最短 */
   /* 路径上的顶点。算法7.16 */
   int u,v,w,i;
   for(v=0;v<G.vexnum;v++) /* 各对结点之间初始已知路径及距离 */
     for(w=0;w<G.vexnum;w++)
     {
       (*D)[v][w]=G.arcs[v][w].adj;
       for(u=0;u<G.vexnum;u++)
         (*P)[v][w][u]=FALSE;
       if((*D)[v][w]<INFINITY) /* 从v到w有直接路径 */
       {
         (*P)[v][w][v]=TRUE;
         (*P)[v][w][w]=TRUE;
       }
     }
   for(u=0;u<G.vexnum;u++)
     for(v=0;v<G.vexnum;v++)
       for(w=0;w<G.vexnum;w++)
         if((*D)[v][u]+(*D)[u][w]<(*D)[v][w]) /* 从v经u到w的一条路径更短 */
         {
           (*D)[v][w]=(*D)[v][u]+(*D)[u][w];
           for(i=0;i<G.vexnum;i++)
             (*P)[v][w][i]=(*P)[v][u][i]||(*P)[u][w][i];
         }
 }

 void main()
 {
   MGraph g;
   int i,j,k,l,m,n;
   PathMatrix p;
   DistancMatrix d;
   CreateDN(&g);
   for(i=0;i<g.vexnum;i++)
     g.arcs[i][i].adj=0; /* ShortestPath_FLOYD()要求对角元素值为0 */
   printf("邻接矩阵:\n");
   for(i=0;i<g.vexnum;i++)
   {
     for(j=0;j<g.vexnum;j++)
       printf("%11d",g.arcs[i][j]);
     printf("\n");
   }
   ShortestPath_FLOYD(g,&p,&d);
   printf("d矩阵:\n");
   for(i=0;i<g.vexnum;i++)
   {
     for(j=0;j<g.vexnum;j++)
       printf("%6d",d[i][j]);
     printf("\n");
   }
   for(i=0;i<g.vexnum;i++)
     for(j=0;j<g.vexnum;j++)
       printf("%s到%s的最短距离为%d\n",g.vexs[i],g.vexs[j],d[i][j]);
   printf("p矩阵:\n");
   l=strlen(g.vexs[0]); /* 顶点向量字符串的长度 */
   for(i=0;i<g.vexnum;i++)
   {
     for(j=0;j<g.vexnum;j++)
     {
       if(i!=j)
       {
         m=0; /* 占位空格 */
         for(k=0;k<g.vexnum;k++)
           if(p[i][j][k]==1)
             printf("%s",g.vexs[k]);
           else
             m++;
         for(n=0;n<m*l;n++) /* 输出占位空格 */
           printf(" ");
       }
       else
         for(k=0;k<g.vexnum*l;k++) /* 输出占位空格 */
           printf(" ");
       printf("   "); /* 输出矩阵元素之间的间距 */
     }
     printf("\n");
   }
 }


**********BO7-1.C**********
 /* bo7-1.c 图的数组(邻接矩阵)存储(存储结构由c7-1.h定义)的基本操作(20个) */
 int LocateVex(MGraph G,VertexType u)
 { /* 初始条件:图G存在,u和G中顶点有相同特征 */
   /* 操作结果:若G中存在顶点u,则返回该顶点在图中位置;否则返回-1 */
   int i;
   for(i=0;i<G.vexnum;++i)
     if(strcmp(u,G.vexs[i])==0)
       return i;
   return -1;
 }

 Status CreateFAG(MGraph *G)
 { /* 采用数组(邻接矩阵)表示法,由文件构造没有相关信息的无向图G */
   int i,j,k;
   char filename[13];
   VertexType va,vb;
   FILE *graphlist;
   printf("请输入数据文件名(f7-1.dat)：");
   scanf("%s",filename);
   graphlist=fopen(filename,"r");
   fscanf(graphlist,"%d",&(*G).vexnum);
   fscanf(graphlist,"%d",&(*G).arcnum);
   for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
     fscanf(graphlist,"%s",(*G).vexs[i]);
   for(i=0;i<(*G).vexnum;++i) /* 初始化邻接矩阵 */
     for(j=0;j<(*G).vexnum;++j)
     {
       (*G).arcs[i][j].adj=0; /* 图 */
       (*G).arcs[i][j].info=NULL; /* 没有相关信息 */
     }
   for(k=0;k<(*G).arcnum;++k)
   {
     fscanf(graphlist,"%s%s",va,vb);
     i=LocateVex(*G,va);
     j=LocateVex(*G,vb);
     (*G).arcs[i][j].adj=(*G).arcs[j][i].adj=1; /* 无向图 */
   }
   fclose(graphlist);
   (*G).kind=AG;
   return OK;
 }

 Status CreateDG(MGraph *G)
 { /* 采用数组(邻接矩阵)表示法,构造有向图G */
   int i,j,k,l,IncInfo;
   char s[MAX_INFO],*info;
   VertexType va,vb;
   printf("请输入有向图G的顶点数,弧数,弧是否含其它信息(是:1,否:0): ");
   scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
   printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
   for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
     scanf("%s",(*G).vexs[i]);
   for(i=0;i<(*G).vexnum;++i) /* 初始化邻接矩阵 */
     for(j=0;j<(*G).vexnum;++j)
     {
       (*G).arcs[i][j].adj=0; /* 图 */
       (*G).arcs[i][j].info=NULL;
     }
   printf("请输入%d条弧的弧尾 弧头(以空格作为间隔): \n",(*G).arcnum);
   for(k=0;k<(*G).arcnum;++k)
   {
     scanf("%s%s%*c",va,vb);  /* %*c吃掉回车符 */
     i=LocateVex(*G,va);
     j=LocateVex(*G,vb);
     (*G).arcs[i][j].adj=1; /* 有向图 */
     if(IncInfo)
     {
       printf("请输入该弧的相关信息(<%d个字符): ",MAX_INFO);
       gets(s);
       l=strlen(s);
       if(l)
       {
         info=(char*)malloc((l+1)*sizeof(char));
         strcpy(info,s);
         (*G).arcs[i][j].info=info; /* 有向 */
       }
     }
   }
   (*G).kind=DG;
   return OK;
 }

 Status CreateDN(MGraph *G)
 { /* 采用数组(邻接矩阵)表示法,构造有向网G */
   int i,j,k,w,IncInfo;
   char s[MAX_INFO],*info;
   VertexType va,vb;
   printf("请输入有向网G的顶点数,弧数,弧是否含其它信息(是:1,否:0): ");
   scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
   printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
   for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
     scanf("%s",(*G).vexs[i]);
   for(i=0;i<(*G).vexnum;++i) /* 初始化邻接矩阵 */
     for(j=0;j<(*G).vexnum;++j)
     {
       (*G).arcs[i][j].adj=INFINITY; /* 网 */
       (*G).arcs[i][j].info=NULL;
     }
   printf("请输入%d条弧的弧尾 弧头 权值(以空格作为间隔): \n",(*G).arcnum);
   for(k=0;k<(*G).arcnum;++k)
   {
     scanf("%s%s%d%*c",va,vb,&w);  /* %*c吃掉回车符 */
     i=LocateVex(*G,va);
     j=LocateVex(*G,vb);
     (*G).arcs[i][j].adj=w; /* 有向网 */
     if(IncInfo)
     {
       printf("请输入该弧的相关信息(<%d个字符): ",MAX_INFO);
       gets(s);
       w=strlen(s);
       if(w)
       {
         info=(char*)malloc((w+1)*sizeof(char));
         strcpy(info,s);
         (*G).arcs[i][j].info=info; /* 有向 */
       }
     }
   }
   (*G).kind=DN;
   return OK;
 }

 Status CreateAG(MGraph *G)
 { /* 采用数组(邻接矩阵)表示法,构造无向图G */
   int i,j,k,l,IncInfo;
   char s[MAX_INFO],*info;
   VertexType va,vb;
   printf("请输入无向图G的顶点数,边数,边是否含其它信息(是:1,否:0): ");
   scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
   printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
   for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
     scanf("%s",(*G).vexs[i]);
   for(i=0;i<(*G).vexnum;++i) /* 初始化邻接矩阵 */
     for(j=0;j<(*G).vexnum;++j)
     {
       (*G).arcs[i][j].adj=0; /* 图 */
       (*G).arcs[i][j].info=NULL;
     }
   printf("请输入%d条边的顶点1 顶点2(以空格作为间隔): \n",(*G).arcnum);
   for(k=0;k<(*G).arcnum;++k)
   {
     scanf("%s%s%*c",va,vb); /* %*c吃掉回车符 */
     i=LocateVex(*G,va);
     j=LocateVex(*G,vb);
     (*G).arcs[i][j].adj=(*G).arcs[j][i].adj=1; /* 无向图 */
     if(IncInfo)
     {
       printf("请输入该边的相关信息(<%d个字符): ",MAX_INFO);
       gets(s);
       l=strlen(s);
       if(l)
       {
         info=(char*)malloc((l+1)*sizeof(char));
         strcpy(info,s);
         (*G).arcs[i][j].info=(*G).arcs[j][i].info=info; /* 无向 */
       }
     }
   }
   (*G).kind=AG;
   return OK;
 }

 Status CreateAN(MGraph *G)
 { /* 采用数组(邻接矩阵)表示法,构造无向网G。算法7.2 */
   int i,j,k,w,IncInfo;
   char s[MAX_INFO],*info;
   VertexType va,vb;
   printf("请输入无向网G的顶点数,边数,边是否含其它信息(是:1,否:0): ");
   scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
   printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
   for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
     scanf("%s",(*G).vexs[i]);
   for(i=0;i<(*G).vexnum;++i) /* 初始化邻接矩阵 */
     for(j=0;j<(*G).vexnum;++j)
     {
       (*G).arcs[i][j].adj=INFINITY; /* 网 */
       (*G).arcs[i][j].info=NULL;
     }
   printf("请输入%d条边的顶点1 顶点2 权值(以空格作为间隔): \n",(*G).arcnum);
   for(k=0;k<(*G).arcnum;++k)
   {
     scanf("%s%s%d%*c",va,vb,&w); /* %*c吃掉回车符 */
     i=LocateVex(*G,va);
     j=LocateVex(*G,vb);
     (*G).arcs[i][j].adj=(*G).arcs[j][i].adj=w; /* 无向 */
     if(IncInfo)
     {
       printf("请输入该边的相关信息(<%d个字符): ",MAX_INFO);
       gets(s);
       w=strlen(s);
       if(w)
       {
         info=(char*)malloc((w+1)*sizeof(char));
         strcpy(info,s);
         (*G).arcs[i][j].info=(*G).arcs[j][i].info=info; /* 无向 */
       }
     }
   }
   (*G).kind=AN;
   return OK;
 }

 Status CreateGraph(MGraph *G)
 { /* 采用数组(邻接矩阵)表示法,构造图G。算法7.1 */
   printf("请输入图G的类型(有向图:0,有向网:1,无向图:2,无向网:3): ");
   scanf("%d",&(*G).kind);
   switch((*G).kind)
   {
     case DG: return CreateDG(G); /* 构造有向图 */
     case DN: return CreateDN(G); /* 构造有向网 */
     case AG: return CreateAG(G); /* 构造无向图 */
     case AN: return CreateAN(G); /* 构造无向网 */
     default: return ERROR;
   }
 }

 void DestroyGraph(MGraph *G)
 { /* 初始条件: 图G存在。操作结果: 销毁图G */
   int i,j;
   if((*G).kind<2) /* 有向 */
     for(i=0;i<(*G).vexnum;i++) /* 释放弧的相关信息(如果有的话) */
     {
       for(j=0;j<(*G).vexnum;j++)
         if((*G).arcs[i][j].adj==1&&(*G).kind==0||(*G).arcs[i][j].adj!=INFINITY&&(*G).kind==1) /* 有向图的弧||有向网的弧 */
           if((*G).arcs[i][j].info) /* 有相关信息 */
           {
             free((*G).arcs[i][j].info);
             (*G).arcs[i][j].info=NULL;
           }
     }
   else /* 无向 */
     for(i=0;i<(*G).vexnum;i++) /* 释放边的相关信息(如果有的话) */
       for(j=i+1;j<(*G).vexnum;j++)
         if((*G).arcs[i][j].adj==1&&(*G).kind==2||(*G).arcs[i][j].adj!=INFINITY&&(*G).kind==3) /* 无向图的边||无向网的边 */
           if((*G).arcs[i][j].info) /* 有相关信息 */
           {
             free((*G).arcs[i][j].info);
             (*G).arcs[i][j].info=(*G).arcs[j][i].info=NULL;
           }
   (*G).vexnum=0;
   (*G).arcnum=0;
 }

 VertexType* GetVex(MGraph G,int v)
 { /* 初始条件: 图G存在，v是G中某个顶点的序号。操作结果: 返回v的值 */
   if(v>=G.vexnum||v<0)
     exit(ERROR);
   return &G.vexs[v];
 }

 Status PutVex(MGraph *G,VertexType v,VertexType value)
 { /* 初始条件: 图G存在，v是G中某个顶点。操作结果: 对v赋新值value */
   int k;
   k=LocateVex(*G,v); /* k为顶点v在图G中的序号 */
   if(k<0)
     return ERROR;
   strcpy((*G).vexs[k],value);
   return OK;
 }

 int FirstAdjVex(MGraph G,VertexType v)
 { /* 初始条件: 图G存在,v是G中某个顶点 */
   /* 操作结果: 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1 */
   int i,j=0,k;
   k=LocateVex(G,v); /* k为顶点v在图G中的序号 */
   if(G.kind==DN||G.kind==AN) /* 网 */
     j=INFINITY;
   for(i=0;i<G.vexnum;i++)
     if(G.arcs[k][i].adj!=j)
       return i;
   return -1;
 }

 int NextAdjVex(MGraph G,VertexType v,VertexType w)
 { /* 初始条件: 图G存在,v是G中某个顶点,w是v的邻接顶点 */
   /* 操作结果: 返回v的(相对于w的)下一个邻接顶点的序号, */
   /*           若w是v的最后一个邻接顶点,则返回-1 */
   int i,j=0,k1,k2;
   k1=LocateVex(G,v); /* k1为顶点v在图G中的序号 */
   k2=LocateVex(G,w); /* k2为顶点w在图G中的序号 */
   if(G.kind==DN||G.kind==AN) /* 网 */
     j=INFINITY;
   for(i=k2+1;i<G.vexnum;i++)
     if(G.arcs[k1][i].adj!=j)
       return i;
   return -1;
 }

 void InsertVex(MGraph *G,VertexType v)
 { /* 初始条件: 图G存在,v和图G中顶点有相同特征 */
   /* 操作结果: 在图G中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做) */
   int i;
   strcpy((*G).vexs[(*G).vexnum],v); /* 构造新顶点向量 */
   for(i=0;i<=(*G).vexnum;i++)
   {
     if((*G).kind%2) /* 网 */
     {
       (*G).arcs[(*G).vexnum][i].adj=INFINITY; /* 初始化该行邻接矩阵的值(无边或弧) */
       (*G).arcs[i][(*G).vexnum].adj=INFINITY; /* 初始化该列邻接矩阵的值(无边或弧) */
     }
     else /* 图 */
     {
       (*G).arcs[(*G).vexnum][i].adj=0; /* 初始化该行邻接矩阵的值(无边或弧) */
       (*G).arcs[i][(*G).vexnum].adj=0; /* 初始化该列邻接矩阵的值(无边或弧) */
     }
     (*G).arcs[(*G).vexnum][i].info=NULL; /* 初始化相关信息指针 */
     (*G).arcs[i][(*G).vexnum].info=NULL;
   }
   (*G).vexnum+=1; /* 图G的顶点数加1 */
 }

 Status DeleteVex(MGraph *G,VertexType v)
 { /* 初始条件: 图G存在,v是G中某个顶点。操作结果: 删除G中顶点v及其相关的弧 */
   int i,j,k;
   VRType m=0;
   k=LocateVex(*G,v); /* k为待删除顶点v的序号 */
   if(k<0) /* v不是图G的顶点 */
     return ERROR;
   if((*G).kind==DN||(*G).kind==AN) /* 网 */
     m=INFINITY;
   for(j=0;j<(*G).vexnum;j++)
     if((*G).arcs[j][k].adj!=m) /* 有入弧或边 */
     {
       if((*G).arcs[j][k].info) /* 有相关信息 */
         free((*G).arcs[j][k].info); /* 释放相关信息 */
       (*G).arcnum--; /* 修改弧数 */
     }
   if((*G).kind==DG||(*G).kind==DN) /* 有向 */
     for(j=0;j<(*G).vexnum;j++)
       if((*G).arcs[k][j].adj!=m) /* 有出弧 */
       {
         if((*G).arcs[k][j].info) /* 有相关信息 */
           free((*G).arcs[k][j].info); /* 释放相关信息 */
         (*G).arcnum--; /* 修改弧数 */
       }
   for(j=k+1;j<(*G).vexnum;j++) /* 序号k后面的顶点向量依次前移 */
     strcpy((*G).vexs[j-1],(*G).vexs[j]);
   for(i=0;i<(*G).vexnum;i++)
     for(j=k+1;j<(*G).vexnum;j++)
       (*G).arcs[i][j-1]=(*G).arcs[i][j]; /* 移动待删除顶点之后的矩阵元素 */
   for(i=0;i<(*G).vexnum;i++)
     for(j=k+1;j<(*G).vexnum;j++)
       (*G).arcs[j-1][i]=(*G).arcs[j][i]; /* 移动待删除顶点之下的矩阵元素 */
   (*G).vexnum--; /* 更新图的顶点数 */
   return OK;
 }

 Status InsertArc(MGraph *G,VertexType v,VertexType w)
 { /* 初始条件: 图G存在,v和W是G中两个顶点 */
   /* 操作结果: 在G中增添弧<v,w>,若G是无向的,则还增添对称弧<w,v> */
   int i,l,v1,w1;
   char *info,s[MAX_INFO];
   v1=LocateVex(*G,v); /* 尾 */
   w1=LocateVex(*G,w); /* 头 */
   if(v1<0||w1<0)
     return ERROR;
   (*G).arcnum++; /* 弧或边数加1 */
   if((*G).kind%2) /* 网 */
   {
     printf("请输入此弧或边的权值: ");
     scanf("%d",&(*G).arcs[v1][w1].adj);
   }
   else /* 图 */
     (*G).arcs[v1][w1].adj=1;
   printf("是否有该弧或边的相关信息(0:无 1:有): ");
   scanf("%d%*c",&i);
   if(i)
   {
     printf("请输入该弧或边的相关信息(<%d个字符)：",MAX_INFO);
     gets(s);
     l=strlen(s);
     if(l)
     {
       info=(char*)malloc((l+1)*sizeof(char));
       strcpy(info,s);
       (*G).arcs[v1][w1].info=info;
     }
   }
   if((*G).kind>1) /* 无向 */
   {
     (*G).arcs[w1][v1].adj=(*G).arcs[v1][w1].adj;
     (*G).arcs[w1][v1].info=(*G).arcs[v1][w1].info; /* 指向同一个相关信息 */
   }
   return OK;
 }

 Status DeleteArc(MGraph *G,VertexType v,VertexType w)
 { /* 初始条件: 图G存在,v和w是G中两个顶点 */
   /* 操作结果: 在G中删除弧<v,w>,若G是无向的,则还删除对称弧<w,v> */
   int v1,w1;
   v1=LocateVex(*G,v); /* 尾 */
   w1=LocateVex(*G,w); /* 头 */
   if(v1<0||w1<0) /* v1、w1的值不合法 */
     return ERROR;
   if((*G).kind%2==0) /* 图 */
     (*G).arcs[v1][w1].adj=0;
   else /* 网 */
     (*G).arcs[v1][w1].adj=INFINITY;
   if((*G).arcs[v1][w1].info) /* 有其它信息 */
   {
     free((*G).arcs[v1][w1].info);
     (*G).arcs[v1][w1].info=NULL;
   }
   if((*G).kind>=2) /* 无向,删除对称弧<w,v> */
   {
     (*G).arcs[w1][v1].adj=(*G).arcs[v1][w1].adj;
     (*G).arcs[w1][v1].info=NULL;
   }
   (*G).arcnum--;
   return OK;
 }

 Boolean visited[MAX_VERTEX_NUM]; /* 访问标志数组(全局量) */
 Status(*VisitFunc)(VertexType); /* 函数变量 */
 void DFS(MGraph G,int v)
 { /* 从第v个顶点出发递归地深度优先遍历图G。算法7.5 */
   VertexType w1,v1;
   int w;
   visited[v]=TRUE; /* 设置访问标志为TRUE(已访问) */
   VisitFunc(G.vexs[v]); /* 访问第v个顶点 */
   strcpy(v1,*GetVex(G,v));
   for(w=FirstAdjVex(G,v1);w>=0;w=NextAdjVex(G,v1,strcpy(w1,*GetVex(G,w))))
     if(!visited[w])
       DFS(G,w); /* 对v的尚未访问的序号为w的邻接顶点递归调用DFS */
 }

 void DFSTraverse(MGraph G,Status(*Visit)(VertexType))
 { /* 初始条件: 图G存在,Visit是顶点的应用函数。算法7.4 */
   /* 操作结果: 从第1个顶点起,深度优先遍历图G,并对每个顶点调用函数Visit */
   /*           一次且仅一次。一旦Visit()失败,则操作失败 */
   int v;
   VisitFunc=Visit; /* 使用全局变量VisitFunc,使DFS不必设函数指针参数 */
   for(v=0;v<G.vexnum;v++)
     visited[v]=FALSE; /* 访问标志数组初始化(未被访问) */
   for(v=0;v<G.vexnum;v++)
     if(!visited[v])
       DFS(G,v); /* 对尚未访问的顶点调用DFS */
   printf("\n");
 }

 typedef VRType QElemType; /* 队列类型 */
 #include"c3-2.h" /* BFSTraverse()用 */
 #include"bo3-2.c" /* BFSTraverse()用 */
 void BFSTraverse(MGraph G,Status(*Visit)(VertexType))
 { /* 初始条件: 图G存在,Visit是顶点的应用函数。算法7.6 */
   /* 操作结果: 从第1个顶点起,按广度优先非递归遍历图G,并对每个顶点调用函数 */
   /*           Visit一次且仅一次。一旦Visit()失败,则操作失败。 */
   /*           使用辅助队列Q和访问标志数组visited */
   int v,u,w;
   VertexType w1,u1;
   LinkQueue Q;
   for(v=0;v<G.vexnum;v++)
     visited[v]=FALSE; /* 置初值 */
   InitQueue(&Q); /* 置空的辅助队列Q */
   for(v=0;v<G.vexnum;v++)
     if(!visited[v]) /* v尚未访问 */
     {
       visited[v]=TRUE; /* 设置访问标志为TRUE(已访问) */
       Visit(G.vexs[v]);
       EnQueue(&Q,v); /* v入队列 */
       while(!QueueEmpty(Q)) /* 队列不空 */
       {
         DeQueue(&Q,&u); /* 队头元素出队并置为u */
         strcpy(u1,*GetVex(G,u));
         for(w=FirstAdjVex(G,u1);w>=0;w=NextAdjVex(G,u1,strcpy(w1,*GetVex(G,w))))
           if(!visited[w]) /* w为u的尚未访问的邻接顶点的序号 */
           {
             visited[w]=TRUE;
             Visit(G.vexs[w]);
             EnQueue(&Q,w);
           }
       }
     }
   printf("\n");
 }

 void Display(MGraph G)
 { /* 输出邻接矩阵G */
   int i,j;
   char s[7],s1[3];
   switch(G.kind)
   {
     case DG: strcpy(s,"有向图\0");
              strcpy(s1,"弧\0");
              break;
     case DN: strcpy(s,"有向网\0");
              strcpy(s1,"弧\0");
              break;
     case AG: strcpy(s,"无向图\0");
              strcpy(s1,"边\0");
              break;
     case AN: strcpy(s,"无向网\0");
              strcpy(s1,"边\0");
   }
   printf("%d个顶点%d条%s的%s\n",G.vexnum,G.arcnum,s1,s);
   for(i=0;i<G.vexnum;++i) /* 输出G.vexs */
     printf("G.vexs[%d]=%s\n",i,G.vexs[i]);
   printf("G.arcs.adj:\n"); /* 输出G.arcs.adj */
   for(i=0;i<G.vexnum;i++)
   {
     for(j=0;j<G.vexnum;j++)
       printf("%6d",G.arcs[i][j].adj);
     printf("\n");
   }
   printf("G.arcs.info:\n"); /* 输出G.arcs.info */
   printf("顶点1(弧尾) 顶点2(弧头) 该%s信息：\n",s1);
   if(G.kind<2) /* 有向 */
     for(i=0;i<G.vexnum;i++)
       for(j=0;j<G.vexnum;j++)
       {
         if(G.arcs[i][j].info)
           printf("%5s %11s     %s\n",G.vexs[i],G.vexs[j],G.arcs[i][j].info);
       }
   else /* 无向 */
   {
     for(i=0;i<G.vexnum;i++)
       for(j=i+1;j<G.vexnum;j++)
	 if(G.arcs[i][j].info)
	   printf("%5s %11s     %s\n",G.vexs[i],G.vexs[j],G.arcs[i][j].info);
   }
 }


**********Bo7-2.c**********
 /* bo7-2.c 图的邻接表存储(存储结构由c7-2.h定义)的基本操作(15个) */
 int LocateVex(ALGraph G,VertexType u)
 { /* 初始条件: 图G存在,u和G中顶点有相同特征 */
   /* 操作结果: 若G中存在顶点u,则返回该顶点在图中位置;否则返回-1 */
   int i;
   for(i=0;i<G.vexnum;++i)
     if(strcmp(u,G.vertices[i].data)==0)
       return i;
   return -1;
 }

 Status CreateGraph(ALGraph *G)
 { /* 采用邻接表存储结构,构造没有相关信息的图G(用一个函数构造4种图) */
   int i,j,k;
   int w; /* 权值 */
   VertexType va,vb;
   ArcNode *p;
   printf("请输入图的类型(有向图:0,有向网:1,无向图:2,无向网:3): ");
   scanf("%d",&(*G).kind);
   printf("请输入图的顶点数,边数: ");
   scanf("%d,%d",&(*G).vexnum,&(*G).arcnum);
   printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
   for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
   {
     scanf("%s",(*G).vertices[i].data);
     (*G).vertices[i].firstarc=NULL;
   }
   if((*G).kind==1||(*G).kind==3) /* 网 */
     printf("请顺序输入每条弧(边)的权值、弧尾和弧头(以空格作为间隔):\n");
   else /* 图 */
     printf("请顺序输入每条弧(边)的弧尾和弧头(以空格作为间隔):\n");
   for(k=0;k<(*G).arcnum;++k) /* 构造表结点链表 */
   {
     if((*G).kind==1||(*G).kind==3) /* 网 */
       scanf("%d%s%s",&w,va,vb);
     else /* 图 */
       scanf("%s%s",va,vb);
     i=LocateVex(*G,va); /* 弧尾 */
     j=LocateVex(*G,vb); /* 弧头 */
     p=(ArcNode*)malloc(sizeof(ArcNode));
     p->adjvex=j;
     if((*G).kind==1||(*G).kind==3) /* 网 */
     {
       p->info=(int *)malloc(sizeof(int));
       *(p->info)=w;
     }
     else
       p->info=NULL; /* 图 */
     p->nextarc=(*G).vertices[i].firstarc; /* 插在表头 */
     (*G).vertices[i].firstarc=p;
     if((*G).kind>=2) /* 无向图或网,产生第二个表结点 */
     {
       p=(ArcNode*)malloc(sizeof(ArcNode));
       p->adjvex=i;
       if((*G).kind==3) /* 无向网 */
       {
         p->info=(int*)malloc(sizeof(int));
         *(p->info)=w;
       }
       else
         p->info=NULL; /* 无向图 */
       p->nextarc=(*G).vertices[j].firstarc; /* 插在表头 */
       (*G).vertices[j].firstarc=p;
     }
   }
   return OK;
 }

 void DestroyGraph(ALGraph *G)
 { /* 初始条件: 图G存在。操作结果: 销毁图G */
   int i;
   ArcNode *p,*q;
   (*G).vexnum=0;
   (*G).arcnum=0;
   for(i=0;i<(*G).vexnum;++i)
   {
     p=(*G).vertices[i].firstarc;
     while(p)
     {
       q=p->nextarc;
       if((*G).kind%2) /* 网 */
         free(p->info);
       free(p);
       p=q;
     }
   }
 }

 VertexType* GetVex(ALGraph G,int v)
 { /* 初始条件: 图G存在,v是G中某个顶点的序号。操作结果: 返回v的值 */
   if(v>=G.vexnum||v<0)
     exit(ERROR);
   return &G.vertices[v].data;
 }

 Status PutVex(ALGraph *G,VertexType v,VertexType value)
 { /* 初始条件: 图G存在,v是G中某个顶点 */
   /* 操作结果: 对v赋新值value */
   int i;
   i=LocateVex(*G,v);
   if(i>-1) /* v是G的顶点 */
   {
     strcpy((*G).vertices[i].data,value);
     return OK;
   }
   return ERROR;
 }

 int FirstAdjVex(ALGraph G,VertexType v)
 { /* 初始条件: 图G存在,v是G中某个顶点 */
   /* 操作结果: 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1 */
   ArcNode *p;
   int v1;
   v1=LocateVex(G,v); /* v1为顶点v在图G中的序号 */
   p=G.vertices[v1].firstarc;
   if(p)
     return p->adjvex;
   else
     return -1;
 }

 int NextAdjVex(ALGraph G,VertexType v,VertexType w)
 { /* 初始条件: 图G存在,v是G中某个顶点,w是v的邻接顶点 */
   /* 操作结果: 返回v的(相对于w的)下一个邻接顶点的序号。 */
   /*           若w是v的最后一个邻接点,则返回-1 */
   ArcNode *p;
   int v1,w1;
   v1=LocateVex(G,v); /* v1为顶点v在图G中的序号 */
   w1=LocateVex(G,w); /* w1为顶点w在图G中的序号 */
   p=G.vertices[v1].firstarc;
   while(p&&p->adjvex!=w1) /* 指针p不空且所指表结点不是w */
     p=p->nextarc;
   if(!p||!p->nextarc) /* 没找到w或w是最后一个邻接点 */
     return -1;
   else /* p->adjvex==w */
     return p->nextarc->adjvex; /* 返回v的(相对于w的)下一个邻接顶点的序号 */
 }

 void InsertVex(ALGraph *G,VertexType v)
 { /* 初始条件: 图G存在,v和图中顶点有相同特征 */
   /* 操作结果: 在图G中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做) */
   strcpy((*G).vertices[(*G).vexnum].data,v); /* 构造新顶点向量 */
   (*G).vertices[(*G).vexnum].firstarc=NULL;
   (*G).vexnum++; /* 图G的顶点数加1 */
 }

 Status DeleteVex(ALGraph *G,VertexType v)
 { /* 初始条件: 图G存在,v是G中某个顶点 */
   /* 操作结果: 删除G中顶点v及其相关的弧 */
   int i,j;
   ArcNode *p,*q;
   j=LocateVex(*G,v); /* j是顶点v的序号 */
   if(j<0) /* v不是图G的顶点 */
     return ERROR;
   p=(*G).vertices[j].firstarc; /* 删除以v为出度的弧或边 */
   while(p)
   {
     q=p;
     p=p->nextarc;
     if((*G).kind%2) /* 网 */
       free(q->info);
     free(q);
     (*G).arcnum--; /* 弧或边数减1 */
   }
   (*G).vexnum--; /* 顶点数减1 */
   for(i=j;i<(*G).vexnum;i++) /* 顶点v后面的顶点前移 */
     (*G).vertices[i]=(*G).vertices[i+1];
   for(i=0;i<(*G).vexnum;i++) /* 删除以v为入度的弧或边且必要时修改表结点的顶点位置值 */
   {
     p=(*G).vertices[i].firstarc; /* 指向第1条弧或边 */
     while(p) /* 有弧 */
     {
       if(p->adjvex==j)
       {
         if(p==(*G).vertices[i].firstarc) /* 待删结点是第1个结点 */
         {
           (*G).vertices[i].firstarc=p->nextarc;
           if((*G).kind%2) /* 网 */
             free(p->info);
           free(p);
           p=(*G).vertices[i].firstarc;
           if((*G).kind<2) /* 有向 */
             (*G).arcnum--; /* 弧或边数减1 */
         }
         else
         {
           q->nextarc=p->nextarc;
           if((*G).kind%2) /* 网 */
             free(p->info);
           free(p);
           p=q->nextarc;
           if((*G).kind<2) /* 有向 */
             (*G).arcnum--; /* 弧或边数减1 */
         }
       }
       else
       {
         if(p->adjvex>j)
           p->adjvex--; /* 修改表结点的顶点位置值(序号) */
         q=p;
         p=p->nextarc;
       }
     }
   }
   return OK;
 }

 Status InsertArc(ALGraph *G,VertexType v,VertexType w)
 { /* 初始条件: 图G存在,v和w是G中两个顶点 */
   /* 操作结果: 在G中增添弧<v,w>,若G是无向的,则还增添对称弧<w,v> */
   ArcNode *p;
   int w1,i,j;
   i=LocateVex(*G,v); /* 弧尾或边的序号 */
   j=LocateVex(*G,w); /* 弧头或边的序号 */
   if(i<0||j<0)
     return ERROR;
   (*G).arcnum++; /* 图G的弧或边的数目加1 */
   if((*G).kind%2) /* 网 */
   {
     printf("请输入弧(边)%s→%s的权值: ",v,w);
     scanf("%d",&w1);
   }
   p=(ArcNode*)malloc(sizeof(ArcNode));
   p->adjvex=j;
   if((*G).kind%2) /* 网 */
   {
     p->info=(int*)malloc(sizeof(int));
     *(p->info)=w1;
   }
   else
     p->info=NULL;
   p->nextarc=(*G).vertices[i].firstarc; /* 插在表头 */
   (*G).vertices[i].firstarc=p;
   if((*G).kind>=2) /* 无向,生成另一个表结点 */
   {
     p=(ArcNode*)malloc(sizeof(ArcNode));
     p->adjvex=i;
     if((*G).kind==3) /* 无向网 */
     {
       p->info=(int*)malloc(sizeof(int));
       *(p->info)=w1;
     }
     else
       p->info=NULL;
     p->nextarc=(*G).vertices[j].firstarc; /* 插在表头 */
     (*G).vertices[j].firstarc=p;
   }
   return OK;
 }

 Status DeleteArc(ALGraph *G,VertexType v,VertexType w)
 { /* 初始条件: 图G存在,v和w是G中两个顶点 */
   /* 操作结果: 在G中删除弧<v,w>,若G是无向的,则还删除对称弧<w,v> */
   ArcNode *p,*q;
   int i,j;
   i=LocateVex(*G,v); /* i是顶点v(弧尾)的序号 */
   j=LocateVex(*G,w); /* j是顶点w(弧头)的序号 */
   if(i<0||j<0||i==j)
     return ERROR;
   p=(*G).vertices[i].firstarc; /* p指向顶点v的第一条出弧 */
   while(p&&p->adjvex!=j) /* p不空且所指之弧不是待删除弧<v,w> */
   { /* p指向下一条弧 */
     q=p;
     p=p->nextarc;
   }
   if(p&&p->adjvex==j) /* 找到弧<v,w> */
   {
     if(p==(*G).vertices[i].firstarc) /* p所指是第1条弧 */
       (*G).vertices[i].firstarc=p->nextarc; /* 指向下一条弧 */
     else
       q->nextarc=p->nextarc; /* 指向下一条弧 */
     if((*G).kind%2) /* 网 */
       free(p->info);
     free(p); /* 释放此结点 */
     (*G).arcnum--; /* 弧或边数减1 */
   }
   if((*G).kind>=2) /* 无向,删除对称弧<w,v> */
   {
     p=(*G).vertices[j].firstarc; /* p指隙サ鉾的第一条出弧 */
     while(p&&p->adjvex!=i) /* p不空且所指之弧不是待删除弧<w,v> */
     { /* p指向下一条弧 */
       q=p;
       p=p->nextarc;
     }
     if(p&&p->adjvex==i) /* 找到弧<w,v> */
     {
       if(p==(*G).vertices[j].firstarc) /* p所指是第1条弧 */
         (*G).vertices[j].firstarc=p->nextarc; /* 指向下一条弧 */
       else
         q->nextarc=p->nextarc; /* 指向下一条弧 */
       if((*G).kind==3) /* 无向网 */
         free(p->info);
       free(p); /* 释放此结点 */
     }
   }
   return OK;
 }

 Boolean visited[MAX_VERTEX_NUM]; /* 访问标志数组(全局量) */
 void(*VisitFunc)(char* v); /* 函数变量(全局量) */
 void DFS(ALGraph G,int v)
 { /* 从第v个顶点出发递归地深度优先遍历图G。算法7.5 */
   int w;
   VertexType v1,w1;
   strcpy(v1,*GetVex(G,v));
   visited[v]=TRUE; /* 设置访问标志为TRUE(已访问) */
   VisitFunc(G.vertices[v].data); /* 访问第v个顶点 */
   for(w=FirstAdjVex(G,v1);w>=0;w=NextAdjVex(G,v1,strcpy(w1,*GetVex(G,w))))
     if(!visited[w])
       DFS(G,w); /* 对v的尚未访问的邻接点w递归调用DFS */
 }

 void DFSTraverse(ALGraph G,void(*Visit)(char*))
 { /* 对图G作深度优先遍历。算法7.4 */
   int v;
   VisitFunc=Visit; /* 使用全局变量VisitFunc,使DFS不必设函数指针参数 */
   for(v=0;v<G.vexnum;v++)
     visited[v]=FALSE; /* 访问标志数组初始化 */
   for(v=0;v<G.vexnum;v++)
     if(!visited[v])
       DFS(G,v); /* 对尚未访问的顶点调用DFS */
   printf("\n");
 }

 typedef int QElemType; /* 队列类型 */
 #include"c3-2.h"
 #include"bo3-2.c"
 void BFSTraverse(ALGraph G,void(*Visit)(char*))
 {/*按广度优先非递归遍历图G。使用辅助队列Q和访问标志数组visited。算法7.6 */
   int v,u,w;
   VertexType u1,w1;
   LinkQueue Q;
   for(v=0;v<G.vexnum;++v)
     visited[v]=FALSE; /* 置初值 */
   InitQueue(&Q); /* 置空的辅助队列Q */
   for(v=0;v<G.vexnum;v++) /* 如果是连通图,只v=0就遍历全图 */
     if(!visited[v]) /* v尚未访问 */
     {
       visited[v]=TRUE;
       Visit(G.vertices[v].data);
       EnQueue(&Q,v); /* v入队列 */
       while(!QueueEmpty(Q)) /* 队列不空 */
       {
         DeQueue(&Q,&u); /* 队头元素出队并置为u */
         strcpy(u1,*GetVex(G,u));
         for(w=FirstAdjVex(G,u1);w>=0;w=NextAdjVex(G,u1,strcpy(w1,*GetVex(G,w))))
           if(!visited[w]) /* w为u的尚未访问的邻接顶点 */
           {
             visited[w]=TRUE;
             Visit(G.vertices[w].data);
             EnQueue(&Q,w); /* w入队 */
           }
       }
     }
   printf("\n");
 }

 void Display(ALGraph G)
 { /* 输出图的邻接矩阵G */
   int i;
   ArcNode *p;
   switch(G.kind)
   {
     case DG: printf("有向图\n");
              break;
     case DN: printf("有向网\n");
              break;
     case AG: printf("无向图\n");
              break;
     case AN: printf("无向网\n");
   }
   printf("%d个顶点：\n",G.vexnum);
   for(i=0;i<G.vexnum;++i)
     printf("%s ",G.vertices[i].data);
   printf("\n%d条弧(边):\n",G.arcnum);
   for(i=0;i<G.vexnum;i++)
   {
     p=G.vertices[i].firstarc;
     while(p)
     {
       if(G.kind<=1) /* 有向 */
       {
         printf("%s→%s ",G.vertices[i].data,G.vertices[p->adjvex].data);
         if(G.kind==DN) /* 网 */
           printf(":%d ",*(p->info));
       }
       else /* 无向(避免输出两次) */
       {
         if(i<p->adjvex)
         {
           printf("%s－%s ",G.vertices[i].data,G.vertices[p->adjvex].data);
           if(G.kind==AN) /* 网 */
             printf(":%d ",*(p->info));
         }
       }
       p=p->nextarc;
     }
     printf("\n");
   }
 }

**********Bo7-3.c**********
 /* bo7-3.c 有向图的十字链表存储(存储结构由c7-3.h定义)的基本函数(15个) */
 int LocateVex(OLGraph G,VertexType u)
 { /* 返回顶点u在有向图G中的位置(序号),如不存在则返回-1 */
   int i;
   for(i=0;i<G.vexnum;++i) /* 用循环查找该结点 */
     if(!strcmp(G.xlist[i].data,u))
       return i;
   return -1;
 }

 Status CreateDG(OLGraph *G)
 { /* 采用十字链表存储表示,构造有向图G。算法7.3 */
   int i,j,k;
   int IncInfo;
   char str[MAX_Info];
   ArcBox *p;
   VertexType v1,v2;
   printf("请输入有向图的顶点数,弧数,弧是否含其它信息(是:1，否:0): ");
   scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
   printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_VERTEX_NAME);
   for(i=0;i<(*G).vexnum;++i)
   { /* 构造表头向量 */
     scanf("%s",&(*G).xlist[i].data); /* 输入顶点值 */
     (*G).xlist[i].firstin=NULL; /* 初始化指针 */
     (*G).xlist[i].firstout=NULL;
   }
   printf("请输入%d条弧的弧尾和弧头(空格为间隔):\n",(*G).arcnum);
   for(k=0;k<(*G).arcnum;++k)
   { /* 输入各弧并构造十字链表 */
     scanf("%s%s",&v1,&v2);
     i=LocateVex(*G,v1); /* 确定v1和v2在G中的位置 */
     j=LocateVex(*G,v2);
     p=(ArcBox *)malloc(sizeof(ArcBox)); /* 产生弧结点(假定有足够空间) */
     p->tailvex=i; /* 对弧结点赋值 */
     p->headvex=j;
     p->hlink=(*G).xlist[j].firstin; /* 完成在入弧和出弧链表表头的插入 */
     p->tlink=(*G).xlist[i].firstout;
     (*G).xlist[j].firstin=(*G).xlist[i].firstout=p;
     if(IncInfo)
     { /* 若弧含有相关信息，则输入 */
       printf("请输入该弧的相关信息(<%d个字符): ",MAX_Info);
       scanf("%s",str);
       p->info=(InfoType *)malloc((strlen(str)+1)*sizeof(InfoType));
       strcpy(p->info,str);
     }
     else /* 弧不含有相关信息 */
       p->info=NULL;
   }
   return OK;
 }

 void DestroyGraph(OLGraph *G)
 { /* 初始条件: 有向图G存在 */
   /* 操作结果: 销毁有向图G */
   int j;
   ArcBox *p,*q;
   for(j=0;j<(*G).vexnum;j++) /* 对所有顶点 */
   {
     p=(*G).xlist[j].firstout; /* 仅处理出弧 */
     while(p)
     {
       q=p;
       p=p->tlink;
       if(q->info)
         free(q->info);
       free(q);
     }
   }
   (*G).arcnum=0;
   (*G).vexnum=0;
 }

 VertexType* GetVex(OLGraph G,int v)
 { /* 初始条件:有向图G存在,v是G中某个顶点的序号。操作结果:返回v的值 */
   if(v>=G.vexnum||v<0)
     exit(ERROR);
   return &G.xlist[v].data;
 }

 Status PutVex(OLGraph *G,VertexType v,VertexType value)
 { /* 初始条件: 有向图G存在,v是G中某个顶点 */
   /* 操作结果: 对v赋新值value */
   int i;
   i=LocateVex(*G,v);
   if(i<0) /* v不是G的顶点 */
     return ERROR;
   strcpy((*G).xlist[i].data,value);
   return OK;
 }

 int FirstAdjVex(OLGraph G,VertexType v)
 { /* 初始条件: 有向图G存在,v是G中某个顶点 */
   /* 操作结果: 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1 */
   int i;
   ArcBox *p;
   i=LocateVex(G,v);
   p=G.xlist[i].firstout; /* p指向顶点v的第1个出弧 */
   if(p)
     return p->headvex;
   else
     return -1;
 }

 int NextAdjVex(OLGraph G,VertexType v,VertexType w)
 { /* 初始条件: 有向图G存在,v是G中某个顶点,w是v的邻接顶点 */
   /* 操作结果: 返回v的(相对于w的)下一个邻接顶点的序号, */
   /*           若w是v的最后一个邻接顶点,则返回-1 */
   int i,j;
   ArcBox *p;
   i=LocateVex(G,v); /* i是顶点v的序号 */
   j=LocateVex(G,w); /* j是顶点w的序号 */
   p=G.xlist[i].firstout; /* p指向顶点v的第1个出弧 */
   while(p&&p->headvex!=j)
     p=p->tlink;
   if(p) /* w不是v的最后一个邻接顶点 */
     p=p->tlink; /* p指向相对于w的下一个邻接顶点 */
   if(p) /* 有下一个邻接顶点 */
     return p->headvex;
   else
     return -1;
 }

 void InsertVex(OLGraph *G,VertexType v)
 { /* 初始条件: 有向图G存在,v和有向图G中顶点有相同特征 */
   /* 操作结果: 在有向图G中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做) */
   strcpy((*G). xlist[(*G). vexnum].data,v);
   (*G). xlist[(*G). vexnum].firstin=(*G). xlist[(*G). vexnum].firstout=NULL;
   (*G). vexnum++;
 }

 Status DeleteVex(OLGraph *G,VertexType v)
 { /* 初始条件: 有向图G存在,v是G中某个顶点 */
   /* 操作结果: 删除G中顶点v及其相关的弧 */
   int j,k;
   ArcBox *p,*q;
   k=LocateVex(*G,v); /* k是顶点v的序号 */
   if(k<0) /* v不是图G的顶点 */
     return ERROR;
   /* 以下删除顶点v的出弧 */
   for(j=0;j<(*G). vexnum;j++) /* 顶点v的出弧是其它顶点的入弧 */
   {
     if(j==k)
       continue;
     p=(*G). xlist[j].firstin; /* 在其它顶点的入弧链表中删除顶点v的出弧 */
     while(p)
       if(p->tailvex==k&&p==(*G). xlist[j].firstin) /* 待删结点为首结点 */
       {
         (*G). xlist[j].firstin=p->hlink;
         break;
       }
       else if(p->tailvex!=k) /* 没找到待删结点 */
       {
         q=p;
         p=p->hlink;
       }
       else /* 找到待删结点且不是首结点 */
       {
         q->hlink=p->hlink;
         break;
       }
   }
   p=(*G). xlist[k].firstout; /* 删除与顶点v有关的出弧 */
   while(p)
   {
     q=p->tlink; /* q指向p的下一个出弧 */
     if(p->info) /* 释放p */
       free(p->info);
     free(p);
     (*G). arcnum--;
     p=q;
   }
   /* 以下删除顶点v的入弧 */
   for(j=0;j<(*G). vexnum;j++) /* 顶点v的入弧是其它顶点的出弧 */
   {
     if(j==k)
       continue;
     p=(*G). xlist[j].firstout; /* 在其它顶点的出弧链表中删除顶点v的入弧 */
     while(p)
       if(p->headvex==k&&p==(*G). xlist[j].firstout) /* 待删结点为首结点 */
       {
         (*G). xlist[j].firstout=p->tlink;
         break;
       }
       else if(p->headvex!=k) /* 没找到待删结点 */
       {
         q=p;
         p=p->tlink;
       }
       else /* 找到待删结点且不是首结点 */
       {
         q->tlink=p->tlink;
         break;
       }
   }
   p=(*G). xlist[k].firstin; /* 删除与顶点v有关的入弧 */
   while(p)
   {
     q=p->hlink; /* q指向p的下一个入弧 */
     if(p->info) /* 释放p */
       free(p->info);
     free(p);
     (*G). arcnum--;
     p=q;
   }
   for(j=k+1;j<(*G). vexnum;j++) /* 序号>k的顶点依次向前移 */
     (*G). xlist[j-1]=(*G). xlist[j];
   (*G). vexnum--; /* 顶点数减1 */
   for(j=0;j<(*G). vexnum;j++) /* 结点序号>k的要减1 */
   {
     p=(*G). xlist[j].firstout; /* 处理出弧 */
     while(p)
     {
       if(p->tailvex>k)
         p->tailvex--; /* 序号-1 */
       if(p->headvex>k)
         p->headvex--; /* 序号-1 */
       p=p->tlink;
     }
   }
   return OK;
 }

 Status InsertArc(OLGraph *G,VertexType v,VertexType w)
 { /* 初始条件: 有向图G存在,v和w是G中两个顶点 */
   /* 操作结果: 在G中增添弧<v,w> */
   int i,j;
   int IncInfo;
   char str[MAX_Info];
   ArcBox *p;
   i=LocateVex(*G,v); /* 弧尾的序号 */
   j=LocateVex(*G,w); /* 弧头的序号 */
   if(i<0||j<0)
     return ERROR;
   p=(ArcBox *)malloc(sizeof(ArcBox)); /* 生成新结点 */
   p->tailvex=i; /* 给新结点赋值 */
   p->headvex=j;
   p->hlink=(*G). xlist[j].firstin; /* 插在入弧和出弧的链头 */
   p->tlink=(*G). xlist[i].firstout;
   (*G). xlist[j].firstin=(*G). xlist[i].firstout=p;
   (*G). arcnum++; /* 弧数加1 */
   printf("要插入的弧是否含有其它信息(是: 1,否: 0): ");
   scanf("%d",&IncInfo);
   if(IncInfo)
   {
     printf("请输入该弧的相关信息(<%d个字符): ",MAX_Info);
     scanf("%s",str);
     p->info=(InfoType *)malloc((strlen(str)+1)*sizeof(InfoType));
     strcpy(p->info,str);
   }
   else
     p->info=NULL;
   return OK;
 }

 Status DeleteArc(OLGraph *G,VertexType v,VertexType w)
 { /* 初始条件: 有向图G存在,v和w是G中两个顶点 */
   /* 操作结果: 在G中删除弧<v,w> */
   int i,j;
   ArcBox *p1,*p2;
   i=LocateVex(*G,v); /* 弧尾的序号 */
   j=LocateVex(*G,w); /* 弧头的序号 */
   if(i<0||j<0||i==j)
     return ERROR;
   p2=(*G). xlist[i].firstout; /* 将弧结点从出弧链表中删去 */
   if(p2&&p2->headvex==j) /* 第1个结点为待删除结点 */
     (*G). xlist[i].firstout=p2->tlink;
   else
   {
     while(p2&&p2->headvex!=j) /* 向后找 */
     {
       p1=p2;
       p2=p2->tlink;
     }
     if(p2) /* 没到表尾 */
       p1->tlink=p2->tlink;
   }
   p2=(*G). xlist[j].firstin; /* 将弧结点从入弧链表中删去 */
   if(p2&&p2->tailvex==i)
     (*G). xlist[j].firstin=p2->hlink;
   else
   {
     while(p2&&p2->tailvex!=i)
     {
       p1=p2;
       p2=p2->hlink;
     }
     if(p2) /* 没到表尾 */
       p1->hlink=p2->hlink;
   }
   if(p2->info) /* 释放弧结点 */
     free(p2->info);
   free(p2);
   (*G). arcnum--; /* 弧数减1 */
   return OK;
 }

 Boolean visited[MAX_VERTEX_NUM]; /* 访问标志数组 */
 Status(*VisitFunc)(VertexType); /* 函数变量 */
 void DFS(OLGraph G,int i) /* DFSTraverse()调用 */
 {
   ArcBox *p;
   visited[i]=TRUE; /* 访问标志数组置1(已被访问) */
   VisitFunc(G.xlist[i].data); /* 遍历第i个顶点 */
   p=G.xlist[i].firstout; /* p指向第i个顶点的出度 */
   while(p&&visited[p->headvex]) /* p没到表尾且该弧的头顶点已被访问 */
     p=p->tlink; /* 查找下一个结点 */
   if(p&&!visited[p->headvex]) /* 该弧的头顶点未被访问 */
     DFS(G,p->headvex); /* 递归调用DFS() */
 }

 void DFSTraverse(OLGraph G,Status(*Visit)(VertexType))
 { /* 初始条件: 有向图G存在,v是G中某个顶点,Visit是顶点的应用函数 */
   /* 操作结果: 从第1个顶点起,按深度优先递归遍历有向图G,并对每个顶点调用 */
   /*           函数Visit一次且仅一次。一旦Visit()失败,则操作失败 */
   int i;
   for(i=0;i<G.vexnum;i++)
     visited[i]=FALSE; /* 访问标志数组置初值(未被访问) */
   VisitFunc=Visit;
   for(i=0;i<G.vexnum;i++) /* 由序号0开始,继续查找未被访问过的顶点 */
     if(!visited[i])
       DFS(G,i);
   printf("\n");
 }

 typedef int QElemType;
 #include"c3-3.h"
 #include"bo3-3.c"
 void BFSTraverse(OLGraph G,Status(*Visit)(VertexType))
 { /* 初始条件: 有向图G存在,Visit是顶点的应用函数。算法7.6 */
   /* 操作结果: 从第1个顶点起,按广度优先非递归遍历有向图G,并对每个顶点调用 */
   /*           函数Visit一次且仅一次。一旦Visit()失败,则操作失败。 */
   /*           使用辅助队列Q和访问标志数组visited */
   int v,u,w;
   VertexType u1,w1;
   SqQueue Q;
   for(v=0;v<G.vexnum;v++)
     visited[v]=FALSE;
   InitQueue(&Q);
   for(v=0;v<G.vexnum;v++)
     if(!visited[v])
     {
       visited[v]=TRUE;
       Visit(G.xlist[v].data);
       EnQueue(&Q,v);
       while(!QueueEmpty(Q))
       {
         DeQueue(&Q,&u);
         strcpy(u1,*GetVex(G,u));
         for(w=FirstAdjVex(G,u1);w>=0;w=NextAdjVex(G,u1,strcpy(w1,*GetVex(G,w))))
           if(!visited[w]) /* w为u的尚未访问的邻接顶点的序号 */
           {
             visited[w]=TRUE;
             Visit(G.xlist[w].data);
             EnQueue(&Q,w);
           }
       }
     }
   printf("\n");
 }

 void Display(OLGraph G)
 { /* 输出有向图G */
   int i;
   ArcBox *p;
   printf("共%d个顶点,%d条弧:\n",G.vexnum,G.arcnum);
   for(i=0;i<G.vexnum;i++)
   {
     printf("顶点%s: 入度: ",G.xlist[i].data);
     p=G.xlist[i].firstin;
     while(p)
     {
       printf("%s ",G.xlist[p->tailvex].data);
       p=p->hlink;
     }
     printf("出度: ");
     p=G.xlist[i].firstout;
     while(p)
     {
       printf("%s ",G.xlist[p->headvex].data);
       if(p->info) /* 该弧有相关信息 */
         printf("弧信息: %s ",p->info);
       p=p->tlink;
     }
     printf("\n");
   }
 }

**********Bo7-4.c**********
 /* bo7-4.c 无向图的邻接多重表存储(存储结构由c7-4.h定义)的基本函数类型(16个) */
 int LocateVex(AMLGraph G,VertexType u)
 { /* 初始条件: 无向图G存在,u和G中顶点有相同特征 */
   /* 操作结果: 若G中存在顶点u,则返回该顶点在无向图中位置;否则返回-1 */
   int i;
   for(i=0;i<G.vexnum;++i)
     if(strcmp(u,G.adjmulist[i].data)==0)
       return i;
   return -1;
 }

 Status CreateGraph(AMLGraph *G)
 { /* 采用邻接多重表存储结构,构造无向图G */
   int i,j,k,l,IncInfo;
   char s[MAX_INFO];
   VertexType va,vb;
   EBox *p;
   printf("请输入无向图G的顶点数,边数,边是否含其它信息(是:1，否:0): ");
   scanf("%d,%d,%d",&(*G).vexnum,&(*G).edgenum,&IncInfo);
   printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
   for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
   {
     scanf("%s",(*G).adjmulist[i].data);
     (*G).adjmulist[i].firstedge=NULL;
   }
   printf("请顺序输入每条边的两个端点(以空格作为间隔):\n");
   for(k=0;k<(*G).edgenum;++k) /* 构造表结点链表 */
   {
     scanf("%s%s%*c",va,vb); /* %*c吃掉回车符 */
     i=LocateVex(*G,va); /* 一端 */
     j=LocateVex(*G,vb); /* 另一端 */
     p=(EBox*)malloc(sizeof(EBox));
     p->mark=unvisited; /* 设初值 */
     p->ivex=i;
     p->jvex=j;
     p->info=NULL;
     p->ilink=(*G).adjmulist[i].firstedge; /* 插在表头 */
     (*G).adjmulist[i].firstedge=p;
     p->jlink=(*G).adjmulist[j].firstedge; /* 插在表头 */
     (*G).adjmulist[j].firstedge=p;
     if(IncInfo) /* 边有相关信息 */
     {
       printf("请输入该弧的相关信息(<%d个字符)：",MAX_INFO);
       gets(s);
       l=strlen(s);
       if(l)
       {
         p->info=(char*)malloc((l+1)*sizeof(char));
         strcpy(p->info,s);
       }
     }
   }
   return OK;
 }

 VertexType* GetVex(AMLGraph G,int v)
 { /* 初始条件: 无向图G存在,v是G中某个顶点的序号。操作结果: 返回v的值 */
   if(v>=G.vexnum||v<0)
     exit(ERROR);
   return &G.adjmulist[v].data;
 }

 Status PutVex(AMLGraph *G,VertexType v,VertexType value)
 { /* 初始条件: 无向图G存在,v是G中某个顶点 */
   /* 操作结果: 对v赋新值value */
   int i;
   i=LocateVex(*G,v);
   if(i<0) /* v不是G的顶点 */
     return ERROR;
   strcpy((*G).adjmulist[i].data,value);
   return OK;
 }

 int FirstAdjVex(AMLGraph G,VertexType v)
 { /* 初始条件: 无向图G存在,v是G中某个顶点 */
   /* 操作结果: 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1 */
   int i;
   i=LocateVex(G,v);
   if(i<0)
     return -1;
   if(G.adjmulist[i].firstedge) /* v有邻接顶点 */
     if(G.adjmulist[i].firstedge->ivex==i)
       return G.adjmulist[i].firstedge->jvex;
     else
       return G.adjmulist[i].firstedge->ivex;
   else
     return -1;
 }

 int NextAdjVex(AMLGraph G,VertexType v,VertexType w)
 { /* 初始条件: 无向图G存在,v是G中某个顶点,w是v的邻接顶点 */
   /* 操作结果: 返回v的(相对于w的)下一个邻接顶点的序号。 */
   /*           若w是v的最后一个邻接点,则返回-1 */
   int i,j;
   EBox *p;
   i=LocateVex(G,v); /* i是顶点v的序号 */
   j=LocateVex(G,w); /* j是顶点w的序号 */
   if(i<0||j<0) /* v或w不是G的顶点 */
     return -1;
   p=G.adjmulist[i].firstedge; /* p指向顶点v的第1条边 */
   while(p)
     if(p->ivex==i&&p->jvex!=j) /* 不是邻接顶点w(情况1) */
       p=p->ilink; /* 找下一个邻接顶点 */
     else if(p->jvex==i&&p->ivex!=j) /* 不是邻接顶点w(情况2) */
       p=p->jlink; /* 找下一个邻接顶点 */
     else /* 是邻接顶点w */
       break;
   if(p&&p->ivex==i&&p->jvex==j) /* 找到邻接顶点w(情况1) */
   {
     p=p->ilink;
     if(p&&p->ivex==i)
       return p->jvex;
     else if(p&&p->jvex==i)
       return p->ivex;
   }
   if(p&&p->ivex==j&&p->jvex==i) /* 找到邻接顶点w(情况2) */
   {
     p=p->jlink;
     if(p&&p->ivex==i)
       return p->jvex;
     else if(p&&p->jvex==i)
       return p->ivex;
   }
   return -1;
 }

 Status InsertVex(AMLGraph *G,VertexType v)
 { /* 初始条件: 无向图G存在,v和G中顶点有相同特征 */
   /* 操作结果: 在G中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做) */
   if((*G).vexnum==MAX_VERTEX_NUM) /* 结点已满，不能插入 */
     return ERROR;
   if(LocateVex(*G,v)>=0) /* 结点已存在,不能插入 */
     return ERROR;
   strcpy((*G).adjmulist[(*G).vexnum].data,v);
   (*G).adjmulist[(*G).vexnum].firstedge=NULL;
   (*G).vexnum++;
   return OK;
 }

 Status DeleteArc(AMLGraph *G,VertexType v,VertexType w)
 { /* 初始条件: 无向图G存在,v和w是G中两个顶点 */
   /* 操作结果: 在G中删除弧<v,w> */
   int i,j;
   EBox *p,*q;
   i=LocateVex(*G,v);
   j=LocateVex(*G,w);
   if(i<0||j<0||i==j)
     return ERROR;  /* 图中没有该点或弧 */
   /* 以下使指向待删除边的第1个指针绕过这条边 */
   p=(*G).adjmulist[i].firstedge; /* p指向顶点v的第1条边 */
   if(p&&p->jvex==j) /* 第1条边即为待删除边(情况1) */
     (*G).adjmulist[i].firstedge=p->ilink;
   else if(p&&p->ivex==j) /* 第1条边即为待删除边(情况2) */
     (*G).adjmulist[i].firstedge=p->jlink;
   else /* 第1条边不是待删除边 */
   {
     while(p) /* 向后查找弧<v,w> */
     {
       if(p->ivex==i&&p->jvex!=j) /* 不是待删除边 */
       {
         q=p;
         p=p->ilink; /* 找下一个邻接顶点 */
       }
       else if(p->jvex==i&&p->ivex!=j) /* 不是待删除边 */
       {
         q=p;
         p=p->jlink; /* 找下一个邻接顶点 */
       }
       else /* 是邻接顶点w */
         break;
     }
     if(!p) /* 没找到该边 */
       return ERROR;
     if(p->ivex==i&&p->jvex==j) /* 找到弧<v,w>(情况1) */
       if(q->ivex==i)
         q->ilink=p->ilink;
       else
         q->jlink=p->ilink;
     else if(p->ivex==j&&p->jvex==i) /* 找到弧<v,w>(情况2) */
       if(q->ivex==i)
         q->ilink=p->jlink;
       else
         q->jlink=p->jlink;
   }
   /* 以下由另一顶点起找待删除边且删除之 */
   p=(*G).adjmulist[j].firstedge; /* p指向顶点w的第1条边 */
   if(p->jvex==i) /* 第1条边即为待删除边(情况1) */
   {
     (*G).adjmulist[j].firstedge=p->ilink;
     if(p->info) /* 有相关信息 */
       free(p->info);
     free(p);
   }
   else if(p->ivex==i) /* 第1条边即为待删除边(情况2) */
   {
     (*G).adjmulist[j].firstedge=p->jlink;
     if(p->info) /* 有相关信息 */
       free(p->info);
     free(p);
   }
   else /* 第1条边不是待删除边 */
   {
     while(p) /* 向后查找弧<v,w> */
       if(p->ivex==j&&p->jvex!=i) /* 不是待删除边 */
       {
         q=p;
         p=p->ilink; /* 找下一个邻接顶点 */
       }
       else if(p->jvex==j&&p->ivex!=i) /* 不是待删除边 */
       {
         q=p;
         p=p->jlink; /* 找下一个邻接顶点 */
       }
       else /* 是邻接顶点v */
         break;
     if(p->ivex==i&&p->jvex==j) /* 找到弧<v,w>(情况1) */
     {
       if(q->ivex==j)
         q->ilink=p->jlink;
       else
         q->jlink=p->jlink;
       if(p->info) /* 有相关信息 */
         free(p->info);
       free(p);
     }
     else if(p->ivex==j&&p->jvex==i) /* 找到弧<v,w>(情况2) */
     {
       if(q->ivex==j)
         q->ilink=p->ilink;
       else
         q->jlink=p->ilink;
       if(p->info) /* 有相关信息 */
         free(p->info);
       free(p);
     }
   }
   (*G).edgenum--;
   return OK;
 }

 Status DeleteVex(AMLGraph *G,VertexType v)
 { /* 初始条件: 无向图G存在,v是G中某个顶点 */
   /* 操作结果: 删除G中顶点v及其相关的边 */
   int i,j;
   VertexType w;
   EBox *p;
   i=LocateVex(*G,v); /* i为待删除顶点的序号 */
   if(i<0)
     return ERROR;
   for(j=0;j<(*G).vexnum;j++) /* 删除与顶点v相连的边(如果有的话) */
   {
     if(j==i)
       continue;
     strcpy(w,*GetVex(*G,j)); /* w是第j个顶点的值 */
     DeleteArc(G,v,w);
   }
   for(j=i+1;j<(*G).vexnum;j++) /* 排在顶点v后面的顶点的序号减1 */
     (*G).adjmulist[j-1]=(*G).adjmulist[j];
   (*G).vexnum--; /* 顶点数减1 */
   for(j=i;j<(*G).vexnum;j++) /* 修改顶点的序号 */
   {
     p=(*G).adjmulist[j].firstedge;
     if(p)
     {
       if(p->ivex==j+1)
       {
         p->ivex--;
         p=p->ilink;
       }
       else
       {
         p->jvex--;
         p=p->jlink;
       }
     }
   }
   return OK;
 }

 void DestroyGraph(AMLGraph *G)
 {
   int i;
   for(i=(*G).vexnum-1;i>=0;i--)
     DeleteVex(G,(*G).adjmulist[i].data);
 }

 Status InsertArc(AMLGraph *G,VertexType v,VertexType w)
 { /* 初始条件: 无向图G存在,v和W是G中两个顶点 */
   /* 操作结果: 在G中增添弧<v,w> */
   int i,j,l,IncInfo;
   char s[MAX_INFO];
   EBox *p;
   i=LocateVex(*G,v); /* 一端 */
   j=LocateVex(*G,w); /* 另一端 */
   if(i<0||j<0)
     return ERROR;
   p=(EBox*)malloc(sizeof(EBox));
   p->mark=unvisited;
   p->ivex=i;
   p->jvex=j;
   p->info=NULL;
   p->ilink=(*G).adjmulist[i].firstedge; /* 插在表头 */
   (*G).adjmulist[i].firstedge=p;
   p->jlink=(*G).adjmulist[j].firstedge; /* 插在表头 */
   (*G).adjmulist[j].firstedge=p;
   printf("该边是否有相关信息(1:有 0:无): ");
   scanf("%d%*c",&IncInfo); /* 吃掉回车符 */
   if(IncInfo) /* 边有相关信息 */
   {
     printf("请输入该边的相关信息(<%d个字符)：",MAX_INFO);
     gets(s);
     l=strlen(s);
     if(l)
     {
       p->info=(char*)malloc((l+1)*sizeof(char));
       strcpy(p->info,s);
     }
   }
   (*G).edgenum++;
   return OK;
 }

 Boolean visite[MAX_VERTEX_NUM]; /* 访问标志数组(全局量) */
 Status(*VisitFunc)(VertexType v);
 void DFS(AMLGraph G,int v)
 {
   int j;
   EBox *p;
   VisitFunc(G.adjmulist[v].data);
   visite[v]=TRUE;
   p=G.adjmulist[v].firstedge;
   while(p)
   {
     j=p->ivex==v?p->jvex:p->ivex;
     if(!visite[j])
       DFS(G,j);
     p=p->ivex==v?p->ilink:p->jlink;
   }
 }

 void DFSTraverse(AMLGraph G,Status(*visit)(VertexType))
 { /* 初始条件: 图G存在,Visit是顶点的应用函数。算法7.4 */
   /* 操作结果: 从第1个顶点起,深度优先遍历图G,并对每个顶点调用函数Visit */
   /*           一次且仅一次。一旦Visit()失败,则操作失败 */
   int v;
   VisitFunc=visit;
   for(v=0;v<G.vexnum;v++)
     visite[v]=FALSE;
   for(v=0;v<G.vexnum;v++)
     if(!visite[v])
       DFS(G,v);
   printf("\n");
 }

 typedef int QElemType; /* 队列类型 */
 #include"c3-2.h" /* BFSTraverse()用 */
 #include"bo3-2.c" /* BFSTraverse()用 */
 void BFSTraverse(AMLGraph G,Status(*Visit)(VertexType))
 { /* 初始条件: 图G存在,Visit是顶点的应用函数。算法7.6 */
   /* 操作结果: 从第1个顶点起,按广度优先非递归遍历图G,并对每个顶点调用函数 */
   /*           Visit一次且仅一次。一旦Visit()失败,则操作失败。 */
   /*           使用辅助队列Q和访问标志数组visite */
   int v,u,w;
   VertexType w1,u1;
   LinkQueue Q;
   for(v=0;v<G.vexnum;v++)
     visite[v]=FALSE; /* 置初值 */
   InitQueue(&Q); /* 置空的辅助队列Q */
   for(v=0;v<G.vexnum;v++)
     if(!visite[v]) /* v尚未访问 */
     {
       visite[v]=TRUE; /* 设置访问标志为TRUE(已访问) */
       Visit(G.adjmulist[v].data);
       EnQueue(&Q,v); /* v入队列 */
       while(!QueueEmpty(Q)) /* 队列不空 */
       {
         DeQueue(&Q,&u); /* 队头元素出队并置为u */
         strcpy(u1,*GetVex(G,u));
         for(w=FirstAdjVex(G,u1);w>=0;w=NextAdjVex(G,u1,strcpy(w1,*GetVex(G,w))))
           if(!visite[w]) /* w为u的尚未访问的邻接顶点的序号 */
           {
             visite[w]=TRUE;
             Visit(G.adjmulist[w].data);
             EnQueue(&Q,w);
           }
       }
     }
   printf("\n");
 }

 void MarkUnvizited(AMLGraph G)
 { /* 置边的访问标记为未被访问 */
   int i;
   EBox *p;
   for(i=0;i<G.vexnum;i++)
   {
     p=G.adjmulist[i].firstedge;
     while(p)
     {
       p->mark=unvisited;
       if(p->ivex==i)
         p=p->ilink;
       else
         p=p->jlink;
     }
   }
 }

 void Display(AMLGraph G)
 { /* 输出无向图的邻接多重表G */
   int i;
   EBox *p;
   MarkUnvizited(G); /* 置边的访问标记为未被访问 */
   printf("%d个顶点：\n",G.vexnum);
   for(i=0;i<G.vexnum;++i)
     printf("%s ",G.adjmulist[i].data);
   printf("\n%d条边:\n",G.edgenum);
   for(i=0;i<G.vexnum;i++)
   {
     p=G.adjmulist[i].firstedge;
     while(p)
       if(p->ivex==i) /* 边的i端与该顶点有关 */
       {
         if(!p->mark) /* 只输出一次 */
         {
           printf("%s－%s ",G.adjmulist[i].data,G.adjmulist[p->jvex].data);
           p->mark=visited;
           if(p->info) /* 输出附带信息 */
             printf("相关信息: %s ",p->info);
         }
         p=p->ilink;
       }
       else /* 边的j端与该顶点有关 */
       {
         if(!p->mark) /* 只输出一次 */
         {
           printf("%s－%s ",G.adjmulist[p->ivex].data,G.adjmulist[i].data);
           p->mark=visited;
           if(p->info) /* 输出附带信息 */
             printf("相关信息: %s ",p->info);
         }
         p=p->jlink;
       }
     printf("\n");
   }
 }


**********C7-1.H**********
 /* c7-1.h 图的数组(邻接矩阵)存储表示 */
 #define INFINITY INT_MAX /* 用整型最大值代替∞ */
 #define MAX_VERTEX_NUM 20 /* 最大顶点个数 */
 typedef enum{DG,DN,AG,AN}GraphKind; /* {有向图,有向网,无向图,无向网} */
 typedef struct
 {
   VRType adj; /* 顶点关系类型。对无权图，用1(是)或0(否)表示相邻否； */
	       /* 对带权图，c则为权值类型 */
   InfoType *info; /* 该弧相关信息的指针(可无) */
 }ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
 typedef struct
 {
   VertexType vexs[MAX_VERTEX_NUM]; /* 顶点向量 */
   AdjMatrix arcs; /* 邻接矩阵 */
   int vexnum,arcnum; /* 图的当前顶点数和弧数 */
   GraphKind kind; /* 图的种类标志 */
 }MGraph;

**********C7-2.H**********
 /* c7-2.h 图的邻接表存储表示 */
 #define MAX_VERTEX_NUM 20
 typedef enum{DG,DN,AG,AN}GraphKind; /* {有向图,有向网,无向图,无向网} */
 typedef struct ArcNode
 {
   int adjvex; /* 该弧所指向的顶点的位置 */
   struct ArcNode *nextarc; /* 指向下一条弧的指针 */
   InfoType *info; /* 网的权值指针） */
 }ArcNode; /* 表结点 */
 typedef struct
 {
   VertexType data; /* 顶点信息 */
   ArcNode *firstarc; /* 第一个表结点的地址,指向第一条依附该顶点的弧的指针 */
 }VNode,AdjList[MAX_VERTEX_NUM]; /* 头结点 */
 typedef struct
 {
   AdjList vertices;
   int vexnum,arcnum; /* 图的当前顶点数和弧数 */
   int kind; /* 图的种类标志 */
 }ALGraph;

**********C7-3.H**********
 /* c7-3.h 有向图的十字链表存储表示 */
 #define MAX_VERTEX_NUM 20
 typedef struct ArcBox
 {
   int tailvex,headvex; /* 该弧的尾和头顶点的位置 */
   struct ArcBox *hlink,*tlink; /* 分别为弧头相同和弧尾相同的弧的链域 */
   InfoType *info; /* 该弧相关信息的指针(可无) */
 }ArcBox; /* 弧结点 */
 typedef struct
 {
   VertexType data;
   ArcBox *firstin,*firstout; /* 分别指向该顶点第一条入弧和出弧 */
 }VexNode; /* 顶点结点 */
 typedef struct
 {
   VexNode xlist[MAX_VERTEX_NUM]; /* 表头向量(数组) */
   int vexnum,arcnum; /* 有向图的当前顶点数和弧数 */
 }OLGraph;
**********C7-4.H**********
 /* c7-4.h 无向图的邻接多重表存储表示 */
 #define MAX_VERTEX_NUM 20
 typedef enum{unvisited,visited}VisitIf;
 typedef struct EBox
 {
   VisitIf mark; /* 访问标记 */
   int ivex,jvex; /* 该边依附的两个顶点的位置 */
   struct EBox *ilink,*jlink; /* 分别指向依附这两个顶点的下一条边 */
   InfoType *info; /* 该边信息指针 */
 }EBox;
 typedef struct
 {
   VertexType data;
   EBox *firstedge; /* 指向第一条依附该顶点的边 */
 }VexBox;
 typedef struct
 {
   VexBox adjmulist[MAX_VERTEX_NUM];
   int vexnum,edgenum; /* 无向图的当前顶点数和边数 */
 }AMLGraph;
**********MAIN7-1.c**********
 /* main7-1.c 检验bo7-1.c的主程序 */
 #include"c1.h"
 #define MAX_NAME 5 /* 顶点字符串的最大长度+1 */
 #define MAX_INFO 20 /* 相关信息字符串的最大长度+1 */
 typedef int VRType;
 typedef char InfoType;
 typedef char VertexType[MAX_NAME];
 #include"c7-1.h"
 #include"bo7-1.c"

 Status visit(VertexType i)
 {
   printf("%s ",i);
   return OK;
 }

 void main()
 {
   int i,j,k,n;
   VertexType v1,v2;
   MGraph g;
   CreateFAG(&g);
   Display(g);
   printf("修改顶点的值，请输入原值 新值: ");
   scanf("%s%s",v1,v2);
   PutVex(&g,v1,v2);
   printf("深度优先搜索的结果:\n");
   DFSTraverse(g,visit);
   printf("广度优先搜索的结果:\n");
   BFSTraverse(g,visit);
   printf("删除一条边或弧，请输入待删除边或弧的弧尾 弧头：");
   scanf("%s%s",v1,v2);
   DeleteArc(&g,v1,v2);
   Display(g);
   DestroyGraph(&g);
   printf("请顺序选择有向图,有向网,无向图,无向网\n");
   for(i=0;i<4;i++) /* 验证4种情况 */
   {
     CreateGraph(&g);
     Display(g);
     printf("插入新顶点，请输入顶点的值: ");
     scanf("%s",v1);
     InsertVex(&g,v1);
     printf("插入与新顶点有关的弧或边，请输入弧或边数: ");
     scanf("%d",&n);
     for(k=0;k<n;k++)
     {
       printf("请输入另一顶点的值: ");
       scanf("%s",v2);
       if(g.kind<=1) /* 有向 */
       {
         printf("对于有向图或网，请输入另一顶点的方向(0:弧头 1:弧尾): ");
         scanf("%d",&j);
         if(j)
           InsertArc(&g,v2,v1);
         else
           InsertArc(&g,v1,v2);
       }
       else /* 无向 */
         InsertArc(&g,v1,v2);
     }
     Display(g);
     printf("删除顶点及相关的弧或边，请输入顶点的值: ");
     scanf("%s",v1);
     DeleteVex(&g,v1);
     Display(g);
     DestroyGraph(&g);
   }
 }


**********Main7-2.c**********
 /* main7-2.c 检验bo7-2.c的主程序 */
 #include"c1.h"
 #define MAX_NAME 3 /* 顶点字符串的最大长度+1 */
 typedef int InfoType; /* 存放网的权值 */
 typedef char VertexType[MAX_NAME]; /* 字符串类型 */
 #include"c7-2.h"
 #include"bo7-2.c"

 void print(char *i)
 {
   printf("%s ",i);
 }

 void main()
 {
   int i,j,k,n;
   ALGraph g;
   VertexType v1,v2;
   printf("请选择有向图\n");
   CreateGraph(&g);
   Display(g);
   printf("删除一条边或弧，请输入待删除边或弧的弧尾 弧头：");
   scanf("%s%s",v1,v2);
   DeleteArc(&g,v1,v2);
   printf("修改顶点的值，请输入原值 新值: ");
   scanf("%s%s",v1,v2);
   PutVex(&g,v1,v2);
   printf("插入新顶点，请输入顶点的值: ");
   scanf("%s",v1);
   InsertVex(&g,v1);
   printf("插入与新顶点有关的弧或边，请输入弧或边数: ");
   scanf("%d",&n);
   for(k=0;k<n;k++)
   {
     printf("请输入另一顶点的值: ");
     scanf("%s",v2);
     printf("对于有向图，请输入另一顶点的方向(0:弧头 1:弧尾): ");
     scanf("%d",&j);
     if(j)
       InsertArc(&g,v2,v1);
     else
       InsertArc(&g,v1,v2);
   }
   Display(g);
   printf("删除顶点及相关的弧或边，请输入顶点的值: ");
   scanf("%s",v1);
   DeleteVex(&g,v1);
   Display(g);
   printf("深度优先搜索的结果:\n");
   DFSTraverse(g,print);
   printf("广度优先搜索的结果:\n");
   BFSTraverse(g,print);
   DestroyGraph(&g);
   printf("请顺序选择有向网,无向图,无向网\n");
   for(i=0;i<3;i++) /* 验证另外3种情况 */
   {
     CreateGraph(&g);
     Display(g);
     printf("插入新顶点，请输入顶点的值: ");
     scanf("%s",v1);
     InsertVex(&g,v1);
     printf("插入与新顶点有关的弧或边，请输入弧或边数: ");
     scanf("%d",&n);
     for(k=0;k<n;k++)
     {
       printf("请输入另一顶点的值: ");
       scanf("%s",v2);
       if(g.kind<=1) /* 有向 */
       {
         printf("对于有向图或网，请输入另一顶点的方向(0:弧头 1:弧尾): ");
         scanf("%d",&j);
         if(j)
           InsertArc(&g,v2,v1);
         else
           InsertArc(&g,v1,v2);
       }
       else /* 无向 */
         InsertArc(&g,v1,v2);
     }
     Display(g);
     printf("删除顶点及相关的弧或边，请输入顶点的值: ");
     scanf("%s",v1);
     DeleteVex(&g,v1);
     Display(g);
     DestroyGraph(&g);
   }
 }

**********Main7-3.c**********
 /* main7-3.c 检验bo7-3.c的主程序 */
 #include"c1.h"
 typedef char InfoType;
 #define MAX_Info 80 /* 信息字符串最大长度+1 */
 #define MAX_VERTEX_NAME 3  /* 顶点字符串最大长度+1 */
 typedef char  VertexType[MAX_VERTEX_NAME];
 #include"c7-3.h"
 #include"bo7-3.c"
 Status visit(VertexType v)
 {
   printf("%s ",v);
   return OK;
 }

 void main()
 {
   int j,k,n;
   OLGraph g;
   VertexType v1,v2;
   CreateDG(&g);
   Display(g);
   printf("修改顶点的值，请输入原值 新值: ");
   scanf("%s%s",v1,v2);
   PutVex(&g,v1,v2);
   printf("插入新顶点，请输入顶点的值: ");
   scanf("%s",v1);
   InsertVex(&g,v1);
   printf("插入与新顶点有关的弧，请输入弧数: ");
   scanf("%d",&n);
   for(k=0;k<n;k++)
   {
     printf("请输入另一顶点的值 另一顶点的方向(0:弧头 1:弧尾): ");
     scanf("%s%d",v2,&j);
     if(j)
       InsertArc(&g,v2,v1);
     else
       InsertArc(&g,v1,v2);
   }
   Display(g);
   printf("删除一条弧，请输入待删除弧的弧尾 弧头：");
   scanf("%s%s",v1,v2);
   DeleteArc(&g,v1,v2);
   Display(g);
   printf("删除顶点及相关的弧，请输入顶点的值: ");
   scanf("%s",v1);
   DeleteVex(&g,v1);
   Display(g);
   printf("深度优先搜索的结果:\n");
   DFSTraverse(g,visit);
   printf("广度优先搜索的结果:\n");
   BFSTraverse(g,visit);
   DestroyGraph(&g);
 }

**********Main7-4.c**********
 /* main7-4.cpp 检验bo7-4.cpp的主程序 */
 #include"c1.h"
 #define MAX_NAME 3 /* 顶点字符串的最大长度+1 */
 #define MAX_INFO 80 /* 相关信息字符串的最大长度+1 */
 typedef char InfoType;
 typedef char VertexType[MAX_NAME]; /* 字符串类型 */
 #include"c7-4.h"
 #include"bo7-4.c"
 Status visit(VertexType v)
 {
   printf("%s ",v);
   return OK;
 }

 void main()
 {
   int k,n;
   AMLGraph g;
   VertexType v1,v2;
   CreateGraph(&g);
   Display(g);
   printf("修改顶点的值，请输入原值 新值: ");
   scanf("%s%s",v1,v2);
   PutVex(&g,v1,v2);
   printf("插入新顶点，请输入顶点的值: ");
   scanf("%s",v1);
   InsertVex(&g,v1);
   printf("插入与新顶点有关的边，请输入边数: ");
   scanf("%d",&n);
   for(k=0;k<n;k++)
   {
     printf("请输入另一顶点的值: ");
     scanf("%s",v2);
     InsertArc(&g,v1,v2);
   }
   Display(g);
   printf("深度优先搜索的结果:\n");
   DFSTraverse(g,visit);
   printf("广度优先搜索的结果:\n");
   BFSTraverse(g,visit);
   DestroyGraph(&g);
 }
F:\GitHubCode\Code\Csjjg\严蔚敏《数据结构》的全部代码实现（C语言）\ch8
**********algo8-2.c**********
 /* algo8-2.c 伙伴系统。实现算法8.2的程序 */
 #include"c1.h"
 #include"c8-2.h"
 #define N 100 /* 占用块个数的最大值 */
 Space r; /* r为生成空间的首地址,全局量 */

 Space AllocBuddy(FreeList *avail,int n)
 { /* avail[0..m]为可利用空间表,n为申请分配量,若有不小于n的空闲块, */
   /* 则分配相应的存储块,并返回其首地址;否则返回NULL。算法8.2 */
   int i,k;
   Space pa,pi,pre,suc;
   for(k=0;k<=m&&((*avail)[k].nodesize<n+1||!(*avail)[k].first);++k); /* 查找满足分配要求的子表 */
   if(k>m) /* 分配失败，返回NULL */
     return NULL;
   else /* 进行分配 */
   {
     pa=(*avail)[k].first; /* 指向可分配子表的第一个结点 */
     pre=pa->llink; /* 分别指向前驱和后继 */
     suc=pa->rlink;
     if(pa==suc)
       (*avail)[k].first=NULL; /* 分配后该子表变成空表 */
     else /* 从子表删去*pa结点 */
     {
       pre->rlink=suc;
       suc->llink=pre;
       (*avail)[k].first=suc;
     }
     for(i=1;(*avail)[k-i].nodesize>=n+1;++i)
     {
       pi=pa+(int)pow(2,k-i);
       pi->rlink=pi;
       pi->llink=pi;
       pi->tag=0;
       pi->kval=k-i;
       (*avail)[k-i].first=pi;
     } /* 将剩余块插入相应子表 */
     pa->tag=1;
     pa->kval=k-(--i);
   }
   return pa;
 }

 Space buddy(Space p)
 { /* 返回相对起始地址为p,块大小为pow(2,k)的块的伙伴地址 */
   if((p-r)%(int)pow(2,p->kval+1)==0) /* p为前块 */
     return p+(int)pow(2,p->kval);
   else /* p为后块 */
     return p-(int)pow(2,p->kval);
 }

 void Reclaim(FreeList *pav,Space *p)
 { /* 伙伴系统的回收算法 将p所指的释放块回收到可利用空间表pav中 */
   Space s;
   s=buddy(*p); /* 伙伴块的起始地址 */
   while(s>=r&&s<r+(*pav)[m].nodesize&&s->tag==0) /* 归并伙伴块,伙伴块起始地址在有效范围内且伙伴块空闲 */
   { /* 从链表上删除该结点 */
     if(s->llink==s&&s->rlink==s) /* 链表上仅此一个结点 */
       (*pav)[s->kval].first=NULL; /* 置此链表为空 */
     else /* 链表上不止一个结点 */
     {
       s->llink->rlink=s->rlink; /* 前驱的后继为该结点的后继 */
       s->rlink->llink=s->llink; /* 后继的前驱为该结点的前驱 */
       if((*pav)[s->kval].first==s) /* s是链表的第一个结点 */
         (*pav)[s->kval].first=s->rlink; /* 表头指向下一个结点 */
     } /* 以下修改结点头部 */
     if((*p-r)%(int)pow(2,(*p)->kval+1)==0) /* p为前块 */
       (*p)->kval++;
     else /* p为后块 */
     {
       s->kval=(*p)->kval+1;
       *p=s; /* p指向新块首地址 */
     }
     s=buddy(*p); /* 下一个伙伴块的起始地址 */
   }
   /* 以下将p插到可利用空间表中 */
   (*p)->tag=0;
   if((*pav)[(*p)->kval].first==NULL) /* 该链表空 */
     (*pav)[(*p)->kval].first=(*p)->llink=(*p)->rlink=*p;
   else /* 插在表头 */
   {
     (*p)->rlink=(*pav)[(*p)->kval].first;
     (*p)->llink=(*p)->rlink->llink;
     (*p)->rlink->llink=*p;
     (*p)->llink->rlink=*p;
     (*pav)[(*p)->kval].first=*p;
   }
   *p=NULL;
 }

 void Print(FreeList p)
 { /* 输出p中所有可利用空间表 */
   int i;
   Space h;
   for(i=0;i<=m;i++)
   {
     if(p[i].first) /* 第i个可利用空间表不空 */
     {
       h=p[i].first; /* h指向链表的第一个结点的头部域(首地址) */
       do
       {
         printf("块的大小=%d 块的首地址=%u ",(int)pow(2,h->kval),h); /* 输出结点信息 */
         printf("块标志=%d(0:空闲 1:占用)\n",h->tag);
         h=h->rlink; /* 指向下一个结点的头部域(首地址) */
       }while(h!=p[i].first); /* 没到循环链表的表尾 */
     }
   }
 }

 void PrintUser(Space p[])
 { /* 输出p数组所指的已分配空间 */
   int i;
   for(i=0;i<N;i++)
     if(p[i]) /* 指针不为0(指向一个占用块) */
     {
       printf("占用块%d的首地址=%u ",i,p[i]); /* 输出结点信息 */
       printf("块的大小=%d",(int)pow(2,p[i]->kval));
       printf(" 块标志=%d(0:空闲 1:占用)\n",p[i]->tag);
     }
 }

 void main()
 {
   int i,n;
   FreeList a;
   Space q[N]={NULL}; /* q数组为占用块的首地址 */
   printf("sizeof(WORD)=%u m=%u (int)pow(2,m)=%u\n",sizeof(WORD),m,(int)pow(2,m));
   for(i=0;i<=m;i++) /* 初始化a */
   {
     a[i].nodesize=(int)pow(2,i);
     a[i].first=NULL;
   }
   r=a[m].first=(WORD*)malloc(a[m].nodesize*sizeof(WORD)); /* 在最大链表中生成一个结点 */
   if(r) /* 生成结点成功 */
   {
     r->llink=r->rlink=r; /* 初始化该结点 */
     r->tag=0;
     r->kval=m;
     Print(a);
     PrintUser(q);
     n=100;
     q[0]=AllocBuddy(&a,n); /* 向a申请100个WORD的内存(实际获得128个WORD) */
     printf("申请%d个字后，可利用空间为:\n",n);
     Print(a);
     PrintUser(q);
     n=200;
     q[1]=AllocBuddy(&a,n); /* 向a申请200个WORD的内存(实际获得256个WORD) */
     printf("申请%d个字又",n);
     n=220;
     q[2]=AllocBuddy(&a,n); /* 向a申请220个WORD的内存(实际获得256个WORD) */
     printf("申请%d个字后，可利用空间为:\n",n);
     Print(a);
     PrintUser(q);
     Reclaim(&a,&q[1]); /* 回收q[1]，伙伴不空闲 */
     printf("回收q[1]后，可利用空间为:\n");
     Print(a);
     PrintUser(q);
     Reclaim(&a,&q[0]); /* 回收q[0]，伙伴空闲 */
     printf("回收q[0]后，可利用空间为:\n");
     Print(a);
     PrintUser(q);
     Reclaim(&a,&q[2]); /* 回收q[2]，伙伴空闲，生成一个大结点 */
     printf("回收q[2]后，可利用空间为:\n");
     Print(a);
     PrintUser(q);
   }
   else
     printf("ERROR\n");
 }

**********algo8-3.c**********
 /* algo8-3.c 实现算法8.3的程序 */
 #include"c1.h"
 typedef char AtomType; /* 定义原子类型为字符型 */
 #include"c8-3.h"
 #include"bo5-51.c"

 Status CreateMarkGList(GList *L,SString S) /* 由bo5-51.c改 */
 { /* 采用头尾链表存储结构,由广义表的书写形式串S创建广义表L。设emp="()" */
   SString sub,hsub,emp;
   GList p,q;
   StrAssign(emp,"()");
   if(!StrCompare(S,emp))
     *L=NULL; /* 创建空表 */
   else
   {
     *L=(GList)malloc(sizeof(GLNode));
     if(!*L) /* 建表结点 */
       exit(OVERFLOW);
     if(StrLength(S)==1) /* S为单原子 */
     {
       (*L)->tag=ATOM;
       (*L)->a.atom=S[1]; /* 创建单原子广义表 */
       (*L)->mark=0; /* 加 */
     }
     else
     {
       (*L)->tag=LIST;
       (*L)->mark=0; /* 加 */
       p=*L;
       SubString(sub,S,2,StrLength(S)-2); /* 脱外层括号 */
       do
       { /* 重复建n个子表 */
         sever(sub,hsub); /* 从sub中分离出表头串hsub */
         CreateMarkGList(&p->a.ptr.hp,hsub); /* 改 */
         q=p;
         if(!StrEmpty(sub)) /* 表尾不空 */
         {
           p=(GLNode *)malloc(sizeof(GLNode));
           if(!p)
             exit(OVERFLOW);
           p->tag=LIST;
           p->mark=0; /* 加 */
           q->a.ptr.tp=p;
         }
       }while(!StrEmpty(sub));
       q->a.ptr.tp=NULL;
     }
   }
   return OK;
 }

 void MarkList(GList GL) /* 算法8.3 */
 { /* 遍历非空广义表GL(GL!=NULL且GL->mark==0),对表中所有未加标志的结点加标志。*/
   GList t,p,q;
   Status finished;
   if(GL!=NULL&&GL->mark==0)
   {
     t=NULL; /* t指示p的母表 */
     p=GL;
     finished=FALSE;
     while(!finished)
     {
       while(p->mark==0)
       {
	 p->mark=1; /* MarkHead(p)的细化 */
         q=p->a.ptr.hp; /* q指向*p的表头 */
         if(q&&q->mark==0)
           if(q->tag==0)
             q->mark=1; /* ATOM,表头为原子结点 */
           else
           { /* 继续遍历子表 */
             p->a.ptr.hp=t;
             p->tag=ATOM;
             t=p;
             p=q;
           }
       } /* 完成对表头的标志 */
       q=p->a.ptr.tp; /* q指向*p的表尾 */
       if(q&&q->mark==0)
       { /* 继续遍历表尾 */
         p->a.ptr.tp=t;
         t=p;
         p=q;
       }
       else /* BackTrack(finished)的细化 */
       {
         while(t&&t->tag==1) /* LIST,表结点,从表尾回溯 */
         {
           q=t;
           t=q->a.ptr.tp;
           q->a.ptr.tp=p;
           p=q;
         }
         if(!t)
           finished=TRUE; /* 结束 */
         else
         { /* 从表头回溯 */
           q=t;
           t=q->a.ptr.hp;
           q->a.ptr.hp=p;
           p=q;
           p->tag=LIST;
         } /* 继续遍历表尾 */
       }
     }
   }
 }

 void Traverse_GL(GList L,void(*v)(GList))
 { /* 利用递归算法遍历广义表L,由bo5-5.c改 */
   if(L) /* L不空 */
     if(L->tag==ATOM) /* L为单原子 */
       v(L);
     else /* L为广义表 */
     {
       v(L);
       Traverse_GL(L->a.ptr.hp,v);
       Traverse_GL(L->a.ptr.tp,v);
     }
 }

 void visit(GList p)
 {
   if(p->tag==ATOM)
     printf("mark=%d %c\n",p->mark,p->a.atom);
   else
     printf("mark=%d list\n",p->mark);
 }

 void main()
 {
   char p[80];
   SString t;
   GList l;
   printf("请输入广义表l(书写形式：空表:(),单原子:a,其它:(a,(b),b)):\n");
   gets(p);
   StrAssign(t,p);
   CreateMarkGList(&l,t);
   Traverse_GL(l,visit);
   MarkList(l);
   printf("加标志后:\n");
   Traverse_GL(l,visit);
 }

**********C8-1.H**********
 /* c8-1.h 边界标识法可利用空间表的结点结构 */
 /* head和foot分别是可利用空间表中结点的第一个字和最后一个字(WORD) */

 typedef struct WORD /* 字类型 */
 {
   union
   {
     struct WORD *llink; /* 头部域，指向前驱结点 */
     struct WORD *uplink; /* 底部域，指向本结点头部 */
   }a;
   int tag; /* 块标志，0：空闲，1：占用，头部和尾部均有 */
   int size; /* 头部域，块大小 */
   struct WORD *rlink; /* 头部域，指向后继结点 */
 }WORD,head,foot,*Space; /* *Space：可利用空间指针类型 */

 #define FootLoc(p) (p)+(p)->size-1 /* 带参数的宏定义，指向p所指结点的底部(最后一个字) */
**********C8-2.H**********
 /* c8-2.h 伙伴系统可利用空间表的结构 */
 #define m 10 /* 可利用空间总容量1024字的2的幂次,子表的个数为m+1 */
 typedef struct WORD
 {
   struct WORD *llink; /* 指向前驱结点 */
   int tag; /* 块标志,0:空闲,1:占用 */
   int kval; /* 块大小,值为2的幂次k */
   struct WORD *rlink; /* 头部域,指向后继结点 */
 }WORD,head,*Space; /* WORD:内存字类型,结点的第一个字也称为head */

 typedef struct HeadNode
 {
   int nodesize; /* 该链表的空闲块的大小 */
   struct WORD *first; /* 孩链表的表头指针 */
 }FreeList[m+1]; /* 表头向量类型 */
**********c8-3.H**********
 /* c8-3.h 加标志域的广义表的头尾链表存储表示(由c5-5.h改) */
 typedef enum{ATOM,LIST}ElemTag; /* ATOM==0:原子,LIST==1:子表 */
 typedef struct GLNode
 {
   int mark; /* 加此域，其余同c5-5.h */
   ElemTag tag; /* 公共部分,用于区分原子结点和表结点 */
   union /* 原子结点和表结点的联合部分 */
   {
     AtomType atom; /* atom是原子结点的值域,AtomType由用户定义 */
     struct
     {
       struct GLNode *hp,*tp;
     }ptr; /* ptr是表结点的指针域,prt.hp和ptr.tp分别指向表头和表尾 */
   }a;
 }*GList,GLNode; /* 广义表类型 */

F:\GitHubCode\Code\Csjjg\严蔚敏《数据结构》的全部代码实现（C语言）\ch9
**********Algo9-2.c**********
 /* algo9-2.c 检验bo9-1.(有序表部分)的程序 */
 #include"c1.h"
 #define N 11 /* 数据元素个数 */
 typedef int KeyType; /* 设关键字域为整型 */
 typedef struct /* 数据元素类型 */
 {
   KeyType key; /* 关键字域 */
   int others; /* 其它部分 */
 }ElemType;
 ElemType r[N]={{5,1},{13,2},{19,3},{21,4},{37,5},{56,6},{64,7},{75,8},
		{80,9},{88,10},{92,11}}; /* 数据元素(以教科书P.219的数据为例),全局变量 */
 #include"c9.h"
 #include"c9-1.h"
 #include"bo9-1.c"

 void print(ElemType c) /* Traverse()调用的函数 */
 {
   printf("(%d %d) ",c.key,c.others);
 }

 void main()
 {
   SSTable st;
   int i;
   KeyType s;
   Creat_Ord(&st,N); /* 由全局数组产生非降序静态查找表st */
   Traverse(st,print); /* 顺序输出非降序静态查找表st */
   printf("\n");
   printf("请输入待查找值的关键字: ");
   scanf("%d",&s);
   i=Search_Bin(st,s); /* 折半查找有序表 */
   if(i)
     printf("(%d %d) %d是第%d个记录的关键字\n",st.elem[i].key,st.elem[i].others,s,i);
   else
     printf("没找到\n");
   Destroy(&st);
 }

**********Algo9-3.c**********
 /* algo9-3.c 静态查找表(静态树表)的操作 */
 #include"c1.h"
 #define N 9 /* 数据元素个数 */
 typedef char KeyType; /* 设关键字域为字符型 */
 typedef struct /* 数据元素类型 */
 {
   KeyType key;
   int weight;
 }ElemType;
 ElemType r[N]={{'A',1},{'B',1},{'C',2},{'D',5},{'E',3},
                {'F',4},{'G',4},{'H',3},{'I',5}}; /* 数据元素(以教科书例9-1为例),全局变量 */
 int sw[N+1]; /* 累计权值，全局变量 */
 #include"c9.h"
 #include"c9-1.h"
 #include"bo9-1.c"

 typedef ElemType TElemType;
 #include"c6-2.h"
 Status SecondOptimal(BiTree *T, ElemType R[],int sw[],int low,int high)
 { /* 由有序表R[low..high]及其累计权值表sw(其中sw[0]==0)递归构造 */
   /* 次优查找树T。算法9.3 */
   int i,j;
   double min,dw;
   i=low;
   min=fabs(sw[high]-sw[low]);
   dw=sw[high]+sw[low-1];
   for(j=low+1;j<=high;++j) /* 选择最小的△Pi值 */
     if(fabs(dw-sw[j]-sw[j-1])<min)
     {
       i=j;
       min=fabs(dw-sw[j]-sw[j-1]);
     }
   *T=(BiTree)malloc(sizeof(BiTNode));
   if(!*T)
     return ERROR;
   (*T)->data=R[i]; /* 生成结点 */
   if(i==low)
     (*T)->lchild=NULL; /* 左子树空 */
   else
     SecondOptimal(&(*T)->lchild,R,sw,low,i-1); /* 构造左子树 */
   if(i==high)
     (*T)->rchild=NULL; /* 右子树空 */
   else
     SecondOptimal(&(*T)->rchild,R,sw,i+1,high); /* 构造右子树 */
   return OK;
 }

 void FindSW(int sw[],SSTable ST)
 { /* 按照有序表ST中各数据元素的Weight域求累计权值表sw */
   int i;
   sw[0]=0;
   for(i=1;i<=ST.length;i++)
     sw[i]=sw[i-1]+ST.elem[i].weight;
 }

 typedef BiTree SOSTree; /* 次优查找树采用二叉链表的存储结构 */
 Status CreateSOSTree(SOSTree *T,SSTable ST)
 { /* 由有序表ST构造一棵次优查找树T。ST的数据元素含有权域weight。算法9.4 */
   if(ST.length==0)
     *T=NULL;
   else
   {
     FindSW(sw,ST); /* 按照有序表ST中各数据元素的Weight域求累计权值表sw */
     SecondOptimal(T,ST.elem,sw,1,ST.length);
   }
   return OK;
 }

 Status Search_SOSTree(SOSTree *T,KeyType key)
 { /* 在次优查找树T中查找关键字等于key的元素。找到则返回OK，否则返回FALSE */
   while(*T) /* T非空 */
     if((*T)->data.key==key)
       return OK;
     else if((*T)->data.key>key)
       *T=(*T)->lchild;
     else
       *T=(*T)->rchild;
   return FALSE; /* 顺序表中不存在待查元素 */
 }

 void print(ElemType c) /* Traverse()调用的函数 */
 {
   printf("(%c %d) ",c.key,c.weight);
 }

 void main()
 {
   SSTable st;
   SOSTree t;
   Status i;
   KeyType s;
   Creat_Ord(&st,N); /* 由全局数组产生非降序静态查找表st */
   Traverse(st,print);
   CreateSOSTree(&t,st); /* 由有序表构造一棵次优查找树 */
   printf("\n请输入待查找的字符: ");
   scanf("%c",&s);
   i=Search_SOSTree(&t,s);
   if(i)
     printf("%c的权值是%d\n",s,t->data.weight);
   else
     printf("表中不存在此字符\n");
 }


**********Algo9-4.c**********
 /* algo9-4.c 检验bo9-2.c的程序 */
 #include"c1.h"
 #define N 10 /* 数据元素个数 */
 typedef int KeyType; /* 设关键字域为整型 */
 typedef struct
 {
   KeyType key;
   int others;
 } ElemType; /* 数据元素类型 */
 #include"c9.h"
 #include"bo9-2.c"

 void print(ElemType c)
 {
   printf("(%d,%d) ",c.key,c.others);
 }

 void main()
 {
   BiTree dt,p;
   int i;
   KeyType j;
   ElemType r[N]={{45,1},{12,2},{53,3},{3,4},{37,5},{24,6},{100,7},{61,8},{90,9},{78,10}}; /* 以教科书图9.7(a)为例 */
   InitDSTable(&dt); /* 构造空表 */
   for(i=0;i<N;i++)
     InsertBST(&dt,r[i]); /* 依次插入数据元素 */
   TraverseDSTable(dt,print);
   printf("\n请输入待查找的值: ");
   scanf("%d",&j);
   p=SearchBST(dt,j);
   if(p)
   {
     printf("表中存在此值。");
     DeleteBST(&dt,j);
     printf("删除此值后:\n");
     TraverseDSTable(dt,print);
     printf("\n");
   }
   else
     printf("表中不存在此值\n");
   DestroyDSTable(&dt);
 }

**********Algo9-5.c**********
 /* algo9-5.c 检验bo9-3.c的程序 */
 #include"c1.h"
 #define N 5 /* 数据元素个数 */
 typedef char KeyType; /* 设关键字域为字符型 */
 typedef struct
 {
   KeyType key;
   int order;
 }ElemType; /* 数据元素类型 */

 #include"c9.h"
 #include"c9-2.h"
 #include"bo9-3.c"

 void print(ElemType c)
 {
   printf("(%d,%d)",c.key,c.order);
 }

 void main()
 {
   BSTree dt,p;
   Status k;
   int i;
   KeyType j;
   ElemType r[N]={{13,1},{24,2},{37,3},{90,4},{53,5}}; /* (以教科书图9.12为例) */
   InitDSTable(&dt); /* 初始化空树 */
   for(i=0;i<N;i++)
     InsertAVL(&dt,r[i],&k); /* 建平衡二叉树 */
   TraverseDSTable(dt,print); /* 按关键字顺序遍历二叉树 */
   printf("\n请输入待查找的关键字: ");
   scanf("%d",&j);
   p=SearchBST(dt,j); /* 查找给定关键字的记录 */
   if(p)
     print(p->data);
   else
     printf("表中不存在此值");
   printf("\n");
   DestroyDSTable(&dt);
 }

**********Algo9-6.c**********
 /* algo9-6.c 检验bo9-4.c的程序 */
 #include"c1.h"
 #define m 3 /* B树的阶，暂设为3 */
 #define N 16 /* 数据元素个数 */
 #define MAX 5 /* 字符串最大长度+1 */
 typedef int KeyType; /* 设关键字域为整型 */
 typedef struct
 {
   char info[MAX];
 }Others;/* 记录的其它部分 */

 #include"c9-3.h"
 #include"bo9-4.c"

 void print(BTNode c,int i) /* TraverseDSTable()调用的函数 */
 {
   printf("(%d,%s)",c.node[i].key,c.node[i].recptr->others.info);
 }

 void main()
 {
   Record r[N]={{24,"1"},{45,"2"},{53,"3"},{12,"4"},{37,"5"},
                {50,"6"},{61,"7"},{90,"8"},{100,"9"},{70,"10"},
                {3,"11"},{30,"12"},{26,"13"},{85,"14"},{3,"15"},
		{7,"16"}}; /* (以教科书中图9.16为例) */
   BTree t;
   Result s;
   int i;
   InitDSTable(&t);
   for(i=0;i<N;i++)
   {
     s=SearchBTree(t,r[i].key);
     if(!s.tag)
       InsertBTree(&t,&r[i],s.pt,s.i);
   }
   printf("按关键字的顺序遍历B_树:\n");
   TraverseDSTable(t,print);
   printf("\n请输入待查找记录的关键字: ");
   scanf("%d",&i);
   s=SearchBTree(t,i);
   if(s.tag)
     print(*(s.pt),s.i);
   else
     printf("没找到");
   printf("\n");
   DestroyDSTable(&t);
 }

**********Algo9-7.c**********
 /* algo9-7.c 检验bo9-5.c的程序 */
 #include"c1.h"
 #define N 16 /* 数据元素个数 */
 typedef struct
 {
   int ord;
 }Others; /* 记录的其它部分 */
 #define Nil ' ' /* 定义结束符为空格(与教科书不同) */
 #include"c9-4.h"
 #include"bo9-5.c"

 void print(Record e)
 {
   int i;
   printf("(");
   for(i=0;i<e.key.num;i++)
     printf("%c",e.key.ch[i]);
   printf(",%d)",e.others.ord);
 }

 void main()
 {
   DLTree t;
   int i;
   char s[MAXKEYLEN+1];
   KeysType k;
   Record *p;
   Record r[N]={{{"CAI"},1},{{"CAO"},2},{{"LI"},3},{{"LAN"},4},
                {{"CHA"},5},{{"CHANG"},6},{{"WEN"},7},{{"CHAO"},8},
                {{"YUN"},9},{{"YANG"},10},{{"LONG"},11},{{"WANG"},12},
                {{"ZHAO"},13},{{"LIU"},14},{{"WU"},15},{{"CHEN"},16}};
   /* 数据元素(以教科书式9-24为例) */
   InitDSTable(&t);
   for(i=0;i<N;i++)
   {
     r[i].key.num=strlen(r[i].key.ch);
     p=SearchDLTree(t,r[i].key);
     if(!p) /* t中不存在关键字为r[i].key的项 */
       InsertDSTable(&t,&r[i]);
   }
   printf("按关键字符串的顺序遍历双链键树:\n");
   TraverseDSTable(t,print);
   printf("\n请输入待查找记录的关键字符串: ");
   scanf("%s",s);
   k.num=strlen(s);
   strcpy(k.ch,s);
   p=SearchDLTree(t,k);
   if(p)
     print(*p);
   else
     printf("没找到");
   printf("\n");
   DestroyDSTable(&t);
 }

**********Algo9-8.c**********
 /* algo9-8.c 检验bo9-6.c的程序 */
 #include"c1.h"
 #define N 16 /* 数据元素个数 */
 #define LENGTH 27 /* 结点的最大度+1(大写英文字母) */
 typedef struct
 {
   int ord;
 }Others; /* 记录的其它部分 */
 #define Nil ' ' /* 定义结束符为空格(与教科书不同) */
 #include"c9-5.h"
 #include"bo9-6.c"

 Status pr(Record *r)
 {
   printf("(%s,%d)",r->key.ch,r->others.ord);
   return OK;
 }

 void main()
 {
   TrieTree t;
   int i;
   char s[MAXKEYLEN+1];
   KeysType k;
   Record *p;
   Record r[N]={{{"CAI"},1},{{"CAO"},2},{{"LI"},3},{{"LAN"},4},
                {{"CHA"},5},{{"CHANG"},6},{{"WEN"},7},{{"CHAO"},8},
                {{"YUN"},9},{{"YANG"},10},{{"LONG"},11},{{"WANG"},12},
                {{"ZHAO"},13},{{"LIU"},14},{{"WU"},15},{{"CHEN"},16}};
   /* 数据元素(以教科书式9-24为例) */
   InitDSTable(&t);
   for(i=0;i<N;i++)
   {
     r[i].key.num=strlen(r[i].key.ch)+1;
     r[i].key.ch[r[i].key.num]=Nil; /* 在关键字符串最后加结束符 */
     p=SearchTrie(t,r[i].key);
     if(!p)
       InsertTrie(&t,&r[i]);
   }
   printf("按关键字符串的顺序遍历Trie树(键树):\n");
   TraverseDSTable(t,pr);
   printf("\n请输入待查找记录的关键字符串: ");
   scanf("%s",s);
   k.num=strlen(s)+1;
   strcpy(k.ch,s);
   k.ch[k.num]=Nil; /* 在关键字符串最后加结束符 */
   p=SearchTrie(t,k);
   if(p)
     pr(p);
   else
     printf("没找到");
   printf("\n");
   DestroyDSTable(&t);
 }

**********algo9-9.C**********
 /* algo9-9.c 检验bo9-7.c的程序 */
 #include"c1.h"
 #define NULLKEY 0 /* 0为无记录标志 */
 #define N 10 /* 数据元素个数 */
 typedef int KeyType; /* 设关键字域为整型 */
 typedef struct
 {
   KeyType key;
   int ord;
 }ElemType; /* 数据元素类型 */

 #include"c9.h"
 #include"c9-6.h"
 #include"bo9-7.c"

 void print(int p,ElemType r)
 {
   printf("address=%d (%d,%d)\n",p,r.key,r.ord);
 }

 void main()
 {
   ElemType r[N]={{17,1},{60,2},{29,3},{38,4},{1,5},{2,6},{3,7},{4,8},{60,9},{13,10}};
   HashTable h;
   int i,p;
   Status j;
   KeyType k;
   InitHashTable(&h);
   for(i=0;i<N-1;i++)
   { /* 插入前N-1个记录 */
     j=InsertHash(&h,r[i]);
     if(j==DUPLICATE)
       printf("表中已有关键字为%d的记录，无法再插入记录(%d,%d)\n",r[i].key,r[i].key,r[i].ord);
   }
   printf("按哈希地址的顺序遍历哈希表:\n");
   TraverseHash(h,print);
   printf("请输入待查找记录的关键字: ");
   scanf("%d",&k);
   j=Find(h,k,&p);
   if(j==SUCCESS)
     print(p,h.elem[p]);
   else
     printf("没找到\n");
   j=InsertHash(&h,r[i]); /* 插入第N个记录 */
   if(j==ERROR) /* 重建哈希表 */
     j=InsertHash(&h,r[i]); /* 重建哈希表后重新插入第N个记录 */
   printf("按哈希地址的顺序遍历重建后的哈希表:\n");
   TraverseHash(h,print);
   printf("请输入待查找记录的关键字: ");
   scanf("%d",&k);
   j=Find(h,k,&p);
   if(j==SUCCESS)
     print(p,h.elem[p]);
   else
     printf("没找到\n");
   DestroyHashTable(&h);
 }

**********BO9-1.c**********
 /* bo9-1.c 静态查找表(顺序表和有序表)的基本操作(7个) */
 Status Creat_Seq(SSTable *ST,int n)
 { /* 操作结果: 构造一个含n个数据元素的静态顺序查找表ST(数据来自全局数组r) */
   int i;
   (*ST).elem=(ElemType *)calloc(n+1,sizeof(ElemType)); /* 动态生成n个数据元素空间(0号单元不用) */
   if(!(*ST).elem)
     return ERROR;
   for(i=1;i<=n;i++)
     *((*ST).elem+i)=r[i-1]; /* 将全局数组r的值依次赋给ST */
   (*ST).length=n;
   return OK;
 }

 void Ascend(SSTable *ST)
 { /* 重建静态查找表为按关键字非降序排序 */
   int i,j,k;
   for(i=1;i<(*ST).length;i++)
   {
     k=i;
     (*ST).elem[0]=(*ST).elem[i]; /* 待比较值存[0]单元 */
     for(j=i+1;j<=(*ST).length;j++)
       if LT((*ST).elem[j].key,(*ST).elem[0].key)
       {
         k=j;
         (*ST).elem[0]=(*ST).elem[j];
       }
     if(k!=i) /* 有更小的值则交换 */
     {
       (*ST).elem[k]=(*ST).elem[i];
       (*ST).elem[i]=(*ST).elem[0];
     }
   }
 }

 Status Creat_Ord(SSTable *ST,int n)
 { /* 操作结果: 构造一个含n个数据元素的静态按关键字非降序查找表ST */
   /* 数据来自全局数组r */
   Status f;
   f=Creat_Seq(ST,n);
   if(f)
     Ascend(ST);
   return f;
 }

 Status Destroy(SSTable *ST)
 { /* 初始条件: 静态查找表ST存在。操作结果: 销毁表ST */
   free((*ST).elem);
   (*ST).elem=NULL;
   (*ST).length=0;
   return OK;
 }

 int Search_Seq(SSTable ST,KeyType key)
 { /* 在顺序表ST中顺序查找其关键字等于key的数据元素。若找到，则函数值为 */
   /* 该元素在表中的位置，否则为0。算法9.1 */
   int i;
   ST.elem[0].key=key; /* 哨兵 */
   for(i=ST.length;!EQ(ST.elem[i].key,key);--i); /* 从后往前找 */
   return i; /* 找不到时，i为0 */
 }

 int Search_Bin(SSTable ST,KeyType key)
 { /* 在有序表ST中折半查找其关键字等于key的数据元素。若找到，则函数值为 */
   /* 该元素在表中的位置，否则为0。算法9.2 */
   int low,high,mid;
   low=1; /* 置区间初值 */
   high=ST.length;
   while(low<=high)
   {
     mid=(low+high)/2;
     if EQ(key,ST.elem[mid].key)  /* 找到待查元素 */
       return mid;
     else if LT(key,ST.elem[mid].key)
       high=mid-1; /* 继续在前半区间进行查找 */
     else
       low=mid+1; /* 继续在后半区间进行查找 */
   }
   return 0; /* 顺序表中不存在待查元素 */
 }

 Status Traverse(SSTable ST,void(*Visit)(ElemType))
 { /* 初始条件: 静态查找表ST存在，Visit()是对元素操作的应用函数 */
   /* 操作结果: 按顺序对ST的每个元素调用函数Visit()一次且仅一次。 */
   /* 一旦Visit()失败，则操作失败 */
   ElemType *p;
   int i;
   p=++ST.elem; /* p指向第一个元素 */
   for(i=1;i<=ST.length;i++)
     Visit(*p++);
   return OK;
 }

**********bo9-2.c**********
 /* bo9-2.c 动态查找表(二叉排序树)的基本操作(8个) */
 typedef ElemType TElemType;
 #include"c6-2.h"

 Status InitDSTable(BiTree *DT) /* 同bo6-2.c */
 { /* 操作结果: 构造一个空的动态查找表DT */
   *DT=NULL;
   return OK;
 }

 void DestroyDSTable(BiTree *DT) /* 同bo6-2.c */
 { /* 初始条件: 动态查找表DT存在。操作结果: 销毁动态查找表DT */
   if(*DT) /* 非空树 */
   {
     if((*DT)->lchild) /* 有左孩子 */
       DestroyDSTable(&(*DT)->lchild); /* 销毁左孩子子树 */
     if((*DT)->rchild) /* 有右孩子 */
       DestroyDSTable(&(*DT)->rchild); /* 销毁右孩子子树 */
     free(*DT); /* 释放根结点 */
     *DT=NULL; /* 空指针赋0 */
   }
 }

 BiTree SearchBST(BiTree T,KeyType key)
 { /* 在根指针T所指二叉排序树中递归地查找某关键字等于key的数据元素， */
   /* 若查找成功，则返回指向该数据元素结点的指针,否则返回空指针。算法9.5(a) */
   if((!T)||EQ(key,T->data.key))
     return T; /* 查找结束 */
   else if LT(key,T->data.key) /* 在左子树中继续查找 */
     return SearchBST(T->lchild,key);
   else
     return SearchBST(T->rchild,key); /* 在右子树中继续查找 */
 }

 void SearchBST1(BiTree *T,KeyType key,BiTree f,BiTree *p,Status *flag) /* 算法9.5(b)改 */
 { /* 在根指针T所指二叉排序树中递归地查找其关键字等于key的数据元素，若查找 */
   /* 成功，则指针p指向该数据元素结点，并返回TRUE，否则指针p指向查找路径上 */
   /* 访问的最后一个结点并返回FALSE,指针f指向T的双亲，其初始调用值为NULL */
   if(!*T) /* 查找不成功 */
   {
     *p=f;
     *flag=FALSE;
   }
   else if EQ(key,(*T)->data.key) /*  查找成功 */
   {
     *p=*T;
     *flag=TRUE;
   }
   else if LT(key,(*T)->data.key)
     SearchBST1(&(*T)->lchild,key,*T,p,flag); /* 在左子树中继续查找 */
   else
     SearchBST1(&(*T)->rchild,key,*T,p,flag); /*  在右子树中继续查找 */
 }

 Status InsertBST(BiTree *T, ElemType e)
 { /* 当二叉排序树T中不存在关键字等于e.key的数据元素时，插入e并返回TRUE， */
   /* 否则返回FALSE。算法9.6(改) */
   BiTree p,s;
   Status flag;
   SearchBST1(T,e.key,NULL,&p,&flag);
   if(!flag) /* 查找不成功 */
   {
     s=(BiTree)malloc(sizeof(BiTNode));
     s->data=e;
     s->lchild=s->rchild=NULL;
     if(!p)
       *T=s; /* 被插结点*s为新的根结点 */
     else if LT(e.key,p->data.key)
       p->lchild=s; /* 被插结点*s为左孩子 */
     else
       p->rchild=s; /* 被插结点*s为右孩子 */
     return TRUE;
   }
   else
     return FALSE; /* 树中已有关键字相同的结点，不再插入 */
 }

 void Delete(BiTree *p)
 { /* 从二叉排序树中删除结点p，并重接它的左或右子树。算法9.8 */
   BiTree q,s;
   if(!(*p)->rchild) /* 右子树空则只需重接它的左子树（待删结点是叶子也走此分支） */
   {
     q=*p;
     *p=(*p)->lchild;
     free(q);
   }
   else if(!(*p)->lchild) /* 只需重接它的右子树 */
   {
     q=*p;
     *p=(*p)->rchild;
     free(q);
   }
   else /* 左右子树均不空 */
   {
     q=*p;
     s=(*p)->lchild;
     while(s->rchild) /* 转左，然后向右到尽头（找待删结点的前驱） */
     {
       q=s;
       s=s->rchild;
     }
     (*p)->data=s->data; /* s指向被删结点的＂前驱＂（将被删结点前驱的值取代被删结点的值） */
     if(q!=*p)
       q->rchild=s->lchild; /* 重接*q的右子树 */
     else
       q->lchild=s->lchild; /* 重接*q的左子树 */
     free(s);
   }
 }

 Status DeleteBST(BiTree *T,KeyType key)
 { /* 若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素结点， */
   /* 并返回TRUE；否则返回FALSE。算法9.7 */
   if(!*T) /* 不存在关键字等于key的数据元素 */
     return FALSE;
   else
   {
     if EQ(key,(*T)->data.key) /* 找到关键字等于key的数据元素 */
       Delete(T);
     else if LT(key,(*T)->data.key)
       DeleteBST(&(*T)->lchild,key);
     else
       DeleteBST(&(*T)->rchild,key);
     return TRUE;
   }
 }

 void TraverseDSTable(BiTree DT,void(*Visit)(ElemType))
 { /* 初始条件: 动态查找表DT存在，Visit是对结点操作的应用函数 */
   /* 操作结果: 按关键字的顺序对DT的每个结点调用函数Visit()一次且至多一次 */
   if(DT)
   {
     TraverseDSTable(DT->lchild,Visit); /* 先中序遍历左子树 */
     Visit(DT->data); /* 再访问根结点 */
     TraverseDSTable(DT->rchild,Visit); /* 最后中序遍历右子树 */
   }
 }
**********BO9-3.c**********
 /* bo9-3.c 动态查找表(平衡二叉树)的基本操作 */
 Status InitDSTable(BSTree *DT) /* 同bo6-2.c */
 { /* 操作结果: 构造一个空的动态查找表DT */
   *DT=NULL;
   return OK;
 }

 void DestroyDSTable(BSTree *DT) /* 同bo6-2.c */
 { /* 初始条件: 动态查找表DT存在。操作结果: 销毁动态查找表DT */
   if(*DT) /* 非空树 */
   {
     if((*DT)->lchild) /* 有左孩子 */
       DestroyDSTable(&(*DT)->lchild); /* 销毁左孩子子树 */
     if((*DT)->rchild) /* 有右孩子 */
       DestroyDSTable(&(*DT)->rchild); /* 销毁右孩子子树 */
     free(*DT); /* 释放根结点 */
     *DT=NULL; /* 空指针赋0 */
   }
 }

 BSTree SearchBST(BSTree T,KeyType key)
 { /* 在根指针T所指二叉排序树中递归地查找某关键字等于key的数据元素， */
   /* 若查找成功，则返回指向该数据元素结点的指针,否则返回空指针。算法9.5(a) */
   if((!T)||EQ(key,T->data.key))
     return T; /* 查找结束 */
   else if LT(key,T->data.key) /* 在左子树中继续查找 */
     return SearchBST(T->lchild,key);
   else
     return SearchBST(T->rchild,key); /* 在右子树中继续查找 */
 }

 void R_Rotate(BSTree *p)
 { /* 对以*p为根的二叉排序树作右旋处理，处理之后p指向新的树根结点，即旋转 */
   /* 处理之前的左子树的根结点。算法9.9 */
   BSTree lc;
   lc=(*p)->lchild; /* lc指向p的左子树根结点 */
   (*p)->lchild=lc->rchild; /* lc的右子树挂接为p的左子树 */
   lc->rchild=*p;
   *p=lc; /* p指向新的根结点 */
 }

 void L_Rotate(BSTree *p)
 { /* 对以*p为根的二叉排序树作左旋处理，处理之后p指向新的树根结点，即旋转 */
   /* 处理之前的右子树的根结点。算法9.10 */
   BSTree rc;
   rc=(*p)->rchild; /* rc指向p的右子树根结点 */
   (*p)->rchild=rc->lchild; /* rc的左子树挂接为p的右子树 */
   rc->lchild=*p;
   *p=rc; /* p指向新的根结点 */
 }

 #define LH +1 /* 左高 */
 #define EH 0  /* 等高 */
 #define RH -1 /* 右高 */

 void LeftBalance(BSTree *T)
 { /* 对以指针T所指结点为根的二叉树作左平衡旋转处理，本算法结束时， */
   /* 指针T指向新的根结点。算法9.12 */
   BSTree lc,rd;
   lc=(*T)->lchild; /* lc指向*T的左子树根结点 */
   switch(lc->bf)
   { /* 检查*T的左子树的平衡度，并作相应平衡处理 */
     case LH: /* 新结点插入在*T的左孩子的左子树上，要作单右旋处理 */
              (*T)->bf=lc->bf=EH;
              R_Rotate(T);
              break;
     case RH: /* 新结点插入在*T的左孩子的右子树上，要作双旋处理 */
              rd=lc->rchild; /* rd指向*T的左孩子的右子树根 */
              switch(rd->bf)
              { /* 修改*T及其左孩子的平衡因子 */
                case LH: (*T)->bf=RH;
                         lc->bf=EH;
                         break;
                case EH: (*T)->bf=lc->bf=EH;
                         break;
                case RH: (*T)->bf=EH;
                         lc->bf=LH;
	      }
              rd->bf=EH;
              L_Rotate(&(*T)->lchild); /* 对*T的左子树作左旋平衡处理 */
              R_Rotate(T); /* 对*T作右旋平衡处理 */
   }
 }

 void RightBalance(BSTree *T)
 { /* 对以指针T所指结点为根的二叉树作右平衡旋转处理，本算法结束时， */
   /* 指针T指向新的根结点 */
   BSTree rc,rd;
   rc=(*T)->rchild; /* rc指向*T的右子树根结点 */
   switch(rc->bf)
   { /* 检查*T的右子树的平衡度，并作相应平衡处理 */
     case RH: /* 新结点插入在*T的右孩子的右子树上，要作单左旋处理 */
              (*T)->bf=rc->bf=EH;
              L_Rotate(T);
              break;
     case LH: /* 新结点插入在*T的右孩子的左子树上，要作双旋处理 */
              rd=rc->lchild; /* rd指向*T的右孩子的左子树根 */
	      switch(rd->bf)
              { /* 修改*T及其右孩子的平衡因子 */
                case RH: (*T)->bf=LH;
                         rc->bf=EH;
                         break;
                case EH: (*T)->bf=rc->bf=EH;
                         break;
                case LH: (*T)->bf=EH;
                         rc->bf=RH;
              }
              rd->bf=EH;
              R_Rotate(&(*T)->rchild); /* 对*T的右子树作右旋平衡处理 */
              L_Rotate(T); /* 对*T作左旋平衡处理 */
   }
 }

 Status InsertAVL(BSTree *T,ElemType e,Status *taller)
 { /* 若在平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入一个 */
   /* 数据元素为e的新结点，并返回1，否则返回0。若因插入而使二叉排序树 */
   /* 失去平衡，则作平衡旋转处理，布尔变量taller反映T长高与否。算法9.11 */
   if(!*T)
   { /* 插入新结点，树“长高”，置taller为TRUE */
     *T=(BSTree)malloc(sizeof(BSTNode));
     (*T)->data=e;
     (*T)->lchild=(*T)->rchild=NULL;
     (*T)->bf=EH;
     *taller=TRUE;
   }
   else
   {
     if EQ(e.key,(*T)->data.key)
     { /* 树中已存在和e有相同关键字的结点则不再插入 */
       *taller=FALSE;
       return FALSE;
     }
     if LT(e.key,(*T)->data.key)
     { /* 应继续在*T的左子树中进行搜索 */
       if(!InsertAVL(&(*T)->lchild,e,taller)) /* 未插入 */
         return FALSE;
       if(*taller) /*  已插入到*T的左子树中且左子树“长高” */
         switch((*T)->bf) /* 检查*T的平衡度 */
         {
           case LH: /* 原本左子树比右子树高，需要作左平衡处理 */
                    LeftBalance(T);
                    *taller=FALSE;
                    break;
           case EH: /* 原本左、右子树等高，现因左子树增高而使树增高 */
                    (*T)->bf=LH;
                    *taller=TRUE;
                    break;
           case RH: (*T)->bf=EH; /* 原本右子树比左子树高，现左、右子树等高 */
                    *taller=FALSE;
         }
     }
     else
     { /* 应继续在*T的右子树中进行搜索 */
       if(!InsertAVL(&(*T)->rchild,e,taller)) /* 未插入 */
         return FALSE;
       if(*taller) /* 已插入到T的右子树且右子树“长高” */
         switch((*T)->bf) /* 检查T的平衡度 */
         {
           case LH: (*T)->bf=EH; /* 原本左子树比右子树高，现左、右子树等高 */
                    *taller=FALSE;
                    break;
           case EH: /* 原本左、右子树等高，现因右子树增高而使树增高 */
                    (*T)->bf=RH;
                    *taller=TRUE;
		    break;
	   case RH: /* 原本右子树比左子树高，需要作右平衡处理 */
		    RightBalance(T);
		    *taller=FALSE;
	 }
     }
   }
   return TRUE;
 }

 void TraverseDSTable(BSTree DT,void(*Visit)(ElemType))
 { /* 初始条件: 动态查找表DT存在，Visit是对结点操作的应用函数 */
   /* 操作结果: 按关键字的顺序对DT的每个结点调用函数Visit()一次且至多一次 */
   if(DT)
   {
     TraverseDSTable(DT->lchild,Visit); /* 先中序遍历左子树 */
     Visit(DT->data); /* 再访问根结点 */
     TraverseDSTable(DT->rchild,Visit); /* 最后中序遍历右子树 */
   }
 }

**********BO9-4.c**********
 /* bo9-4.c 动态查找表(B树)的基本操作 */
 Status InitDSTable(BTree *DT)
 { /* 操作结果: 构造一个空的动态查找表DT */
   *DT=NULL;
   return OK;
 }

 void DestroyDSTable(BTree *DT)
 { /* 初始条件: 动态查找表DT存在。操作结果: 销毁动态查找表DT */
   int i;
   if(*DT) /* 非空树 */
   {
     for(i=0;i<=(*DT)->keynum;i++)
       DestroyDSTable(&(*DT)->node[i].ptr); /* 依次销毁第i棵子树 */
     free(*DT); /* 释放根结点 */
     *DT=NULL; /* 空指针赋0 */
   }
 }

 int Search(BTree p, KeyType K)
 { /* 在p->node[1..keynum].key中查找i,使得p->node[i].key≤K＜p->node[i+1].key */
   int i=0,j;
   for(j=1;j<=p->keynum;j++)
     if(p->node[j].key<=K)
       i=j;
   return i;
 }

 Result SearchBTree(BTree T, KeyType K)
 { /* 在m阶B树T上查找关键字K，返回结果(pt,i,tag)。若查找成功，则特征值 */
   /* tag=1，指针pt所指结点中第i个关键字等于K；否则特征值tag=0，等于K的 */
   /* 关键字应插入在指针Pt所指结点中第i和第i+1个关键字之间。算法9.13 */
   BTree p=T,q=NULL; /* 初始化，p指向待查结点，q指向p的双亲 */
   Status found=FALSE;
   int i=0;
   Result r;
   while(p&&!found)
   {
     i=Search(p,K); /* p->node[i].key≤K<p->node[i+1].key */
     if(i>0&&p->node[i].key==K) /* 找到待查关键字 */
       found=TRUE;
     else
     {
       q=p;
       p=p->node[i].ptr;
     }
   }
   r.i=i;
   if(found) /* 查找成功 */
   {
     r.pt=p;
     r.tag=1;
   }
   else /*  查找不成功，返回K的插入位置信息 */
   {
     r.pt=q;
     r.tag=0;
   }
   return r;
 }

 void Insert(BTree *q,int i,Record *r,BTree ap)
 { /* 将r->key、r和ap分别插入到q->key[i+1]、q->recptr[i+1]和q->ptr[i+1]中 */
   int j;
   for(j=(*q)->keynum;j>i;j--) /* 空出q->node[i+1] */
     (*q)->node[j+1]=(*q)->node[j];
   (*q)->node[i+1].key=r->key;
   (*q)->node[i+1].ptr=ap;
   (*q)->node[i+1].recptr=r;
   (*q)->keynum++;
 }

 void split(BTree *q,BTree *ap)
 { /* 将结点q分裂成两个结点，前一半保留，后一半移入新生结点ap */
   int i,s=(m+1)/2;
   *ap=(BTree)malloc(sizeof(BTNode)); /* 生成新结点ap */
   (*ap)->node[0].ptr=(*q)->node[s].ptr; /* 后一半移入ap */
   for(i=s+1;i<=m;i++)
   {
     (*ap)->node[i-s]=(*q)->node[i];
     if((*ap)->node[i-s].ptr)
       (*ap)->node[i-s].ptr->parent=*ap;
   }
   (*ap)->keynum=m-s;
   (*ap)->parent=(*q)->parent;
   (*q)->keynum=s-1; /* q的前一半保留，修改keynum */
 }

 void NewRoot(BTree *T,Record *r,BTree ap)
 { /* 生成含信息(T,r,ap)的新的根结点*T，原T和ap为子树指针 */
   BTree p;
   p=(BTree)malloc(sizeof(BTNode));
   p->node[0].ptr=*T;
   *T=p;
   if((*T)->node[0].ptr)
     (*T)->node[0].ptr->parent=*T;
   (*T)->parent=NULL;
   (*T)->keynum=1;
   (*T)->node[1].key=r->key;
   (*T)->node[1].recptr=r;
   (*T)->node[1].ptr=ap;
   if((*T)->node[1].ptr)
     (*T)->node[1].ptr->parent=*T;
 }

 void InsertBTree(BTree *T,Record *r,BTree q,int i)
 { /* 在m阶B树T上结点*q的key[i]与key[i+1]之间插入关键字K的指针r。若引起 */
   /* 结点过大,则沿双亲链进行必要的结点分裂调整,使T仍是m阶B树。算法9.14改 */
   BTree ap=NULL;
   Status finished=FALSE;
   int s;
   Record *rx;
   rx=r;
   while(q&&!finished)
   {
     Insert(&q,i,rx,ap); /* 将r->key、r和ap分别插入到q->key[i+1]、q->recptr[i+1]和q->ptr[i+1]中 */
     if(q->keynum<m)
       finished=TRUE; /* 插入完成 */
     else
     { /* 分裂结点*q */
       s=(m+1)/2;
       rx=q->node[s].recptr;
       split(&q,&ap); /* 将q->key[s+1..m],q->ptr[s..m]和q->recptr[s+1..m]移入新结点*ap */
       q=q->parent;
       if(q)
         i=Search(q,rx->key); /* 在双亲结点*q中查找rx->key的插入位置 */
     }
   }
   if(!finished) /* T是空树(参数q初值为NULL)或根结点已分裂为结点*q和*ap */
     NewRoot(T,rx,ap); /* 生成含信息(T,rx,ap)的新的根结点*T，原T和ap为子树指针 */
 }

 void TraverseDSTable(BTree DT,void(*Visit)(BTNode,int))
 { /* 初始条件: 动态查找表DT存在，Visit是对结点操作的应用函数 */
   /* 操作结果: 按关键字的顺序对DT的每个结点调用函数Visit()一次且至多一次 */
   int i;
   if(DT) /* 非空树 */
   {
     if(DT->node[0].ptr) /* 有第0棵子树 */
       TraverseDSTable(DT->node[0].ptr,Visit);
     for(i=1;i<=DT->keynum;i++)
     {
       Visit(*DT,i);
       if(DT->node[i].ptr) /* 有第i棵子树 */
	 TraverseDSTable(DT->node[i].ptr,Visit);
     }
   }
 }

**********Bo9-5.c**********
 /* bo9-5.c 动态查找表(双链键树)的基本操作 */
 Status InitDSTable(DLTree *DT)
 { /* 操作结果: 构造一个空的双链键树DT */
   *DT=NULL;
   return OK;
 }

 void DestroyDSTable(DLTree *DT)
 { /* 初始条件: 双链键树DT存在。操作结果: 销毁双链键树DT */
   if(*DT) /* 非空树 */
   {
     if((*DT)->kind==BRANCH&&(*DT)->a.first) /* *DT是分支结点且有孩子 */
       DestroyDSTable(&(*DT)->a.first); /* 销毁孩子子树 */
     if((*DT)->next) /* 有兄弟 */
       DestroyDSTable(&(*DT)->next); /* 销毁兄弟子树 */
     free(*DT); /* 释放根结点 */
     *DT=NULL; /* 空指针赋0 */
   }
 }

 Record *SearchDLTree(DLTree T,KeysType K)
 { /* 在非空双链键树T中查找关键字等于K的记录，若存在， */
   /* 则返回指向该记录的指针，否则返回空指针。算法9.15，有改动 */
   DLTree p;
   int i;
   if(T)
   {
     p=T; /* 初始化 */
     i=0;
     while(p&&i<K.num)
     {
       while(p&&p->symbol!=K.ch[i]) /* 查找关键字的第i位 */
         p=p->next;
       if(p&&i<K.num) /* 准备查找下一位 */
         p=p->a.first;
       ++i;
     } /* 查找结束 */
     if(!p) /* 查找不成功 */
       return NULL;
     else /* 查找成功 */
       return p->a.infoptr;
   }
   else
     return NULL; /* 树空 */
 }

 void InsertDSTable(DLTree *DT,Record *r)
 { /* 初始条件: 双链键树DT存在，r为待插入的数据元素的指针 */
   /* 操作结果: 若DT中不存在其关键字等于(*r).key.ch的数据元素， */
   /*           则按关键字顺序插r到DT中 */
   DLTree p=NULL,q,ap;
   int i=0;
   KeysType K=r->key;
   if(!*DT&&K.num) /* 空树且关键字符串非空 */
   {
     *DT=ap=(DLTree)malloc(sizeof(DLTNode));
     for(;i<K.num;i++) /* 插入分支结点 */
     {
       if(p)
         p->a.first=ap;
       ap->next=NULL;
       ap->symbol=K.ch[i];
       ap->kind=BRANCH;
       p=ap;
       ap=(DLTree)malloc(sizeof(DLTNode));
     }
     p->a.first=ap; /* 插入叶子结点 */
     ap->next=NULL;
     ap->symbol=Nil;
     ap->kind=LEAF;
     ap->a.infoptr=r;
   }
   else /* 非空树 */
   {
     p=*DT; /* 指向根结点 */
     while(p&&i<K.num)
     {
       while(p&&p->symbol<K.ch[i]) /* 沿兄弟结点查找 */
       {
         q=p;
         p=p->next;
       }
       if(p&&p->symbol==K.ch[i]) /* 找到与K.ch[i]相符的结点 */
       {
         q=p;
         p=p->a.first; /* p指向将与K.ch[i+1]比较的结点 */
         ++i;
       }
       else /* 没找到,插入关键字 */
       {
         ap=(DLTree)malloc(sizeof(DLTNode));
         if(q->a.first==p)
           q->a.first=ap; /* 在长子的位置插入 */
         else /* q->next==p */
           q->next=ap; /* 在兄弟的位置插入 */
         ap->next=p;
         ap->symbol=K.ch[i];
         ap->kind=BRANCH;
         p=ap;
         ap=(DLTree)malloc(sizeof(DLTNode));
         i++;
         for(;i<K.num;i++) /* 插入分支结点 */
         {
           p->a.first=ap;
           ap->next=NULL;
           ap->symbol=K.ch[i];
           ap->kind=BRANCH;
	   p=ap;
           ap=(DLTree)malloc(sizeof(DLTNode));
         }
         p->a.first=ap; /* 插入叶子结点 */
         ap->next=NULL;
         ap->symbol=Nil;
         ap->kind=LEAF;
         ap->a.infoptr=r;
       }
     }
   }
 }

 typedef struct
 {
   char ch;
   DLTree p;
 }SElemType; /* 定义栈元素类型 */
 #include"c3-1.h"
 #include"bo3-1.c"
 void TraverseDSTable(DLTree DT,void(*Vi)(Record))
 { /* 初始条件: 双链键树DT存在，Vi是对结点操作的应用函数， */
   /*           ViR是对记录操作的应用函数 */
   /* 操作结果: 按关键字的顺序输出关键字及其对应的记录 */
   SqStack s;
   SElemType e;
   DLTree p;
   int i=0,n=8;
   if(DT)
   {
     InitStack(&s);
     e.p=DT;
     e.ch=DT->symbol;
     Push(&s,e);
     p=DT->a.first;
     while(p->kind==BRANCH) /* 分支结点 */
     {
       e.p=p;
       e.ch=p->symbol;
       Push(&s,e);
       p=p->a.first;
     }
     e.p=p;
     e.ch=p->symbol;
     Push(&s,e);
     Vi(*(p->a.infoptr));
     i++;
     while(!StackEmpty(s))
     {
       Pop(&s,&e);
       p=e.p;
       if(p->next) /* 有兄弟结点 */
       {
         p=p->next;
         while(p->kind==BRANCH) /* 分支结点 */
         {
           e.p=p;
           e.ch=p->symbol;
           Push(&s,e);
           p=p->a.first;
         }
         e.p=p;
         e.ch=p->symbol;
         Push(&s,e);
         Vi(*(p->a.infoptr));
         i++;
         if(i%n==0)
           printf("\n"); /* 输出n个元素后换行 */
       }
     }
   }
 }

**********Bo9-6.c**********
 /* bo9-6.c 动态查找表(Trie键树)的基本操作 */
 Status InitDSTable(TrieTree *T)
 { /* 操作结果: 构造一个空的Trie键树T */
   *T=NULL;
   return OK;
 }

 void DestroyDSTable(TrieTree *T)
 { /* 初始条件: Trie树T存在。操作结果: 销毁Trie树T */
   int i;
   if(*T) /* 非空树 */
   {
     for(i=0;i<LENGTH;i++)
       if((*T)->kind==BRANCH&&(*T)->a.bh.ptr[i]) /* 第i个结点不空 */
         if((*T)->a.bh.ptr[i]->kind==BRANCH) /* 是子树 */
           DestroyDSTable(&(*T)->a.bh.ptr[i]);
         else /* 是叶子 */
         {
           free((*T)->a.bh.ptr[i]);
           (*T)->a.bh.ptr[i]=NULL;
         }
     free(*T); /* 释放根结点 */
     *T=NULL; /* 空指针赋0 */
   }
 }

 int ord(char c)
 {
   c=toupper(c);
   if(c>='A'&&c<='Z')
     return c-'A'+1; /* 英文字母返回其在字母表中的序号 */
   else
     return 0; /* 其余字符返回0 */
 }

 Record *SearchTrie(TrieTree T,KeysType K)
 { /* 在键树T中查找关键字等于K的记录。算法9.16 */
   TrieTree p;
   int i;
   for(p=T,i=0;p&&p->kind==BRANCH&&i<K.num;p=p->a.bh.ptr[ord(K.ch[i])],++i);
   /* 对K的每个字符逐个查找,*p为分支结点,ord()求字符在字母表中序号 */
   if(p&&p->kind==LEAF&&p->a.lf.K.num==K.num&&EQ(p->a.lf.K.ch,K.ch)) /* 查找成功 */
     return p->a.lf.infoptr;
   else /* 查找不成功 */
     return NULL;
 }

 void InsertTrie(TrieTree *T,Record *r)
 { /* 初始条件: Trie键树T存在，r为待插入的数据元素的指针 */
   /* 操作结果: 若T中不存在其关键字等于(*r).key.ch的数据元素， */
   /*           则按关键字顺序插r到T中 */
   TrieTree p,q,ap;
   int i=0,j;
   KeysType K1,K=r->key;
   if(!*T) /* 空树 */
   {
     *T=(TrieTree)malloc(sizeof(TrieNode));
     (*T)->kind=BRANCH;
     for(i=0;i<LENGTH;i++) /* 指针量赋初值NULL */
       (*T)->a.bh.ptr[i]=NULL;
     p=(*T)->a.bh.ptr[ord(K.ch[0])]=(TrieTree)malloc(sizeof(TrieNode));
     p->kind=LEAF;
     p->a.lf.K=K;
     p->a.lf.infoptr=r;
   }
   else /* 非空树 */
   {
     for(p=*T,i=0;p&&p->kind==BRANCH&&i<K.num;++i)
     {
       q=p;
       p=p->a.bh.ptr[ord(K.ch[i])];
     }
     i--;
     if(p&&p->kind==LEAF&&p->a.lf.K.num==K.num&&EQ(p->a.lf.K.ch,K.ch)) /* T中存在该关键字 */
       return;
     else /* T中不存在该关键字,插入之 */
     {
       if(!p) /* 分支空 */
       {
         p=q->a.bh.ptr[ord(K.ch[i])]=(TrieTree)malloc(sizeof(TrieNode));
         p->kind=LEAF;
         p->a.lf.K=K;
         p->a.lf.infoptr=r;
       }
       else if(p->kind==LEAF) /* 有不完全相同的叶子 */
       {
         K1=p->a.lf.K;
         do
	 {
           ap=q->a.bh.ptr[ord(K.ch[i])]=(TrieTree)malloc(sizeof(TrieNode));
           ap->kind=BRANCH;
           for(j=0;j<LENGTH;j++) /* 指针量赋初值NULL */
             ap->a.bh.ptr[j]=NULL;
           q=ap;
           i++;
         }while(ord(K.ch[i])==ord(K1.ch[i]));
         q->a.bh.ptr[ord(K1.ch[i])]=p;
         p=q->a.bh.ptr[ord(K.ch[i])]=(TrieTree)malloc(sizeof(TrieNode));
         p->kind=LEAF;
         p->a.lf.K=K;
         p->a.lf.infoptr=r;
       }
     }
   }
 }

 void TraverseDSTable(TrieTree T,Status(*Vi)(Record*))
 { /* 初始条件: Trie键树T存在，Vi是对记录指针操作的应用函数 */
   /* 操作结果: 按关键字的顺序输出关键字及其对应的记录 */
   TrieTree p;
   int i;
   if(T)
   {
     for(i=0;i<LENGTH;i++)
     {
       p=T->a.bh.ptr[i];
       if(p&&p->kind==LEAF)
         Vi(p->a.lf.infoptr);
       else if(p&&p->kind==BRANCH)
         TraverseDSTable(p,Vi);
     }
   }
 }

**********Bo9-7.c**********
 /* bo9-7.c 哈希函数的基本操作 */
 Status InitHashTable(HashTable *H)
 { /* 操作结果: 构造一个空的哈希表 */
   int i;
   (*H).count=0; /* 当前元素个数为0 */
   (*H).sizeindex=0; /* 初始存储容量为hashsize[0] */
   m=hashsize[0];
   (*H).elem=(ElemType*)malloc(m*sizeof(ElemType));
   if(!(*H).elem)
     exit(OVERFLOW); /* 存储分配失败 */
   for(i=0;i<m;i++)
     (*H).elem[i].key=NULLKEY; /* 未填记录的标志 */
   return OK;
 }

 void DestroyHashTable(HashTable *H)
 { /* 初始条件: 哈希表H存在。操作结果: 销毁哈希表H */
   free((*H).elem);
   (*H).elem=NULL;
   (*H).count=0;
   (*H).sizeindex=0;
 }

 unsigned Hash(KeyType K)
 { /* 一个简单的哈希函数(m为表长，全局变量) */
   return K%m;
 }

 void collision(int *p,int d) /* 线性探测再散列 */
 { /* 开放定址法处理冲突 */
   *p=(*p+d)%m;
 }

 Status SearchHash(HashTable H,KeyType K,int *p,int *c)
 { /* 在开放定址哈希表H中查找关键码为K的元素,若查找成功,以p指示待查数据 */
   /* 元素在表中位置,并返回SUCCESS;否则,以p指示插入位置,并返回UNSUCCESS */
   /* c用以计冲突次数，其初值置零，供建表插入时参考。算法9.17 */
   *p=Hash(K); /* 求得哈希地址 */
   while(H.elem[*p].key!=NULLKEY&&!EQ(K,H.elem[*p].key))
   { /* 该位置中填有记录．并且关键字不相等 */
     (*c)++;
     if(*c<m)
       collision(p,*c); /* 求得下一探查地址p */
     else
       break;
   }
   if EQ(K,H.elem[*p].key)
     return SUCCESS; /* 查找成功，p返回待查数据元素位置 */
   else
     return UNSUCCESS; /* 查找不成功(H.elem[p].key==NULLKEY)，p返回的是插入位置 */
 }

 Status InsertHash(HashTable *,ElemType); /* 对函数的声明 */
 void RecreateHashTable(HashTable *H) /* 重建哈希表 */
 { /* 重建哈希表 */
   int i,count=(*H).count;
   ElemType *p,*elem=(ElemType*)malloc(count*sizeof(ElemType));
   p=elem;
   printf("重建哈希表\n");
   for(i=0;i<m;i++) /* 保存原有的数据到elem中 */
     if(((*H).elem+i)->key!=NULLKEY) /* 该单元有数据 */
       *p++=*((*H).elem+i);
   (*H).count=0;
   (*H).sizeindex++; /* 增大存储容量 */
   m=hashsize[(*H).sizeindex];
   p=(ElemType*)realloc((*H).elem,m*sizeof(ElemType));
   if(!p)
     exit(OVERFLOW); /* 存储分配失败 */
   (*H).elem=p;
   for(i=0;i<m;i++)
     (*H).elem[i].key=NULLKEY; /* 未填记录的标志(初始化) */
   for(p=elem;p<elem+count;p++) /* 将原有的数据按照新的表长插入到重建的哈希表中 */
     InsertHash(H,*p);
 }

 Status InsertHash(HashTable *H,ElemType e)
 { /* 查找不成功时插入数据元素e到开放定址哈希表H中，并返回OK； */
   /* 若冲突次数过大，则重建哈希表。算法9.18 */
   int c,p;
   c=0;
   if(SearchHash(*H,e.key,&p,&c)) /* 表中已有与e有相同关键字的元素 */
     return DUPLICATE;
   else if(c<hashsize[(*H).sizeindex]/2) /* 冲突次数c未达到上限,(c的阀值可调) */
   { /* 插入e */
     (*H).elem[p]=e;
     ++(*H).count;
     return OK;
   }
   else
     RecreateHashTable(H); /* 重建哈希表 */
   return ERROR;
 }

 void TraverseHash(HashTable H,void(*Vi)(int,ElemType))
 { /* 按哈希地址的顺序遍历哈希表 */
   int i;
   printf("哈希地址0～%d\n",m-1);
   for(i=0;i<m;i++)
     if(H.elem[i].key!=NULLKEY) /* 有数据 */
       Vi(i,H.elem[i]);
 }

 Status Find(HashTable H,KeyType K,int *p)
 { /* 在开放定址哈希表H中查找关键码为K的元素,若查找成功,以p指示待查数据 */
   /* 元素在表中位置,并返回SUCCESS;否则,返回UNSUCCESS */
   int c=0;
   *p=Hash(K); /* 求得哈希地址 */
   while(H.elem[*p].key!=NULLKEY&&!EQ(K,H.elem[*p].key))
   { /* 该位置中填有记录．并且关键字不相等 */
     c++;
     if(c<m)
       collision(p,c); /* 求得下一探查地址p */
     else
       return UNSUCCESS; /* 查找不成功(H.elem[p].key==NULLKEY) */
   }
   if EQ(K,H.elem[*p].key)
     return SUCCESS; /* 查找成功，p返回待查数据元素位置 */
   else
     return UNSUCCESS; /* 查找不成功(H.elem[p].key==NULLKEY) */
 }

**********C9-1.H**********
 /* c9-1.h 静态查找表的顺序存储结构 */
 typedef struct
 {
   ElemType *elem; /* 数据元素存储空间基址，建表时按实际长度分配，0号单元留空 */
   int length; /* 表长度 */
 }SSTable;

**********c9-2.h**********
 /* c9-2.h 平衡二叉树的类型 */
 typedef struct BSTNode
 {
   ElemType data;
   int bf; /* 结点的平衡因子 */
   struct BSTNode *lchild,*rchild; /* 左、右孩子指针 */
 }BSTNode,*BSTree;

**********C9-3.h**********
 /* c9-3.h B树的结点类型 */
 typedef struct
 {
   KeyType key; /* 关键字 */
   Others others; /* 其它部分(由主程定义) */
 }Record; /* 记录类型 */

 typedef struct BTNode
 {
   int keynum; /* 结点中关键字个数，即结点的大小 */
   struct BTNode *parent; /* 指向双亲结点 */
   struct Node /* 结点向量类型 */
   {
     KeyType key; /* 关键字向量 */
     struct BTNode *ptr; /* 子树指针向量 */
     Record *recptr; /* 记录指针向量 */
   }node[m+1]; /* key,recptr的0号单元未用 */
 }BTNode,*BTree; /* B树结点和B树的类型 */

 typedef struct
 {
   BTNode *pt; /* 指向找到的结点 */
   int i; /* 1..m，在结点中的关键字序号 */
   int tag; /* 1:查找成功，O:查找失败 */
 }Result; /* B树的查找结果类型 */

**********C9-4.H**********
 /* c9-4.h 双链树的存储结构 */
 #define MAXKEYLEN 16 /* 关键字的最大长度 */
 typedef struct
 {
   char ch[MAXKEYLEN]; /* 关键字 */
   int num; /* 关键字长度 */
 }KeysType; /* 关键字类型 */

 typedef struct
 {
   KeysType key; /* 关键字 */
   Others others; /* 其它部分(由主程定义) */
 }Record; /* 记录类型 */

 typedef enum{LEAF,BRANCH}NodeKind; /* 结点种类:{叶子,分支} */
 typedef struct DLTNode /* 双链树类型 */
 {
   char symbol;
   struct DLTNode *next; /* 指向兄弟结点的指针 */
   NodeKind kind;
   union
   {
     Record *infoptr; /* 叶子结点的记录指针 */
     struct DLTNode *first; /* 分支结点的孩子链指针 */
   }a;
 }DLTNode,*DLTree;

**********C9-5.H**********
 /* c9-5.h Trie键树类型 */
 #define MAXKEYLEN 16 /* 关键字的最大长度，同c9-4.h */
 typedef struct
 {
   char ch[MAXKEYLEN]; /* 关键字 */
   int num; /* 关键字长度 */
 }KeysType; /* 关键字类型，同c9-4.h */

 typedef struct
 {
   KeysType key; /* 关键字 */
   Others others; /* 其它部分(由主程定义) */
 }Record; /* 记录类型，同c9-4.h */

 typedef enum{LEAF,BRANCH}NodeKind; /* 结点种类:{叶子,分支}，同c9-4.h */

 typedef struct TrieNode /* Trie键树类型 */
 {
   NodeKind kind;
   union
   {
     struct /* 叶子结点 */
     {
       KeysType K;
       Record *infoptr;
     }lf;
     struct /* 分支结点 */
     {
       struct TrieNode *ptr[LENGTH]; /* LENGTH为结点的最大度+1,在主程定义 */
     /*  int num; 改 */
     }bh;
   }a;
 }TrieNode,*TrieTree;

 /* 对两个字符串型关键字的比较约定为如下的宏定义 */
 #define EQ(a,b) (!strcmp((a),(b)))
 #define LT(a,b) (strcmp((a),(b))<0)
 #define LQ(a,b) (strcmp((a),(b))<=0)

**********C9-6.H**********
 /* c9-6.h 开放定址哈希表的存储结构 */
 int hashsize[]={11,19,29,37}; /* 哈希表容量递增表，一个合适的素数序列 */
 int m=0; /* 哈希表表长，全局变量 */
 typedef struct
 {
   ElemType *elem; /* 数据元素存储基址，动态分配数组 */
   int count; /* 当前数据元素个数 */
   int sizeindex; /* hashsize[sizeindex]为当前容量 */
 }HashTable;

 #define SUCCESS 1
 #define UNSUCCESS 0
 #define DUPLICATE -1

**********C9.H**********
 /* c9.h 对两个数值型关键字的比较约定为如下的宏定义 */
 #define EQ(a,b) ((a)==(b))
 #define LT(a,b) ((a)<(b))
 #define LQ(a,b) ((a)<=(b))

