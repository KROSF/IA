#ifndef MINIMAX_H
#define MINIMAX_H
#include <limits.h>

#include "node.h"

#define MIN INT_MIN
#define MAX INT_MAX

Node *minimax(Node *node, char player);

Node *minimax_with_limit(Node *node, char player, int limit);

Node *minimax_alpha_beta(Node *node, char player);

Node *minimax_alpha_beta_with_limit(Node *node, char player, int limit);

#endif