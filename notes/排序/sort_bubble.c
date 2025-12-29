/* 起泡排序的算法源程序*/

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


void  bubbleSort(SortObject * pvector) {
    int i, j, noswap; 
    RecordNode temp, *data = pvector->record;

    for(i = 0; i < pvector->n-1; i++) {         /* 做n-1次起泡 */
        noswap = TRUE;                          /* 置交换标志 */
        for (j = 0; j < pvector->n-i-1; j++)    /* 从前向后扫描 */
            if (data[j+1].key < data[j].key) {  /* 交换记录 */
                temp = data[j]; 
                data[j] = data[j+1];
                data[j+1] = temp;
                noswap = FALSE;
            }
        if ( noswap ) break;    /* 本趟起泡未发生记录交换，算法结束 */
    }
}

SortObject vector={8, 49,38,65,97,76,13,27,49};

int main(){
    int i;
    bubbleSort(&vector);
    for(i = 0; i < 8; i++)
        printf("%d ", vector.record[i]);
    getchar();
    return 0;
}
