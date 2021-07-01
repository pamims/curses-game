ifeq ($(OS),Windows_NT)
	RM = cmd /c del
else
	RM = rm -f
endif

CC		:= gcc
LINK	:= gcc
TARGET	:= test.exe
OBJS	:= entity.o game.o init.o main.o map.o

# Needs changed later to support ncurses
CURSES	:= lpdcurses

$(TARGET): $(OBJS)
	$(LINK) $(OBJS) -o $@ -$(CURSES)

entity.o: entity.c entity.h
	$(CC) -c entity.c

game.o: game.c entity.h game.h
	$(CC) -c game.c

init.o: init.c constants.h game.h
	$(CC) -c init.c

main.o: main.c game.h
	$(CC) -c main.c

map.o: map.c constants.h map.h
	$(CC) -c map.c

clean:
	-$(RM) *.o
	-$(RM) *.exe
