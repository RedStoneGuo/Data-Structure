/* AVL树的检索算法*/


#include<stdio.h>
#include<stdlib.h>

enum { FALSE, TRUE };

typedef int KeyType;
struct AVLNode;
typedef struct AVLNode * PAVLNode;

struct AVLNode {
    KeyType key;                             /* 结点的关键码 */
    /*DataType value;                          结点的其它信息 */
    int bf;                                  /* 结点的平衡因子 */
    PAVLNode llink, rlink;         /* 分别指向结点的左、右子女 */
};

typedef struct AVLNode *AVLTree;
typedef AVLTree * PAVLTree;

PAVLNode creatNode(KeyType key) { 
    PAVLNode node;
    node = (PAVLNode)malloc(sizeof(struct AVLNode));
    if (node != NULL) { 
        node->key = key; node->bf = 0;
        node->llink = node->rlink = NULL;
    }
    return node;
}

PAVLNode lL(PAVLNode a, PAVLNode b) {
    a->bf = 0;  a->llink = b->rlink;
    b->bf = 0;  b->rlink = a;        /* b指向调整后的子树的根结点 */
    return b;
}

PAVLNode rR(PAVLNode a, PAVLNode b) {
    a->bf = 0;  a->rlink = b->llink;
    b->bf = 0;  b->llink = a;
    return b;
}

PAVLNode lR(PAVLNode a, PAVLNode b) {
    PAVLNode c = b->rlink; 
    a->llink = c->rlink; b->rlink = c->llink;
    c->llink = b;  c->rlink = a;

    switch (c->bf){
    case 0:
        a->bf = 0;  b->bf = 0;  break; /* LR(0)型调整 */
    case 1:
        a->bf = 1;  b->bf = 0;  break; /* 新结点插在*c的左子树中，LR(L)型调整 */
    case -1:
        a->bf = 0;  b->bf = -1; break;/* 新结点插在*c的右子树中，LR(R)型调整 */
    }
    c->bf = 0;
    return c;
}

PAVLNode rL(PAVLNode a, PAVLNode b){
    PAVLNode c = b->llink;
    a->rlink = c->llink;  b->llink = c->rlink;
    c->llink = a;  c->rlink = b;

    switch(c->bf){
    case 0:
        a->bf = 0;  b->bf = 0;  break;/* *c本身就是插入结点，RL(0)型调整 */
    case 1:
        a->bf = 0;  b->bf = 1;  break;/* 插在*c的左子树中，RL(L)型调整 */
    case -1:
        a->bf = -1; b->bf = 0;  break; /* 插在*c的右子树中，RL(R)型调整 */
    }
    c->bf = 0;
    return c;
}

