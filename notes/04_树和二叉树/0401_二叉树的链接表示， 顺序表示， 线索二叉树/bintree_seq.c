/* 二叉树的顺序表示*/

#define  MAXNODE    20
typedef int DataType;
struct SeqBTree	{ 			/* 顺序树类型定义 */
    int       n;			/* 改造成完全二叉树后，结点的个数 */
    DataType  nodelist[MAXNODE];
};

typedef  struct SeqBTree  *PSeqBTree;

int root_seq(PSeqBTree t) {
    return t->nodelist[0];
}

int parent_seq(PSeqBTree t, int p) {
    return t-> nodelist[(p-1)/2];
}

int leftChild_seq(PSeqBTree t, int p) {
    return t-> nodelist[2*p+1];
}

int rightChild_seq(PSeqBTree t, int p) {
    return t-> nodelist[2*(p+1)];
}

int main() {
    return 0;
}
