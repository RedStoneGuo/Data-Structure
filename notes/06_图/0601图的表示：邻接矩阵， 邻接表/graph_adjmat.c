/*  用图邻接矩阵表示实现的一些基本运算*/


#include<stdio.h>
#include<stdlib.h>

#define MAXVEX 20
#define NON -1

typedef struct {char vex;  int mark;}  VexType;

typedef float AdjType;

typedef struct {
    int n;                                 /* 图的顶点个数 */
    VexType vexs[MAXVEX];                 /*  顶点信息 */
    AdjType arcs[MAXVEX][MAXVEX];           /* 边信息 */
} GraphMatrix;

int firstVertex(GraphMatrix* pgraph) {    
    return pgraph->n == 0 ? NON : 0;
}

int nextVertex(GraphMatrix* pgraph,int n) {    
    return n == pgraph->n-1 ? NON : n+1;
}

int firstAdjacent(GraphMatrix* pgraph, int i) {
    int k;
    for (k = 0; k < pgraph->n; k++)
        if(pgraph->arcs[i][k] != 0) return k;
    return NON; 
}  

int  nextAdjacent(GraphMatrix* pgraph, int i, int j) {
    int k;
    for (k = j+1; k < pgraph->n; k++)
        if (pgraph->arcs[i][k] != 0) return k;
    return NON; 
}   



GraphMatrix* makeMatrix(){
    GraphMatrix* p;
    int i,j;
    p = (GraphMatrix*)malloc(sizeof(GraphMatrix));
    p->n = 9;
    for (i = 0; i < p->n; i++)
        for (j = 0; j < p->n; j++)
            p->arcs[i][j] = 0;
    p->vexs[0].vex='a';  p->vexs[1].vex='b';p->vexs[2].vex='c';p->vexs[3].vex='d';p->vexs[4].vex='e';
    p->vexs[0].mark=0;   p->vexs[1].mark=0; p->vexs[2].mark=0; p->vexs[3].mark=0; p->vexs[4].mark=0;
    p->arcs[0][2] = 1;
    p->arcs[0][7] = 1; 
    p->arcs[1][2] = 1;
    p->arcs[1][3] = 1;
    p->arcs[1][4] = 1;
    p->arcs[2][3] = 1;
    p->arcs[3][5] = 1;
    p->arcs[3][6] = 1;
    p->arcs[4][5] = 1;
    p->arcs[7][8] = 1;
    p->arcs[8][6] = 1;
    return p;
}

void dfs(GraphMatrix *g, int v) 
{  int v1;  
printf("图周游的第%d个点的数据为 %c\n",v,g->vexs[v].vex);
g->vexs[v].mark =1;
for(v1=firstAdjacent(g,v);v1!= NULL; v1=nextAdjacent(g,v,v1)) 
if (g->vexs[v1].mark==0) 
dfs (g ,v1); /* 递归调用 dfs */
}

void dft (GraphMatrix *g){   int v;
for (v=firstVertex(g);v != NULL; v=nextVertex(g,v)) 
 if (g->vexs[v].mark==0) 
 dfs(g,v) ; /* 调用 dfs */
}






int main() {
    return 0;
}
