//
// Created by Yiyang Zhao on 16/10/2017.
//


#include <SFML/Graphics.hpp>
#include <stdlib.h>

#include "GameView.h"
#include "Block.h"




int main(int argc, char** argv) {
    // create main Window


    int length = 800;
    int width = 600;
    GameView view(length, width);
    sf::RectangleShape* b = view.init();
    while(view.isOpen()) {
        view.draw(b);
    }
    return 0;

}
