#include "minimax.h"

static int max(int a, int b) { return (a > b) ? a : b; }

static int min(int a, int b) { return (a < b) ? a : b; }

static int utility(const Node *node) {
  if (node->pieces.a == node->size) {
    return 10 * node->pieces.a;
  }

  return -10 * node->pieces.b;
}

static int heuristic(const Node *node, char player) {
  int value = abs(node->pieces.a - node->pieces.b) + 2;

  return player == PLAYER_A ? value * 10 : value * -10;
}

static int minimax_with_limit_(Node *node, int depth, bool isMax, char player, int limit) {
  if (node_is_leaf(node)) {
    int value = utility(node);
    node_free(node);
    return value;
  }

  if (depth >= limit) {
    int value = heuristic(node, player);
    node_free(node);
    return value;
  }

  if (isMax) {
    int i = 0;
    int best = MIN;
    Move *move = NULL;
    vec_move_t moves = node_next_moves(node, player);

    vec_foreach_ptr(&moves, move, i) {
      if (node_is_valid_move(node, *move)) {
        best = max(best, minimax_with_limit_(node_apply_move(node, *move), depth + 1, !isMax, player, limit));
      }
    }

    vec_deinit(&moves);
    node_free(node);

    return best;
  } else {
    int best = MAX;
    vec_move_t moves = node_next_moves(node, oposite_player(player));
    int i;
    Move *move;
    vec_foreach_ptr(&moves, move, i) {
      if (node_is_valid_move(node, *move)) {
        best = min(best,
                   minimax_with_limit_(node_apply_move(node, *move), depth + 1, !isMax, oposite_player(player), limit));
      }
    }

    vec_deinit(&moves);
    node_free(node);

    return best;
  }
}

static int minimax_alpha_beta_with_limit_(Node *node, int depth, bool isMax, char player, int alpha, int beta,
                                          int limit) {
  if (node_is_leaf(node)) {
    int value = utility(node);
    node_free(node);
    return value;
  }

  if (depth >= limit) {
    int value = heuristic(node, player);
    node_free(node);
    return value;
  }

  if (isMax) {
    int best = MIN;
    vec_move_t moves = node_next_moves(node, player);
    int i;
    Move *move;
    vec_foreach_ptr(&moves, move, i) {
      if (node_is_valid_move(node, *move)) {
        int value =
            minimax_alpha_beta_with_limit_(node_apply_move(node, *move), depth + 1, !isMax, player, alpha, beta, limit);
        best = max(best, value);
        alpha = max(alpha, best);
        if (beta <= alpha) {
          break;
        }
      }
    }

    vec_deinit(&moves);
    node_free(node);

    return best;
  } else {
    int best = MAX;
    vec_move_t moves = node_next_moves(node, oposite_player(player));
    int i;
    Move *move;
    vec_foreach_ptr(&moves, move, i) {
      int value = minimax_alpha_beta_with_limit_(node_apply_move(node, *move), depth + 1, !isMax,
                                                 oposite_player(player), alpha, beta, limit);
      best = min(best, value);
      beta = min(beta, best);
      if (beta <= alpha) {
        break;
      }
    }

    vec_deinit(&moves);
    node_free(node);

    return best;
  }
}

Node *minimax_with_limit(Node *node, char player, int limit) {
  int i = 0;
  int best = MIN;
  Move *move = NULL;
  Move best_move = {};
  Node *applied = NULL;
  vec_move_t moves = node_next_moves(node, player);

  vec_foreach_ptr(&moves, move, i) {
    if (node_is_valid_move(node, *move)) {
      int value = minimax_with_limit_(node_new(node->board), 0, false, player, limit);
      if (value > best) {
        best_move = *move;
        best = value;
      }
    }
  }

  applied = node_apply_move(node, best_move);

  printf("IA move was { begin: %d, end: %d }\n\n", best_move.begin, best_move.end);

  vec_deinit(&moves);
  node_free(node);

  return applied;
}

Node *minimax(Node *node, char player) { return minimax_with_limit(node, player, MAX); }

Node *minimax_alpha_beta_with_limit(Node *node, char player, int limit) {
  int i = 0;
  int best = MIN;
  Move *move = NULL;
  Move best_move = {};
  Node *applied = NULL;
  vec_move_t moves = node_next_moves(node, player);

  vec_foreach_ptr(&moves, move, i) {
    if (node_is_valid_move(node, *move)) {
      int value = minimax_alpha_beta_with_limit_(node_new(node->board), 0, false, player, MIN, MAX, limit);
      if (value > best) {
        best_move = *move;
        best = value;
      }
    }
  }

  applied = node_apply_move(node, best_move);

  printf("IA move was { begin: %d, end: %d }\n\n", best_move.begin, best_move.end);

  vec_deinit(&moves);
  node_free(node);

  return applied;
}

Node *minimax_alpha_beta(Node *node, char player) { return minimax_alpha_beta_with_limit(node, player, MAX); }