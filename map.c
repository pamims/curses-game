#include "map.h"
#include "constants.h"
#include <stdlib.h>
#include <curses.h>
#include <assert.h>


/* - STRUCT DEFINITIONS - */
// Represents a single tile on the map
typedef struct s_tile {
    unsigned char properties;
} tile;
// typedef unsigned char tile;

struct s_tile_map {
    tile array[MAP_HEIGHT][MAP_WIDTH];
}; // tile_map

typedef struct s_room {
    int x1, y1, x2, y2;
    //size_t width, height;
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
    r->x1 = x;
    r->y1 = y;
    r->x2 = x + width - 1;
    r->y2 = y + height - 1;
    return r;
}

tile_map *make_tile_map(void) {
    tile_map *map = (tile_map *)malloc(sizeof(tile_map));
    if (!map) return NULL;
    for (int row = 0; row < MAP_HEIGHT; row++)
        for (int column = 0; column < MAP_WIDTH; column++)
            map->array[row][column] = make_tile(TF_NONE);
    return map;
}

int generate_map_rooms(tile_map *map) {
    if (!map) return 0;
    // Magic numbers test room until random generation is implemented...
    room *r = make_room(25, 10, 20, 8);
    if (!r) return 0;
    unsigned char tile_properties = TF_NONE;
    for (int row = r->y1; row <= r->y2; row++)
        for (int column = r->x1; column <= r->x2; column++) {
            tile_properties = TF_VISIBLE;
            if (row == r->y1 || row == r->y2)
                tile_properties |= TF_SOLID;
                // -- make it a ceiling or floor
            else if (column == r->x1 || column == r->x2)
                tile_properties |= TF_SOLID;
                // -- make it a wall
            // More map construction logic
            map->array[row][column].properties = tile_properties;
            tile_properties = TF_NONE;
        }
    // don't forget to clean up the room pointer
    // might end up returning pointers later for a room list data structure...
    free(r);
    return 1;
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

int map_collision(int x, int y, tile_map *map) {
    if (!map || !(map->array[y][x].properties & (TF_SOLID | TF_OCCUPIED)))
        return 0;
    return 1;
}
