#ifndef DICE_H
#define DICE_H

typedef enum { d4 = 4, d6 = 6, d8 = 8, d10 = 10, d12 = 12, d20 = 20 } dice_type;

void seed_dice(int seed);           // seeds the RNG
void shake_dice(int num);           // shakes up the RNG sauce
int flip_coin(void);                // returns only 0 or 1
int flip_coins(int);                // returns the number of heads
int roll(int num, dice_type dice);  // rolls num amount of specified dice type
int roll_percentile(void);          // rolls a percentile (2 d10) returns 1->100

//void test_wheels(void); // test out the wheels

#endif // DICE_H
