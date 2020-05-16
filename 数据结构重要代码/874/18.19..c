//18年19题用邻接表表示的图，你个顶点从0->n-1,编写算法求顶点k的入度
#define MaxVexnum 100

typedef struct 
{
    int vex;//该边表存储的当前弧尾位置
    struct ArcNode *nextnode;//下一个节点
} *ArcNode;

typedef struct
{
    int vex;
    struct ArcNode *firstNeighbor;
} Glist[MaxVexnum],Gvex;

typedef struct 
{
    Glist *List;
    int vexnum,arcnum;
}Graph;


int InDegree(Graph G,int k)
{
    int count=0;
    for(int i =0 ; i<G.vexnum ; i++)
    {
        count = count +NeighborArc(G.List[i],k);
    }
    return count;
}

int NeighborArc(Gvex *vex ,int k)
{
    Gvex *p  = vex->firstNeighbor;
    while(p)
    {
        if(p == k)
            return 1;//k是v的邻接边
    }
    return 0;
}


