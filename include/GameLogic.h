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
#include <iostream>
#include <string>

class GameLogic {
private:
    GameBoard * board;
    int selected_x = -1;
    int selected_y = -1;
public:
    bool detect_collision(int x, int y, std::string direction);
    bool path_blocked(int x, int y, std::string direction);
    bool can_move(int block_x, int block_y, std::string direction);
    void try_move_any(int x, int y, std::string direction);
    void try_move_selected(std::string direction);
    void try_move(std::string direction);
    void check_mousePosition(sf::RenderWindow App);
    void set_GameBoard(GameBoard &board);

    int get_selected_x();
    int get_selected_y();
    int get_selected_block();
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
