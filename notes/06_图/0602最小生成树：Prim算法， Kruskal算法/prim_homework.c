/* Prim算法求最小生成树 */
#include<stdio.h>
#define MAXVEX 5
#define MAX 1e+8  /* 表示∞ */

typedef char VexType;
typedef float AdjType;

typedef struct {
    int n;                          /* 图的顶点个数 */
    AdjType arcs[MAXVEX][MAXVEX];   /* 边信息 */
} GraphMatrix;

typedef struct {
    int start_vex, stop_vex;        /* 边的起点和终点 */
    AdjType weight;                 /* 边的权 */
} Edge;

Edge mst[4];  /* 最小生成树有n-1=4条边 */

void prim(GraphMatrix * pgraph, Edge mst[]) {
    int i, j, min, vx, vy;
    float weight, minweight;
    Edge edge;

    /* 初始化：从顶点0开始，生成初始边集合 */
    for (i = 0; i < pgraph->n-1; i++) {
        mst[i].start_vex = 0;              /* 起点为顶点0 */
        mst[i].stop_vex = i+1;            /* 终点为其他顶点 */
        mst[i].weight = pgraph->arcs[0][i+1];  /* 权值为边(0,i+1)的权重 */
    }

    /* 循环n-1次，每次选择一条最短边加入生成树 */
    for (i = 0; i < pgraph->n-1; i++) {
        /* 步骤1：从候选边中选择权值最小的边 */
        minweight = MAX;
        min = i;
        for (j = i; j < pgraph->n-1; j++) {
            if (mst[j].weight < minweight) {
                minweight = mst[j].weight;
                min = j;
            }
        }

        /* 步骤2：将选中的边交换到mst[i]位置 */
        edge = mst[min];
        mst[min] = mst[i];
        mst[i] = edge;
        
        vx = mst[i].stop_vex;  /* vx是新加入生成树的顶点 */

        /* 步骤3：更新候选边集合 */
        for (j = i+1; j < pgraph->n-1; j++) {
            vy = mst[j].stop_vex;
            weight = pgraph->arcs[vx][vy];
            if (weight < mst[j].weight) {
                mst[j].weight = weight;
                mst[j].start_vex = vx;
            }
        }
    }
}

/* 给定的图：5个顶点，邻接矩阵如下 */
/* 
    0   1   2   3   4
0   0   3   5   8   ∞
1   3   0   6   4   11
2   5   6   0   2   ∞
3   8   4   2   0   10
4   ∞   11  ∞   10  0
*/
GraphMatrix graph = {
    5,
    {
        {0,   3,   5,   8,   MAX},  // 顶点0的边
        {3,   0,   6,   4,   11},   // 顶点1的边  
        {5,   6,   0,   2,   MAX},  // 顶点2的边
        {8,   4,   2,   0,   10},   // 顶点3的边
        {MAX, 11, MAX, 10,    0}    // 顶点4的边
    }
};

/* 打印邻接矩阵 */
void printGraph(GraphMatrix *pgraph) {
    int i, j;
    printf("图的邻接矩阵（∞表示MAX）：\n");
    printf("   ");
    for (i = 0; i < pgraph->n; i++) {
        printf("%4d", i);
    }
    printf("\n");
    
    for (i = 0; i < pgraph->n; i++) {
        printf("%2d ", i);
        for (j = 0; j < pgraph->n; j++) {
            if (pgraph->arcs[i][j] == MAX)
                printf(" MAX");
            else
                printf("%4.0f", pgraph->arcs[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int i;
    float total_weight = 0;
    
    printf("========== Prim算法求最小生成树 ==========\n\n");
    
    // 打印原图
    printGraph(&graph);
    
    // 执行Prim算法
    prim(&graph, mst);
    
    // 输出最小生成树的边
    printf("最小生成树的边（起点 终点 权值）：\n");
    for (i = 0; i < graph.n-1; i++) {
        printf("边 %d: (%d, %d, %.0f)\n", 
               i+1, mst[i].start_vex, mst[i].stop_vex, mst[i].weight);
        total_weight += mst[i].weight;
    }
    
    printf("\n最小生成树的总权值: %.0f\n", total_weight);
    printf("\n========== 算法执行过程解释 ==========\n");
    printf("Prim算法步骤：\n");
    printf("1. 从顶点0开始，初始化候选边集合：\n");
    printf("   - (0,1)=3, (0,2)=5, (0,3)=8, (0,4)=∞\n");
    printf("2. 选择最小边(0,1)=3加入生成树\n");
    printf("3. 加入顶点1后更新候选边：\n");
    printf("   - 检查顶点1到其他顶点的边：\n");
    printf("   - (1,2)=6 > 原来的(0,2)=5，不更新\n");
    printf("   - (1,3)=4 < 原来的(0,3)=8，更新为(1,3)=4\n");
    printf("   - (1,4)=11 < 原来的(0,4)=∞，更新为(1,4)=11\n");
    printf("4. 继续选择最小边，直到得到n-1条边\n");
    
    return 0;
}