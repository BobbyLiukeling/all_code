//最小生成树prime算法，时间复杂度O(|V|^2)，时间复杂度只与顶点个数有关，与边无关
/*
Gedge = {
    {A,B:3},{A,C:1},{A,E:4},{B,C:2},{C,D:5},{C,E:6}
}

*/



void MinTree_Prime(Graph G)
{
    int min_weight[G.vexnum];//未计算的每个顶点到已计算所有顶点间，所有边最小的值（是一组），已计算的节点的值均为0
    //即每个为计算顶点都有一个到已计算顶点群中权值最小的边，或者暂时还不可达（为正无穷）
    int adjvex[G.vexnum];//min_weight中每个边对应的已计算了的那个顶点（每条边两个顶点，一边在已计算的边群中，一边在未计算的边群中）
   
   for(int i = 0;i<G.vexnum;i++)//初始化两个数组
    {
        min_weight[i] = G.Edge[i][0]//默认从图中标号为0的顶点，开始寻找最小生成树，也可以自定义为其他点
        adjvex[i] = 0;//初始化时，每条min_weight的一端都连载顶点0上。        
    }

    int min_arc;//从min_weight中挑选出的最小的边，即已计算的顶点群与未计算的顶点群所有相连接的边中的最小边
    int min_vex;//对应与min_arc相连接的边的未计算顶点群中的那一个顶点
    for(int i= 1;i<G.vexnum;i++)
    {
        min_arc = MAX;//首先初始化

        /*
        第一个for循环功能：
        （1）找到min_weight中的边的最小权值min_arc（除0以外）
        （2）找到min_arc在min_weight中对应的下标
        */
        for(int j = 1;j<G.vexnum;j++)//除去小标为0 的结点还剩n-1个结点
            if(min_weight[j]!=0&&min_weight[j]<min_arc)
            //min_weight[j]!=0：若结点加入到了已计算结点群中，则将该结点对应的min_weight值修改为0 ，
            {
                min_arc = min_weight[j];
                min_vex = j;
            }
        min_weight[min_vex] = 0;//修改已找到的 已计算结点群与未计算节点群权值最小边，所连接的未计算的结点min_weight的下标，

        /*
        第二个for循环功能：
        （1）由于新加入了min_vex顶点，更新min_weight数组
        （2）由于min_weight的更新，从而更新adjvex数组
        */
        for(int j = 0;j<G.numvex;j++)
            /*
            if的判断条件
            （1)min_weight[j]!=0
                排除掉所有已计算的结点，此时的j均为未计算的结点的下标
            (2) G.Edge[min_arc][j]
                新加入已计算群的结点到其他未计算结点的边的权值
            （3）min_weight[j]
                原来的已计算结点群到各个未计算结点的边的最小权值
            */
            if(min_weight[j]!=0 && G.Edge[min_arc][j]<min_weight[j])//
            {
                min_weight[j] = G.Edge[min_arc][j];
                adjvex[j] = min_arc;
            }        
    }
}
