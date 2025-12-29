/* 基数排序的算法源程序*/


#include<stdio.h>

#define D 3                       /* D为排序码的最大位数 */
#define R 10                      /* R为基数 */

typedef int KeyType;
typedef int DataType;

struct Node;                      /* 单链表结点类型 */
typedef struct Node RadixNode;

struct Node {
    KeyType key[D]; 
    /* DataType info;*/
    RadixNode *next;
};

typedef RadixNode * RadixList;

typedef struct QueueNode {
    RadixNode *f;                  /* 队列的头指针 */
    RadixNode *e;                  /* 队列的尾指针 */
} Queue;

Queue queue[R];

void radixSort(RadixList * plist, int d, int r) {
    int i,j,k; 
    RadixNode *p, *head = (*plist)->next;

    for(j = d-1; j >= 0; j--) {         /* 进行d次分配和收集*/
        p = head;
        for(i = 0; i < r; i++) { 
            queue[i].f = NULL;  queue[i].e = NULL; /* 清队列 */
        }

        while (p != NULL) {
            k = p->key[j];              /* 按排序码的第j个分量进行分配*/
            if (queue[k].f == NULL) 
                queue[k].f = p;         /* 若第k个队列为空，则当前记录为队头*/ 
            else (queue[k].e)->next = p;/* 否则当前记录链接到第k队的队尾*/
            queue[k].e = p;
            p = p->next;
        }

        for(i = 0; queue[i].f == NULL; i++) /* 找出第一个非空队列*/
            ;
        p = queue[i].e;  head = queue[i].f; /* head为收集链表的头指针*/

        for(i++; i < r; i++)
            if(queue[i].f != NULL) { /* 收集非空队列 */
                p->next = queue[i].f;
                p = queue[i].e;
            }       
        p->next = NULL;
    }
    (*plist)->next = head;
}

struct Node element[11]={
    0,0,0,NULL,/*表头*/
    0,3,6,NULL,/*36*/
    0,0,5,NULL,/*5*/
    0,1,6,NULL,/*16*/
    0,9,8,NULL,/*98*/
    0,9,5,NULL,/*95*/
    0,4,7,NULL,/*47*/
    0,3,2,NULL,/*32*/
    0,3,6,NULL,/*36*/
    0,4,8,NULL,/*48*/
    0,1,0,NULL /*10*/
};

int main(){
    int i;
    RadixList p = element;
    for (i = 0; i < 10; i++)
        element[i].next = &element[i+1];
    element[10].next = NULL;
    radixSort(&p, 3, 10);
    p = p->next;
    while (p != NULL){
        printf("%d ", p->key[1]*10+p->key[2]);
        p = p->next;
    }
    getchar();
    return 0;
}

