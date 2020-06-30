DEBUG ?= 1

ifeq ($(DEBUG), 1)
  CFLAGS = -std=c11 -g -Wall -Wextra -I./include -DDEBUG
else
  CFLAGS = -std=c11 -Wall -Wextra -Werror -I./include -DNDEBUG -O3
endif

CC = gcc

SRC = $(addprefix src/, main.c vec.c move.c node.c minimax.c commander.c)
OBJ = $(SRC:.c=.o)
EXE = ab.out

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