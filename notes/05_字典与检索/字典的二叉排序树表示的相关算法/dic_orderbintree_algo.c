/* 二叉排序树的检索算法*/

#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAXNUM 100

typedef int KeyType;

typedef struct {
    KeyType key;                  /* 字典元素的关键码字段     */
    /*DataType value;             /* 字典元素的属性字段    */
} DicElement;

typedef struct {
    int n;                          /* n<=MAXNUM，为字典中元素的个数 */
    DicElement element[MAXNUM];
} SeqDictionary;

struct BinTreeNode;

typedef struct BinTreeNode BinTreeNode, *PBinTreeNode;

struct BinTreeNode {
    KeyType key;                       /* 结点的关键码字段 */
    /*DataType value;                         结点的属性字段 */
    PBinTreeNode llink, rlink;        /* 二叉树的左、右指针 */
};

typedef struct BinTreeNode * BinTree;
typedef BinTree * PBinTree;

int searchNode(PBinTree ptree, KeyType key, PBinTreeNode *position) {
    PBinTreeNode p = *ptree, q = NULL;

    while (p != NULL) {
        q = p;
        if(p->key == key) { /* 检索成功，设参数position使之指向找到的结点 */
            *position = p; return TRUE;
        }
        else if (p->key > key)      /* 进入左子树继续检索 */
            p = p->llink;
        else p = p->rlink;          /* 进入右子树继续检索 */
    }
    
    *position = q;    /* 检索失败时，position指向该结点应插入位置的父结点 */
    return FALSE; 
}

/* 创建新结点，无空间时返回NULL */
PBinTreeNode newNode(KeyType key) {
    PBinTreeNode p = (PBinTreeNode)malloc(sizeof(BinTreeNode));
    if (p == NULL) {
        printf("Error!\n"); 
        return NULL;
    }     /* 申请空间出错 */

    p->key = key;                             /* 忽略对p->value的赋值 */
    p->llink = p->rlink = NULL;
    return p;
}

void insertNode(PBinTree ptree, KeyType key) {
    PBinTreeNode p, position;
    
    if (*ptree == NULL) {
        *ptree = newNode(key);     /* 原树为空树 */
        return;
    }

    if (searchNode(ptree, key, &position) == TRUE)
        return;/* 已存在关键码为key的结点 */

    p = newNode(key);
    if (key < position->key)
        position->llink = p;                  /* 插入position的左子树 */
    else position->rlink = p;                 /* 插入position的右子树 */
}

void deleteNode(PBinTree ptree, KeyType key) {
    PBinTreeNode parentp = NULL, p = *ptree, r;
    while (p!=NULL) {
        if (p->key == key) break;      /* 找到了关键码为key的结点 */
        parentp = p;
        if(p->key>key) 
            p = p->llink;              /* 进入左子树 */
        else  p=p->rlink;              /* 进入右子树 */
    }

    if (p == NULL) return;             /* 二叉排序树中无关键码为key的结点 */

    if (p->llink == NULL) {            /* 结点*p无左子树 */
        if (parentp == NULL)  
            *ptree = p->rlink;         /* 被删除的结点是原二叉排序树的根结点*/
        else if(parentp->llink == p)   /* *p是其父结点的左子女 */
            parentp->llink = p->rlink; /* 将*p的右子树链到其父结点的左链上 */
        else parentp->rlink = p->rlink;/* 将*p的右子树链到其父结点的右链上 */
    }
    else {  /* 结点*p有左子树 */
        r = p->llink;
        while(r->rlink != NULL)        /* 在*p的左子树中找最右下结点*r */ 
            r = r->rlink;
        r->rlink = p->rlink;                   /* 用*r的右指针指向*p的右子女 */
        if (parentp == NULL) *ptree = p->llink;
        else if(parentp->llink == p)           /* 用*p的左子女代替*p */
            parentp->llink = p->llink;
        else parentp->rlink = p->llink;

    }
    free(p);                                   /* 释放被删除结点 */
}

void creatBinTree (PBinTree ptree, SeqDictionary dic) {
    int i;
    *ptree = NULL; /* 这里假定了原来树中无结点 */
    for(i = 0; i < dic.n; i++)
        insertNode(ptree, dic.element[i].key); /* 将新结点插入树中 */
}

/* 释放整个二叉树。假定tree指向合法的二叉树 */ 
void destroyBinTree (BinTree tree) {
    BinTree l, r;
    if (tree == NULL) return;
    l = tree->llink;
    r = tree->rlink;
    free(tree);
    destroyBinTree(l);
    destroyBinTree(r);
}

void printBinTree (BinTree tree) {
    if (tree == NULL) return;
    printBinTree(tree->llink);
    printf("%d ", tree->key);
    printBinTree(tree->rlink);
}

SeqDictionary dic = {11, 
    {18, 10, 73, 5, 68, 99, 27, 25, 41, 32, 51}
};

int main() {
    BinTree tree = NULL;
    creatBinTree(&tree, dic);
	
    while(1){
        int i, key;
        PBinTreeNode position;
        
        printf("Input 1 to insert element\n"
                "2 to search element\n"
                "3 to delete element\n"
                "4 to print (inorder) all element in the tree \n"
                "5 to destroy all element in the tree \n"
                "else to exit\nWhat do you want to do? ");
        scanf("%d", &i);
		
        if (i == 1) {
            printf("Input the key you want to insert: ");
            scanf("%d", &key);
            insertNode(&tree, key);
        }
        else if (i == 2) {
            printf("Input the key you want to search: ");
            scanf("%d", &key);
            if(searchNode(&tree, key, &position) == TRUE)
                printf("It is in the dictionary.\n");
            else printf("It is not in the dictionary!\n");
        }
        else if (i == 3) {
            printf("Input the key you want to delete: ");
            scanf("%d", &key);
            deleteNode(&tree, key);
        }
        else if (i == 4) {
            printBinTree(tree);
            putchar('\n');
        }
        else if (i == 5) {
            destroyBinTree(tree);
            tree = NULL;
            putchar('\n');
        }
        else break;
    }
	
    return 0;
}

