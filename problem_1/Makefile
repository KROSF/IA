DEBUG ?= 1

ifeq ($(DEBUG), 1)
    CFLAGS = -std=c11 -g -Wall -I./include -DDEBUG
else
    CFLAGS = -std=c11 -Wall -I./include -DNDEBUG
endif

CC = gcc

SRC = $(addprefix src/, main.c list.c list_node.c list_iterator.c c_printf.c)
OBJ = $(SRC:.c=.o)
EXE = vehicle.out

all: $(EXE)

build: $(EXE)

run: $(EXE)
	@./$<

$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ) : $(SRC)

.PHONY: clean
clean:
	rm -f $(EXE) $(OBJ)