/* 用邻接矩阵表示的图的Kruskal算法的源程序*/

#include<stdio.h>
#include<stdlib.h>
#define MAXVEX 5
enum {FALSE, TRUE};

typedef char VexType;
typedef float AdjType;

typedef struct {
    int n;                                           /* 图的顶点个数 */
    AdjType arcs[MAXVEX][MAXVEX];           /* 边信息 */
} GraphMatrix;

typedef struct {
    int start_vex, stop_vex;              /* 边的起点和终点 */
    AdjType weight;                  /* 边的权 */
} Edge;

Edge mst[4];  /* 最小生成树有n-1=4条边 */

#define MAX 1e+8

/* Kruskal算法求最小生成树 */
int kruskal(GraphMatrix graph, Edge mst[]) {   
    int i, j, num = 0, start, stop;
    float minweight;
    
    /* 创建并查集数组，每个顶点初始时自成一个集合 */
    int* status = (int *)malloc(sizeof(int) * graph.n);
    for (i = 0; i < graph.n; i++)
        status[i] = i;
    
    /* 当生成树边数小于n-1时继续 */
    while (num < graph.n - 1) {
        minweight = MAX;
        
        /* 在所有边中找到权值最小的边 */
        for (i = 0; i < graph.n-1; i++)
            for (j = i+1; j < graph.n; j++)
                if (graph.arcs[i][j] < minweight) {
                    start = i; 
                    stop = j;
                    minweight = graph.arcs[i][j];
                }
        
        /* 如果没有找到有效边，说明无法生成最小生成树 */
        if (minweight == MAX) {
            free(status);
            return FALSE;  /* 不能得到最小生成树*/
        }
        
        /* 如果start和stop不在同一个集合中（即加入此边不会形成环） */
        if (status[start] != status[stop]) {
            mst[num].start_vex = start;
            mst[num].stop_vex = stop;
            mst[num].weight = graph.arcs[start][stop];
            num++;
            
            /* 合并两个集合：将stop所在的集合合并到start所在的集合 */
            j = status[stop];
            for (i = 0; i < graph.n; i++)	
                if (status[i] == j)
                    status[i] = status[start];
        }
        
        /* "删除"已处理的边（设为极大值，避免再次选中） */
        graph.arcs[start][stop] = MAX;
    }		
    
    free(status);
    return TRUE;  /* 能得到最小生成树*/
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
        {MAX, 11, MAX, 10,  0}      // 顶点4的边
    }
};

/* 打印邻接矩阵 */
void printGraph(GraphMatrix *pgraph) {
    int i, j;
    printf("图的邻接矩阵（MAX表示∞）：\n");
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

/* 按权值排序边 */
void sortEdges(Edge edges[], int count) {
    int i, j;
    Edge temp;
    for (i = 0; i < count-1; i++) {
        for (j = 0; j < count-i-1; j++) {
            if (edges[j].weight > edges[j+1].weight) {
                temp = edges[j];
                edges[j] = edges[j+1];
                edges[j+1] = temp;
            }
        }
    }
}

int main() {
    int i;
    float total_weight = 0;
    
    printf("========== Kruskal算法求最小生成树 ==========\n\n");
    
    // 打印原图
    printGraph(&graph);
    
    // 执行Kruskal算法
    if (kruskal(graph, mst) == TRUE) {
        // 对生成树的边按权值排序（方便查看）
        sortEdges(mst, graph.n-1);
        
        // 输出最小生成树的边
        printf("最小生成树的边（按权值排序）：\n");
        for (i = 0; i < graph.n-1; i++) {
            printf("边 %d: (%d, %d, %.0f)\n", 
                   i+1, mst[i].start_vex, mst[i].stop_vex, mst[i].weight);
            total_weight += mst[i].weight;
        }
        
        printf("\n最小生成树的总权值: %.0f\n", total_weight);
        
        printf("\n========== Kruskal算法执行过程解释 ==========\n");
        printf("Kruskal算法步骤：\n");
        printf("1. 将图中所有边按权值从小到大排序\n");
        printf("2. 初始化：每个顶点自成一个集合\n");
        printf("3. 从最小权值边开始，依次考虑每条边：\n");
        printf("   a. 如果边的两个顶点不在同一集合，则加入生成树并合并集合\n");
        printf("   b. 如果边的两个顶点在同一集合，则跳过（避免形成环）\n");
        printf("4. 重复步骤3，直到生成树包含n-1条边\n\n");
        
        printf("边处理顺序（原顺序）：\n");
        printf("1. 边(2,3)=2 （权值最小）\n");
        printf("2. 边(0,1)=3\n");
        printf("3. 边(1,3)=4\n");
        printf("4. 边(0,2)=5\n");
        printf("5. 边(1,2)=6\n");
        printf("6. 边(0,3)=8\n");
        printf("7. 边(3,4)=10\n");
        printf("8. 边(1,4)=11\n");
        printf("... 其他边\n\n");
        
        printf("算法执行过程：\n");
        printf("1. 选择边(2,3)=2，顶点2和3不在同一集合，加入生成树\n");
        printf("   集合状态：{0},{1},{2,3},{4}\n");
        printf("2. 选择边(0,1)=3，顶点0和1不在同一集合，加入生成树\n");
        printf("   集合状态：{0,1},{2,3},{4}\n");
        printf("3. 选择边(1,3)=4，顶点1在集合{0,1}，顶点3在集合{2,3}\n");
        printf("   不在同一集合，加入生成树，合并集合{0,1}和{2,3}\n");
        printf("   集合状态：{0,1,2,3},{4}\n");
        printf("4. 选择边(0,2)=5，顶点0和2都在集合{0,1,2,3}\n");
        printf("   在同一集合，跳过（会形成环）\n");
        printf("5. 选择边(1,2)=6，顶点1和2都在集合{0,1,2,3}\n");
        printf("   在同一集合，跳过（会形成环）\n");
        printf("6. 选择边(0,3)=8，顶点0和3都在集合{0,1,2,3}\n");
        printf("   在同一集合，跳过（会形成环）\n");
        printf("7. 选择边(3,4)=10，顶点3在集合{0,1,2,3}，顶点4在集合{4}\n");
        printf("   不在同一集合，加入生成树，合并集合{0,1,2,3}和{4}\n");
        printf("   集合状态：{0,1,2,3,4} （已完成）\n");
    } else {
        printf("无法生成最小生成树！\n");
    }
    
    return 0;
}