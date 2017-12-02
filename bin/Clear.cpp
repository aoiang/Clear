//
// Created by Yiyang Zhao on 16/10/2017.
// Additional work by Ivan & Yosef
//

#include <SFML/Graphics.hpp>
#include "GameLogic.hpp"
#include "GameView.hpp"
#include "BoardStateLoader.hpp"

int main(int argc, char** argv) {
    BoardState * board = BoardStateLoader::loadBoardState(LEVEL_01);
    GameView view;
    GameLogic logic;

    logic.set_BoardState(*board);
    view.run(logic);

    return 0;
}
