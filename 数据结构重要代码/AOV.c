//拓扑排序
 bool AOV(Graph G,int list[])//list保存拓扑排序序列
 {
     InitStak(S);
     for(int i = 0;i<G.vexnum;i++)
     {
         if(indegree[i] == 0)//indegree数组中存放着每个顶点的入度
         {
             push(S,i);
         }
     }

     int count = 0;
     while(!isEmptyStack(S))
     {
         pop(S,v);
         list[count++] = v;//将删除顶点顺序保存在数组中
         for(p = G.Vertices(v).firstarc;p!=-1;p = p->nextarc)
         //遍历与v相连的所有边，并修改这些边的另外一个顶点的入度，将修改后入度为0 的顶点入栈
        {
            v = p->adjvex;
            if(--indegree[v] == 0)//修改顶点的入度，并判断此时入度是否为0
                push(S,v);
        }
     }
     return count<G.vexnum?false:true;//若栈为空则返回TRUE表示此图为有向无环图
 }



 Insert(SqList L[],int x)
 {
     int i = 0;
     for(; x<L[i];i++)
     for(int j = L.length;j>i;j++)//移动元素
     {
         L[j] = L[j-1];
     }
     L[i] = x;//插入
 }