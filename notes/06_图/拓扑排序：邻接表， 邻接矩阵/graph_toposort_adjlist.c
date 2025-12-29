/* 用邻接表表示图的拓扑排序算法*/


#include<stdio.h>
#include<stdlib.h>
#define MAXVEX 100
#define TRUE 1
#define FALSE 0

typedef struct EdgeNode EdgeNode;
typedef struct EdgeNode * PEdgeNode;
typedef struct EdgeNode * EdgeList;

struct EdgeNode {
    int endvex;			/* 相邻顶点字段 */
    PEdgeNode nextedge;	/* 链字段 */
};					/* 边表中的结点 */

typedef struct {
    /*VexType vertex;*/		/* 顶点信息 */
    EdgeList edgelist;		/* 边表头指针 */
} VexNode;				/* 顶点表中的结点 */

typedef struct{
    int n;				/* 图的顶点个数 */
    VexNode vexs[MAXVEX];
} GraphList;

typedef struct {
    int vexsno[MAXVEX];		/* 顶点在顶点表中的下标值 */
    /*VexType vexs[MAXVEX];*/	/* 顶点信息 */	
} Topo;

/* 求出图中所有顶点的入度 */
/* 方法是搜索整个邻接表 */
void findInDegree(GraphList* g, int *inDegree){
    int i; PEdgeNode p;        
    for (i = 0; i < g->n; i++)
        inDegree[i] = 0;
    for (i = 0; i < g->n; i++){
        p = g->vexs[i].edgelist;
        while (p) {
            ++inDegree[p->endvex];
            p = p->nextedge;
        }
    }
}

void makeNewAOV(EdgeList p, int* indegree, int* top) {
    int k;
    while (p) {                        /* 删除以该顶点为起点的边 */
        k = p->endvex; 
        indegree[k]--;
        if (indegree[k] == 0) {        /* 将新的入度为零的边入栈 */
            indegree[k] = *top;
            *top = k; 
        }
        p = p->nextedge;
    }
}

int topoSort(GraphList * paov, Topo * ptopo) {
    EdgeList p;
    int i, j, nodeno = 0, top = -1;
    int indegree[MAXVEX];
    findInDegree(paov, indegree); /* 求出图中所有顶点的入度 */
    for (i = 0; i < paov->n; i++)
        if (indegree[i] == 0) {         /* 将入度为零的顶点入栈 */ 
            indegree[i] = top; top = i; 
        }
        while (top != -1) {                           /* 栈不为空 */
            j = top;
            top = indegree[top];               /* 取出当前栈顶元素 */
            /*ptopo->vexs[nodeno]=paov->vexs[j].vertex;*/ /* 将该元素输出到拓扑序列中 */
            ptopo->vexsno[nodeno++] = j;
            p = paov->vexs[j].edgelist;    /* 取该元素边表中的第一个边结点 */
            /*删除该结点,构造新的AOV网*/
            /*对indegree数组进行修改*/
            makeNewAOV(p, indegree, &top);
        }
        if (nodeno < paov->n) {      /* AOV网中存在回路 */
            printf("The aov network has a cycle\n");
            return FALSE;
        }
    return TRUE;
}

/* 边的插入算法*/
void insert(GraphList* p,int a,int b){
    EdgeList pp;
    PEdgeNode temp;
    temp = (PEdgeNode)malloc(sizeof(EdgeNode));
    temp->endvex = b;
    temp->nextedge = NULL;
    pp = p->vexs[a].edgelist;
    if (pp == NULL) p->vexs[a].edgelist = temp;
    else {
        while (pp->nextedge != NULL)
            pp = pp->nextedge;
        pp->nextedge = temp;
    }
}
	
/* 实例邻接表的构造 */
GraphList* makeList(){
    GraphList* p;
    int i;
    p = (GraphList*)malloc(sizeof(GraphList));
    p->n = 9;
    for (i = 0; i < p->n; i++)
        p->vexs[i].edgelist = NULL;
    insert(p, 0, 2);
    insert(p, 0, 7);
    insert(p, 1, 2);
    insert(p, 1, 3);
    insert(p, 1, 4);
    insert(p, 2, 3);
    insert(p, 3, 5);
    insert(p, 3, 6);
    insert(p, 4, 5);
    insert(p, 7, 8);
    insert(p, 8, 6);
    return p;
}

Topo topo;

int main(){
    GraphList* p;
    int i;
    p = makeList();
    if (topoSort(p, &topo) == TRUE)
        for (i = 0; i < p->n; i++)
            printf("%d ", topo.vexsno[i]);
    return 0;
}
