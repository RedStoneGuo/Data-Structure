/* 本程序是用开地址法实现散列的检索算法*/

#include<stdio.h>

#define TRUE 1
#define FALSE 0

#define null    -1     /* null为空结点标记 */
#define REGION_LEN 13

typedef int KeyType;

typedef struct {
    KeyType key;                  /* 字典元素的关键码字段     */
    /*DataType value;             /* 字典元素的属性字段    */
} DicElement;

typedef struct {
    int m;                   /* m=REGION_LEN，为基本区域长度 */
    DicElement element[REGION_LEN];
} HashDictionary;

int h(KeyType key){
    return key % REGION_LEN;
}

int linearSearch(HashDictionary * phash, KeyType key, int *position)  {
    int d = h(key), inc;                  /* d为散列地址，散列函数为h(key) */

    for (inc = 0; inc < phash->m; inc++) {
        if (phash->element[d].key == key) {
            *position = d;                /* 检索成功 */
            return TRUE;
        }
        else if (phash->element[d].key == null) {
            *position = d;                /* 检索失败，也找到插入位置 */
            return FALSE;
        }
        d = (d+1) % phash->m;
    }

    *position = -1;                       /* 散列表溢出 */
    return FALSE;
}

int linearInsert(HashDictionary *phash, KeyType key) {
    int position;
    if(linearSearch(phash, key, &position) == TRUE )/* 已有关键码为key的结点*/
        printf("Find\n");
    else if(position != -1) {   
        phash->element[position].key = key; /* 插入结点，还应对value字段赋值 */
    }
    else  return FALSE;                    /* 散列表溢出 */

    return TRUE;
}

HashDictionary dic;

int main(){
    int i, position, key;
    dic.m = REGION_LEN;
    for (i = 0; i < REGION_LEN; i++)
        dic.element[i].key = null;
    while (1) {
        printf("Input 1 to insert element\n"
                "2 to search element\n"
                "else to exit\nWhat do you want to do?");
        scanf("%d",&i);
        if (i == 1){
            printf("Input the key you want to insert:");
            scanf("%d", &key);
            if (linearInsert(&dic, key) == FALSE)
                printf("There is no space!\n");
        }
        else if (i == 2){
            printf("Input the key you want to search:");
            scanf("%d", &key);
            if(linearSearch(&dic, key, &position) == TRUE)
                printf("It is the %dth element!\n", position+1);
            else printf("It is not in the dictionary!\n");
        }
        else break;
    }
    return 0;
}
			
