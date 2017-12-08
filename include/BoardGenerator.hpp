#ifndef CLEAR_BOARD_GENERATOR_HPP
#define CLEAR_BOARD_GENERATOR_HPP

#include "GameLogic.hpp"
#include "BoardState.hpp"
#include <random>

class BoardGenerator {
    private:
        GameLogic generator_logic;
        GameState * state;
        BoardState * board;
        int width;
        int height;
        static const int number_of_configs = 90;
        static int type_ratio[6];
        void add_block_if_possible(int x, int y);
        void add_block_if_possible();
        std::mt19937 get_random_num_generator();
        std::mt19937 number_generator;
        std::string pick_config();
        int pick_type();
        int pick_number_between(int min, int max);
        int random_x();
        int random_y();
        std::tuple<int, int> pick_location();
        bool potential_location(int x, int y);
        int potential_locations();
        int removable_blocks();
        int potentially_removable_blocks();
        void remove_pointless_tabs();
    public:
        BoardGenerator();
        BoardState * make_board(int width, int height);
        BoardState * make_board(int width, int height, std::string filepath);
};

#endif //CLEAR_BOARD_GENERATOR_HPP
