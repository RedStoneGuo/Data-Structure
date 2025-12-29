/* 树的子表表示法*/

#include<stdio.h>
#define MAXNUM 20

typedef int DataType ;

struct EdgeNode {   	/* 子表中结点的结构 */
    int             nodeposition;
    struct EdgeNode *link;
};

struct ChiTreeNode {   /* 结点表中结点的结构 */
    DataType        info;
    struct EdgeNode *children;
};

struct ChiTree {   		/* 树结构 */
    int                n; 		/* 结点个数 */
    int                root;	/* 根结点的下标 */
    struct ChiTreeNode nodelist[MAXNUM];
};

typedef struct ChiTree *PChiTree;		/* 树类型的指针类型 */

int rightSibling_chitree(PChiTree t, int p) {
    int i;
    struct EdgeNode  *v;
    for (i = 0; i < t->n; i++) {
        v = t->nodelist[i].children;
        while (v != NULL)
            if (v->nodeposition == p)
                if (v->link == NULL)
                    return -1;
                else
                    return(v->link->nodeposition);
            else
                v = v->link;
    }
    return -1;
}

int parent_chitree(PChiTree t, int p) {
    int i;
    struct EdgeNode *v;
    for (i = 0; i < t->n; i++) {    /* 逐个检查树的各个结点，是不是父结点 */
        v = t->nodelist[i].children;/* 若检查的结点子表中有p，则返回值是该结点的位置 */
        while (v!=NULL)
            if (v->nodeposition == p)
                return(i);
            else
                v = v->link;
    }
    return -1;  /* 无父结点，则返回值为-1 */
}

int main() {
    return 0;
}
