PROJECT_NAME:=raylib_c
SRC:=main.c
CC:=gcc
CFLAGS:=-Wall
INCLUDE=-Irlights.h

all:
	$(CC) $(CFLAGS) $(shell pkg-config --libs --cflags raylib) $(SRC) $(INCLUDE) -o $(PROJECT_NAME)

clear:
	rm -vf $(PROJECT_NAME)
