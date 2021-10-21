#include "division.h"
#include <stddef.h>
#include <stdlib.h>


void ll_free(Linkedlist *l) {
    Linkedlist *temp;
    if (l != NULL) {
        while (l->next != NULL) {
            gr_free(l->arr);
            temp=l;
            l=l->next;
            free(temp);
        }
    }
}

void gdiv_free(gdiv *g) {
    if (g != NULL) {
        gr_free(g->g1);
        gr_free(g->g2);
        free(g);
    }
}

void division_free(division *O){
    ll_free(O->final_division);
}
