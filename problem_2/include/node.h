#ifndef NODE_H
#define NODE_H
#include <stdbool.h>
#include <stdio.h>

#include "move.h"
#include "vec.h"

typedef struct tuple_int_t {
  int a;
  int b;
} tuple_int_t;
typedef struct node_t {
  char *board;
  int size;
  tuple_int_t pieces;
} Node;

typedef vec_t(Move) vec_move_t;

Node *node_new(const char *board);

void node_free(Node *node);

vec_move_t node_next_moves(const Node *node, char player);

bool node_is_valid_move(const Node *node, Move move);

bool node_is_leaf(const Node *node);

Node *node_apply_move(Node *node, Move move);

void node_display(FILE *stream, const Node *node);

Node *node_user_move(Node *node, char player);

int node_has_winner(const Node *node);

#endif