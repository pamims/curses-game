#ifndef GAME_H
#define GAME_H

/* - CONSTANTS - */
#define TERMINAL_ROWS 24
#define TERMINAL_COLUMNS 80
#define MAX_ENTITIES 25


/* - FUNCTION PROTOTYPES - */
// Initialize all of the important stuff
int init_game(void);
// Main game loop
int game_loop(void);
// Clean up all of the things
int clean_up(void);



#endif //GAME_H
