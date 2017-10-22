//
// Created by Yiyang Zhao on 16/10/2017.
// Additional work by Ivan Echevarria
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
    view.init(state.get_Normal_Block());
    while(view.isOpen()) {
        view.check_mousePosition(state.get_Normal_Block());
        state.check_keyboard_in();
        view.draw(state.get_Normal_Block());
    }
    return 0;
}
