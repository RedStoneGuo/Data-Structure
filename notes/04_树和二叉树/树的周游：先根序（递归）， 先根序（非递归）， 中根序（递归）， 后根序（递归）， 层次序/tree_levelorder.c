/* 树的广度优先周游算法*/

#include<stdio.h>
#include<stdlib.h>

#define MAXNUM 20
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

/*队列顺序表示*/
typedef Node DataType;
struct SeqQueue {	/* 顺序队列类型定义 */
    int f, r;
    DataType q[MAXNUM];
};

typedef struct SeqQueue *PSeqQueue;	/* 顺序队列类型的指针类型 */

/*创建一个空队列*/
PSeqQueue  createEmptyQueue_seq( void ) {  
    PSeqQueue paqu;
    paqu = (PSeqQueue)malloc(sizeof(struct SeqQueue));
    if (paqu == NULL)
        printf("Out of space!! \n");
    else
        paqu->f = paqu->r = 0;
	return paqu;
}

/*判队列是否为空队列*/
int  isEmptyQueue_seq( PSeqQueue paqu ) {
    return (paqu->f == paqu->r);
}

/* 在队列中插入一元素x */
void  enQueue_seq( PSeqQueue paqu, DataType x ) {
    if( (paqu->r + 1) % MAXNUM == paqu->f  )
        printf( "Full queue.\n" );
    else {
        paqu->q[paqu->r] = x;
        paqu->r = (paqu->r + 1) % MAXNUM;
    }
}

/* 删除队列头部元素 */
void  deQueue_seq( PSeqQueue paqu ) {
    if( paqu->f == paqu->r )
        printf( "Empty Queue.\n" );
    else
        paqu->f = (paqu->f + 1) % MAXNUM;
}

/* 对非空队列,求队列头部元素 */
DataType  frontQueue_seq( PSeqQueue paqu ) {
    return paqu->q[paqu->f];
}

void levelOrder(PParTree t) {
    Node c;
    PSeqQueue q;	/* 队列元素的类型为 Node */
    q = createEmptyQueue_seq();
    
    c = 0; /*c = root(t);*/
    if (c == null)  return;
    enQueue_seq(q,c);
    while (!isEmptyQueue_seq(q)) {
        c = frontQueue_seq(q);
        deQueue_seq(q);
        visit(c);
        c = leftChild_partree(t, c);
        while (c!=null) {
            enQueue_seq(q,c);
            c = rightSibling_partree(t, c);
        }
    }
}

struct ParTree tree = {10, -1,0,1,1,3,3,3,0,7,7};

int main(){
    PParTree t = &tree;
    levelOrder(t);
    putchar('\n');
    return 0;
}

