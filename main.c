#include <curses.h>


/* - FUNCTION PROTOTYPES - */
int game_loop(char player, int row, int col);


/* - CODE ENTRY POINT - */
int main(int argc, char *argv[]) {
    char player = '@';
    int row = 10;
    int col = 30;
    initscr();
    noecho();
    curs_set(0);
    raw();
    printw("use WASD to move. use Q to quit.\n");
    printw("press any key to continue...\n");
    refresh();
    getch();
    clear();
    game_loop(player, row, col);
    endwin();
    return 0;
}


/* - FUNCTION DEFINITIONS - */
// Main game loop.
int game_loop(char player, int row, int col) {
    int ch = '\0';
    mvaddch(row, col, player);
    refresh();
    for(;;) {
        napms(50);
        flushinp();
        ch = getch();
        switch(ch) {
            case KEY_LEFT:
            case 'a':
                col--;
                break;
            case KEY_RIGHT:
            case 'd':
                col++;
                break;
            case KEY_DOWN:
            case 's':
                row++;
                break;
            case KEY_UP:
            case 'w':
                row--;
                break;
            case 'q':
            case 'Q':
                return 0;
            default:
                break;
        }
        clear();
        mvaddch(row, col, player);
        refresh();
    }
    return 0;
}
