/* 背包问题的贪心法算法*/

#include<stdio.h>
#include<stdlib.h>

/* 线性表p和w中,按p[i]/w[i]的降序分别存放物体的价格（单位为元）和重量（单位为公斤）;*/
/* m是背包能放的物体总重量，n是物体件数。x存放解向量*/
double knapSack(double* p, double* w, double* x ,double m, int n) {
    int i = 0;
    double s = 0;
    for (i = 0; i < n; i++)
        x[i] = 0;	
    i = 0;
    while (i < n && w[i] < m) {
        m -= w[i];
        s += p[i];
        x[i] = 1;
        i++;
    }
    if (i < n && m > 0) {
        s += p[i]*m/w[i];
        x[i] = m/w[i];		
        i++;
    }
    return s;
}

int main() {
    double m = 0, s = 0, temp = 0;
    double *p, *w, *x;
    int n = 0, i = 0, flag = 1;
    printf("please input the maximum weight of the bag:\nm = ");
    scanf("%f", &m);
    printf("please input the number of objects:\nn = ");
    scanf("%d", &n);
    p = (double*)malloc(n*sizeof(double));
    printf("please input  the prices of all the objects:\n");
    for (i = 0; i < n; i++)
        scanf("%f", p+i);
    w = (double*)malloc(n*sizeof(double));
    printf("please input  the weight of all the objects:\n");
    for (i = 0; i < n; i++)
        scanf("%f", w+i);
    /* 线性表p和w中,按p[i]/w[i]的降序分别存放物体的价格（单位为元）和重量（单位为公斤）;*/
    while (flag != 0) {
        flag = 0;
        for (i = 0; i < n-1; i++) {
            if (p[i]/w[i] < p[i+1]/w[i+1]) 	{
                temp = p[i];
                p[i] = p[i+1];
                p[i+1] = temp;
                temp = w[i];
                w[i] = w[i+1];
                w[i+1] = temp;
                flag = 1;
            }
        }
    }
    x = (double*)malloc(n*sizeof(double));
    s = knapSack(p,w,x,m,n);
    printf("the max value is %f\n",s);/*输出*/
    for(i = 0; i < n; i++) {
        if(x[i] > 0) {
            printf("the x:  %f",x[i]);
            printf("     the p:  %f",p[i]);
            printf("     the w:  %f\n",w[i]);
        }
    }
    return 0;
}







