//
// Created by Yiyang Zhao on 16/10/2017.
// Additional work by Ivan & Yosef
//

#include <SFML/Graphics.hpp>
#include "GameLogic.hpp"
#include "GameView.hpp"

int main(int argc, char** argv) {
    GameView view;
    GameLogic logic;
    GameState * state = new GameState();
    logic.set_GameState(*state);

    view.run(logic);
    return 0;
}
