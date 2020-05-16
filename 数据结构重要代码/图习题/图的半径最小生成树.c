//找出图的半径最小生成树

// 采用广度优先搜索的方式，并在每次搜索是记下层数，使用辅助队列
//G的数据结构中增加一个表示数的层次的标志位

int GetVExHeigh(Graph G,int v)//默认从下标为1的节点开始搜索
{
    InitQueue(Q);//初始化队列    
    int s[G.vexnum];
    int heigh = 0;
    for(int i = 0;i<G.vexnum;i++)
    {
        s[i]=0;
    }
    EnQueue(Q,v);//图的下标从v开始搜索
    s[v] = 1;//顶点v一倍访问将v顶点访问标记记为1
    setheigh(Q,v,0);//根节点高度为0
    while(!isEmpty(Q))
    {
        DeQueue(Q,v);
        for(int p = FirstNeighbor(G,v);p!=-1;p=NextNeoghbor(G,v))
        {
            if(s[p]!=1)
            {
                EnQueue(Q,p);
                setheigh(Q,p,getheigh(Q,v)+1);
                if(heigh<getheigh(Q,v)+1)
                    heigh = getheigh(Q,v)+1;//更新当前树的最大半径
                s[p] =1;
            }
        }
    }
    return heigh;
}

int GetMinRadis(Graph,G)
{
    int MinHeigh = 0,heigh;
    for(int i = 0, i<G.vexnum;i++)
    {
        heigh = GetVExHeigh(G,i);
        if(MinHeigh<heigh);//将每个顶点产生的生成树高度都查找一遍
            MinHeigh = heigh;
    }
    return MinHeigh;//返回所有顶点生成树高度中最小的高度
}