//
// Created by Yiyang Zhao on 16/10/2017.
// Additional work by Ivan & Yosef
//

#include <SFML/Graphics.hpp>
#include "GameLogic.h"
#include "GameBoard.hpp"
#include "GameView.h"

int main(int argc, char** argv) {
    GameView view;
    GameLogic logic;
    GameBoard board;

    board.init(10, 10);
    logic.set_GameBoard(board);
    view.set_GameLogic(logic);
    view.init();

    while(view.isOpen()) {
        view.update();
    }

    return 0;
}