void avlSearchInsert(PAVLTree ptree, KeyType key){    
    PAVLNode node_a, node_b, parent_a, p, q, r,node;
    int d;

    if(*ptree == NULL) { /* 原来AVL树为空 */
        *ptree = creatNode(key); return;
    }        

    node_a = *ptree;  parent_a = NULL;  p = node_a;  q = NULL;

    while(p != NULL) {   /* 寻找插入位置及最小不平衡子树 */
        if(key == p->key) return;       /* AVL树中已经有关键码为key的结点 */    
        r = q; q = p;
        if(key < p->key) p = p->llink;  /* 进入*p的左子树 */ 
        else p = p->rlink;              /* 进入*p的右子树 */ 
        if(q->bf != 0) {                /* 寻找最小不平衡子树*node_a */
            parent_a = r;  node_a = q;
        }
    }

    node = creatNode(key);
    if (key < q->key) q->llink = node;  /* 使新结点成为*p的左子女 */        
    else q->rlink = node;               /* 使新结点成为*p的右子女 */ 

    /* 已经将新结点结点插入到AVL树中，node_a指向最小不平衡子树。 */
    if (key < node_a->key) {            /* 新结点是插在*node_a的左子树中 */
        node_b = p = node_a->llink; d = -1;
    }
    else {                              /* 新结点是插在*node_a的右子树中 */
        node_b = p = node_a->rlink;  d = 1;
    }

    /* 下面修改*node_b到新结点路径上的各结点的平衡因子，*node_b为*node_a的子女 */
    while ( p != NULL && p != node ) {
        if (key < p->key) {             /* *p的左子树高度加1 */
            p->bf = -1;  p = p->llink;
        }
        else {                          /* *p的右子树高度加1 */
            p->bf = 1;  p = p->rlink;
        }
    }

    if (node_a->bf == 0) {
        /* *node_a原平衡因子为0，插入结点后只可能为1或－1，没有破坏平衡性 */
        node_a->bf = d;  return;
    }

    if (node_a->bf == -d) {           /* 新结点插在原来高度较小的子树中 */
        node_a->bf = 0;  return;
    }

    /* 下面是新结点插在原来高度较大的子树中，破坏了平衡性，要对子树进行调整 */
    if (d == -1)                           /* 新结点插在*node_a的左子树中*/
        if(node_b->bf == -1)
            node_b = lL(node_a, node_b);   /* LL型调整*/
        else node_b = lR(node_a, node_b);  /* LR型调整*/
    else                                   /* 新结点插在*node_a的右子树中*/
        if(node_b->bf == 1)
            node_b = rR(node_a, node_b);   /* RR型调整 */
        else node_b = rL(node_a, node_b);  /* RL 型调整 */

    if(parent_a == NULL)                   /* node_a原来指向树的根结点 */
        *ptree = node_b;
    else {
        if(parent_a->llink == node_a)
            parent_a->llink = node_b;
        else parent_a->rlink = node_b;
    }
}

int searchNode(PAVLTree ptree, KeyType key, PAVLNode *position) { 
    PAVLNode p = *ptree, q = p;

    while (p != NULL) {
        q = p;
        if (p->key == key) { /* 检索成功时，由参数position指向查找到的结点 */
            *position = p; return TRUE;
        }
        else if (p->key > key)  /* 进入左子树继续检索 */
            p = p->llink;
        else p = p->rlink;      /* 进入右子树继续检索 */
    }
    *position = q;
    return FALSE;     /* 检索失败时，position指向该结点应插入的父结点 */
}

/* 下面是试验程序 */
#define MAXNUM 100

typedef struct {
    KeyType key;                  /* 字典元素的关键码字段     */
    /*DataType value;             /* 字典元素的属性字段    */
} DicElement;

typedef struct {
    int n;                          /* n<=MAXNUM，为字典中元素的个数 */
    DicElement element[MAXNUM];
} SeqDictionary;


SeqDictionary dic = {11, 
    18, 10, 73, 5, 68, 99, 27, 25, 41, 32, 51
};

void creatTree(PAVLTree ptree, SeqDictionary dic);
int searchNode(PAVLTree ptree, KeyType key, PAVLNode *position);

/* 用一个线性字典创建平衡二叉树。假定 *ptree 原为空树 */
void creatTree(PAVLTree ptree, SeqDictionary dic) {
    int i;
    *ptree = NULL;
    for(i = 0; i < dic.n; i++)
        avlSearchInsert(ptree, dic.element[i].key);      /* 将新结点插入树中 */
}

int main(){
    AVLTree tree = NULL;
    int i, key;
    PAVLNode position;
    creatTree(&tree, dic);
    while(1){
        printf("Input 1 to insert element\n"
            "2 to search element\n"
            "else to exit\nWhat do you want to do?");
        scanf("%d", &i);
        if(i==1){
            printf("Input the key you want to insert:");
            scanf("%d",&key);
            avlSearchInsert(&tree,key);
        }
        else if (i == 2){
            printf("Input the key you want to search:");
            scanf("%d",&key);
            if (searchNode(&tree, key, &position) == TRUE)
                printf("It is in the dictionary!\n");
            else printf("It is not in the dictionary!\n");
        }
        else break;
    }
    return 0;
}


