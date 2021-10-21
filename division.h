/**
 * Division Summary:
 *
 * This module creates the structures Linked-List and g-division and includes
 * the functions that free these structures:
 *
 * ll_free 		- frees the linked-list
 * gdiv_free	- frees the g-division
 *
 */

#ifndef PROJECT_DIVISION_H
#define PROJECT_DIVISION_H

#include "group.h"

typedef struct LinkedList{
    group_g *arr;
    struct LinkedList *next;
}Linkedlist;

void ll_free(Linkedlist *l);

typedef struct gdiv{
    group_g *g1;
    group_g *g2;
}gdiv;

void gdiv_free(gdiv *g);

typedef struct division{
    struct LinkedList *final_division;
    int NumOfGroups;
}division;

void division_free(division *O);
#endif
