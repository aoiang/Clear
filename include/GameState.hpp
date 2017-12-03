#ifndef CLEAR_GAMESTATE_HPP
#define CLEAR_GAMESTATE_HPP

#include <iostream>

class GameState {
  private:
      int current_board_wrong_moves = 0;
  public:
      GameState(std::string);
      GameState() {};
      void init_current_board();
      void add_wrong_move();
};

#endif //CLEAR_GAMESTATE_HPP
