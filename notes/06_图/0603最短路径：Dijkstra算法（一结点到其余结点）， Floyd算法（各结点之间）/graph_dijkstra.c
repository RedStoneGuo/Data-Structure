/* 用邻接矩阵表示的图的Dijkstra算法的源程序*/

#include<stdio.h>
#define MAXVEX    100
                       
typedef char VexType;
typedef float AdjType;

typedef struct {
    int n;                                           /* 图的顶点个数 */
    VexType vexs[MAXVEX];                   /* 顶点信息 */
    AdjType arcs[MAXVEX][MAXVEX];           /* 边信息 */
} GraphMatrix;

typedef struct {
    VexType vertex;        /* 顶点信息 */
    AdjType length;        /* 最短路径长度 */
    int prevex;           /* 从v0到达vi(i=1,2,…n-1)的最短路径上vi的前趋顶点 */
} Path;

Path dist[6];                    /* n为图中顶点个数*/

#define MAX 1e+8

void init(GraphMatrix* pgraph, Path dist[]) {
    int i; 
    dist[0].length = 0;
    dist[0].prevex = 0;      
    dist[0].vertex = pgraph->vexs[0];

    pgraph->arcs[0][0] = 1;                    /* 表示顶点v0在集合U中 */

    for(i = 1; i < pgraph->n; i++) {             /* 初始化集合V-U中顶点的距离值 */
        dist[i].length=pgraph->arcs[0][i];
        dist[i].vertex=pgraph->vexs[i];
        if (dist[i].length != MAX)
            dist[i].prevex=0;
        else  dist[i].prevex= -1;
    }
}


void dijkstra(GraphMatrix graph, Path dist[]) {
    int i,j,minvex;
    AdjType min;
	init(&graph,dist); /* 初始化，此时集合U中只有顶点v0*/
    for(i = 1; i < graph.n; i++) {
        min=MAX;	minvex=0;
        for (j = 1; j < graph.n; j++) /*在V-U中选出距离值最小顶点*/
            if( graph.arcs[j][j] == 0 && dist[j].length < min ) {
                min=dist[j].length;  minvex=j;  
            }

        if(minvex == 0) break;	/* 从v0没有路径可以通往集合V-U中的顶点 */
        graph.arcs[minvex][minvex] = 1;	/* 集合V-U中路径最小的顶点为minvex */
        for (j = 1; j < graph.n; j++) {	/* 调整集合V-U中的顶点的最短路径 */
            if(graph.arcs[j][j] == 1)  continue;
            if(dist[j].length > dist[minvex].length + graph.arcs[minvex][j]) {
                dist[j].length = dist[minvex].length + graph.arcs[minvex][j];
                dist[j].prevex = minvex;
            }
        }
    }
}

GraphMatrix graph;

void initgraph(){
    int i,j;
    graph.n=6;
    for (i = 0; i < graph.n; i++)
        for (j = 0; j < graph.n; j++)
            graph.arcs[i][j] = (i == j ? 0 : MAX);
    graph.arcs[0][1] = 50;
    graph.arcs[0][2] = 10;
    graph.arcs[1][2] = 15;
    graph.arcs[1][4] = 5;
    graph.arcs[2][0] = 20;
    graph.arcs[2][3] = 15;
    graph.arcs[3][1] = 20;
    graph.arcs[3][4] = 35;
    graph.arcs[4][3] = 30;
    graph.arcs[5][3] = 3;
    graph.arcs[0][4] = 45;
}

int main(){
    int i;
    initgraph();
    dijkstra(graph, dist);
    for (i = 0; i < graph.n; i++)
        printf("(%.0f %d)", dist[i].length,dist[i].prevex);
    return 0;
}



