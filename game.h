#ifndef GAME_H
#define GAME_H


#define TERMINAL_ROWS 40
#define TERMINAL_COLUMNS 100
#define MAX_ENTITIES 25

// Initialize all of the important stuff
int init_game(void);
// Main game loop
int game_loop(void);
// Clean up all of the things
int clean_up(void);



#endif
