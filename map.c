#include "map.h"
#include "constants.h"
#include <stdlib.h>
#include <curses.h>


/* - STRUCT DEFINITIONS - */
// Represents a single tile on the map
typedef unsigned char tile_mask;
static const tile_mask TM_NONE      = (tile_mask)0u;
static const tile_mask TM_SOLID     = (tile_mask)1u;
static const tile_mask TM_VISIBLE   = (tile_mask)2u;
static const tile_mask TM_OCCUPIED  = (tile_mask)4u;

struct s_tile_map {
    tile_mask tiles[MAP_HEIGHT][MAP_WIDTH];
};

typedef struct s_room {
    int x1, y1, x2, y2;
} room;


/* - FUNCTION DEFINITIONS - */
room *make_room(int x, int y, size_t width, size_t height) {
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
            map->tiles[row][column] = TM_NONE;
    return map;
}

int generate_map_rooms(tile_map *map) {
    if (!map) return 0;
    // Magic numbers test room until random generation is implemented...
    room *r = make_room(25, 10, 20, 8);
    if (!r) return 0;
    tile_mask mask = TM_NONE;
    for (int row = r->y1; row <= r->y2; row++)
        for (int column = r->x1; column <= r->x2; column++) {
            mask = TM_VISIBLE;
            if (row == r->y1 || row == r->y2 ||
                column == r->x1 || column == r->x2) {
                mask |= TM_SOLID;
            }
            map->tiles[row][column] = mask;
            mask = TM_NONE;
        }
    free(r);
    return 1;
}

int draw_tile_map(const tile_map *map) {
    if (!map) return 0;

    tile_mask mask = TM_NONE;
    for (int row = 0; row < MAP_HEIGHT; row++)
        for (int column = 0; column < MAP_WIDTH; column++) {
            mask = map->tiles[row][column];
            if (!(mask & TM_VISIBLE) || mask & TM_OCCUPIED)
                continue;
            mvaddch(row, column, mask & TM_SOLID ? '#' : '.');
        }

    return 1;
}

int destroy_tile_map(tile_map *map) {
    if (!map) return 0;
    free(map);
    return 1;
}

int map_collision(int x, int y, tile_map *map) {
    if (!map || !(map->tiles[y][x] & (TM_SOLID | TM_OCCUPIED)))
        return 0;
    return 1;
}
