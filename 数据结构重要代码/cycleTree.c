//判断无向图是否为一棵树

bool JudgeCycle(Graph G,int v)//传入一张图和图中任意一个顶点位置
{
    if(G.vexnum != G.edgenum+1)//实现排除基本的不能构造成熟的条件
        return 0;
    int visited[G.vexnum];
    for (int i = 0;i<G.vexnum;i++)
        visited[i] = -1;
    InitQueue(Q);
    visited[v] = 1;
    EnQueue(Q,v)//将第一个顶点进队，    
    while(!isEmpty(Q))//当队列不为空时执行以下操作
    {
        DeQueue(Q,v);
        for(int w = FirstNeighbor(G,v);w!=-1;w = NextNeighbor(G,v))//遍历v顶点的所有连接的边
        {
            if(visited[w] == 1)//遍历时发现该顶点已被访问
                return 0;//图中存在环，则退出，不存在树
            if(visited[w] == -1)
            {
                visited[w] =1;//访问后将改顶点的标识为置1
            EnQueue(Q,w);//w入队
            }
            
        }
    }
    return 1;
}