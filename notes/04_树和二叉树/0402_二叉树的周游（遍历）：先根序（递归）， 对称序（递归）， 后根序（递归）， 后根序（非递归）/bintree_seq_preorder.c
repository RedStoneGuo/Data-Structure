/* 二叉树的顺序表示*/
#include<stdio.h>
#define  MAXNODE    20

typedef char DataType;  // 根据题目需要改为char类型
struct SeqBTree {       /* 顺序树类型定义 */
    int       n;        /* 改造成完全二叉树后，结点的个数 */
    DataType  nodelist[MAXNODE];
};

typedef  struct SeqBTree  *PSeqBTree;

/* 创建空二叉树 */
PSeqBTree createEmptyBTree_seq() {
    PSeqBTree t = (PSeqBTree)malloc(sizeof(struct SeqBTree));
    if (t != NULL) {
        t->n = 0;  // 初始节点数为0
        for (int i = 0; i < MAXNODE; i++) {
            t->nodelist[i] = '@';  // 用 @ 表示空位置
        }
    }
    return t;
}

/* 基础函数 */
DataType root_seq(PSeqBTree t) {
    return t->nodelist[0];
}

DataType parent_seq(PSeqBTree t, int p) {
    if (p <= 0 || p >= t->n) return -1;
    return t->nodelist[(p-1)/2];
}

DataType leftChild_seq(PSeqBTree t, int p) {
    int leftIndex = 2*p + 1;
    if (leftIndex >= t->n) return -1;
    return t->nodelist[leftIndex];
}

DataType rightChild_seq(PSeqBTree t, int p) {
    int rightIndex = 2*p + 2;
    if (rightIndex >= t->n) return -1;
    return t->nodelist[rightIndex];
}

/* 先根周游的递归函数 */
void preOrder_seq(PSeqBTree t, int p) {
    if (p >= t->n || t->nodelist[p] == '@') {
        return;  // 超出范围或空节点则返回
    }
    
    // 访问根节点
    printf("%c ", t->nodelist[p]);
    
    // 递归遍历左子树
    preOrder_seq(t, 2*p + 1);
    
    // 递归遍历右子树
    preOrder_seq(t, 2*p + 2);
}

/* 建立指定二叉树的函数 */
PSeqBTree createBTree() {
    PSeqBTree t = createEmptyBTree_seq();
    
    // 建立二叉树
    char nodes[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    t->n = 10;
    
    // 将节点数据填入数组
    for (int i = 0; i < t->n; i++) {
        t->nodelist[i] = nodes[i];
    }
    
    return t;
}

int main() {
    PSeqBTree tree = createBTree();
    
    printf("\n先根周游结果：");
    preOrder_seq(tree, 0);
    printf("\n");
    
    free(tree);
    return 0;
}