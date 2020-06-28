#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

void clear() {
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
  system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
  system("cls");
#endif
}

int main() {
  Node *game = node_new("BABAABBA");
  int winner = 0;
  char answer;
  char player;

  node_display(stdout, game);

  printf("\nthe AI is going to play as A\n");
  printf("you are going to play as B\n");

  printf("do you want to go first? Y/y");
  scanf("%s", &answer);
  player = (answer == 'y' || answer == 'Y') ? PLAYER_B : PLAYER_A;

  while (winner == 0) {
    game = (player == PLAYER_A) ? minimax(game, PLAYER_A) : node_user_move(game, PLAYER_B);
    node_display(stdout, game);
    player = oposite_player(player);
    winner = evaluation(game);
  }

  switch (winner) {
    case -10:
      printf("win player B\n");
      break;
    case 0:
      printf("draw!!\n");
      break;
    case 10:
      printf("win player A\n");
      break;
  }
}