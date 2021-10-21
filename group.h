/**
 * Group Summary:
 *
 * This module creates the structure group_g for each group in the division and can free it using
 * the gr_free function.
 *
 */

#ifndef _GROUP_H
#define _GROUP_H
typedef struct group_g{
    int n;
    int *g;
} group_g;

void gr_free(struct group_g *gr) ;

#endif
