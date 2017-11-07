//
// Created by Yiyang Zhao on 18/10/2017.
// Additional work by Ivan & Yosef
//

#ifndef CLEAR_GAMEVIEW_H
#define CLEAR_GAMEVIEW_H

#include <SFML/Graphics.hpp>
#include "Block.h"
#include "Normal_Block.h"
#include "GameLogic.h"

class GameView {
private:
    sf::Texture texture[15];
    Normal_Block block[5];
    sf::RectangleShape * block_shapes;
    GameLogic *logic;
public:
    sf::RenderWindow App;
    GameView(float, float);
    void init();
    bool isOpen();
    void draw();
    void poll_event();
    sf::RectangleShape make_block_shape(Normal_Block block);
    void check_mouse_position();
    void block_init();
    void check_keyboard_in();
    bool collision_detector(sf::RectangleShape current_b, sf::RectangleShape * b, std::string direction);
    sf::RenderWindow get_App();
    int draw_selected_block(Normal_Block * normal_block);
    void draw_movement(Normal_Block * normal_block);
    void set_GameLogic(GameLogic &logic);
    void update();
};


#endif //CLEAR_GAMEVIEW_H
