#ifndef MAP_H
#define MAP_H


/* - STRUCTS - */
// Represents a single tile of a map
typedef struct s_tile tile;
typedef struct s_tile_map tile_map;


/* - FUNCTION PROTOTYPES - */
// Makes a map of tiles with the given dimensions
tile_map *make_tile_map(void);
// Draws the map to the screen
int draw_tile_map(const tile_map *map);
// Frees all map memory
int destroy_tile_map(tile_map *map);


#endif // MAP_H
