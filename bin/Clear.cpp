//
// Created by Yiyang Zhao on 16/10/2017.
// Additional work by Ivan & Yosef
//

#include <SFML/Graphics.hpp>
#include "GameLogic.hpp"
#include "GameView.hpp"
#include "GameStateLoader.hpp"

int main(int argc, char** argv) {
    auto * board = new BoardState(LEVEL_01);
    GameView view;
    GameLogic logic;

    logic.set_BoardState(*board);
    view.run(logic);

    return 0;
}
