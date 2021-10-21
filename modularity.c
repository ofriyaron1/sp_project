#include <stdlib.h>
#include "modularity.h"

#define IS_POSITIVE(X) ((X)>0.00001)

void B_mult(struct spmat *A,struct group_g *gr,double *v,int *k, int M, double *result) {
    int i,j,row,col,deg_row;
    double temp;
    sp_mult(A,k,gr,v, result);
    for (i = 0; i <gr->n; i++) {
        temp=0;
        row=gr->g[i];
        deg_row=k[row];
        if (IS_POSITIVE(deg_row)) {
            for (j = 0; j < gr->n; j++) {
                col = gr->g[j];
                temp += ((deg_row * k[col] / (double) M) * v[j]);
            }
            result[i]-=temp;
        }
    }
}

void Bhat_mult(struct spmat *A,struct group_g *gr,double *v,int *k, int M, double *result) {
    int i;
    double *f;
    double *vec1;

    f=(double *)malloc(sizeof(double)*gr->n);
    vec1=(double *)malloc(sizeof(double)*gr->n);

    B_mult(A,gr,v,k,M,result);
    for(i=0;i<gr->n;i++){
        vec1[i]=1;
    }
    B_mult(A,gr,vec1,k,M,f);
    free(vec1);
    for(i=0;i<gr->n;i++){
        result[i]-=f[i]*v[i];
    }
    free(f);
}
