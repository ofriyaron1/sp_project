/**
 * Modularity Summary:
 *
 * This module contains the functions that are required for modularity maximization:
 *
 * B_mult 			- calculates the multiplication of modularity matrix B[g] such that Bij = Aij−(kikj/M) with a vector.
 * Bhat_mult		- calculates the multiplication of matrix B_hat[g] with a vector.
 *
 */

#ifndef PROJECT_MODULARITY_H
#define PROJECT_MODULARITY_H

#include "spmat.h"
#include "group.h"
void B_mult(struct spmat *A,struct group_g *gr,double *v,int *k, int M, double *result);
void Bhat_mult(struct spmat *A,struct group_g *gr,double *v, int *k, int M, double *result);

#endif
