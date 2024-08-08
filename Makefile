PROJECT_NAME:=raylib_c
SRC:=main.c
CC:=clang
CFLAGS:=-Wall -Werror=implicit-function-declaration
export LD_LIBRARY_PATH=/usr/local/lib

raylib_c:
	$(CC) $(CFLAGS) $(shell pkg-config --libs --cflags raylib) $(SRC) -o $(PROJECT_NAME)

.PHONY: start
start: clear raylib_c
	XDG_RUNTIME_DIR=/run/user/$$UID ./$(PROJECT_NAME)

.PHOMY: clear
clear:
	rm -vf $(PROJECT_NAME)
