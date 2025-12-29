/* 树的先根周游的非递归算法*/

#include<stdio.h>
#include<stdlib.h>

typedef int DataType;
#define MAXNUM 20       /* 栈中最大元素个数 */
struct  SeqStack {      /* 顺序栈类型定义 */
    DataType  s[MAXNUM];
    int  t; 			/* 指示栈顶位置 */
};
typedef  struct SeqStack  *PSeqStack;	/* 顺序栈类型的指针类型 */ 

/*创建一个空栈;为栈结构申请空间，并将栈顶变量赋值为-1*/
PSeqStack  createEmptyStack_seq( void ) {
    PSeqStack pastack;
    pastack = (PSeqStack)malloc(sizeof(struct SeqStack));
    if (pastack==NULL)
        printf("Out of space!! \n");
    else
        pastack->t = -1;
    return  pastack;
}

/*判断pastack所指的栈是否为空栈，为空栈时返回1，否则返回0*/
int  isEmptyStack_seq( PSeqStack pastack ) {
    return pastack->t == -1;
}

/* 在栈中压入一元素x */
void  push_seq( PSeqStack pastack, DataType x ) {
    if( pastack->t >= MAXNUM - 1  )
        printf( "Overflow! \n" );
    else {
        pastack->t++;
        pastack->s[pastack->t] = x;
    }
}

/* 删除栈顶元素 */
void  pop_seq( PSeqStack pastack ) {
    if (pastack->t == -1 )
        printf( "Underflow!\n" );
    else
        pastack->t = pastack->t - 1;
}

/* 当pastack所指的栈不为空栈时，求栈顶元素的值 */
DataType  top_seq( PSeqStack pastack ) {
    return (pastack->s[pastack->t]);
}

struct  ParTreeNode	{
    /*DataType  info;		 结点中的元素 */
    int parent;	/* 结点的父结点位置 */
};

#define  MAXNUM   20
#define null -1

struct  ParTree{ 
    int   n;                 	/* 树中结点的个数 */
    struct ParTreeNode  nodelist[MAXNUM];  	/* 存放树中的结点 */
};

typedef struct ParTree  *PParTree;		/* 树类型的指针类型 */

int rightSibling_partree(PParTree t, int p) {
    int i;
    if (p >= 0 && p < t->n) {
        for (i = p+1; i <= t->n; i++)
            if (t->nodelist[i].parent == t->nodelist[p].parent) return i;
    }
    return null;
}

/* 依先根序列存储时,求最左子结点的运算可简化如下*/
int leftChild_partree(PParTree t, int p) {
    if (t->nodelist[p+1].parent == p)
        return p + 1;
    else
        return null;
}

typedef int Node;

void visit(Node p) { printf("%d ",p); }

void npreOrder ( PParTree t, Node p ) {
    Node c;
    PSeqStack s;	/* 栈元素的类型是 Node */
    s = createEmptyStack_seq ( );
    
    c = 0; /*c = root ( p );*/
    do {
        while ( c!=null ) {
            visit ( c );
            push_seq( s, c );
            c = leftChild_partree ( t, c );
        }
        while ( c == null && !isEmptyStack_seq(s)) {
            c = rightSibling_partree(t, top_seq(s));
            pop_seq(s);
        }
    } while(c != null);
}

struct  ParTree tree = {10, -1,0,1,1,3,3,3,0,7,7};

int main(){
    npreOrder(&tree, 0);
    putchar('\n');
    return 0;
}


