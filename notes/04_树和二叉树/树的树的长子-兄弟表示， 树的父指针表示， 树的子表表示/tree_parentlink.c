/* 树的父指针表示法*/
#include <stdio.h>
#include <stdlib.h>
#define MAXNUM 20

typedef int DataType;

struct ParTreeNode {
    DataType info;		/* 结点中的元素 */
    int     parent;	/* 结点的父结点位置 */
};

struct  ParTree { 
    int n;                 	/* 树中结点的个数 */
    struct ParTreeNode *nodelist;  	/* 存放树中的结点 */
};

typedef struct ParTree *PParTree;		/* 树类型的指针类型 */
PParTree create_Null_PParTree(int m)
{
         PParTree ptree=(PParTree)malloc(sizeof(struct ParTree)); 
         ptree->nodelist=(struct ParTreeNode*)malloc(m*sizeof(struct ParTreeNode));
         return ptree;
}

PParTree create_Partree()
{
         struct ParTreeNode parnode;
         int par; int n; int i;
         PParTree ptree= create_Null_PParTree(100);
         printf("按父指针表示法输入树的节点值,按先根次序输入,以 @ 结尾");
         printf("树节点个数 n = %d",&n);
         ptree->n=10;
         ptree->nodelist= { 0,-1,1,0,2,1,3,1,4,3,5,3,6,3,7,0,8,7,9,7 };
}
         
                          
         
          
         
int rightSibling_partree(PParTree t, int p) {
    int i;
    if (p >= 0 && p < t->n) {
        for (i = p+1; i <= t->n; i++)
            if (t->nodelist[i].parent == t->nodelist[p].parent)
                return i;
    }
    return -1;
}



/* 依先根序列存储时,求最左子结点的运算可简化如下*/
int leftChild_partree(PParTree t, int p) {     
    if (t->nodelist[p+1].parent == p)
        return p+1;
    else
        return -1;
}

int main(){
    PParTree create_Partree();
    return 0;
}
