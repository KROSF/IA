CFLAGS= -std=c11 -O3 -I. -g -Wall
CC = clang
SRC = main.c puzleAlum.c
OBJ = $(SRC:.c=.o)
EXE = puzzle.out

all: $(EXE)

build: $(EXE)

run: $(EXE)
	@./$<

$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
	@rm -f $^

$(OBJ) : $(SRC)

.PHONY: clean
clean:
	rm $(EXE) $(OBJ)
