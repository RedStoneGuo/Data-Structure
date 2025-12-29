/*队列链接表示：函数定义*/

#include<stdio.h>
#include<stdlib.h>

#include "lqueue.h"

/*创建一个空队列*/
PLinkQueue  createEmptyQueue_link( ) { 	
    PLinkQueue plqu = (PLinkQueue )malloc(sizeof(struct LinkQueue));
    if (plqu != NULL)
        plqu->f = plqu->r = NULL;
    else
        printf("Out of space!! \n");
  		
    return (plqu);
}

/*判断链接表示队列是否为空队列*/ 
int  isEmptyQueue_link( PLinkQueue plqu ) {
    return (plqu->f == NULL);
}


/*进队列*/
void  enQueue_link( PLinkQueue plqu, DataType x) { 
    PNode p = (PNode )malloc( sizeof( struct Node ) );
    if ( p == NULL  )
        printf("Out of space!");
    else { 
        p->info = x;
        p->link = NULL;
        if (plqu->f == NULL)
            plqu->f = p;
        else
            plqu->r->link = p;

        plqu->r = p;
    }
}

/*出队列*/
void  deQueue_link( PLinkQueue plqu ) { 
    PNode   p;
    if( plqu->f == NULL )
        printf( "Empty queue.\n " );
    else { 
        p = plqu->f;
        plqu->f = plqu->f->link;
        free(p);
    }
}

/* 在非空队列中求队头元素 */
DataType  frontQueue_link( PLinkQueue plqu ) { 
    return (plqu->f->info);
}

