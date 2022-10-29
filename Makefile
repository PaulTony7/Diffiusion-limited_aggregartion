CC = g++
CFLAGS = -std=c11 -O2 -g -Wall -Wextra
LDFLAGS = -lsfml-graphics -lsfml-system -lsfml-window

SRC = $(wildcard *.cc)
OBJ = $(SRC:.cc=.o)

all: program

run: all
	./program

program: $(OBJ)
	$(CC) -o program $^ $(LDFLAGS)

%.o: %.cc
	$(CC) -o $@ -c $< $(CFLAGS)