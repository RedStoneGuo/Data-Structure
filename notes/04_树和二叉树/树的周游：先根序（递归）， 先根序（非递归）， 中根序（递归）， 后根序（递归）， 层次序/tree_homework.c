/* 树的周游的递归算法*/

#include<stdio.h>
#include<stdlib.h>

#define  MAXNUM 20
#define null -1

typedef char DataType;  // 修改为char型

struct  ParTreeNode {
    DataType  info;     // 结点中的元素
    int parent;         /* 结点的父结点位置 */
};

struct ParTree { 
    int n;              /* 树中结点的个数 */
    struct ParTreeNode nodelist[MAXNUM];  /* 存放树中的结点 */
};

typedef struct ParTree *PParTree;        /* 树类型的指针类型 */

/* 求右兄弟结点 */
int rightSibling_partree(PParTree t, int p) {
    int i;
    if (p >= 0 && p < t->n) {
        for (i = p+1; i < t->n; i++)
            if (t->nodelist[i].parent == t->nodelist[p].parent)
                return(i);
    }
    return null;
}

/* 求最左子结点 */
int leftChild_partree(PParTree t, int p) { 
    int i;
    for (i = 0; i < t->n; i++) {
        if (t->nodelist[i].parent == p)
            return i;
    }
    return null;
}

/* 依先根序列存储时,求最左子结点的运算可简化如下*/
// int leftChild_partree(PParTree t, int p) { 
//     if (t->nodelist[p+1].parent == p)
//         return(p+1);
//     else
//         return null;
// }

/* 访问结点 */
void visit(PParTree tree, int p) { 
    printf("%c ", tree->nodelist[p].info); 
}

/* 先根周游 */
void preOrder(PParTree t, int p) {
    int c;
    visit(t, p);
    c = leftChild_partree(t, p);
    while (c != null) {
        preOrder(t, c);
        c = rightSibling_partree(t, c);
    }
}

/* 后根周游 */
void postOrder(PParTree t, int p) {
    int c;
    c = leftChild_partree(t, p);
    while (c != null) {
        postOrder(t, c);
        c = rightSibling_partree(t, c);
    }
    visit(t, p);
}

/* ------------------------ */

#define M 10
#define N 10

typedef struct
{
    int index;  // 存储树节点在nodelist中的索引
} DataTypeQ;  

struct  SeqQueue {	/* 顺序队列类型定义 */
    int f, r;
    DataTypeQ q[MAXNUM];
};

typedef struct SeqQueue SeqQueue, *PSeqQueue;	/* 顺序队列类型和指针类型 */


/*创建一个空队列*/
PSeqQueue  createEmptyQueue_seq( void ) {  
    PSeqQueue paqu = (PSeqQueue)malloc(sizeof(struct SeqQueue));
    if (paqu==NULL)
        printf("Out of space!! \n");
    else
        paqu->f = paqu->r = 0;
    return paqu;
}

/*判队列是否为空队列*/
int  isEmptyQueue_seq(PSeqQueue paqu) {
    return paqu->f == paqu->r;
}

/* 在队列中插入一元素x */
void enQueue_seq( PSeqQueue paqu, DataTypeQ x ) {
    if( (paqu->r + 1) % MAXNUM == paqu->f  )
        printf( "Full queue.\n" );
    else 	{
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
DataTypeQ  frontQueue_seq( PSeqQueue paqu ) {
    return paqu->q[paqu->f];
}


/* 广度优先周游（层次遍历） */
void levelOrder(PParTree t, int p) {
    PSeqQueue q = createEmptyQueue_seq();
    if (t == NULL) return;

    // 将根节点索引入队
    DataTypeQ rootNode;
    rootNode.index = p;
    enQueue_seq(q, rootNode);
    
    while (!isEmptyQueue_seq(q)) {
        // 出队并访问
        DataTypeQ c = frontQueue_seq(q);
        deQueue_seq(q);
        visit(t, c.index);
        
        // 将当前节点的所有子节点入队
        int child = leftChild_partree(t, c.index);
        while (child != null) {
            DataTypeQ childNode;
            childNode.index = child;
            enQueue_seq(q, childNode);
            child = rightSibling_partree(t, child);
        }
    }
    free(q);
}

/* 数组实现广度优先周游 */
void bfsOrder(PParTree t, int p) {
    int queue[MAXNUM];
    int front = 0, rear = 0;
    
    // 将根节点入队
    queue[rear++] = p;
    
    while (front < rear) {
        // 出队并访问
        int current = queue[front++];
        visit(t, current);
        
        // 将所有子节点入队
        int child = leftChild_partree(t, current);
        while (child != null) {
            queue[rear++] = child;
            child = rightSibling_partree(t, child);
        }
    }
}

int main() {
    
    struct ParTree tree = {
        10,  // 共11个节点
        {
            {'a', -1},
            {'b', 0}, 
            {'c', 0},   
            {'d', 1},   
            {'e', 1},   
            {'f', 2},
            {'g', 2},
            {'h', 4},
            {'i', 4},
            {'j', 4},
        }
    };
    
    PParTree t = &tree;
    
    printf("先根周游结果:\t");
    preOrder(t, 0);
    putchar('\n');
    
    printf("后根周游结果:\t");
    postOrder(t, 0);
    putchar('\n');
    
    printf("数组实现广度周游结果:\t");
    bfsOrder(t, 0);
    putchar('\n');
    
    printf("队列实现广度周游结果:\t");
    levelOrder(t, 0);
    putchar('\n');

    return 0;
}