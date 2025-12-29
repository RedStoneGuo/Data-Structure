/* 二分法插入排序的算法源程序*/

#include<stdio.h>

#define MAXNUM 100
typedef int KeyType;
typedef int DataType;

typedef struct {
    KeyType key;       /* 排序码字段 */
    /*DataType info;   记录的其它字段 */
} RecordNode;

typedef struct {
    int n;               /* n为文件中的记录个数，n<MAXNUM */
    RecordNode record[MAXNUM];
} SortObject;

void binSort(SortObject * pvector) {      /* 按递增序进行二分法插入排序 */
    int i, j, left, mid, right;
    RecordNode temp;
    RecordNode *data = pvector->record;
    
    for( i = 1; i < pvector->n; i++ ) {
        temp = data[i];
        left = 0;  right = i-1;           /* 置已排序区间的下、上界初值 */
        while (left <= right) {
            mid = (left + right)/2;       /* mid指向已排序区间的中间位置 */
            if (temp.key < data[mid].key)
                right = mid-1;            /* 插入元素应在左子区间 */
            else left = mid+1;            /* 插入元素应在右子区间 */
        }
        for (j = i-1;  j >= left;  j--)
            data[j+1] = data[j];          /* 将排序码大于ki的记录后移 */
        if (left != i) data[left] = temp;
    }
}

SortObject vector={10, 49,38,65,97,76,13,27,49,50,101};

int main(){
    int i;
    binSort(&vector);
    for(i = 0; i < vector.n; i++)
        printf("%d ", vector.record[i]);
    getchar();
    return 0;
}
