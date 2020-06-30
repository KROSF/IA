#ifndef MOVE_H
#define MOVE_H
#define PLAYER_A 'A'
#define PLAYER_B 'B'

typedef struct move_t
{
  /**
   * player who is doing the move
   */
  char player;
  /**
   * where move should begin
   */
  int begin;
  /**
    * where move should end
   */
  int end;
} Move;

/**
 * @param  player: 
 * @retval oposite player
 */
char oposite_player(char player);

#endif