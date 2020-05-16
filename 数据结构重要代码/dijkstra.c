//dijkstra算法，求带权单源最短路径
#define MAX 1000
void dijkstra(Graph G,int v1,int v2)//求v1到v2最短路径
{
    int dist[G.vexnum];//主源到其他每个顶点的距离
    int path[G.vexnum];//每个顶点的前驱顶点
    int s[G.vexnum];//标记当前顶点是否已访问
    for(int i = 0;i<G.vexnum;i++)//初始化以上三个数组
    {
        dist[i] = arc[v1][i];
        if(arc[v1][i] == MAX)//其他顶点到源顶点不可直达，还包括特殊的源顶点自己
        {
            path[i] = -1;
        }
        else
        {
            path[i] = v1;
        }
        s[i] =0;        
    }
    s[v1] = 1;//将源顶点标记为已访问
    
    for(int i=1;i<G.vexnum;i++)//还剩n-1个顶点
    {
        int min_arc = MAX;
        int min_vex;

        for(int j = 0;j<G.vexnum;j++)
            if(s[j]!=1 && min_arc>dist[j])
            {
                min_arc = dist[j];
                min_vex = j;
            }
        
        s[min_vex] = 1;

        for(int j = 0;j<G.vexnum;j++)
        {
            if(s[j]!=1&& arc[j][min_vex]+dist[min_vex]<dist[j])
            {
                dist[j] = arc[j][min_vex] + dist[min_vex];
                path[j] = min_vex;//修改j的前驱
            }
        }
    }
}
//最后s[v1]的下标为-1，其他顶点均为0，
//查找path[]就能找到v1到v2的路径，dist[v2]就是到v1的最短路径长度