#ifndef MAP_H
#define MAP_H


/* - STRUCTS - */
typedef struct s_tile_map tile_map;


/* - FUNCTION PROTOTYPES - */
tile_map *make_tile_map(void);                  // Allocate a map
int generate_map_rooms(tile_map *map);          // Put rooms on the map
int draw_tile_map(const tile_map *map);         // Draws the map to the screen
int destroy_tile_map(tile_map *map);            // Frees all map memory
int map_collision(int x, int y, tile_map *map); // Returns true if map collision


#endif // MAP_H
