/* Dijkstra算法求最短路径 */

#include<stdio.h>
#define MAXVEX 5
#define MAX 1e+8

typedef int VexType;
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

Path dist[MAXVEX];        /* 存储从源点到各顶点的最短路径信息 */

/* 初始化函数 */
void init(GraphMatrix* pgraph, Path dist[]) {
    int i; 
    
    /* 初始化源点（顶点0） */
    dist[0].length = 0;
    dist[0].prevex = 0;      
    dist[0].vertex = pgraph->vexs[0];
    
    /* 标记源点已在集合U中 */
    pgraph->arcs[0][0] = 1;  /* 使用-1表示顶点在集合U中 */

    /* 初始化其他顶点到源点的距离 */
    for(i = 1; i < pgraph->n; i++) {
        dist[i].length = pgraph->arcs[0][i];
        dist[i].vertex = pgraph->vexs[i];
        if (dist[i].length != MAX)
            dist[i].prevex = 0;    /* 前驱为源点 */
        else  
            dist[i].prevex = -1;   /* 不可达 */
    }
}

/* Dijkstra算法主函数 */
void dijkstra(GraphMatrix graph, Path dist[]) {
    int i, j, minvex;
    AdjType min;
    
    init(&graph, dist); /* 初始化，此时集合U中只有顶点v0 */
    
    for(i = 1; i < graph.n; i++) {  /* 需要找到n-1个顶点的最短路径 */
        min = MAX; 
        minvex = 0;
        
        /* 在集合V-U中选出距离值最小的顶点 */
        for(j = 1; j < graph.n; j++) {
            if(graph.arcs[j][j] == 0 && dist[j].length < min) {
                min = dist[j].length;  
                minvex = j;  
            }
        }

        if(minvex == 0) break;  /* 没有可达顶点 */
        
        /* 将minvex加入集合U */
        graph.arcs[minvex][minvex] = 1;
        
        /* 调整集合V-U中的顶点的最短路径 */
        for(j = 1; j < graph.n; j++) {
            if(graph.arcs[j][j] == 1) continue;  /* 跳过已在U中的顶点 */
            
            if(dist[j].length > dist[minvex].length + graph.arcs[minvex][j]) {
                dist[j].length = dist[minvex].length + graph.arcs[minvex][j];
                dist[j].prevex = minvex;
            }
        }
    }
}

/* 创建题目给定的图 */
GraphMatrix initgraph() {
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
    graph.arcs[0][1] = 3;   graph.arcs[1][0] = 3;
    graph.arcs[0][2] = 5;   graph.arcs[2][0] = 5;
    graph.arcs[0][3] = 8;   graph.arcs[3][0] = 8;
    
    graph.arcs[1][2] = 6;   graph.arcs[2][1] = 6;
    graph.arcs[1][3] = 4;   graph.arcs[3][1] = 4;
    graph.arcs[1][4] = 11;  graph.arcs[4][1] = 11;
    
    graph.arcs[2][3] = 2;   graph.arcs[3][2] = 2;
    
    graph.arcs[3][4] = 10;  graph.arcs[4][3] = 10;
    
    return graph;
}

/* 打印邻接矩阵 */
void printGraph(GraphMatrix* pgraph) {
    int i, j;
    printf("图的邻接矩阵（MAX表示∞）：\n");
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

/* 打印最短路径结果 */
void printShortestPaths(Path dist[], int n, int source) {
    int i, j;
    int path[MAXVEX];
    
    printf("从顶点 %d 到各顶点的最短路径：\n", source);
    printf("顶点\t距离\t路径\n");
    printf("----------------------------\n");
    
    for(i = 0; i < n; i++) {
        if(i == source) continue;
        
        printf("%d → %d\t%.0f\t", source, i, dist[i].length);
        
        /* 回溯构建路径 */
        j = i;
        int count = 0;
        while(j != source) {
            path[count++] = j;
            j = dist[j].prevex;
        }
        path[count] = source;
        
        /* 打印路径 */
        for(j = count; j > 0; j--) {
            printf("%d → ", path[j]);
        }
        printf("%d\n", path[0]);
    }
}

/* 打印算法执行过程 */
void printProcess(GraphMatrix* graph, Path dist[], int iteration) {
    printf("\n第%d次迭代后：\n", iteration);
    printf("顶点\t距离\t前驱\t状态\n");
    for(int i = 0; i < graph->n; i++) {
        printf("%d\t", i);
        if(dist[i].length == MAX)
            printf("∞\t");
        else
            printf("%.0f\t", dist[i].length);
        
        if(dist[i].prevex == -1)
            printf("-\t");
        else
            printf("%d\t", dist[i].prevex);
        
        if(i == 0 || graph->arcs[i][i] == -1)
            printf("U（已确定）\n");
        else
            printf("V-U（未确定）\n");
    }
}

int main() {
    printf("========== Dijkstra算法验证 ==========\n\n");
    
    /* 创建图 */
    GraphMatrix graph = initgraph();
    
    /* 打印原图 */
    printGraph(&graph);
    
    printf("执行Dijkstra算法（源点为顶点0）...\n\n");
    
    /* 执行Dijkstra算法 */
    dijkstra(graph, dist);
    
    /* 打印最终结果 */
    printf("最终结果（格式：顶点[距离,前驱]）：\n");
    for(int i = 0; i < graph.n; i++) {
        printf("顶点%d: [", i);
        if(dist[i].length == MAX)
            printf("∞, ");
        else
            printf("%.0f, ", dist[i].length);
        
        if(dist[i].prevex == -1)
            printf("-]\n");
        else
            printf("%d]\n", dist[i].prevex);
    }
    printf("\n");
    
    /* 打印详细的最短路径 */
    printShortestPaths(dist, graph.n, 0);
    
    printf("\n========== 算法执行过程解释 ==========\n");
    printf("Dijkstra算法步骤（从顶点0开始）：\n");
    printf("1. 初始化：\n");
    printf("   - dist[0]=[0,0], dist[1]=[3,0], dist[2]=[5,0]\n");
    printf("   - dist[3]=[8,0], dist[4]=[∞,-1]\n");
    printf("   - 集合U={0}, V-U={1,2,3,4}\n\n");
    
    printf("2. 第1轮：\n");
    printf("   - 在V-U中选最小dist[1]=3，将顶点1加入U\n");
    printf("   - 通过顶点1更新：\n");
    printf("     dist[3]=min(8, 3+4=7) → 更新为7（前驱1）\n");
    printf("     dist[4]=min(∞, 3+11=14) → 更新为14（前驱1）\n\n");
    
    printf("3. 第2轮：\n");
    printf("   - 当前：dist[2]=5, dist[3]=7, dist[4]=14\n");
    printf("   - 选最小dist[2]=5，将顶点2加入U\n");
    printf("   - 通过顶点2更新：\n");
    printf("     dist[3]=min(7, 5+2=7) → 保持7\n");
    printf("     dist[4]=min(14, 5+∞=∞) → 保持14\n\n");
    
    printf("4. 第3轮：\n");
    printf("   - 当前：dist[3]=7, dist[4]=14\n");
    printf("   - 选最小dist[3]=7，将顶点3加入U\n");
    printf("   - 通过顶点3更新：\n");
    printf("     dist[4]=min(14, 7+10=17) → 保持14\n\n");
    
    printf("5. 第4轮：\n");
    printf("   - 当前：dist[4]=14\n");
    printf("   - 选最小dist[4]=14，将顶点4加入U\n");
    printf("   - 算法结束\n");
    
    return 0;
}