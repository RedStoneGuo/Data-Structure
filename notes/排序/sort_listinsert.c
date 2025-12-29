/* 表插入排序的算法源程序*/

#include<stdio.h>

struct Node;                    /* 单链表结点类型 */
typedef int KeyType;
typedef int DataType;

typedef struct Node ListNode;

struct Node {
    KeyType key;            /* 排序码字段 */
    /*DataType info;                记录的其它字段 */
    ListNode *next;              /* 记录的指针字段 */
};

typedef ListNode * LinkList;

/* 对链表按递增序进行表插入排序，链表中第一个结点为表头结点。 */
void listSort(LinkList * plist) {
    ListNode *now, *pre, *p, *q, *head; head=*plist;
    if (head->next == NULL || head->next->next == NULL)
        return;  /* 为空链表或链表中只有一个结点 */

    pre = head->next; now = pre->next;
    while (now != NULL) {
        q = head; p = head->next;
        while(p != now && p->key <= now->key) {
            q = p;  p = p->next;
        } /* 本循环结束时，已经找到了now的插入位置 */

        if (p == now) {                        /* now应放在原位置 */
            pre = pre->next; now = pre->next; continue;
        }

        /* 使now记录脱链，将now记录插入链表中 */
        pre->next = now->next; q->next = now;
        now->next = p; now = pre->next;
    }
}

ListNode element[9]={
    0, &element[1],
    49, &element[2],
    38, &element[3],
    65, &element[4],
    97, &element[5],
    76, &element[6],
    13, &element[7],
    27, &element[8],
    49, NULL
};

int main(){
    LinkList p = element;
    listSort(&p);
    p = p->next;
    while (p != NULL){
        printf("%d ",p->key);
        p = p->next;
    }
    getchar();
    return 0;
}
