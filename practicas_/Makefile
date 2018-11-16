UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CC = gcc
endif
ifeq ($(UNAME_S),Darwin)
	CC = clang
endif

CFLAGS= -std=c11 -O3 -I../ctest -g -lm -Wall
SRC = main.c puzleAlum.c busquedaAlum.c listaia.c
OBJ = $(SRC:.c=.o)
EXE = puzzle.out

all: $(EXE)

build: $(EXE)

run: $(EXE)
	@./$<

$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
	@rm -f $^

.PHONY: clean
clean:
	rm -f $(EXE)
