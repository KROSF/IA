#ifndef NODE_H
#define NODE_H
#include <stdbool.h>
#include <stdio.h>

#include "move.h"
#include "vec.h"

typedef struct node_t {
  char *board;
  int size;
} Node;

typedef vec_t(Move) vec_move_t;

Node *node_new(const char *board);

void node_free(Node *node);

bool node_is_valid_move(Node *node, Move move);

void node_display(FILE *stream, const Node *node);

vec_move_t node_next_moves(const Node *node, char player);

Node *node_apply_move(Node *node, Move move);

Node *node_user_move(Node *node, char player);

Node *minimax(Node *node, char player);

int evaluation(Node *node);

#endif