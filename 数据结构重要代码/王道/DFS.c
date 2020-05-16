int Visited[MAX_VEX_NUM]
void DFSTrace(Graph G)
{
    for(int i = 0; i<G.vexnum;i++)
    {
        visited[i] = 0;
    }
    for (int i = 0;i<G.vexnum;i++)
    {
        if (visited[i] == 0)
        {
            DFS(G,i);
        }
    }
}

void DFS(Graph G, int v)
{
    visite(v);
    visited[v] = 1;
    for(int w = firstneighbor(G,v);w>0;w = nextneoghbor(G,v,w))
    {
        if(visited[w] == 0)
            DFS(G,w);
    }
}