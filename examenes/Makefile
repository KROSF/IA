UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CC = gcc
	CFLAGS= -std=c11 -O3 -g -Wall -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
endif
ifeq ($(UNAME_S),Darwin)
	CC = clang
	CFLAGS= -std=c11 -O3 -g -Wall $(shell pkg-config --cflags glib-2.0)
endif
SRC = main.c busqueda.c nodo.c puzzle.c 
OBJ = $(SRC:.c=.o)
EXE = puzzle.out

all: $(EXE)

build: $(EXE)

run: $(EXE)
	@./$<

$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lm $(shell pkg-config --libs glib-2.0)
	@rm -f $^

$(OBJ) : $(SRC)

.PHONY: clean
clean:
	rm -f $(EXE) $(OBJ)
