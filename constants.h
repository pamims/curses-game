#ifndef CONSTANTS_H
#define CONSTANTS_H


/* - STATIC_ASSERT DEFINITION - */
// Check that we can use built-in _Static_assert
#if defined( __STDC_VERSION__ ) && __STDC_VERSION__ >= 201112L
    #define STATIC_ASSERT(cond, msg) _Static_assert(cond, msg)
#else // We make our own
    #define JOIN(pre) JOIN2(pre, __LINE__)
    #define JOIN2(pre, post) JOIN3(pre, post)
    #define JOIN3(pre, post) pre ## post
    #define STATIC_ASSERT(cond, msg) \
        static const char *JOIN(static_assert)[(cond) * 2 - 1] = { msg }
#endif // STATIC_ASSERT


/* - WINDOW CONSTANTS - */
// TERMINAL SIZE
#define TERMINAL_ROWS       24
#define TERMINAL_COLUMNS    80
#define RESERVED_ROWS       3

// MAP SIZE
#define MAP_HEIGHT  (TERMINAL_ROWS - RESERVED_ROWS)
#define MAP_WIDTH   (TERMINAL_COLUMNS)

// GAME STATE MESSAGE POSITION
#define MESSAGE_Y   (MAP_HEIGHT)
#define MESSAGE_X   0

// Assert that the defined constant values make sense
STATIC_ASSERT(TERMINAL_ROWS > RESERVED_ROWS,
    "The number of TERMINAL_ROWS must be larger "
    "than the number of RESERVED_ROWS.");
STATIC_ASSERT(TERMINAL_ROWS > 0,
    "TERMINAL_ROWS must be greater than zero.");
STATIC_ASSERT(TERMINAL_COLUMNS > 0,
    "TERMINAL_COLUMNS must be greater than zero.");
STATIC_ASSERT(RESERVED_ROWS >= 0,
    "RESERVED_ROWS must not be negative");
/* - WINDOW CONSTANTS - */


/* - ROOM SIZE CONSTANTS - */
#define MIN_ROOM_WIDTH 6
#define MAX_ROOM_WIDTH 20
#define MIN_ROOM_HEIGHT 5
#define MAX_ROOM_HEIGHT 8

// Enter all the static asserts

/* - ROOM SIZE CONSTANTS - */


/* - CLEANUP - */
// Clean up unnecessary macros
#undef STATIC_ASSERT
#ifdef JOIN
    #undef JOIN
    #undef JOIN2
    #undef JOIN3
#endif // undef JOIN


#endif // CONSTANTS_H
