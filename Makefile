ifeq ($(OS),Windows_NT)
	RM := cmd /c del
else
	RM := rm -f
endif

CC		:= gcc
LINK	:= gcc
TARGET	:= test.exe
OBJS	:= dice.o entity.o game.o main.o map.o
FLAGS	:= -pedantic -Wall -Werror -D_FORTIFY_SOURCE=2 -g3 -O2

# Needs changed later to support ncurses
CURSES	:= lpdcurses

$(TARGET): $(OBJS)
	$(LINK) $(OBJS) -o $@ -$(CURSES) $(FLAGS)

dice.o: dice.c dice.h
	$(CC) -c dice.c

entity.o: entity.c entity.h
	$(CC) -c entity.c

game.o: game.c constants.h entity.h game.h
	$(CC) -c game.c

main.o: main.c game.h
	$(CC) -c main.c

map.o: map.c constants.h map.h
	$(CC) -c map.c

clean:
	-$(RM) *.o
	-$(RM) *.exe
