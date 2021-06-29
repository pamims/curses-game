#include "entity.h"
#include <curses.h>


/* - FUNCTION DEFINITIONS - */
int move_entity(entity *ent, int dx, int dy) {
    if (!ent) return 0;
    ent->x += dx;
    ent->y += dy;
    return 1;
}


int draw_entity(const entity *ent) {
    if (!ent) return 0;
    mvaddch(ent->y, ent->x, ent->symbol);
    return 1;
}
