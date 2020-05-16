//广度优先，查看无向图 中是否存在从v1到v2的路径
//
bool BFS_Path_A_B(Graph G,int v1,int v2)
{
    int visited[G.vexnum];
    for(int i = 0;i<G.vexnum,i++)//初始化，顶点表
    {
        visited[i] = -1;
    }
    visited[v1] = 1;
    InitQueue(Q);
    EnQueue(Q,v1);
    // int flag = 0;//标志位，如果遍历经过v2则将标志位设置为1
    while(!isEmpty(Q))
    {
        DeQueue(Q,v1);
        for(int w = FirstNeighbor(G,v1);w!=-1;w = NextNeighbor(G,v1))//依次遍历与v邻接的所有顶点
        {
            if(w == v2)
                return 1;
            if(visited[w] == -1)
            {
                visited[w] = 1;
                EnQueue(Q,w);
            }            
        }
    }
    return 0;    
}




//深度优先，查看图中是否存在从v1到v2的路径

void DFS_Path_A_B(Graph G,int v1,int v2)
{
    int visited[G.vexnum];
    for (int i = 0; i < G.vexnum; i++)
    {
        visited[i] = -1;
    }
    InitStack(S);
    Push(S,v1);
    visited[v1] = 1;
    while(!StackEmpty(S))
    {
        Pop(S,v1);
        visited[v1] = 1;
        for(int w = FirstNeighbor(G,v1);w!=-1;w = NextNeighbor(G,v1))
        {
            if(w == v2)
            return 1;
            if(visited[w] == -1)
            {
                push(S,w);
                visited[w] =1;
            }               
        }        
    } 
    return 0;                                                                                                                                    
}

