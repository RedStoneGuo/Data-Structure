/* 字典检索程序 - 字符到ASCII值映射 */
#include<stdio.h>
#define TRUE 1
#define FALSE 0
#define MAXNUM 100

typedef int KeyType ;  /* 关键码类型为int（ASCII值） */

typedef struct {
    char value;         /* 字典元素的属性字段（字符） */
    KeyType key;        /* 字典元素的关键码字段（ASCII值） */
} DicElement;

typedef struct {
    int n;              /* n<=MAXNUM，为字典中元素的个数 */
    DicElement element[MAXNUM];
} SeqDictionary;

/* 在字典中用二分法查找关键码为key的元素 */
int binarySearch(SeqDictionary * pdic, KeyType key, int *position) {
    int low = 0, high = pdic->n-1, mid;

    while(low <= high) {
        mid = (low + high) / 2;                     /* 当前检索的中间位置 */
        if(pdic->element[mid].key == key) {         /* 检索成功 */
            *position = mid;  
            return TRUE;
        }
        else if (pdic->element[mid].key > key) 
            high = mid - 1;                         /* 要检索的元素在左半区 */
        else 
            low = mid + 1;                          /* 要检索的元素在右半区 */
    }
    *position = low;
    return FALSE;                                   /* 检索失败 */
}

/* 通过赋初值的方法建立该字典 */
SeqDictionary createDictionary() {
    SeqDictionary dic = {
        10,
        {
            {'a', 97},
            {'b', 98},
            {'c', 99},
            {'d', 100},
            {'e', 101},
            {'f', 102},
            {'g', 103},
            {'h', 104},
            {'i', 105},
            {'j', 106}
        }
    };
    return dic;
}

/* 打印字典内容 */
void printDictionary(SeqDictionary *pdic) {
    printf("当前字典内容（字符 -> ASCII值）:\n");
    printf("索引\t字符\tASCII值\n");
    printf("------------------------\n");
    for(int i = 0; i < pdic->n; i++) {
        printf("[%d]\t'%c'\t%d\n", i, pdic->element[i].value, pdic->element[i].key);
    }
    printf("------------------------\n");
}

/* 对该字典做查询运算 */
int main(){
    int position;
    int input;
    
    // 建立字典
    SeqDictionary dic = createDictionary();

    printDictionary(&dic);

    printf("\n请输入要查找的ASCII值 (97-106): ");
    scanf("%d", &input);

    if(binarySearch(&dic, input, &position) == TRUE) {
        printf("ASCII值 %d 对应的字符是: '%c'\n", input, dic.element[position].value);
        printf("它在字典中的位置是: 第%d个元素（索引%d）\n", position+1, position);
    } 
    else {
        printf("ASCII值 %d 不在字典中。\n", input);
        printf("它应该插入到位置: 第%d个（索引%d）\n", position+1, position);
    }

    return 0;
}