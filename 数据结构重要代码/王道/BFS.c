int visited[MAX_VEXNUM];
void BFSTrace(Graph G)
{
    for(int i =0;i<G.vexnum;i++)
    {
        visited[i] = 0;
    }
    InitQueue(Q);
    for(int i = 0;i<G.vexnum;i++)
    {
        if(visited[i] == 0)
            BFS(G,i);
    }    
}

void BFS(Grap G,int v)
{
    visited[v] = 1;
    visit[v];
    Enqueue(Q,v);
    while(!isempty(Q))
    {
        DeQueue(Q,v);
        for(int w=FirstNeighbor(G,v);w>0;W = nextNeighbor(G,v,w))
        {
            if(visited[w] == 0)
            {
                visite(w);
                visited[w] = 1;
                EnQueue(Q,w);
            }

        }
    }
}