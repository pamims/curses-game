#ifndef ENTITY_H
#define ENTITY_H

// Used to store all game entities drawn on screen
typedef struct s_entity entity;


/* - FUNCTION PROTOTYPES - */
entity *make_entity(int x, int y, char image);  // Create an entity at x,y
int move_entity(entity *ent, int dx, int dy);   // Move entity by dx,dy
int draw_entity(const entity *ent);             // Draw entity at its position
int destroy_entity(entity *ent);                // Frees entity memory
int entity_x_position(entity *ent);             // Gets entity x position
int entity_y_position(entity *ent);             // Gets entity y position


#endif //ENTITY_H
