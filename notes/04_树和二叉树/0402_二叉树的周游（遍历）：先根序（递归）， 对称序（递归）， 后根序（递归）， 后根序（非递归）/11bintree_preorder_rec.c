/* 二叉树前根、中根、后根周游的递归算法*/

#include<stdlib.h>
#include<stdio.h>

typedef char DataType;

struct BinTreeNode;                         /* 二叉树中结点 */
typedef struct BinTreeNode *PBinTreeNode;   /* 结点的指针类型 */

struct BinTreeNode {
    DataType  info;                         /* 数据域 */
    PBinTreeNode  llink;                    /* 指向左子女 */
    PBinTreeNode  rlink;                    /* 指向右子女 */
};

typedef struct BinTreeNode *BinTree;
typedef BinTree *PBinTree;

PBinTreeNode root_btree(PBinTree t) {
    return *t;
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
    scanf(" %c",&ch);
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

void visit(PBinTreeNode p) { printf("%c ",p->info); }

void preOrder(PBinTreeNode p) {
    if (p == NULL) return;
    visit(p);
    preOrder(leftChild_btree(p));
    preOrder(rightChild_btree(p));
}
void postOrder(PBinTreeNode p) {
    if (p == NULL) return;
    
    postOrder(leftChild_btree(p));
    postOrder(rightChild_btree(p));
	visit(p);
}
int num_of_nodes(PBinTreeNode p)
{

  if(p==0) return 0;
  return (1+num_of_nodes(p->llink)+num_of_nodes( p->rlink));

}

void inOrder(PBinTreeNode p) {
    if (p == NULL) return;
    
    inOrder(leftChild_btree(p));  // 先遍历左子树
    visit(p);                     // 再访问根节点  
    inOrder(rightChild_btree(p)); // 最后遍历右子树
}

int main(){
	PBinTree tree;
	printf("请输入二叉树各节点数据，先构造扩充二叉树，然后以先根次序输入，以@表示扩充的节点\n");
    tree = create_BTree();
    //PBinTreeNode p=*tree;
    printf("二叉树先根输出序列为：\t");
    preOrder(*tree);
    printf("\n");
	printf("二叉树中根输出序列为：\t");
    inOrder(*tree);
    printf("\n");
    return 0;
}

