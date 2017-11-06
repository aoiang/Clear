//
// Created by Yiyang Zhao on 16/10/2017.
// Additional work by Ivan & Yosef
//

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "GameView.h"

int main(int argc, char** argv) {
    int length = 800;
    int width = 600;
    GameView view(length, width);
    GameState state;
    state.init();
    view.set_GameState(state);
    view.init();
    while(view.isOpen()) {
        view.update();
    }
    return 0;
}
