/* Floyd算法求所有顶点对最短路径 */

#include<stdio.h>
#define MAXVEX 5
#define MAX 9999  /* 表示∞ */

typedef int VexType;
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

/* Floyd算法 */
void floyd(GraphMatrix * pgraph, ShortPath * ppath) {
    int i, j, k;

    /* 初始化：A矩阵为邻接矩阵，nextvex记录路径 */
    for (i = 0; i < pgraph->n; i++) {
        for (j = 0; j < pgraph->n; j++) {
            if (pgraph->arcs[i][j] != MAX && i != j) 
                ppath->nextvex[i][j] = j;  /* 直接后继 */
            else 
                ppath->nextvex[i][j] = -1; /* 无路径 */

            ppath->a[i][j] = pgraph->arcs[i][j];
        }
    }

    /* 三重循环：动态规划核心 */
    for (k = 0; k < pgraph->n; k++) {
        for (i = 0; i < pgraph->n; i++) {
            for (j = 0; j < pgraph->n; j++) { 
                /* 如果经过顶点k可以使路径更短 */
                if (ppath->a[i][k] + ppath->a[k][j] < ppath->a[i][j]) {
                    ppath->a[i][j] = ppath->a[i][k] + ppath->a[k][j];
                    ppath->nextvex[i][j] = ppath->nextvex[i][k];
                }
            }
        }
    }
}

/* 创建题目给定的图 */
GraphMatrix createGraph() {
    GraphMatrix graph;
    int i, j;
    
    graph.n = 5;
    
    /* 初始化顶点 */
    for(i = 0; i < graph.n; i++) {
        graph.vexs[i] = i;
    }
    
    /* 初始化邻接矩阵 */
    for(i = 0; i < graph.n; i++) {
        for(j = 0; j < graph.n; j++) {
            graph.arcs[i][j] = (i == j ? 0 : MAX);
        }
    }
    
    /* 设置边权值 */
    /* 
        0   1   2   3   4
    0   0   3   5   8   MAX
    1   3   0   6   4   11
    2   5   6   0   2   MAX
    3   8   4   2   0   10
    4   MAX 11  MAX 10  0
    */
    graph.arcs[0][1] = 3;
    graph.arcs[0][2] = 5;
    graph.arcs[0][3] = 8;
    
    graph.arcs[1][0] = 3;
    graph.arcs[1][2] = 6;
    graph.arcs[1][3] = 4;
    graph.arcs[1][4] = 11;
    
    graph.arcs[2][0] = 5;
    graph.arcs[2][1] = 6;
    graph.arcs[2][3] = 2;
    
    graph.arcs[3][0] = 8;
    graph.arcs[3][1] = 4;
    graph.arcs[3][2] = 2;
    graph.arcs[3][4] = 10;
    
    graph.arcs[4][1] = 11;
    graph.arcs[4][3] = 10;
    
    return graph;
}

