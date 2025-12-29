/* 用邻接矩阵表示图的拓扑排序算法*/


#include<stdio.h>
#include<stdlib.h>
#define MAXVEX 100
#define TRUE 1
#define FALSE 0
					
typedef char VexType;
typedef int AdjType;
typedef struct {
    int n;								/* 图的顶点个数 */
    /*VexType vexs[MAXVEX];*/				/* 顶点信息 */
    AdjType arcs[MAXVEX][MAXVEX];		/* 边信息 */
} GraphMatrix;

typedef struct {
    /*VexType vexs[MAXVEX];*/	/* 顶点信息 */	
    int vexsno[MAXVEX];		/* 顶点在顶点表中的下标值 */
} Topo;

/* 求出图中所有顶点的入度 */
/* 方法是搜索整个邻接表 */
void findInDegree(GraphMatrix* g, int *inDegree) {
    int i, j;       
    for (i = 0; i < g->n; i++) {
        inDegree[i] = 0;
        for (j = 0; j < g->n; j++)
            if (g->arcs[j][i]) ++inDegree[i];
    }
}

void makeNewAOV(GraphMatrix* g, int p, int* indegree, int* top) {
    int k;
    for (k = 0; k < g->n; k++)/* 删除以该顶点为起点的边 */
        if (g->arcs[p][k]) {
            indegree[k]--;
            if (indegree[k] == 0) {         /* 将新的入度为零的边入栈 */
                indegree[k] = *top;
                *top = k; 
            }
        }
}

int topoSort(GraphMatrix * paov, Topo * ptopo) {
    int i, j, nodeno = 0, top = -1;
    int indegree[MAXVEX];

    findInDegree(paov, indegree); /* 求出图中所有顶点的入度 */

    for (i = 0; i < paov->n; i++)
        if (indegree[i] == 0) {          /* 将入度为零的顶点入栈 */ 
            indegree[i] = top; top = i;
        }

    while (top != -1) {                           /* 栈不为空 */
        j = top;
        top = indegree[top];               /* 取出当前栈顶元素 */
        /*ptopo->vexs[nodeno] = paov->vexs[j];*/ /* 将该元素输出到拓扑序列中 */
        ptopo->vexsno[nodeno++] = j;
        /* 取该元素边表中的第一个边结点 */
        /* 删除该结点,构造新的AOV网 */
        /* 对indegree数组进行修改 */
        makeNewAOV(paov, j, indegree, &top);
    }
    if (nodeno < paov->n) {        /* AOV网中存在回路 */
        printf("The aov network has a cycle\n");
        return FALSE;
    }
    return TRUE;
}

/* 构造邻接矩阵*/
GraphMatrix* makeMatrix(){
    GraphMatrix* p;
    int i,j;
    p = (GraphMatrix*)malloc(sizeof(GraphMatrix));
    p->n = 9;
    for (i = 0; i < p->n; i++)
        for (j = 0; j < p->n; j++)
            p->arcs[i][j] = 0;
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

Topo topo;

int main(){
    int i;
    GraphMatrix* p;
    p = makeMatrix();
    if (topoSort(p, &topo) == TRUE)
        for (i = 0; i < p->n; i++)
            printf("%d ", topo.vexsno[i]);
    return 0;
}
