#include "map.h"
#include "constants.h"
#include <stdlib.h>
#include <curses.h>
#include <assert.h>


/* - STRUCT DEFINITIONS - */
struct s_tile {
    unsigned char properties;
}; // tile
// typedef unsigned char tile;

struct s_tile_map {
    tile array[MAP_HEIGHT][MAP_WIDTH];
    // Not yet implemented
    // struct s_tile_map *previous;
    // struct s_tile_map *next;
}; // tile_map

typedef struct s_room {
    int x, y;
    size_t width, height;
} room;


/* - FUNCTION DEFINITIONS - */
// return tile while the tile definition is smaller than a pointer
tile make_tile(unsigned char properties) {
    tile t;
    t.properties = properties;
    return t;
}

room *make_room(int x, int y, size_t width, size_t height) {
    // -- do the asserts --
    room *r = (room *)malloc(sizeof(room));
    if (!r) return NULL;
    r->x = x;
    r->y = y;
    r->width = width;
    r->height = height;
    return r;
}

tile_map *make_tile_map() {
    tile_map *map = (tile_map *)malloc(sizeof(tile_map));
    if (!map) return NULL;
    for (int row = 0; row < MAP_HEIGHT; row++)
        for (int column = 0; column < MAP_WIDTH; column++)
            map->array[row][column] = make_tile(TF_NONE);
    room *r = make_room(25, 10, 20, 8);
    for (int row = r->y; row < r->y + r->height; row++)
        for (int col = r->x; col < r->x + r->width; col++) {
            map->array[row][col].properties = TF_VISIBLE;
        }
    for (int row = 0; row < MAP_HEIGHT; row++)
        for (int col = 0; col < MAP_WIDTH; col++) {
            unsigned char properties = map->array[row][col].properties;
            if (properties & TF_VISIBLE) {
                if (map->array[row][col + 1].properties == TF_NONE ||
                    map->array[row][col - 1].properties == TF_NONE ||
                    map->array[row + 1][col].properties == TF_NONE ||
                    map->array[row - 1][col].properties == TF_NONE) {
                    map->array[row][col].properties |= TF_SOLID;
                }
            }
        }
    return map;
}


int draw_tile_map(const tile_map *map) {
    if (!map) return 0;
    unsigned char tile_properties;
    for (int row = 0; row < MAP_HEIGHT; row++)
        for (int column = 0; column < MAP_WIDTH; column++) {
            tile_properties = map->array[row][column].properties;
            if (!(tile_properties & TF_VISIBLE) ||
                tile_properties & TF_OCCUPIED) {
                continue;
            }
            mvaddch(row, column, tile_properties & TF_SOLID ? '#' : '.');
        }
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
