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

typedef struct s_room {
    int x1, y1, x2, y2;
} room;

struct s_tile_map {
    tile_mask tiles[MAP_HEIGHT][MAP_WIDTH];
    room *rooms[MAX_ROOM_COUNT];
};

/* - MAP IMAGE CONSTANTS - */
static const unsigned char V_LINE   = (unsigned char)179; // '|';
static const unsigned char H_LINE   = (unsigned char)196; // a dash character --
static const unsigned char T_LEFT   = (unsigned char)218; // a corner character
static const unsigned char B_LEFT   = (unsigned char)192; // a corner character
static const unsigned char T_RIGHT  = (unsigned char)191; // a corner character
static const unsigned char B_RIGHT  = (unsigned char)217; // a corner character
static const unsigned char FLOOR    = (unsigned char)250; //'.';


/* - HELPER FUNCTION PROTOTYPES - */
room *make_room(int, int, size_t, size_t);
int add_room_to_map(tile_map *, const room *);
int draw_room_walls(const room *, const tile_map *);
int draw_h_line(int, int, int, const tile_map *);
int draw_v_line(int, int, int, const tile_map *);
int room_collision(room *, room *);
int destroy_room(room *);


/* - FUNCTION DEFINITIONS - */
tile_map *make_tile_map(void) {
    tile_map *map = (tile_map *)malloc(sizeof(tile_map));
    if (!map) return NULL;
    for (int row = 0; row < MAP_HEIGHT; row++)
        for (int col = 0; col < MAP_WIDTH; col++)
            map->tiles[row][col] = TM_SOLID;
    for (int i = 0; i < MAX_ROOM_COUNT; i++)
        map->rooms[i] = NULL;
    return map;
}

int generate_map_rooms(tile_map *map) {
    if (!map) return 0;
    //create rooms that intersect on purpose to test collision function
    map->rooms[0] = make_room(25, 10, 20, 8);
    map->rooms[1] = make_room(35, 15, 15, 6);
    if (room_collision(map->rooms[0], map->rooms[1])) {
        destroy_room(map->rooms[1]);
        map->rooms[1] = NULL;
    }
    for (int i = 0; i < MAX_ROOM_COUNT; i++) {
        if (!map->rooms[i]) break;
        add_room_to_map(map, map->rooms[i]);
    }
    return 1;
}

int draw_tile_map(const tile_map *map) {
    if (!map) return 0;
    for (int i = 0; i < MAX_ROOM_COUNT; i++) {
        if (!map->rooms[i]) break;
        draw_room_walls(map->rooms[i], map);
    }
    for (int row = 0; row < MAP_HEIGHT; row++)
        for (int col = 0; col < MAP_WIDTH; col++)
            if (map->tiles[row][col] == TM_VISIBLE)
                mvaddch(row, col, FLOOR);
    return 1;
}

int destroy_tile_map(tile_map *map) {
    if (!map) return 0;
    for (int i = 0; i < MAX_ROOM_COUNT; i++)
        if (map->rooms[i]) free(map->rooms[i]);
    free(map);
    return 1;
}

int map_collision(int x, int y, const tile_map *map) {
    if (!map || !(map->tiles[y][x] & (TM_SOLID | TM_OCCUPIED)))
        return 0;
    return 1;
}


/* - HELPER FUNCTION DEFINITIONS - */
room *make_room(int x, int y, size_t width, size_t height) {
    room *r = (room *)malloc(sizeof(room));
    if (!r) return NULL;
    r->x1 = x;
    r->y1 = y;
    r->x2 = x + width - 1;
    r->y2 = y + height - 1;
    return r;
}

int add_room_to_map(tile_map *map, const room *r) {
    if (!map || !r) return 0;
    for (int row = r->y1; row <= r->y2; row++)
        for (int col = r->x1; col <= r->x2; col++)
            map->tiles[row][col] |= TM_VISIBLE;
    for (int row = r->y1 + 1; row < r->y2; row++)
        for (int col = r->x1 + 1; col < r->x2; col++)
            map->tiles[row][col] &= ~TM_SOLID;
    return 1;
}

int draw_room_walls(const room *r, const tile_map *map) {
    if (r->x1 < 0 || r->x2 >= MAP_WIDTH || r->y1 < 0 || r->y2 >= MAP_HEIGHT)
        return 0;
    if (map->tiles[r->y1][r->x1] & TM_VISIBLE) mvaddch(r->y1, r->x1, T_LEFT);
    if (map->tiles[r->y2][r->x1] & TM_VISIBLE) mvaddch(r->y2, r->x1, B_LEFT);
    if (map->tiles[r->y1][r->x2] & TM_VISIBLE) mvaddch(r->y1, r->x2, T_RIGHT);
    if (map->tiles[r->y2][r->x2] & TM_VISIBLE) mvaddch(r->y2, r->x2, B_RIGHT);
    draw_h_line(r->x1 + 1, r->x2 - 1, r->y1, map);
    draw_h_line(r->x1 + 1, r->x2 - 1, r->y2, map);
    draw_v_line(r->y1 + 1, r->y2 - 1, r->x1, map);
    draw_v_line(r->y1 + 1, r->y2 - 1, r->x2, map);
    return 1;
}

int draw_h_line(int x1, int x2, int row, const tile_map *map) {
    int x[2] = { (x1 < x2 ? x1 : x2), (x1 > x2 ? x1 : x2) };
    if (x[0] < 0 || x[1] >= MAP_WIDTH || row < 0 || row >= MAP_HEIGHT)
        return 0;
    for (int col = x[0]; col <= x[1]; col++)
        if (map->tiles[row][col] & TM_VISIBLE) mvaddch(row, col, H_LINE);
    return 1;
}

int draw_v_line(int y1, int y2, int col, const tile_map *map) {
    int y[2] = { (y1 < y2 ? y1 : y2), (y1 > y2 ? y1 : y2) };
    if (y[0] < 0 || y[1] >= MAP_HEIGHT || col < 0 || col >= MAP_WIDTH)
        return 0;
    for (int row = y[0]; row <= y[1]; row++)
        if (map->tiles[row][col] & TM_VISIBLE) mvaddch(row, col, V_LINE);
    return 1;
}

int room_collision(room *r1, room *r2) {
    return (r1->x1 <= r2->x2 && r1->x2 >= r2->x1 &&
            r1->y1 <= r2->y2 && r1->y2 >= r2->y1);
}

int destroy_room(room *r) {
    if (!r) return 0;
    free(r);
    return 1;
}
