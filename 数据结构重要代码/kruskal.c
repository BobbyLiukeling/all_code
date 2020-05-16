//最小生成树
// kruskal 时间复杂度为O(ElogE)，是边的堆排序的时间复杂度

typedef struct Edge
{
    int a,b;//一条边的两个顶点
    int weight ;//这条边的权重
};


void kruskal(Graph G,Edge *edges,int parent[])
{
    heap_sort(edges);//堆排序，对边进行从小到大排序，时间复杂度为O(E*logE)
    Initial(parent);
    for(int i = 0;i<G.arcnum;i++)
    {
        int a_root = Find(parent,edges[i].a);//边i的一个顶点的根编号
        int b_root = Find(parent,edges[i].b);//边i的另外一个顶点的根编号
        if(a_root!=b_root)
        {
            Union(parent,a_root,b_root);//将两个顶点合并到一个子集中
        }

    }
}
