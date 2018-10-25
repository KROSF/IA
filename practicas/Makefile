UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CC = gcc
endif
ifeq ($(UNAME_S),Darwin)
	CC = clang
endif


CFLAGS= -std=c11 -O3 -I../ctest -g -Wall
SRC = main.c puzleAlum.c busquedaAlum.c listaia.c
OBJ = $(SRC:.c=.o)
EXE = puzzle.out
TST = puzzleTest.out
SRCT = puzleAlumTest.c puzleAlum.c
OBJT= $(SRCT:.c=.o)

all: $(EXE)

build: $(EXE)

run: $(EXE)
	@./$<

test: $(TST)
	@./$<

$(TST) : $(OBJT)
	$(CC) $(CFLAGS) $^ -o $@
	@rm -f $^

$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
	@rm -f $^

$(OBJ) : $(SRC)

$(OBJT) : $(SRCT)

.PHONY: clean
clean:
	rm -f $(EXE) $(TST)
