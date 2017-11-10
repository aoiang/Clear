//
// Created by Yiyang Zhao on 22/10/2017
// Additional work by Ivan & Yosef
//

#ifndef CLEAR_GAMELOGIC_H
#define CLEAR_GAMELOGIC_H

#include "Block.h"
#include "Normal_Block.h"
#include <SFML/Graphics.hpp>

class GameLogic {
private:
    int board_width = 10;
    int board_height = 10;
    int board_array[10][10] = {{0}};
    int selected_col = -1;
    int selected_row = -1;
public:
    void init();
    void block_init();
    bool collision_detector(int current_block_row, int current_block_col, std::string direction);
    void try_move(std::string direction);
    void check_mousePosition(sf::RenderWindow App);

    int get_selected_col();
    int get_selected_row();
    void set_selected_col(int col);
    void set_selected_row(int row);
    void set_selected_position(int row, int col);

    int get_board_width();
    int get_board_height();

    int get_block(int x, int y);
};

#endif
