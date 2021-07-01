#ifndef CONSTANTS_H
#define CONSTANTS_H

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


// Clean up unnecessary macros
#undef STATIC_ASSERT
#ifdef JOIN
    #undef JOIN
    #undef JOIN2
    #undef JOIN3
#endif // undef JOIN


#endif // CONSTANTS_H
