/**
 * MatrixShift Summary:
 *
 * This module contains the functions that are required to ensure that an
 * eigenpair is the leading eigenpair, by using the following matrix shift
 * according to the following explanation:
 * Let C be a matrix with the eigenvalues {λ1, . . . , λn}, and let the
 * 1-norm of C be the sum of its largest column.
 * Let C' be the sum of C and the product of 1-norm of C and the identity matrix,
 * then C' has the same eigenvectors as C and the eigenvalues of C' are
 * {λ1 + ||C||1, . . . , λn + ||C||1}.
 * Thus, the dominant eigenpair of C' is (λ1 + ||C||1, v1), and the
 * leading eigenpair of C is (λ1, v1).
 *
 * The functions in the module:
 *
 * normcalc		- calculates the 1-norm of a given matrix
 * matrixShifting	- shifts the matrix according to the explanation given above
 *
 */

#ifndef PROJECT_MATRIXSHIFTING_H
#define PROJECT_MATRIXSHIFTING_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "spmat.h"
#include "modularity.h"

double normcalc (struct spmat *A,const  int *k, int M);
void matrixShifting(double *bhatmult, const double *v,double norm,int n);
#endif
