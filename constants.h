#ifndef CONSTANTS_H
#define CONSTANTS_H

/* - CONSTANT VALUES - */
enum window_constants {

// TERMINAL SIZE
    TERMINAL_ROWS = 24,
    TERMINAL_COLUMNS = 80,
    RESERVED_ROWS = 3,

// MAP SIZE
    MAP_HEIGHT = TERMINAL_ROWS - RESERVED_ROWS,
    MAP_WIDTH = TERMINAL_COLUMNS

};

_Static_assert(TERMINAL_ROWS > RESERVED_ROWS,
    "The number of TERMINAL_ROWS must be larger "
    "than the number of RESERVED_ROWS.");
_Static_assert(TERMINAL_ROWS > 0,
    "TERMINAL_ROWS must be greater than zero.");
_Static_assert(TERMINAL_COLUMNS > 0,
    "TERMINAL_COLUMNS must be greater than zero.");
_Static_assert(RESERVED_ROWS >= 0,
    "RESERVED_ROWS must not be negative");

#endif // CONSTANTS_H
