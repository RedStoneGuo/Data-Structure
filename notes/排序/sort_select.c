/* 直接选择排序的算法源程序*/

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

void  selectSort(SortObject * pvector) {   /* 按递增序进行直接选择排序 */
    int i, j, k;
    RecordNode temp, *data = pvector->record;

    for( i = 0; i < pvector->n-1; i++ ) {  /* 做n-1趟选择排序 */
        k = i;
        for (j = i+1; j < pvector->n; j++) /* 在无序区内找出排序码最小的记录Rk*/
            if (data[j].key < data[k].key) k = j;
        if (k != i) {                      /* 记录Rk与Ri互换 */
            temp = data[i];
            data[i] = data[k];
            data[k] = temp;
        }     
    }
}

SortObject vector={8, 49,38,65,97,76,13,27,49};

int main(){
    int i;
    selectSort(&vector);
    for(i = 0; i < 8; i++)
        printf("%d ", vector.record[i]);
    getchar();
    return 0;
}
