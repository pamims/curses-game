#include <curses.h>
#include "game.h"

/* - FUNCTION PROTOTYPES - */



/* - CODE ENTRY POINT - */
int main(int argc, char *argv[]) {
    init_game();
    game_loop();
    endwin();
    return 0;
}


/* - FUNCTION DEFINITIONS - */
