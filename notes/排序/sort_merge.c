/* 二路归并排序算法的源程序*/

#include<stdio.h>

#define MAXNUM 100
#define TRUE 1
#define FALSE 0

typedef int KeyType;
typedef int DataType;

typedef struct {
    KeyType key;       /* 排序码字段 */
    /*DataType info;           记录的其它字段 */
} RecordNode;

typedef struct {
    int n;               /* n为文件中的记录个数，n<MAXNUM */
    RecordNode record[MAXNUM];
} SortObject;

void merge(RecordNode r[], RecordNode r1[], int low, int m, int high) {
    /* r[low]到r[m]和r[m+1]到r[right]是两个有序段 */
    int i = low, j = m + 1, k = low;
    
    while ( i <= m && j <= high ) {    /* 反复复制两个段的第一个记录中较小的 */
        if (r[i].key <= r[j].key)  
            r1[k++] = r[i++];
        else r1[k++] = r[j++];
    }

    while (i <= m) r1[k++] = r[i++];   /* 复制第一个段的剩余记录 */
    while (j <= high) r1[k++] = r[j++];/* 复制第二个段的剩余记录 */

}

/* 对 r 做一趟归并，结果放到 r1 中 */
void mergePass(RecordNode r[], RecordNode r1[], int n, int length) {
    int i = 0, j;                     /* length为本趟归并的有序子段的长度 */

    while(i + 2*length - 1 < n) {
        merge(r, r1, i, i+length-1, i + 2*length - 1);/* 归并长length的两个子段*/
        i += 2*length;
    }
    
    if(i + length - 1 < n - 1)        /* 剩下两段，后一段长度小于 length */
        merge(r, r1, i, i+length-1, n-1);
    else                              /* 将剩下的一段复制到数组r1 */
        for(j = i; j < n; j++) r1[j] = r[j];
}

void mergeSort(SortObject * pvector) {
    RecordNode record[MAXNUM];
    int length = 1;

    while (length < pvector->n) {
        /* 一趟归并，结果存放在数组record中*/
        mergePass(pvector->record, record, pvector->n, length);
        length *= 2;
        /* 一趟归并，结果存回 */
        mergePass(record, pvector->record, pvector->n, length);
        length *= 2;
    }
}

SortObject vector = {8, 49,38,65,97,76,13,27,49};

int main(){
    int i;
    mergeSort(&vector);
    for(i = 0; i < 8; i++)
        printf("%d ", vector.record[i]);
    getchar();
    return 0;
}
