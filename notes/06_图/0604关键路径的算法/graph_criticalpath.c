/* 图的关键路径问题的算法*/


#include<stdio.h>
#include<stdlib.h>
#define MAXVEX 100
#define TRUE 1
#define FALSE 0

typedef struct EdgeNode EdgeNode;
typedef struct EdgeNode * PEdgeNode;
typedef struct EdgeNode * EdgeList;
typedef float AdjType;

struct EdgeNode {
    int endvex;			/* 相邻顶点字段 */
    AdjType weight;
    PEdgeNode nextedge;	/* 链字段 */
};						/* 边表中的结点 */

typedef struct {
    /*VexType vertex;*/		/* 顶点信息 */
    EdgeList edgelist;		/* 边表头指针 */
} VexNode;				/* 顶点表中的结点 */

typedef struct {
    int n;				/* 图的顶点个数 */
    VexNode vexs[MAXVEX];
} GraphList;


typedef struct {
    /*VexType vexs[MAXVEX];*/	/* 顶点信息 */	
    int vexsno[MAXVEX];		/* 顶点在顶点表中的下标值 */
} Topo;


/* 求出图中所有顶点的入度 */
/* 方法是搜索整个邻接表 */
void findInDegree(GraphList* g, int *inDegree) {
    int i; 
    PEdgeNode p;        

    for (i = 0; i < g->n; i++)
        inDegree[i] = 0;

    for (i = 0; i < g->n; i++) {
        p = g->vexs[i].edgelist;
        while(p) {
            inDegree[p->endvex]++; 
            p = p->nextedge; 
        }
    }
}

void makeNewAOV(EdgeList p, int* indegree, int* top) {
    int k;

    while (p) {                       /* 删除以该顶点为起点的边 */
        k = p->endvex; 
        indegree[k]--;
        if (indegree[k] == 0) {         /* 将新的入度为零的边入栈 */
            indegree[k] = *top;
            *top = k; 
        }
        p = p->nextedge;
    }
}

/* 拓扑排序算法*/
int topoSort(GraphList * paov, Topo * ptopo) {
    EdgeList p;
    int i, j, nodeno = 0, top = -1;
    int indegree[MAXVEX];

    findInDegree(paov, indegree);    /* 求出图中所有顶点的入度 */
    for (i = 0; i < paov->n; i++)
        if (indegree[i] == 0) {        /* 将入度为零的顶点入栈 */ 
            indegree[i] = top; top = i;
        }

    while (top != -1) {                /* 栈不为空 */
        j = top;
        top = indegree[top];               /* 取出当前栈顶元素 */
        /*ptopo->vexs[nodeno]=paov->vexs[j].vertex;*/ /* 将该元素输出到拓扑序列中 */
        ptopo->vexsno[nodeno++] = j;
        p = paov->vexs[j].edgelist;    /* 取该元素边表中的第一个边结点 */
        /*删除该结点,构造新的AOV网*/
        /*对indegree数组进行修改*/
        makeNewAOV(p, indegree, &top);
    }

    if (nodeno < paov->n) {       /* AOV网中存在回路 */
        printf("The aov network has a cycle\n");
        return FALSE;
    }
    
    return TRUE;
}

void insert(GraphList* p,int a,int b,float weight){
    EdgeList pp;
    PEdgeNode temp;
    temp = (PEdgeNode)malloc(sizeof(EdgeNode));
    temp->endvex = b;
    temp->nextedge = NULL;
    temp->weight = weight;
    pp = p->vexs[a].edgelist;
    if (pp == NULL)
        p->vexs[a].edgelist = temp;
    else {
        while (pp->nextedge != NULL)
            pp = pp->nextedge;
        pp->nextedge = temp;
    }
}
	
/* 邻接表的构造*/
GraphList* makeList(){
    GraphList* p;
    int i;
    p = (GraphList*)malloc(sizeof(GraphList));
    p->n = 9;
    for (i = 0; i < p->n; i++)
        p->vexs[i].edgelist = NULL;
    insert(p,0,1,6);
    insert(p,0,2,4);
    insert(p,0,3,5);
    insert(p,1,4,1);
    insert(p,2,4,1);
    insert(p,3,5,2);
    insert(p,4,6,9);
    insert(p,4,7,7);
    insert(p,5,7,4);
    insert(p,6,8,2);
    insert(p,7,8,4);
    return p;
}

int CriticalPath(GraphList * paoe);

/* 主程序*/
int main(){
    GraphList* p;
    /*int i;*/
    p = makeList();
    /*if(topoSort(p,&topo)==TRUE)
        for(i=0;i<p->n;i++)
            printf("%d ",topo.vexsno[i]);*/
    if (CriticalPath(p) == FALSE)
        printf("There is no critical path!\n");
    return 0;
}


/*******************************************/
#define MAXEDGE 100 

/* 计算数组ee*/
void countee(GraphList* paoe,Topo* ptopo, AdjType* ee) {
    int i, j, k;
    EdgeList p;

    for (i = 0; i < paoe->n; i++) ee[i] = 0;
    for (k = 0; k < paoe->n; k++) {       /* 求事件vj可能的最早发生时间ee(j) */
        i = ptopo->vexsno[k];
        p = paoe->vexs[i].edgelist;
        while (p != NULL) {
            j = p->endvex;
            if (ee[i] + p->weight > ee[j])
                ee[j] = ee[i] + p->weight;
            p = p->nextedge;
        }
    }
}


/* 计算数组le*/
void countle(GraphList * paoe,Topo* ptopo, AdjType* ee, AdjType* le) {
    int i, j, k;
    EdgeList p;
    for (i = 0; i < paoe->n; i++)         /* 求事件vi允许的最迟发生时间le(i) */
        le[i] = ee[paoe->n - 1];
    for (k = paoe->n - 2; k >= 0; k--) {
        i = ptopo->vexsno[k];
        p = paoe->vexs[i].edgelist;
        while (p != NULL) {
            j = p->endvex;
            if( le[j] - p->weight < le[i] )
                le[i] = le[j] - p->weight;
            p = p->nextedge;
        }
    }
}

/* 计算数组e,l并输出结果*/
void counte_l(GraphList * paoe,Topo* ptopo, AdjType* ee,
                AdjType* le, AdjType* e, AdjType* l) {
    int i, j, k = 0;
    EdgeList p;
    /* 求活动ak的最早开始时间e(k)及最晚开始时间l(k) */
    for (i = 0; i < paoe->n; i++) {
        p = paoe->vexs[i].edgelist;
        while (p != NULL) {
            j = p->endvex;
            e[k] = ee[i];
            l[k] = le[j] - p->weight;
            if (e[k] == l[k])
                printf("<v%2d, v%2d>, ", i, j);
            k++;
            p = p->nextedge;
        }
    }
}

/* 关键路径算法*/
int CriticalPath(GraphList * paoe) {
    AdjType ee[MAXVEX], le[MAXVEX], l[MAXEDGE], e[MAXEDGE];
    Topo topo;
    if (topoSort(paoe, &topo) == FALSE)               /* 求AOE网的一个拓扑序列 */
        return FALSE;
    countee(paoe, &topo, ee); /*计算数组ee*/
    countle(paoe, &topo, ee, le);/*计算数组le*/
    counte_l(paoe, &topo, ee, le, e, l);/*计算数组e,l并输出结果*/
    printf("\n");
    return TRUE;
}
