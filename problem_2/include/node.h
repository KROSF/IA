#ifndef NODE_H
#define NODE_H
#include <stdbool.h>
#include <stdio.h>

#include "move.h"
#include "vec.h"

typedef struct tuple_int_t
{
  int a;
  int b;
} tuple_int_t;
typedef struct node_t
{
  char *board;
  int size;
  tuple_int_t pieces;
} Node;

typedef vec_t(Move) vec_move_t;

/**
 * @brief Create a node from string
 * @param  *board: string
 * @retval a new node with current state
 */
Node *node_new(const char *board);

/**
 * @brief free memory of a node
 */
void node_free(Node *node);

/**
 * @brief  Generate all posible next moves
 * @param  *node: current game state
 * @param  player: who is playing
 * @retval all posible moves valid and invalids.
 */
vec_move_t node_next_moves(const Node *node, char player);

/**
 * @brief  check if a move valid on the current node.
 * @param  *node: current game state
 * @param  move: move to check
 * @retval true is it valid or false otherwise
 */
bool node_is_valid_move(const Node *node, Move move);

/**
 * @brief  is this node a leaf
 * @param  *node: current game state
 * @retval true is it valid or false otherwise
 */
bool node_is_leaf(const Node *node);

/**
 * @brief  Apply given move to the current game state
 * @param  *node: current game state
 * @param  move: which to apply
 * @retval next game state
 */
Node *node_apply_move(Node *node, Move move);

/**
 * @brief  show to the stream the state
 * @param  *stream: 
 * @param  *node: current game state
 */
void node_display(FILE *stream, const Node *node);

/**
 * @brief  ask user to play
 * @param  *node: current game state
 * @param  player
 * @retval node with move applied from user
 */
Node *node_user_move(Node *node, char player);

/**
 * @brief  check if the given node has a winner
 * @param  *node: current game state
 * @retval -10 if win min | 10 if win max | 0 otherwise
 */
int node_has_winner(const Node *node);

#endif