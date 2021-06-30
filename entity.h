#ifndef ENTITY_H
#define ENTITY_H

// Used to store all game entities drawn on screen
typedef struct s_entity entity;


/* - FUNCTION PROTOTYPES - */
// Creates an entity at the given x,y coordinate with the given symbol
entity *make_entity(int x, int y, char symbol);
// Adds dx and dy to the entity's x and y values respectively
int move_entity(entity *ent, int dx, int dy);
// Draws the entity's symbol to the screen at its x,y coordinate
int draw_entity(const entity *ent);


#endif //ENTITY_H
