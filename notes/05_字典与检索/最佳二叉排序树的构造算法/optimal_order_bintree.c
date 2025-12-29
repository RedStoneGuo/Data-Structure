/* 最佳二叉排序树是具有最佳检索效率的二叉排序树,
本程序提供了最佳二叉排序树的构造方法*/

#include<stdio.h>
#define MAXVALUE 1e8
#define N 10

void opticBTree(float p[], float q[], float *c[], float *w[], int *r[], int n) {
    int k0, i, j, k, m; float min;

    for (i = 0; i <= n; i++)                /* 数组下三角清零 */
        for (j = 0; j <= i; j++)
            c[i][j] = w[i][j] = r[i][j] = 0;

    for (i = 0; i <= n; i++) {              /* 计算w[i][j] */
        w[i][i] = q[i];
        for (j = i+1; j <= n; j++)
            w[i][j] = w[i][j-1] + p[j] + q[j];
    }

    for (j = 1; j <= n; j++) {               /* 计算一个内部结点的最佳二叉排序树 */
        c[j-1][j] = w[j-1][j]; r[j-1][j] = j;
    }

    for (m = 2; m <= n; m++)                 /* 计算m个结点的最佳二叉排序树 */
        for (i = 0; i <= n-m; i++) {
            j = i+m; min = MAXVALUE; k0 = i+1;

            for (k = i+1; k <= j; k++)  /* 在i<k≤j范围内，找出使C(i,k-1)+C(k,j)最小的k。*/
                if ( c[i][k-1] + c[k][j] < min) {
                    min = c[i][k-1] + c[k][j]; k0 = k;
                }
            c[i][j] = w[i][j] + min; 
            r[i][j] = k0;
        }
}

int main() {
    float p[] = {0,1,5,4,3};
    float q[] = {5,4,3,2,1};
    float *cc[N];
    float *ww[N];
    int *rr[N];
    float c[N][N], w[N][N];
    int r[N][N];
    int i, j;
    for(i = 0; i < N; i++) {
        cc[i] = c[i];
        ww[i] = w[i];
        rr[i] = r[i];
    }
    opticBTree(p, q, cc, ww, rr, 4);
    for (i = 0; i < 4; i++) {
        for(j = i+1; j <= 4; j++)
            printf("%d ", r[i][j]);/*打印数组r*/
        putchar('\n');
    }
    for (i = 0; i <= 4; i++) {
        for (j = i; j <= 4; j++)
            printf("%.0f ", w[i][j]);/*打印数组w*/
        putchar('\n');
    }
    for (i = 0; i < 4; i++) {
        for (j = i+1; j <= 4; j++)
            printf("%.0f ", c[i][j]);/*打印数组c*/
        putchar('\n');
    }
    getchar();
    return 0;
}
