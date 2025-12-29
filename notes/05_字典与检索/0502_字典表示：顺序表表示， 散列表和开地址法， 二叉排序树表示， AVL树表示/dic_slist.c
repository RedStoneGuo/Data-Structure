/* 本程序提供了用顺序表实现字典的存储表示定义*/

#define MAXNUM 100

typedef int KeyType ;

typedef int DataType;

typedef struct {
    KeyType key;                  /* 字典元素的关键码字段     */
    DataType value;             /* 字典元素的属性字段    */
} DicElement;

typedef struct {
    int n;                          /* n<=MAXNUM，为字典中元素的个数 */
    DicElement element[MAXNUM];
} SeqDictionary;


int main(){
    return 0;
}
