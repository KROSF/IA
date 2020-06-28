#include "node.h"

#include <stdlib.h>
#include <string.h>

#include "colors.h"

vec_move_t node_next_moves(const Node *node, char player) {
  vec_move_t moves;
  vec_init(&moves);
  char *begin = strchr(node->board, player);
  char *end = strchr(begin + 1, player);

  vec_push(&moves, ((Move){
                       .player = player,
                       .begin = -1,
                       .end = begin - node->board,
                   }));

  while (end != NULL) {
    vec_push(&moves, ((Move){
                         .player = player,
                         .begin = begin - node->board,
                         .end = end - node->board,
                     }));
    begin = end;
    end = strchr(begin + 1, player);
  }

  vec_push(&moves, ((Move){
                       .player = player,
                       .begin = begin - node->board,
                       .end = -1,
                   }));
  return moves;
}

Node *node_new(const char *board) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->size = strlen(board);
  node->board = (char *)malloc(node->size + 1 * sizeof(char));
  strcpy(node->board, board);
  node->board[node->size] = '\0';
  return node;
}

void node_free(Node *node) {
  free(node->board);
  free(node);
}

bool node_is_valid_move(Node *node, Move move) {
  bool is_ok;
  size_t begin;
  size_t end;
  if (move.begin == -1) {
    is_ok = (move.end - move.begin) > 1;
    begin = 0;
    end = move.end;
  } else if (move.end == -1) {
    is_ok = (node->size - move.begin) > 1;
    begin = move.begin + 1;
    end = node->size;
  } else {
    is_ok = (move.end - move.begin) > 1;
    begin = move.begin + 1;
    end = move.end;
  }
  while (begin < end && is_ok) {
    is_ok = node->board[begin++] == oposite_player(move.player) && is_ok;
  }
  return is_ok;
}

bool node_is_leaf(const Node *node, Move move) {
  char piece = node->board[0];
  for (size_t i = 1; i < node->size; ++i) {
    if (piece != node->board[i]) {
      return false;
    }
  }
  return true;
}

Node *node_apply_move(Node *node, Move move) {
  int distance;
  if (move.begin == -1) {
    distance = move.end;
  } else if (move.end == -1) {
    distance = node->size - move.begin - 1;
  } else {
    distance = move.end - move.begin - 1;
  }

  Node *tmp = (Node *)malloc(sizeof(Node));
  tmp->size = node->size - distance;
  tmp->board = (char *)malloc((tmp->size + 1) * sizeof(char));

  if (move.begin == -1) {
    memcpy(tmp->board, node->board + move.end, tmp->size * sizeof(char));
  } else if (move.end == -1) {
    memcpy(tmp->board, node->board, tmp->size * sizeof(char));
  } else {
    memcpy(tmp->board, node->board, (move.begin + 1) * sizeof(char));
    memcpy(tmp->board + move.begin + 1, node->board + move.end, (node->size - move.begin) * sizeof(char));
  }
  tmp->board[tmp->size] = '\0';
  return tmp;
}

void node_display(FILE *stream, const Node *node) {
  if (node->size == 1) {
    fprintf(stream, "╔═══╗\n");
    fprintf(stream, "║ %s%c%s ║\n", node->board[0] == PLAYER_A ? CYAN : MAGENTA, node->board[0], NORMAL);
    fprintf(stream, "╚═══╝\n");
  } else {
    for (size_t i = 0; i < node->size; i++) {
      if (i == 0) {
        fprintf(stream, "╔═══");
      } else if (i == node->size - 1) {
        fprintf(stream, "╦═══╗");
      } else {
        fprintf(stream, "╦═══");
      }
    }
    fprintf(stream, "\n");

    for (size_t i = 0; i < node->size; i++) {
      fprintf(stream, "║ %s%c%s ", node->board[i] == PLAYER_A ? CYAN : MAGENTA, node->board[i], NORMAL);
      if (i == node->size - 1) {
        fprintf(stream, "║");
      }
    }
    fprintf(stream, "\n");

    for (size_t i = 0; i < node->size; i++) {
      if (i == 0) {
        fprintf(stream, "╚═══");
      } else if (i == node->size - 1) {
        fprintf(stream, "╩═══╝");
      } else {
        fprintf(stream, "╩═══");
      }
    }
    fprintf(stream, "\n");
  }
}

Node *node_user_move(Node *node, char player) {
  Move move = {.player = player, .begin = 0, .end = 0};

  printf("Insert begin index: ");
  scanf("%d", &move.begin);
  printf("Insert end index: ");
  scanf("%d", &move.end);

  while (!node_is_valid_move(node, move)) {
    printf("\n Try another range previous one is incorrect");
    printf("Insert begin index: ");
    scanf("%d", &move.begin);
    printf("Insert end index: ");
    scanf("%d", &move.end);
  }
  return node_apply_move(node, move);
}

int evaluation(Node *node) {
  // node_display(node);
  int count = 0;
  for (size_t i = 0; i < node->size; ++i) {
    if (PLAYER_A == node->board[i]) {
      ++count;
    }
  }
  if (count == node->size) {
    return 10;
  }
  count = 0;
  for (size_t i = 0; i < node->size; ++i) {
    if (PLAYER_B == node->board[i]) {
      ++count;
    }
  }
  return count == node->size ? -10 : 0;
}

static int max(int a, int b) { return (a > b) ? a : b; }
static int min(int a, int b) { return (a < b) ? a : b; }

static int minimax_(Node *node, int depth, bool isMax, char player) {
  int score = evaluation(node);

  if (score == 10 || score == -10) {
    return score;
  }

  if (isMax) {
    int best = -1000;
    vec_move_t moves = node_next_moves(node, player);
    int i;
    Move *move;
    vec_foreach_ptr(&moves, move, i) {
      if (node_is_valid_move(node, *move)) {
        best = max(best, minimax_(node_apply_move(node, *move), depth + 1, !isMax, player));
      }
    }
    vec_deinit(&moves);
    return best;
  } else {
    int best = 1000;
    vec_move_t moves = node_next_moves(node, oposite_player(player));
    int i;
    Move *move;
    vec_foreach_ptr(&moves, move, i) {
      if (node_is_valid_move(node, *move)) {
        best = min(best, minimax_(node_apply_move(node, *move), depth + 1, !isMax, oposite_player(player)));
      }
    }
    vec_deinit(&moves);
    return best;
  }
}

Node *minimax(Node *node, char player) {
  vec_move_t moves = node_next_moves(node, player);
  int i;
  Move *move;
  Move best_move = {};
  int best = -1000;
  vec_foreach_ptr(&moves, move, i) {
    if (node_is_valid_move(node, *move)) {
      int value = minimax_(node, 0, false, player);
      if (value > best) {
        best_move = *move;
      }
    }
  }
  vec_deinit(&moves);
  return node_apply_move(node, best_move);
}