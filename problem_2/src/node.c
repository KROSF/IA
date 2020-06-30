#include "node.h"

#include <stdlib.h>
#include <string.h>

#include "colors.h"

/**
 * @brief  count pieces of each player
 * @param  *node: current game state
 * @retval a tuple with pieces of each player
 */
static tuple_int_t count_players(const Node *node) {
  tuple_int_t counter = {0, 0};

  for (int i = 0; i < node->size; ++i) {
    if (node->board[i] == PLAYER_A) {
      ++counter.a;
    } else {
      ++counter.b;
    }
  }

  return counter;
}

Node *node_new(const char *board) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->size = strlen(board);
  node->board = (char *)malloc(node->size + 1 * sizeof(char));
  strcpy(node->board, board);
  node->board[node->size] = '\0';
  node->pieces = count_players(node);
  return node;
}

void node_free(Node *node) {
  free(node->board);
  free(node);
}

vec_move_t node_next_moves(const Node *node, char player) {
  vec_move_t moves;
  vec_init(&moves);
  char *begin = strchr(node->board, player);
  if (begin == NULL) {
    return moves;
  }
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

bool node_is_valid_move(const Node *node, Move move) {
  bool is_ok;
  size_t begin;
  size_t end;

  if (move.begin < -1 || move.end < -1) {
    return false;
  }

  if (move.begin == -1 && move.end > node->size - 1) {
    return false;
  }

  if (move.end == -1 && move.begin > node->size - 1) {
    return false;
  }

  if (move.begin == -1 && node->board[move.end] != move.player) {
    return false;
  }

  if (move.end == -1 && node->board[move.begin] != move.player) {
    return false;
  }

  if (move.begin != -1 && move.end != -1 && node->board[move.begin] != move.player &&
      node->board[move.end] != move.player) {
    return false;
  }

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

bool node_is_leaf(const Node *node) { return node->pieces.a == node->size || node->pieces.b == node->size; }

Node *node_apply_move(Node *node, Move move) {
  int pieces = 0;
  if (move.begin == -1) {
    pieces = move.end;
  } else if (move.end == -1) {
    pieces = node->size - move.begin - 1;
  } else {
    pieces = move.end - move.begin - 1;
  }

  Node *tmp = (Node *)malloc(sizeof(Node));
  tmp->size = node->size - pieces;
  tmp->pieces = node->pieces;
  tmp->board = (char *)malloc((tmp->size + 1) * sizeof(char));

  if (move.player == PLAYER_A) {
    tmp->pieces.b -= pieces;
  } else {
    tmp->pieces.a -= pieces;
  }

  if (move.begin == -1) {
    memcpy(tmp->board, node->board + move.end, tmp->size * sizeof(char));
  } else if (move.end == -1) {
    memcpy(tmp->board, node->board, tmp->size * sizeof(char));
  } else {
    memcpy(tmp->board, node->board, (move.begin + 1) * sizeof(char));
    strcpy(tmp->board + move.begin + 1, node->board + move.end);
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
    for (int i = 0; i < node->size; i++) {
      if (i == 0) {
        fprintf(stream, "╔═══");
      } else if (i == node->size - 1) {
        fprintf(stream, "╦═══╗");
      } else {
        fprintf(stream, "╦═══");
      }
    }

    fprintf(stream, "\n");

    for (int i = 0; i < node->size; i++) {
      fprintf(stream, "║ %s%c%s ", node->board[i] == PLAYER_A ? CYAN : MAGENTA, node->board[i], NORMAL);
      if (i == node->size - 1) {
        fprintf(stream, "║");
      }
    }

    fprintf(stream, "\n");

    for (int i = 0; i < node->size; i++) {
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
  Node *applied = NULL;
  Move move = {.player = player, .begin = 0, .end = 0};

  printf("Insert begin index: ");
  scanf("%d", &move.begin);
  printf("Insert end index: ");
  scanf("%d", &move.end);

  while (!node_is_valid_move(node, move)) {
    printf("\nTry another range previous one is incorrect\n");
    printf("Insert begin index: ");
    scanf("%d", &move.begin);
    printf("Insert end index: ");
    scanf("%d", &move.end);
  }

  printf("\n");

  applied = node_apply_move(node, move);

  node_free(node);

  return applied;
}

int node_has_winner(const Node *node) {
  if (node->pieces.a == node->size) {
    return 10;
  }

  if (node->pieces.b == node->size) {
    return -10;
  }

  return 0;
}
