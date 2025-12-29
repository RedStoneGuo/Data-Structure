/* 用邻接矩阵表示的图的Floyd算法的源程序*/


#include<stdio.h>
#define MAXVEX  100
#define MAX 1e+8                         

typedef char VexType;
typedef float AdjType;

typedef struct {
    int n;                                           /* 图的顶点个数 */
    VexType vexs[MAXVEX];                   /* 顶点信息 */
    AdjType arcs[MAXVEX][MAXVEX];           /* 边信息 */
} GraphMatrix;

typedef struct {
    AdjType a[MAXVEX][MAXVEX];/* 关系矩阵A，存放每对顶点间最短路径长度 */
    int nextvex[MAXVEX][MAXVEX];
                /* nextvex[i][j]存放vi到vj最短路径上vi的后继顶点的下标值 */
} ShortPath;

void floyd(GraphMatrix * pgraph, ShortPath * ppath) {
    int i, j, k;

    for (i = 0; i < pgraph->n; i++)
        for (j = 0; j < pgraph->n; j++) {
            if (pgraph->arcs[i][j] != MAX) 
                ppath->nextvex[i][j] = j;
            else ppath->nextvex[i][j] = -1;

            ppath->a[i][j] = pgraph->arcs[i][j];
        }

    for (k = 0; k < pgraph->n; k++)
        for (i = 0; i < pgraph->n; i++)
            for (j = 0; j < pgraph->n; j++) { 
                if ( ppath->a[i][k] >= MAX || ppath->a[k][j] >= MAX )
                    continue;
                if ( ppath->a[i][j] > ppath->a[i][k]+ ppath->a[k][j] ) {
                    ppath->a[i][j] = ppath->a[i][k] + ppath->a[k][j];
                    ppath->nextvex[i][j] = ppath->nextvex[i][k];
                }
            }
}


GraphMatrix graph;
ShortPath path;

void init(){
    int i,j;
    graph.n = 6;
    for(i = 0; i < graph.n; i++)
        for(j = 0; j < graph.n; j++)
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
    int i,j;
    init();
    floyd(&graph, &path);
    for (i = 0; i < graph.n; i++){
        for (j = 0; j < graph.n; j++)
            printf("%d ", path.nextvex[i][j]);
        putchar('\n');
    }
    return 0;
}



