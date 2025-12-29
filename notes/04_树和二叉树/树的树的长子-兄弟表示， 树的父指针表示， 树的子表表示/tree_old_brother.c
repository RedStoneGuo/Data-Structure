/* 树的长子-兄弟表示法*/

#include<stdio.h>

typedef int DataType ;
struct  CSNode;   					/* 树中结点结构 */
typedef  struct  CSNode   *PCSNode;	/* 结点的指针类型 */
struct  CSNode {   					/* 结点结构定义 */
    DataType info;					/* 结点中的元素 */
    PCSNode  lchild;				/* 结点的最左子女的指针 */
    PCSNode  rsibling;				/* 结点的右兄弟的指针 */
};

typedef  struct CSNode  *CSTree;	/* 树类型定义 */
typedef  CSTree   *PCSTree;

PCSNode leftChild_cstree(PCSNode p ) {
    return p->lchild;
}

PCSNode rightSibling_cstree(PCSNode p ) {
    return p->rsibling;
}

PCSNode root_cstree(PCSTree t ) {
    return *t;
}

int isNull_cstree(PCSTree t ) {
    return *t==NULL;
}

int main(){
    return 0;
}
