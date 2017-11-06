//
// Created by Yiyang Zhao on 16/10/2017.
// Additional work by Ivan & Yosef
//

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "GameView.h"

int main(int argc, char** argv) {
    // create main Window
    float length = 800;
    float width = 600;
    GameView view(length, width);
    //printf("dafdsafdasf\n");
    GameState state;
    state.init();
    view.set_GameState(state);
    view.init();
    while(view.isOpen()) {
        view.check_mousePosition(state.get_Normal_Block());
        view.check_keyboard_in();
        view.draw(state.get_Normal_Block());
    }
    return 0;
}
