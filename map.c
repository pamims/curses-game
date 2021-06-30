#include "map.h"
#include "constants.h"
#include <stdlib.h>


/* - STRUCT DEFINITIONS - */
struct s_tile {
    unsigned char solid:1;
    unsigned char visible:1;
    unsigned char reserved:6;
}; // tile


struct s_tile_map {
    tile array[MAP_HEIGHT][MAP_WIDTH];
    // Not yet implemented
    // struct s_tile_map *previous;
    // struct s_tile_map *next;
}; // tile_map


/* - FUNCTION DEFINITIONS - */
tile_map *make_tile_map() {
    tile_map *map = (tile_map *)malloc(sizeof(tile_map));
    if (!map) return NULL;
    // map->next = NULL;
    // map->previous = NULL;
    return map;
}


int draw_tile_map(const tile_map *map) {
    if (!map) return 0;
    // Not implemented yet
    return 1;
}


int destroy_tile_map(tile_map *map) {
    if (!map) return 0;
    // THIS WILL NEED CHANGED WHEN MULTIPLE LEVELS IMPLEMENTED
    // if (map->previous) free(map->previous);
    // if (map->next) free(map->next);
    free(map);
    return 1;
}
