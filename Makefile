UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	CC = gcc
	CFLAGS= -std=c11 -O3 -g -Wall -I./include $(shell pkg-config --cflags glib-2.0)
endif
ifeq ($(UNAME_S), Darwin)
	CC = clang
	CFLAGS= -std=c11 -O3 -g -Wall -I./include $(shell pkg-config --cflags glib-2.0)
endif
SRC = $(addprefix src/, main.c busqueda.c nodo.c puzzle.c)
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