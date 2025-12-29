/* 散列字典（开地址法）程序 */
#include<stdio.h>

#define null -1                 /* null为空结点标记 */
#define TRUE 1
#define FALSE 0

#define REGION_LEN 13

typedef int KeyType;
typedef int DataType;

typedef struct {
    KeyType key;                /* 字典元素的关键码字段 */
    DataType value;             /* 字典元素的属性字段（关键码的平方） */
} DicElement;

typedef struct {
    int m;                      /* m=REGION_LEN，为基本区域长度 */
    DicElement element[REGION_LEN];
} HashDictionary;

/* 散列函数 */
int h(KeyType key) {
    return key % REGION_LEN;
}

/* 线性探索法查找 */
int linearSearch(HashDictionary *phash, KeyType key, int *position) {
    int inc, d = h(key);                    /* d为散列地址 */
    for (inc = 0; inc < phash->m; inc++) {
        if (phash->element[d].key == key) { /* 检索成功 */
            *position = d;                
            return TRUE;
        }
        else if (phash->element[d].key == null) { /* 检索失败，找到插入位置 */
            *position = d;                              
            return FALSE;
        }
        d = (d + 1) % phash->m;            /* 线性探测下一个位置 */
    }

    *position = -1;                         /* 散列表溢出 */
    return FALSE;
}

/* 线性探索法插入 */
int linearInsert(HashDictionary *phash, KeyType key) {
    int position;
    if (linearSearch(phash, key, &position) == TRUE)  /* 散列表中已有关键码为key的结点 */
        printf("Find, key exists!\n");  
    else if (position != -1) {    
        phash->element[position].key = key;     /* 插入结点 */
        phash->element[position].value = key * key;  /* 属性值为关键码的平方 */
    } 
    else return FALSE;  /* 散列表溢出 */
    return TRUE;
}

/* 建立字典 */
HashDictionary createDictionary() {
    HashDictionary dict;
    dict.m = REGION_LEN;
    
    // 初始化散列表所有位置为空
    for (int i = 0; i < REGION_LEN; i++) {
        dict.element[i].key = null;
        dict.element[i].value = null;
    }
    
    // 关键码集合
    KeyType keys[] = {18, 73, 10, 5, 68, 22, 32, 46, 58, 25};
    int n = sizeof(keys) / sizeof(keys[0]);
    
    // 插入所有关键码
    for (int i = 0; i < n; i++) {
        if (!linearInsert(&dict, keys[i])) {
            printf("插入关键码 %d 时散列表溢出！\n", keys[i]);
        }
    }
    
    return dict;
}

/* 打印散列表 */
void printHashDictionary(HashDictionary *phash) {
    printf("散列表内容（h(key)=key%%13，线性探测法）:\n");
    printf("索引\t关键码\t属性值（平方）\t散列地址\n");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < phash->m; i++) {
        if (phash->element[i].key == null) {
            printf("[%2d]\t---\t---\t\t---\n", i);
        } else {
            int hashAddr = h(phash->element[i].key);
            printf("[%2d]\t%2d\t%4d\t\t", i, phash->element[i].key, phash->element[i].value);
            if (i == hashAddr) {
                printf("h(%d)=%d\n", phash->element[i].key, hashAddr);
            } else {
                printf("冲突（原地址%d）\n", hashAddr);
            }
        }
    }
    printf("----------------------------------------\n");
}

/* 2. 按关键字查询 */
void queryByKey(HashDictionary *phash, KeyType key) {
    int position;
    
    printf("\n查询关键码: %d\n", key);
    
    if (linearSearch(phash, key, &position) == TRUE) {
        printf("查询成功！\n");
        printf("关键码: %d\n", key);
        printf("属性值: %d\n", phash->element[position].value);
        printf("存储位置: 索引[%d]\n", position);
        printf("散列地址: h(%d) = %d %% 13 = %d\n", key, key, h(key));
        
        if (position == h(key)) {
            printf("无冲突，直接存储在散列地址\n");
        } else {
            printf("发生冲突，经线性探测存储在位置[%d]\n", position);
        }
    } else {
        printf("查询失败！\n");
        printf("关键码 %d 不在字典中\n", key);
        
        if (position == -1) {
            printf("散列表已满，无法插入\n");
        } else {
            printf("可插入位置: 索引[%d]\n", position);
            printf("计算散列地址: h(%d) = %d %% 13 = %d\n", key, key, h(key));
        }
    }
}

/* 主函数 */
int main() {
    HashDictionary dict = createDictionary();
    
    printHashDictionary(&dict);
  
    KeyType key;
    printf("\n要查询的关键码: ");
    scanf("%d", &key);

    queryByKey(&dict, key);

    return 0;
}