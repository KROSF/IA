#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bench.h"
#include "colors.h"
#include "commander.h"
#include "minimax.h"

void clear() {
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
  system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
  system("cls");
#endif
}

/**
 * @brief  Validate if user given state is valid.
 */
static bool validate_user_state(const char *init) {
  int len = strlen(init);
  int player_a = 0;
  int player_b = 0;

  for (int i = 0; i < len; ++i) {
    if (init[i] == PLAYER_A) {
      ++player_a;
    } else {
      ++player_b;
    }
  }

  if (player_a != player_b) {
    return false;
  }

  if ((player_a + player_b) != len) {
    return false;
  }

  return true;
}

static void game(const char *init) {
  Node *game_node = node_new(init);
  int winner = 0;
  char answer;
  char player;

  printf("The AI is going to play as " CYAN "A\n" NORMAL);
  printf("You are going to play as " MAGENTA "B\n" NORMAL);

  printf("Do you want to go first? Y/y [n]: ");
  scanf("%s", &answer);
  player = (answer == 'y' || answer == 'Y') ? PLAYER_B : PLAYER_A;

  printf("Initial Board\n");
  node_display(stdout, game_node);

  float max_time_on_move = -1.0;

  while (winner == 0) {
    if (player == PLAYER_A) {
      float cpu_start = cpu();
      game_node = minimax_alpha_beta(game_node, PLAYER_A);
      float cpu_end = cpu();
      if ((cpu_end - cpu_start) > max_time_on_move) {
        max_time_on_move = cpu_end - cpu_start;
      }
    } else {
      game_node = node_user_move(game_node, PLAYER_B);
    }
    node_display(stdout, game_node);
    player = oposite_player(player);
    winner = node_has_winner(game_node);
  }

  switch (winner) {
    case -10:
      printf("You win\n\n");
      break;
    case 0:
      printf("draw!!\n");
      break;
    case 10:
      printf("I win :)\n\n");
      break;
  }

  printf("The max time used to calculate a move was " GREEN "%f\n\n" NORMAL, max_time_on_move);
  printf("The used strategy was " GREEN "minmax_alpha_beta\n\n" NORMAL);

  node_free(game_node);
}

char *default_state = NULL;

static void init_default_state() {
  default_state = (char *)malloc(21 * sizeof(char));
  strcpy(default_state, "BBBBABBAABABABABAAAA");
  default_state[20] = '\0';
}

/**
 * @brief  set given user state as intial is if incorrent use default
 */
static void set_intial_state(command_t *self) {
  if (self->arg != NULL && validate_user_state(self->arg)) {
    int len = strlen(self->arg);
    default_state = realloc(default_state, (len + 1) * sizeof(char));
    strcpy(default_state, self->arg);
    default_state[len] = '\0';
  }
}

int main(int argc, char **argv) {
  init_default_state();
  command_t cmd;
  command_init(&cmd, argv[0], "0.0.1");
  command_option(&cmd, "-s", "--state [ABBA]", "set initial state", set_intial_state);
  command_parse(&cmd, argc, argv);
  bool try_again = true;
  char answer;

  while (try_again) {
    game(default_state);

    printf("Do you want to try again [Yy]: ");
    scanf("%s", &answer);
    try_again = (answer == 'y' || answer == 'Y');
    printf("\n");
  }

  free(default_state);

  command_free(&cmd);
  return 0;
}