//图的邻接矩阵表数据结构

#define MaxNum 100 //定义最大顶点数为100

typedef struct 
{
    char vex[MaxNum];//顶点数组
    int edge[MaxNum][MaxNum];//定义边的二维数组
    int vexnum,edgenum;//图中顶点和边的数量
};



(1) Adjacent(G,x,y)   判断图G是否存在x,y边
(2) Neighbors(G,x)  列出图G中与X相邻的边
(3) InsertVertex(G,x) 在图G中插入顶点x
(4) Deletevertex(G,x) 在图G中删除顶点x
(5) AddEdge(G,x,y) 在图G中x与y之间加入一条边
(6) RemoveEdge(G,x,y)
(7) FirstNeighbor(G,x) 图G中与x邻接的第一个顶点，若存在则返回相应的顶点号，否则则返回-1
(8) NextNeighbor(G,x,y) 在图G中顶点y是x的第一个邻接顶点，返回除y以外的x的下一个邻接顶点号，若y是x的最后一个邻接顶点则返回-1
(9) Get_edge_value(G,x,y) 获取x，y之间边的权值
(10) Set_edge_value(G,x,y,v) 设置顶点x，y之间边的权值为v