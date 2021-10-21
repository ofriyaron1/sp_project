#include <stddef.h>
#include <stdlib.h>
#include "group.h"


void gr_free(struct group_g *gr) {
    if (gr != NULL) {
        free(gr->g);
        free(gr);
    }
}
