//非递归的DFS

void DEF_UNRecrision(Graph G,int v,int visited[])
{
    InitStack(S);
    visit(v);
    Push(S,v);
    visited[v] = 1;
    while(!StackEmpty(S))
    {
        Pop(S,v);
        for(int w = FirstNeighbor(G,v);w!=-1;w = NextNeighbor(G,v))
        {
            if(visited[w] == -1)
            {
                visit(w);
                push(S,w);
            visited[w] =1;
            }    
        }
    }                                                                                                                                     
}

void  DFS(Graph G,int v)
{
    int visited[G.vexnum];
    for (int i = 0; i < G.vexnum; i++)
    {
        visited[i] = -1;
    }

    for(int i=0;i<G.vexnum;i++);
    {
        if(visited[i] == -1)
        {
            DEF_UNRecrision(G,v,visited);
        }
    }
    
}

