//
// Created by Yiyang Zhao on 16/10/2017.
//


#include <SFML/Graphics.hpp>


#include "GameView.h"
#include "GameState.h"




int main(int argc, char** argv) {
    // create main Window


    float length = 800;
    float width = 600;
    GameView view(length, width);
    GameState state;
    state.init();
    sf::RectangleShape* b = view.init(state.get_Normal_Block());
    while(view.isOpen()) {
        view.check_mousePosition(state.get_Normal_Block());
        state.check_keyboard_in();
        view.draw(state.get_Normal_Block(), b);
    }
    return 0;

}
