/**
 * Algorithms Summary:
 *
 * The container supports all the following functions:
 *
 * algorithm3	- Divides a network into modularity groups by repeating algorithm2, return the division.
 * algorithm2	- Divides a network into two groups.
 * algorithm4	- optimize a division to the maximal modularity.
 * Score_Update-helper function to algorithm4 which calculate the modified score after moving a vertex.
 * argmax_score- helper function to algorithm4 which finds the vertex with the maximal score.
 * mult_stbs	- computes the modularity.
 *
 */

#ifndef PROJECT_ALGORITHMS_H
#define PROJECT_ALGORITHMS_H

#include "spmat.h"
#include "division.h"
#include "PowerIteration.h"

struct division* algorithm3(struct spmat *A, int *k, int M);
struct gdiv* algorithm2(struct spmat *A,struct group_g *g, int *k, int M);
void algorithm4 (struct spmat *A,struct group_g *g,double *s, int *k, int M);
void Score_Update(int move_vertex,spmat *A,struct group_g *g,double *s,double *score, int *k, int M);
int argmax_score (double *arr,int *unmoved, int n);
double mult_stbs(struct spmat *A,struct group_g *g, int *k, int M, double *s);


#endif
