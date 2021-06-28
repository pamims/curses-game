#include "game.h"
#include <curses.h>


int init_game(void) {
    initscr();
    resize_term(TERMINAL_ROWS, TERMINAL_COLUMNS);
    noecho();
    curs_set(0);
    raw();
    printw("use WASD to move. use Q to quit.\n");
    printw("press any key to continue...\n");
    refresh();
    getch();
    clear();
}
