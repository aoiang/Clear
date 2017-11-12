//
// Created by Yiyang Zhao on 16/10/2017.
// Additional work by Ivan & Yosef
//

#include <SFML/Graphics.hpp>
#include "GameLogic.h"
#include "GameView.h"

int main(int argc, char** argv) {
    int length = 800;//TODO make this a global var or input
    int width = 600;//TODO make this a global var or input
    GameView view(length, width);
    GameLogic logic;
    logic.init();
    view.set_GameLogic(logic);
    view.init();
    while(view.isOpen()) {
        view.update();
    }
    return 0;
}
