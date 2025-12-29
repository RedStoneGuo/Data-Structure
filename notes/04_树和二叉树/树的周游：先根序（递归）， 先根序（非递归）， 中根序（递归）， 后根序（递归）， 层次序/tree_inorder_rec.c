/* 树的中根周游的递归算法*/

#include<stdio.h>

#define  MAXNUM 20
#define null -1

/* typedef int DataType; */
struct  ParTreeNode	{
    /*DataType  info;		 结点中的元素 */
    int parent;	/* 结点的父结点位置 */
};

struct ParTree { 
    int n;                 	/* 树中结点的个数 */
    struct ParTreeNode nodelist[MAXNUM];  	/* 存放树中的结点 */
};

typedef struct ParTree *PParTree;		/* 树类型的指针类型 */

int rightSibling_partree(PParTree t, int p) {
    int i;
    if (p >= 0 && p < t->n) {
        for (i = p+1; i <= t->n; i++)
            if (t->nodelist[i].parent == t->nodelist[p].parent)
                return(i);
    }
    return null;
}

/* 依先根序列存储时,求最左子结点的运算可简化如下*/
int leftChild_partree(PParTree t, int p) { 
    if (t->nodelist[p+1].parent == p)
        return(p+1);
    else
        return null;
}

typedef int Node;

void visit(Node p) { printf("%d ",p); }

void inOrder( PParTree t, Node p ) {
    Node c;  
    c = leftChild_partree ( t, p );
    if (c == null) visit( p );
    else {
        inOrder(t, c);
        visit( p );
        c = rightSibling_partree (t, c );
        while (c != null) {
            inOrder ( t, c );
            c = rightSibling_partree (t, c );
        }
    }
}

struct  ParTree tree = {10, -1,0,1,1,3,3,3,0,7,7};

int main(){
    inOrder(&tree, 0);
    putchar('\n');
    return 0;
}

