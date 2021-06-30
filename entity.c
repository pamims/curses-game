#include "entity.h"
#include <curses.h>
#include <stdlib.h>

/* - STRUCT DEFINITIONS - */
struct s_entity {
    int x, y;
    char symbol;
};


/* - FUNCTION DEFINITIONS - */
entity *make_entity(int x, int y, char symbol) {
    entity *ent = (entity *)malloc(sizeof(entity));
    if (!ent) return NULL;
    ent->x = x;
    ent->y = y;
    ent->symbol = symbol;
    return ent;
}


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
