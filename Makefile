PROJECT_NAME:=raylib_c
SRC:=main.c
CC:=gcc
FLAGS:=-Wall

all:
	$(CC) $(FLAGS) $(SRC) -o $(PROJECT_NAME)
