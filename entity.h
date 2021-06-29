#ifndef ENTITY_H
#define ENTITY_H

// Used to store all game entities drawn on screen
typedef struct {
    int x, y;
    char symbol;
} entity;


/* - FUNCTION PROTOTYPES - */
// Adds dx and dy to the entity's x and y values respectively
int move_entity(entity *ent, int dx, int dy);
// Draws the entity's symbol to the screen at its x,y coordinate
int draw_entity(const entity *ent);


#endif //ENTITY_H
