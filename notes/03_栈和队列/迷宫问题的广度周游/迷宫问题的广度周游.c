/* 队列的顺序表示：函数定义 */
#include "squeue.h"
#include <stdio.h>
#include <stdlib.h>

/*创建一个空队列*/
PSeqQueue  createEmptyQueue_seq( void ) {  
    PSeqQueue paqu = (PSeqQueue)malloc(sizeof(struct SeqQueue));
    if (paqu== NULL )
        printf("Out of space!! \n");
    else
        paqu->f = paqu->r = 0;
    return paqu;
}

/*判队列是否为空队列*/
int  isEmptyQueue_seq( PSeqQueue paqu ) {
    return paqu->f == paqu->r;
}

/* 在队列中插入一元素x */
void  enQueue_seq( PSeqQueue paqu, DataType x ) {
    if( (paqu->r + 1) % MAXNUM == paqu->f  )
        printf( "Full queue.\n" );
    else 	{
        paqu->q[paqu->r] = x;
        paqu->r = (paqu->r + 1) % MAXNUM;
    }
}

/* 删除队列头部元素 */
void  deQueue_seq( PSeqQueue paqu ) {
    if( paqu->f == paqu->r )
        printf( "Empty Queue.\n" );
    else
        paqu->f = (paqu->f + 1) % MAXNUM;
}

/* 对非空队列,求队列头部元素 */
DataType  frontQueue_seq( PSeqQueue paqu ) {
    return paqu->q[paqu->f];
}



int maze[M][N]=
{
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,1,0,0,0,1,0,1},
    {1,0,0,1,0,0,0,1,0,1},
    {1,0,0,0,0,1,1,0,0,1},
    {1,0,1,1,1,0,0,0,0,1},
    {1,0,0,0,1,0,0,0,0,1},
    {1,0,1,0,0,0,1,0,0,1},
    {1,0,1,1,1,0,1,1,0,1},
    {1,1,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};
 int direction[][2]={{0,1},{1,0},{0,-1},{-1,0}};   
 
 void print_maze(int xo,int yo){
	printf("the node is: (%d,%d) \n",xo,yo);
	int x ,y ;
	int pre=maze[xo][yo];
	while(pre!=-1){
		x=pre/M;
		y=pre%M; 
		printf("the node is: (%d,%d)\n",  x,y);
		pre=maze[x][y];
	}

}
	   
 

void mazePath(int x1, int y1,int x2,int y2){
	int i,j,k,g,h; 
	int pre; int x,y;
	PSeqQueue plqu;  
	DataType element;
	 plqu = createEmptyQueue_seq( );
	maze[x1][y1] = -1;
	element.x = x1;  element.y = y1;  
	enQueue_seq(plqu,element);
	while (! isEmptyQueue_seq(plqu )){
		element =  frontQueue_seq( plqu );
		deQueue_seq(   plqu ) ;
		i = element.x;   j = element.y;
		for(k=0;k<=3;k++)
		{
			g=i+direction[k][0];
			h=j+direction[k][1];
			if(maze[g][h]==0)
			{
				maze[g][h]=i*N+j;
				if(g==x2 && h==y2) 
				{
					print_maze(x2,  y2);
					return;
				} 
				element.x=g;
				element.y=h;
				enQueue_seq(plqu,element);
			}
		}
			
			
			
	}
	
}





    
int main()
{
   
   
   mazePath(1, 1, 4,8); 
   getchar();
   return 0;


}