/* 打印邻接矩阵 */
void printMatrix(GraphMatrix* pgraph, const char* title) {
    int i, j;
    printf("%s：\n", title);
    printf("   ");
    for(i = 0; i < pgraph->n; i++) {
        printf("%4d", i);
    }
    printf("\n");
    
    for(i = 0; i < pgraph->n; i++) {
        printf("%2d ", i);
        for(j = 0; j < pgraph->n; j++) {
            if(pgraph->arcs[i][j] == MAX)
                printf("   ∞");
            else
                printf("%4.0f", pgraph->arcs[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* 打印最短路径长度矩阵 */
void printDistanceMatrix(ShortPath* ppath, int n) {
    int i, j;
    printf("最短路径长度矩阵A：\n");
    printf("   ");
    for(i = 0; i < n; i++) {
        printf("%4d", i);
    }
    printf("\n");
    
    for(i = 0; i < n; i++) {
        printf("%2d ", i);
        for(j = 0; j < n; j++) {
            if(ppath->a[i][j] == MAX)
                printf("   ∞");
            else
                printf("%4.0f", ppath->a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* 打印路径后继矩阵 */
void printNextvexMatrix(ShortPath* ppath, int n) {
    int i, j;
    printf("路径后继矩阵nextvex：\n");
    printf("   ");
    for(i = 0; i < n; i++) {
        printf("%4d", i);
    }
    printf("\n");
    
    for(i = 0; i < n; i++) {
        printf("%2d ", i);
        for(j = 0; j < n; j++) {
            if(ppath->nextvex[i][j] == -1)
                printf("   -");
            else
                printf("%4d", ppath->nextvex[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* 根据nextvex矩阵重建并打印路径 */
void printPath(ShortPath* ppath, int i, int j) {
    if(ppath->a[i][j] == MAX) {
        printf("顶点%d到顶点%d：无路径\n", i, j);
        return;
    }
    
    printf("顶点%d到顶点%d：距离%.0f，路径：%d", i, j, ppath->a[i][j], i);
    
    int current = i;
    while(current != j) {
        current = ppath->nextvex[current][j];
        printf(" → %d", current);
    }
    printf("\n");
}

/* 打印所有顶点对的最短路径 */
void printAllPaths(ShortPath* ppath, int n) {
    int i, j;
    printf("所有顶点对的最短路径：\n");
    printf("=========================\n");
    
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if(i != j) {
                printPath(ppath, i, j);
            }
        }
    }
    printf("\n");
}

int main() {
    printf("========== Floyd算法验证 ==========\n\n");
    
    /* 创建图 */
    GraphMatrix graph = createGraph();
    
    /* 打印原图的邻接矩阵 */
    printMatrix(&graph, "原图的邻接矩阵");
    
    /* 执行Floyd算法 */
    ShortPath path;
    floyd(&graph, &path);
    
    /* 打印结果矩阵 */
    printDistanceMatrix(&path, graph.n);
    printNextvexMatrix(&path, graph.n);
    
    /* 打印所有顶点对的最短路径 */
    printAllPaths(&path, graph.n);
    
    printf("========== Floyd算法执行过程解释 ==========\n");
    printf("Floyd算法使用动态规划，通过三重循环更新最短路径：\n");
    printf("for k = 0 to n-1:\n");
    printf("    for i = 0 to n-1:\n");
    printf("        for j = 0 to n-1:\n");
    printf("            if A[i][k] + A[k][j] < A[i][j]:\n");
    printf("                A[i][j] = A[i][k] + A[k][j]\n");
    printf("                nextvex[i][j] = nextvex[i][k]\n\n");
    
    printf("以顶点0到顶点4为例：\n");
    printf("初始：dist[0][4] = ∞\n");
    printf("k=0时：无变化\n");
    printf("k=1时：dist[0][4] = min(∞, dist[0][1]+dist[1][4]) = min(∞, 3+11) = 14\n");
    printf("       nextvex[0][4] = nextvex[0][1] = 1\n");
    printf("k=2时：dist[0][4] = min(14, dist[0][2]+dist[2][4]) = min(14, 5+∞) = 14\n");
    printf("k=3时：dist[0][4] = min(14, dist[0][3]+dist[3][4]) = min(14, 8+10) = 14\n");
    printf("k=4时：dist[0][4] = min(14, dist[0][4]+dist[4][4]) = min(14, 14+0) = 14\n");
    printf("最终：顶点0→4最短路径为0→1→4，距离14\n\n");
    
    printf("重要发现：\n");
    printf("1. 对称性：由于是无向图，A矩阵是对称的（A[i][j] = A[j][i]）\n");
    printf("2. 对角线：A[i][i] = 0（顶点到自身的距离为0）\n");
    printf("3. 不可达：A[4][0] = A[4][2] = ∞（顶点4无法到达顶点0和2）\n");
    
    return 0;
}