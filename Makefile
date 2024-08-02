PROJECT_NAME:=raylib_c
SRC:=main.c
CC:=clang
CFLAGS:=-Wall -Werror=implicit-function-declaration

raylib_c:
	$(CC) $(CFLAGS) $(shell pkg-config --libs --cflags raylib) $(SRC) -o $(PROJECT_NAME)

.PHONY: start
start: clear raylib_c
	./$(PROJECT_NAME)

.PHOMY: clear
clear:
	rm -vf $(PROJECT_NAME)
