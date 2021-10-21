#include <stdlib.h>
#include <math.h>
#include "PowerIteration.h"

#define IS_POSITIVE(X) ((X)>0.00001)
void vectorNorm (int n, double *a){
    int i;
    double v=0.0;
    double *p=&a[0];
    double temp;
    for (i = 0; i< n; i++){
        temp=(*(p+i));
        v +=temp *temp;
    }
    v = sqrt(v);

    for (i = 0; i < n; i++){
        a[i] = (*(p+i)) / v;
    }
}

int diffcalc (int n, double *y,double *ay){
    double *p1=&y[0];
    double *p2=&ay[0];
    int i;
    double diff;
    for (i=0; i<n; i++){
        diff = fabs((*(p1+i)) - (*(p2+i)));
        if (IS_POSITIVE(diff)){
            return 0;
        }
    }
    return 1;
}

double powerIteration(struct spmat *A,struct group_g *gr, double *y, int *k, int M){
    double *ay,*final;
    int diff=0;
    int i;
    int n=gr->n;
    double norm,up,down,eigen,temp;
    double *p2;

    ay = (double*)malloc(n*sizeof(double));
    p2=&ay[0];
    norm=normcalc (A,k,M);
    while (diff==0){
        Bhat_mult(A,gr,y,k,M,ay);
        matrixShifting(ay,y,norm,n);
        vectorNorm (n,ay);
        diff=diffcalc(n,y,ay);
        for (i=0;i<n;i++){
            y[i]=(*(p2+i));
        }
    }
    free(ay);
    up=0;
    down=0;
    /*calculate leading eigen value*/
    final=(double*)malloc(n*sizeof(double));
    Bhat_mult(A,gr,y,k,M,final);
    for (i=0;i<n;i++){
        temp=y[i];
        up+=final[i]*temp;
        down+=temp*temp;
    }
    eigen=(up/down);
    free(final);
    return eigen;
}
