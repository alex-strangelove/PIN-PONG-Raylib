PROJECT_NAME:=ping_pong_raylib
SRC:=main.c game.c start_menu.c
CC:=clang
CFLAGS:=-Wall -Werror -lm

$(PROJECT_NAME):
	$(CC) $(CFLAGS) $(shell pkg-config --libs --cflags raylib) $(SRC) -o $(PROJECT_NAME)

.PHONY: start
start: clear $(PROJECT_NAME)
	XDG_RUNTIME_DIR=/run/user/$$UID ./$(PROJECT_NAME)

.PHOMY: clear
clear:
	rm -vf $(PROJECT_NAME)
