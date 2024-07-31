PROJECT_NAME:=raylib_c
SRC:=main.c
CC:=clang
CFLAGS:=-Wall -Werror=implicit-function-declaration
INCLUDE=-Irlights.h

raylib_c:
	$(CC) $(CFLAGS) $(shell pkg-config --libs --cflags raylib) $(SRC) $(INCLUDE) -o $(PROJECT_NAME)

.PHONY: start
start: raylib_c
	./$(PROJECT_NAME)

clear:
	rm -vf $(PROJECT_NAME)
