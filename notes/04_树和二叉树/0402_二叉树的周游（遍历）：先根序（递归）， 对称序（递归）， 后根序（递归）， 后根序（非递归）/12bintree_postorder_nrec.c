/* 二叉树后根周游的非递归算法*/

#include<stdlib.h>
#include<stdio.h>

typedef char DataType;

struct BinTreeNode;                         /* 二叉树中结点 */
typedef struct BinTreeNode *PBinTreeNode;   /* 创建指向二叉树结点的指针类型 */

struct BinTreeNode {
    DataType  info;         /* 数据域 - 存储结点的实际数据 */
    PBinTreeNode  llink;    /* 指向左子树结点 - 存储左子树的地址 */
    PBinTreeNode  rlink;    /* 指向右子树结点 - 存储右子树的地址 */
};

typedef struct BinTreeNode *BinTree;    //二叉树类型（存放根节点地址的指针）（定义二叉树类型，实际上就是指向根结点的指针）
typedef BinTree *PBinTree;              //二叉树指针类型（二级指针，用于修改二叉树的根指针）
typedef PBinTreeNode BNode;             //为结点指针类型创建别名，提高代码可读性（与 PBinTreeNode 等价）

PBinTreeNode root_btree(PBinTree t) {
    return *t;  //返回t所指二叉树的根结点的地址
}

PBinTreeNode leftChild_btree (PBinTreeNode p){
    return p->llink;
}

PBinTreeNode rightChild_btree (PBinTreeNode p){
    return p->rlink;
}

/*以下算法就是先将二叉树扩充为扩充的二叉树，
然后按先根次序周游的顺序输入结点的信息,
生成一个双链存储的二叉树的过程*/

PBinTreeNode createRest_BTree() {
    /* 递归创建从根开始的二叉树 */
    PBinTreeNode  pbnode;
    char ch;
    scanf("%c",&ch);
    if ( ch == '@') pbnode = NULL;
    else {
        pbnode = (PBinTreeNode )malloc(sizeof(struct BinTreeNode));
        if (pbnode == NULL) {
            printf("Out of space!\n");
            return pbnode;
        }
        pbnode->info = ch;
        pbnode->llink = createRest_BTree();	/* 构造左子树 */
        pbnode->rlink = createRest_BTree();	/* 构造右子树 */
    }
    return pbnode;
}


PBinTree  create_BTree( void ) {
    /* 创建完整的二叉树 */
    PBinTree pbtree = (PBinTree)malloc(sizeof(BinTree));
    if (pbtree != NULL)
        *pbtree = createRest_BTree( );  /* 递归创建从根开始的二叉树 */
    return pbtree; 
}

void visit(BNode p) { printf("%c ",p->info); }

typedef struct { 
    BNode ptr;          /* 进栈结点 */
    int   tag;          /* 标记 */
} Elem;

/*栈顺序表示*/
#define MAXNUM 20       /* 栈中最大元素个数 */
struct  SeqStack {      /* 顺序栈类型定义 */
    int  t;             /* 指示栈顶位置 */
    Elem s[MAXNUM];
};

typedef struct SeqStack *PSeqStack;	/* 顺序栈类型的指针类型 */ 

/*创建一个空栈;为栈结构申请空间，并将栈顶变量赋值为-1*/
PSeqStack  createEmptyStack_seq( void ) {
    PSeqStack pastack;
    pastack = (PSeqStack)malloc(sizeof(struct SeqStack));
    if (pastack == NULL)
        printf("Out of space!! \n");
    else
        pastack->t = -1;
    return pastack;
}

/*判断pastack所指的栈是否为空，为空栈时返回1，否则返回0*/
int isEmptyStack_seq( PSeqStack pastack ) {
    return pastack->t == -1;
}

/* 在栈中压入一元素x */
void push_seq( PSeqStack pastack, Elem x ) {
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
        pastack->t--;
}

/* 假定pastack所指的栈不为空，求栈顶元素的值 */
Elem  top_seq( PSeqStack pastack ) {
    return (pastack->s[pastack->t]);
}

void nPostOrder(PBinTree t) {
    PSeqStack st;	/* 栈中元素类型为 Elem */
    Elem stnode;
    BNode  p;		/* 周游时当前要处理的结点*/
    char continueflag; /* 表明是否继续退栈，从右子树返回时访问完根之后需继续退栈 */
    
    if (*t == NULL) return;
    st = createEmptyStack_seq( ); 	/* 创建空栈 */
    
    p = *t;                 /* 从根结点开始 */
    do {					/* 每执行一次大循环进入一棵由p指出根的子树去周游 */
        while (p != NULL) { /* 反复地把遇到的结点进栈并进入它的左子树 */
            stnode.ptr = p;
            stnode.tag = 1;
            push_seq(st, stnode);
            p = leftChild_btree(p);
        }
        continueflag = 't';
        while ( continueflag == 't' && !isEmptyStack_seq(st) ) {
            stnode = top_seq(st);
            pop_seq(st);	/* 退栈 */
            p = stnode.ptr;				
            if (stnode.tag == 1) { 
            /* 如果是从左子树回来，则改标志重新进栈，停止退栈并进入右子树 */
                stnode.tag = 2;
                push_seq(st, stnode);
                continueflag = 'f';
                p = rightChild_btree(p);
            }
            else visit(p);
        }
    } while (!isEmptyStack_seq (st));	/* 栈为空时，全部周游完 */
}

int main(){
    PBinTree  tree = create_BTree();
    nPostOrder(tree);
    putchar('\n');
    return 0;
}

