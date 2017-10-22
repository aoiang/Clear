//
// Created by Yiyang Zhao on 18/10/2017.
//

#ifndef CLEAR_GAMEVIEW_H
#define CLEAR_GAMEVIEW_H

#include <SFML/Graphics.hpp>
#include "Block.h"
#include "Normal_Block.h"

class GameView {
private:

    sf::Texture texture[15];
    Normal_Block block[5];









public:
    sf::RenderWindow App;
    GameView(float, float);
    //~GameView(){};
    sf::RectangleShape* init(Normal_Block *block);
    bool isOpen();
    void draw(Normal_Block *normal_block, sf::RectangleShape b[]);
    void poll_event();
    sf::RectangleShape directed_block_generator(Normal_Block *normal_block, int i);
    Normal_Block* check_mousePosition(Normal_Block *normal_block);
    void block_init();
    void check_keyboard_in(sf::RectangleShape *b);
    bool collision_detector(sf::RectangleShape current_b, sf::RectangleShape *b, std::string direction);
    sf::RenderWindow get_App();
    void draw_selected_block(Normal_Block *normal_block, sf::RectangleShape *b);
    void draw_movement(Normal_Block *normal_block, sf::RectangleShape *b);


};


#endif //CLEAR_GAMEVIEW_H
