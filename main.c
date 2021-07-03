#include <curses.h>
#include "game.h"

/* - CODE ENTRY POINT - */
int main(int argc, char *argv[]) {
    if (init_game()) {
        game_loop();
    }
    clean_up();
    return 0;
}
