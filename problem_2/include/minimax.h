#ifndef MINIMAX_H
#define MINIMAX_H
#include <limits.h>

#include "node.h"

#define MIN INT_MIN
#define MAX INT_MAX

/**
 * @brief  Perform the next game state using minimax complete.
 * @param  *node: current game state.
 * @param  player: current player.
 * @retval next state applied to the game.
 */
Node *minimax(Node *node, char player);
/**
 * @brief  same as minimax but limiting tree depth.
 * @param  *node: current game state.
 * @param  player: current player.
 * @param  limit: how depth should explore
 * @retval next state applied to the game.
 */
Node *minimax_with_limit(Node *node, char player, int limit);
/**
 * @brief  Perform the next game state using minimax with alpha beta pruning.
 * @param  *node: current game state.
 * @param  player: current player.
 * @retval next state applied to the game.
 */
Node *minimax_alpha_beta(Node *node, char player);
/**
 * @brief  same as minimax_alpha_bera but limiting tree depth.
 * @param  *node: current game state.
 * @param  player: current player.
 * @param  limit: how depth should explore
 * @retval next state applied to the game.
 */
Node *minimax_alpha_beta_with_limit(Node *node, char player, int limit);

#endif