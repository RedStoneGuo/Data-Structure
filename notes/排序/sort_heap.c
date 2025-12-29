/* 堆排序的算法源程序*/

#include<stdio.h>

#define MAXNUM 100
#define TRUE 1
#define FALSE 0
typedef int KeyType;
typedef int DataType;

typedef struct {
    KeyType key;         /* 排序码字段 */
    /*DataType info;     记录的其它字段 */
} RecordNode;

typedef struct {
    int n;               /* n为文件中的记录个数，n<MAXNUM */
    RecordNode record[MAXNUM];
} SortObject;

/* 定义宏是为了使程序清晰 */ 
#define leftChild(i) (2*(i)+1)

void  sift(SortObject * pvector, int i, int n) {
    int child; 
    RecordNode temp = pvector->record[i], *data = pvector->record;

    child = leftChild(i);      /* Rchild是R0的左子女 */
    while(child<n) {
        if (child < n-1 && data[child].key < data[child+1].key)
            child++;           /* child 指向Ri的左、右子女中排序码较大的结点 */
        if (temp.key < data[child].key) {
            data[i] = data[child]; 
            i = child;  child = leftChild(i);/* child换到父结点位置，继续调整*/
        }
        else break;            /* 调整结束 */
    }
    data[i] = temp;            /* 将记录Ri放入正确位置 */
}

void  heapSort(SortObject * pvector) {    /* 对记录R0到Rn-1进行堆排序 */
    int i, n = pvector->n;
    RecordNode temp, *data = pvector->record;
    
    for (i = n/2-1; i >= 0; i--)
        sift(pvector, i, n);              /* 建立初始堆 */
    for (i = n-1; i > 0; i--) {           /* 进行n-1趟堆排序 */
        temp = data[0];                   /* 当前堆顶记录和最后一个记录互换 */
        data[0] = data[i];
        data[i] = temp;
        sift(pvector, 0, i);              /* 从R0到Ri-1重建堆 */
    }
}

SortObject vector={8, 49,38,65,97,76,13,27,49};

int main(){
    int i;
    heapSort(&vector);
    for(i = 0; i < 8; i++)
        printf("%d ", vector.record[i]);
    getchar(); 
    return 0;
}
