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

/* 建立图的邻接矩阵存储 */
GraphMatrix* createGraphMatrix() {
    GraphMatrix* p;
    int i, j;
    
    p = (GraphMatrix*)malloc(sizeof(GraphMatrix));
    p->n = 4;  // 4个顶点
    
    // 初始化邻接矩阵为0
    for (i = 0; i < p->n; i++) {
        for (j = 0; j < p->n; j++) {
            p->arcs[i][j] = 0;
        }
    }
    
    // 设置顶点信息
    p->vexs[0].vex = 'a';
    p->vexs[1].vex = 'b'; 
    p->vexs[2].vex = 'c';
    p->vexs[3].vex = 'd';
    
    // 初始化标记为0（未访问）
    for (i = 0; i < p->n; i++) {
        p->vexs[i].mark = 0;
    }
    
    // 设置边（无向图，对称矩阵）
    // a-b 边
    p->arcs[0][1] = 1;
    p->arcs[1][0] = 1;
    
    // a-c 边
    p->arcs[0][2] = 1;
    p->arcs[2][0] = 1;

    // a-d 边  
    p->arcs[0][3] = 1;
    p->arcs[3][0] = 1;
    
    // b-c 边
    p->arcs[1][2] = 1;
    p->arcs[2][1] = 1;
    
    // b-d 边
    p->arcs[3][1] = 1;
    p->arcs[1][3] = 1;

    return p;
}

/* 辅助函数：打印邻接矩阵 */
void printAdjMatrix(GraphMatrix* pgraph) {
    int i, j;
    
    printf("顶点集合: ");
    for (i = 0; i < pgraph->n; i++) {
        printf("%c ", pgraph->vexs[i].vex);
    }
    printf("\n\n");
    
    printf("邻接矩阵:\n");
    printf("  ");
    for (i = 0; i < pgraph->n; i++) {
        printf("%c ", pgraph->vexs[i].vex);
    }
    printf("\n");
    
    for (i = 0; i < pgraph->n; i++) {
        printf("%c ", pgraph->vexs[i].vex);
        for (j = 0; j < pgraph->n; j++) {
            printf("%.0f ", pgraph->arcs[i][j]);
        }
        printf("\n");
    }
}

int firstVertex(GraphMatrix* pgraph) {    
    return pgraph->n == 0 ? NON : 0;
}

int nextVertex(GraphMatrix* pgraph, int n) {    
    return n == pgraph->n-1 ? NON : n+1;
}

int firstAdjacent(GraphMatrix* pgraph, int i) {
    int k;
    for (k = 0; k < pgraph->n; k++)
        if(pgraph->arcs[i][k] != 0) return k;
    return NON; 
}  

int nextAdjacent(GraphMatrix* pgraph, int i, int j) {
    int k;
    for (k = j+1; k < pgraph->n; k++)
        if (pgraph->arcs[i][k] != 0) return k;
    return NON; 
}

/* 深度优先搜索 */
void dfs(GraphMatrix *g, int v) {  
    int v1;  
    printf("图周游的第 %d 个点的数据为 %c \n", v, g->vexs[v].vex);
    g->vexs[v].mark = 1;  // 标记为已访问
    
    for(v1 = firstAdjacent(g, v); v1 != NON; v1 = nextAdjacent(g, v, v1)) {
        if (g->vexs[v1].mark == 0) {
            dfs(g, v1);  /* 递归调用 dfs */
        }
    }
}

/* 深度优先周游 */
void dft(GraphMatrix *g) {   
    int v;
    
    //重置所有顶点的访问标记
    for (v = 0; v < g->n; v++) {
        g->vexs[v].mark = 0;
    }
    
    for (v = firstVertex(g); v != NON; v = nextVertex(g, v)) {
        if (g->vexs[v].mark == 0) {
            dfs(g, v);  /* 调用 dfs */
        }
    }
}

/* 主函数 */
int main() {
    GraphMatrix* graph = createGraphMatrix();
    
    printAdjMatrix(graph);
    dft(graph);
    free(graph);
    
    return 0;
}