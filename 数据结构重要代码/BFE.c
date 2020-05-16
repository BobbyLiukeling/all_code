//访问图中某个连通分量
void BFS(Graph G , int v, int visited[])//图G和顶点编号
{
    visit(v);//访问图的第一个顶点
    visited[v] = 1;
    InitQueue(Q);
    EnQueue(Q,v)
    while(!isEmpty(Q))
    {
        DeQueue(Q,v);
        for(int w = FirstNeighbor(G,v),w!=-1;w = NextNeighbor(G,v))//依次遍历与v邻接的所有顶点
        {
            if(visited[w] == -1)
            {                
                visit(w);
                visited[w] = 1;
                EnQueue(Q,w);
            }
        }
    }
}

//访问整个图，包括图中所有连通分量
void BSFGraph(Graph G)
{
    int visited[G.vexnum];
    for(int i = 0;i<G.vexnum,i++)//初始化，顶点表
    {
        visited[i] = -1;
    }

    for(int i = 0;i<G.vexnum;i++
    {
        if(visited[i] == -1)//未被访问
            BFS(Q,i,&visited);
    }
}