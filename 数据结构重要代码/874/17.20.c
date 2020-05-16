//判断图中是否存在环，并判断时间复杂度
//采用拓扑排序的方式判断，且图采用邻接表的方式存储，使用时间复杂度为O(n+e)

int CircleInGraph(Graph G)//默认从顶点下标为0 的顶点开始搜索
{
    int s[G.vexnum];
    for(int i =0;i<G.vexnum;i++)
    {
        s[i] = 0;//初始化顶点被访问的标记数组
    }

    int v;
    InitQueue(Q);
    for(int i =0;i<G.vexnum;i++)
    {
        if(G->VexList[i]->Indegree == 0)//找到图中顶点全部入度为0的点
            EnQueue(Q,i);
    }    

    while(!isEmpty(Q))
    {
        DeQueue(Q,v);
        for(int p = FirstNeighbor(Q,v);p!=-1;p = nextNeighbor(Q,v))
        {   
            if(s[p] !=1)
            {
                G->VexList[p]->Indegree = G->VexList[p]->Indegree-1;
                if(G->VexList[p]->Indegree == 0)
                    {
                        EnQueue(p);
                        s[p] = 1;
                    }
            }           
            
        }
    }


    for(int i =0;i<G.vexnum;i++)
    {
        if(s[i] == 0)
            return 0;
    }

    return 1;
}

