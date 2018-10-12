CFLAGS= -std=c11 -O3 -I../ctest -g -Wall
CC = clang
SRC = main.c puzleAlum.c
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
