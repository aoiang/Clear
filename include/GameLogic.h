//
// Created by Yiyang Zhao on 22/10/2017
// Additional work by Ivan & Yosef
//

#ifndef CLEAR_GAMELOGIC_H
#define CLEAR_GAMELOGIC_H

#include "Block.h"
#include "Normal_Block.h"
#include "GameBoard.hpp"
#include <SFML/Graphics.hpp>

class GameLogic {
private:
    GameBoard board;
    int board_width = 10;
    int board_height = 10;
    int board_array[10][10] = {{0}};
    int selected_x = -1;
    int selected_y = -1;
public:
    void init();
    void block_init();
    bool detect_collision(int x, int y, std::string direction);
    void try_move(std::string direction);
    void check_mousePosition(sf::RenderWindow App);

    int get_selected_x();
    int get_selected_y();
    int get_selected_block();
    void set_selected_x(int x);
    void set_selected_y(int y);
    void set_selected_position(int x, int y);

    int get_board_width();
    int get_board_height();
    int is_valid_x(int x);
    int is_valid_y(int y);
    int is_valid_location(int x, int y);
    int is_selected_location_valid();

    int get_block(int x, int y);
    void remove_block(int x, int y);
};

#endif
