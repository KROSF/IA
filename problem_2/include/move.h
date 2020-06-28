#ifndef MOVE_H
#define MOVE_H
#define PLAYER_A 'A'
#define PLAYER_B 'B'

typedef struct move_t {
  char player;
  int begin;
  int end;
} Move;

char oposite_player(char player);

#endif