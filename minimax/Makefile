CC = clang
CFLAGS= -std=c11 -O3 -g -Wall 
SRC = main.c tictactoe.c minimax.c
OBJ = $(SRC:.c=.o)
EXE = minimax.out

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
	rm -f $(EXE) $(OBJ)
