/* shell排序的算法源程序 */

#include<stdio.h>

#define MAXNUM 100
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

void  shellSort(SortObject * pvector, int d) {	/* 按递增序进行Shell排序 */
    int i, j, inc; 
    RecordNode temp, *data = pvector->record;
    
    for (inc = d; inc > 0; inc /= 2) {
        /* inc 为本趟shell排序增量 */
        for (i = inc; i < pvector->n; i++) { 
            temp = data[i];          	/* 保存待插入记录Ri*/ 
            for (j = i-inc; j >= 0 && temp.key < data[j].key; j -= inc)
                data[j+inc] = data[j];	/* 查找插入位置，记录后移 */
            data[j+inc] = temp;			/* 插入记录Ri */
        }
    }
}


SortObject vector={8,49,38,65,97,76,13,27,49};

int main(){
    int i;
    shellSort(&vector,4);
    for(i=0;i<8;i++)
        printf("%d ",vector.record[i]);
    getchar();
    return 0;
}


