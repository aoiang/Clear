#ifndef CLEAR_GAMELOGIC_HPP
#define CLEAR_GAMELOGIC_HPP

#include "Block.hpp"
#include "BlockNormal.hpp"
#include "BlockDirectional.hpp"
#include "BlockRotating.hpp"
#include "BoardState.hpp"
#include "GameState.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class GameLogic {
    private:
        BoardState * board;
        GameState * state;
        int selected_x = -1;
        int selected_y = -1;
        int generated_board_x;
        int generated_board_y;
        std::string nums_of_nor;
        std::string nums_of_rot;
        std::string nums_of_dir;

    public:
        void set_nums_of_blocks(std::string nums_of_nor, std::string nums_of_rot, std::string nums_of_dir);
        std::string get_nums_of_nor();
        std::string get_nums_of_rot();
        std::string get_nums_of_dir();
        int get_generated_board_x();
        int get_generated_board_y();
        void set_generated_board_size(int x, int y);
        void set_BoardState(BoardState &board);
        int get_board_width();
        int get_board_height();
        void set_selected_position(int x, int y);
        int get_selected_x();
        int get_selected_y();
        bool block_exists(int x, int y);
        bool selected_block_exists();
        Block * get_block(int x, int y);
        Block * get_selected_block();
        bool path_blocked(Block * block, char direction);
        bool path_blocked(int x, int y, char direction);
        bool path_fully_blocked(int x, int y);
        bool can_move_block(Block * block, char direction);
        bool can_be_removed(Block * block);
        bool can_be_removed(int x, int y);
        bool potentially_removable(Block * block);
        bool potentially_removable(int x, int y);
        void print_removable();
        bool block_allows_movement(Block * block, char direction);
        bool can_potentially_move_block(Block * block, char direction);
        bool tabs_impede(Block * block, char direction);
        bool tabs_always_impede(Block * block, char direction);
        bool tabs_temporarily_impede(Block * block, char direction);
        bool movement_is_tablocked_by_adjacent(Block * block, char direction);
        bool movement_is_temporarily_tablocked_by_adjacent(Block * block, char direction);
        bool movement_is_tablocked_by_self(Block * block, char direction);
        bool movement_is_temporarily_tablocked_by_self(Block * block, char direction);
        bool side_is_tablocked(Block * block, char direction);
        bool side_is_temporarily_tablocked(Block * block, char direction);
        bool side_is_always_tablocked_by_adjacent(Block * block, char direction);
        bool side_is_tablocked_by_adjacent(Block * block, char direction);
        bool side_is_temporarily_tablocked_by_adjacent(Block * block, char direction);
        bool side_is_tablocked_by_self(Block * block, char direction);
        bool side_is_temporarily_tablocked_by_self(Block * block, char direction);
        bool can_move(int block_x, int block_y, char direction);
        bool try_move(int x, int y, char direction);
        bool try_move_selected(char direction);
        bool is_selected_location_valid();
        void remove_block(int x, int y);
        bool tap_selected();
        bool get_is_clear();
        void add_wrong_move();
        int get_blocks_removed_ct();
        bool block_is_move_restricted(int, int);
        bool selected_block_is_move_restricted();
        void set_GameState(GameState &state);
        void init_current_board();
        int get_max_level();
        void set_max_level(int);
        int get_cur_level();
        void set_cur_level(int);
        void increment_cur_level();
};

#endif //CLEAR_GAMELOGIC_HPP
