struct PriorityQueue{
int MAXNUM; /*堆中元素个数的上限*/
int n; /*堆中实际元素的个数*/
DataType *pq; /*堆中元素的顺序表示*/
}; /*优先队列类型*/
typedef struct PriorityQueue *PPriorityQueue;/


void add_heap(PPriorityQueue papq,DataType x){
int i;
if(papq->n>=papq->MAXNUM-1){printf(“Full!\n”);return;}
for(i=paqu->n;i> 0&& papq->pq[(i-1)/2]>x; i =(i-1)/2)
papq->pq[i]=papq->pq[(i-1)/2];
/*空位向根移动，找插入位置*/
papq->pq[i] =x;n++; /*将x插入*/
}

int isEmpty_heap(PriorityQueue papa){
                           return (papa->n==0);
                           }
                           
void sift(PriorityQueue paqa,  int size,int p)
{
     DataType temp=paqa->pq[p];
     i=p;child=2*i+1;
     while(child<size)
     {
                      if (child<size-1&&paqa->pq[child].key>paqa->pq[child+1].key
                      child=child+1;
                      if(temp<paqa->pq[child].key)
                      {
                                                  paqa->pq[i]=paqa->pq[child];
                                                  i=child;child=2*i+1;                      
                      }
                      else break;
     }
     paqa->pq[i]=temp;
} 

     
     
     
     
     
     }
void removeMin_heap(PriorityQueue papq){
int s;
if(isEmpty_heap(papa)){printf(“Empty!\n”);return;}
s=--paqu->n;
papq->pq[0]=papq->pq[s];
/*先删除,把最后 个元素移动到第 个位置 一个元素移动到第一个位置*/
sift(papq,s,0);
/*把papq所指的完全二叉树从根结点调整为堆*/
}

