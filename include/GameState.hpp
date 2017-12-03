#ifndef CLEAR_GAMESTATE_HPP
#define CLEAR_GAMESTATE_HPP

#include <iostream>

class GameState {
  private:
      int current_board_wrong_moves;
      int current_board_block_removed;
      int max_level;
      int cur_level;
      bool current_board_is_clear;
  public:
      GameState(std::string);
      GameState();
      void init_current_board();
      void add_wrong_move();
      int get_blocks_removed();
      void increment_blocks_removed();
      void set_is_clear();
      bool get_is_clear();
      void set_max_level(int);
      int get_max_level();
      void set_cur_level(int);
      int get_cur_level();
};

#endif //CLEAR_GAMESTATE_HPP
