UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CC = gcc
	CFLAGS= -std=c11 -O3 -g -Wall -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
endif
ifeq ($(UNAME_S),Darwin)
	CC = clang
	CFLAGS= -std=c11 -O3 -g -Wall -I/usr/local/Cellar/glib/2.58.1/include/glib-2.0 -I/usr/local/Cellar/glib/2.58.1/lib/glib-2.0/include -I/usr/local/opt/gettext/include -I/usr/local/Cellar/pcre/8.42/include
endif
SRC = main.c busqueda.c nodo.c puzzle.c 
OBJ = $(SRC:.c=.o)
EXE = puzzle.out

all: $(EXE)

build: $(EXE)

run: $(EXE)
	@./$<

$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) -lm -lglib-2.0 $^ -o $@
	@rm -f $^

$(OBJ) : $(SRC)

.PHONY: clean
clean:
	rm -f $(EXE) $(OBJ)
