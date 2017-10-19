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
    sf::RenderWindow App;
    sf::Texture texture[15];
    Normal_Block block[4];





public:

    GameView(int, int);
    ~GameView(){};
    sf::RectangleShape* init();
    bool isOpen();
    void draw(sf::RectangleShape b[]);
    void poll_event();
    sf::RectangleShape block_generator(int i);
    void check_mousePosition(sf::RectangleShape block[]);
    void block_init();
    void check_keyboard_in(sf::RectangleShape *b);
    void collision_detector(sf::RectangleShape *b);


};


#endif //CLEAR_GAMEVIEW_H
