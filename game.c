#include "game.h"
#include "entity.h"
#include "map.h"
#include "constants.h" // remove when implement messages
#include <curses.h>
#include <stdlib.h>
#include <string.h>


/* - STATIC GLOBAL VARIABLES - */
static struct global_game_state {
    entity *player;
    tile_map *map;
    int input;
    int step_count;
    char message[TERMINAL_COLUMNS * RESERVED_ROWS];
} game_state = { NULL, NULL, '\0', 0, {'\0'} };


/* - HELPER FUNCTION PROTOTYPES - */
// - init_game() helpers
int init_curses(void);              // Sets up curses
int init_game_state(void);          // Sets up the initial game state

// - game_loop() helpers
int get_input(void);                // Get player input
int update_game_state(void);        // Update the game state
int draw_screen(void);              // Draw the screen

// - clean_up() helpers
int clean_game_state(void);         // Frees all game state memory.

// - helper helpers
void print_game_message(void);      // Temporary error output function
int set_game_message(const char *); // Sets game_state.message


/* - FUNCTION DEFINITIONS - */
int init_game(void) {
    if (!init_curses() ||
        !init_game_state() || // make_player and make_map happen here
        !generate_map_rooms(game_state.map)) {
        return 0;
    }
    draw_screen();
    return 1;
}

int game_loop(void) {
    while (game_state.input != 'Q') {
        get_input();
        if (!update_game_state()) return 0;
        draw_screen();
    }
    return 1;
}

int clean_up(void) {
    clean_game_state();
    endwin();
    return 1;
}


/* - HELPER FUNCTION DEFINITIONS - */
// - init_game() helpers
int init_curses(void) {
    initscr();
    resize_term(TERMINAL_ROWS, TERMINAL_COLUMNS);
    noecho();
    curs_set(0);
    raw();
    return 1;
}

int init_game_state(void) {
    game_state.player = make_entity(30, 15, '@');
    game_state.map = make_tile_map();
    set_game_message("Use WASD to move around.");
    if (!game_state.player || !game_state.map) {
        clean_game_state();
        return 0;
    }
    return 1;
}

// - game_loop() helpers
int get_input(void) {
    napms(50);
    flushinp();
    game_state.input = getch();
    return 1;
}

int update_game_state(void) {
    int dx = 0;
    int dy = 0;
    set_game_message(++game_state.step_count > 100 ? "Press Q to exit :)" : "");
    switch(game_state.input) {
        case KEY_LEFT:
        case 'a':
            dx = -1;
            break;
        case KEY_RIGHT:
        case 'd':
            dx = 1;
            break;
        case KEY_DOWN:
        case 's':
            dy = 1;
            break;
        case KEY_UP:
        case 'w':
            dy = -1;
            break;
        case 'q':
            game_state.input = 'Q';
        case 'Q':
            return 0;
        default:
            break;
    }
    if (map_collision(entity_x_position(game_state.player) + dx,
        entity_y_position(game_state.player) + dy,
        game_state.map))
        set_game_message("I can't go through walls...");
    else
        move_entity(game_state.player, dx, dy);
    return 1;
}

int draw_screen(void) {
    clear();
    draw_tile_map(game_state.map);
    draw_entity(game_state.player);
    print_game_message();
    refresh();
    return 1;
}

// - clean_up() helpers
int clean_game_state(void) {
    if (game_state.player) free(game_state.player);
    if (game_state.map) free(game_state.map);
    return 1;
}

// - helper helpers
void print_game_message(void) {
    mvprintw(MESSAGE_Y, MESSAGE_X, game_state.message);
}

int set_game_message(const char *str) {
    strncpy(game_state.message, str, RESERVED_ROWS * TERMINAL_COLUMNS);
}
