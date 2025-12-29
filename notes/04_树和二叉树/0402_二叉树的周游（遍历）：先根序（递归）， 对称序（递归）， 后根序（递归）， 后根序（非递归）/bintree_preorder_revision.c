/* 二叉树前根周游的递归算法*/

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

 struct BinTree {struct BinTreeNode *p;} ;
typedef struct BinTree *PBinTree;

PBinTreeNode root_btree(PBinTree t) {
    return t->p;
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
    PBinTreeNode  pbnode;       //指向二叉树结点的指针
    char ch;
    scanf(" %c",&ch);           //录入结点值
    if ( ch == '@') pbnode = NULL;  //为空判断
    else {
        pbnode = (PBinTreeNode)malloc(sizeof(struct BinTreeNode));  //开辟新空间
        if (pbnode == NULL) {   //开辟空间失败时，报错
            printf("Out of space!\n");
            return pbnode;
        }
        pbnode->info = ch;      //对根结点赋值
        pbnode->llink = createRest_BTree();	/* 构造左子树 */
        pbnode->rlink = createRest_BTree();	/* 构造右子树 */
    }
    return pbnode;
}

PBinTree  create_BTree( void ) {
    /* 创建完整的二叉树 */
    PBinTree pbtree = (PBinTree)malloc(sizeof(struct BinTree));
    if (pbtree != NULL)
        pbtree->p = createRest_BTree( );  /* 递归创建从根开始的二叉树 */
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
int main(){
	PBinTree tree;
	printf("请输入二叉树各节点数据:  先构造扩充二叉树，然后以先根次序输入，以@表示扩充的节点\n");
    tree = create_BTree();
    //PBinTreeNode p=*tree;
	printf("二叉树先根输出序列为：\t");
    postOrder(tree->p);
	printf("二叉树节点个数为 Num=%d ",num_of_nodes(tree->p));
    putchar('\n');
    return 0;
}

