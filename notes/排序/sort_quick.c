/* 快速排序的算法源程序*/

#include<stdio.h>

#define MAXNUM 100
#define TRUE 1
#define FALSE 0
typedef int KeyType;
typedef int DataType;

typedef struct {
    KeyType key;         /* 排序码字段 */
    /*DataType info;        记录的其它字段 */
} RecordNode;

typedef struct {
    int n;               /* n为文件中的记录个数，n<MAXNUM */
    RecordNode record[MAXNUM];
} SortObject;

void quickSort(SortObject * pvector, int l, int r) {
    int i, j;
    RecordNode temp, *data = pvector->record;
    
    if (l >= r) return;   /* 只有一个记录或无记录，则无须排序 */

    i = l;  j = r;  temp = data[i];

    while (i != j) {        /* 寻找Rl的最终位置 */
        while( data[j].key >= temp.key && j > i )
            j--;         /* 从右向左扫描，查找第1个排序码小于temp.key的记录 */
        if (i < j) data[i++] = data[j];   

        while( data[i].key <= temp.key && j > i )
            i++;         /* 从左向右扫描，查找第1个排序码大于temp.key的记录 */
        if (i < j) data[j--] = data[i];
    }

    data[i] = temp;                 /* 找到Rl的最终位置 */
    quickSort(pvector, l, i-1);                 /* 递归处理左区间 */
    quickSort(pvector, i+1, r);            /* 递归处理右区间 */
}

SortObject vector = {8, 49,38,65,97,76,13,27,49};

int main(){
    int i;
    quickSort(&vector, 0, 7);
    for(i = 0; i < 8; i++)
        printf("%d ", vector.record[i]);
    getchar();
    return 0;
}
