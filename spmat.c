#include <stddef.h>
#include <stdlib.h>
#include "spmat.h"

struct spmat *spmat_allocate_array(int n, int nnz) {
    spmat *sp;
    sp = (struct spmat *) malloc(sizeof(struct spmat));
    if (!sp) {
        return NULL;
    }
    sp->n = n;
    sp->rowptr = (int *) malloc((n + 1) *sizeof(int));
    if (!sp->rowptr) {
        sp_free(sp);
        return NULL;
    }
    sp->colind = (int *) malloc(nnz*sizeof(int));
    if (!sp->colind) {
        free(sp->rowptr);
        sp_free(sp);
        return NULL;
    }
    return sp;
}

void add_row(struct spmat *A, const int *row, int k_i, int lastcol) {
    int j, ind;
    for (j = 0; j < k_i; j++) {
        ind = row[j];
        A->colind[j + lastcol] =ind;
    }
}

void sp_free(struct spmat *A) {
    if (A != NULL) {
        free(A->colind);
        free(A->rowptr);
        free(A);
    }
}

void sp_mult(struct spmat *A,const int *k, struct group_g *gr, const double *v, double *result) {
    int i,j,r,ind,col;
    double temp;
    int *a,*gg;
    for (i = 0; i < gr->n; i++) {
        temp = 0;
        j=0;
        r=0;
        ind=gr->g[i];
        col=A->rowptr[ind];
        a=&A->colind[col];
        gg=gr->g;
        while(j<k[ind] && r<gr->n) {
            if (*a < *gg) {
                a = a + 1;
                j++;
            }
            else if (*gg < *a) {
                gg = gg + 1;
                r++;
            }
            else{
                temp += v[r];
                a = a + 1;
                gg = gg + 1;
                j++;
                r++;
            }
        }
        result[i] = temp;
    }
}
