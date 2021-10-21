/**
 * PowerIteration Summary:
 *
 * This module finds the dominant eigenvector using the following functions:
 *
 * vectorNorm 	- normalizes a vector
 * diffcalc		- helper function for powerIteration
 * powerIteration	- finds the dominant eigenvector, the eigenvector with
 * the largest absolute eigenvalue, using Power-Iteration method.
 */

#ifndef PROJECT_POWERITERATION_H
#define PROJECT_POWERITERATION_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "spmat.h"
#include "modularity.h"
#include "MatrixShifting.h"

void vectorNorm (int n, double []);
int diffcalc (int n, double [],double []);
double powerIteration(struct spmat *A,struct group_g *gr, double *y, int *k, int M);

#endif
