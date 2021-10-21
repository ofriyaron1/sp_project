/**
 *
 * spmat Summary:
 *
 * This module creates the spare matrix A and includes its following functions:
 *
 * add_row	- Adds row i to the sparse matrix. Called n times
 * sp_free	- Frees all resources used by A
 * sp_mult	- Multiplies A[g] by vector v, into result (pre-allocated)
 *
 *
 */

#ifndef _SPMAT_H
#define _SPMAT_H

#include "group.h"

typedef struct spmat {
    /* Matrix size (n*n) */
    int n;
    int *rowptr, *colind;
} spmat;

/* Allocates a new arrays sparse matrix of size n with nnz non-zero elements */
struct spmat *spmat_allocate_array(int n, int nnz);
/* Adds row i to the sparse matrix. Called n times*/
void add_row(struct spmat *A,const int *row, int ki, int lastcol);
/* Frees all resources used by A */
void sp_free(struct spmat *A);
/* Multiplies A[g] by vector v, into result (pre-allocated) */
void sp_mult(struct spmat *A,const int *k, struct group_g *gr,const double *v, double *result);

#endif
