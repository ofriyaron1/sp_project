#include <math.h>
#include "MatrixShifting.h"

double normcalc (struct spmat *A,const int *k, int M){
    int n=A->n;
    int i,j,l,col,k_i;
    double maxcol=0;
    double temp,temp1;
    for (i=0;i<n;i++){
        k_i=k[i];
        temp=0;
        for (j=0;j<n;j++){
            temp+=(k_i*k[j]/(double)M);
        }
        for (l= A->rowptr[i]; l< A->rowptr[i + 1]; l++) {
            col=A->colind[l];
            temp1=k[i]*k[col]/(double )M;
            temp= temp-temp1+fabs(1.0-temp1);
        }
        if (temp>maxcol){
        maxcol=temp;
        }
     }
    return maxcol;
}


void matrixShifting(double *bhatmult,const double *v,double norm,int n){
    int i;
    for(i=0;i<n;i++){
        bhatmult[i]+=(v[i]*norm);
    }
}
