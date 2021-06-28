#include "game.h"
#include "entity.h"
#include <curses.h>
#include <stdlib.h>


/* - FUNCTION PROTOTYPES - */
// Get player input
void get_input(int *);
// Update the game state
void update_game(int *, entity *);
// Draw the screen
void draw_screen(entity *);


/* - FUNCTION DEFINITIONS - */
int game_loop(void) {
    int input = '\0';
    entity *player = (entity *)malloc(sizeof(entity));
    if (player == NULL) return 1;
    player->row = 15;
    player->column = 30;
    player->symbol = '@';
    while (input != 'Q') {
        get_input(&input);
        update_game(&input, player);
        draw_screen(player);
    }
    return 0;
}

void get_input(int *input) {
    napms(50);
    flushinp();
    *input = getch();
    return;
}

void update_game(int *input, entity *player) {
    switch(*input) {
        case KEY_LEFT:
        case 'a':
            player->column--;
            break;
        case KEY_RIGHT:
        case 'd':
            player->column++;
            break;
        case KEY_DOWN:
        case 's':
            player->row++;
            break;
        case KEY_UP:
        case 'w':
            player->row--;
            break;
        case 'q':
            *input = 'Q';
        case 'Q':
            return;
        default:
            break;
    }
    return;
}

void draw_screen(entity *player) {
    clear();
    mvaddch(player->row, player->column, player->symbol);
    refresh();
    return;
}
