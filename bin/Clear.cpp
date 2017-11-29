//
// Created by Yiyang Zhao on 16/10/2017.
// Additional work by Ivan & Yosef
//

#include <SFML/Graphics.hpp>
#include "GameLogic.hpp"
#include "GameBoard.hpp"
#include "GameView.hpp"
#include "Screens.hpp"
#include "GameBoardLoader.hpp"

int main(int argc, char** argv) {
    GameBoard * board = GameBoardLoader::loadGameBoard(LEVEL_TEST);
    GameView view;
    GameLogic logic;

    logic.set_GameBoard(*board);
    view.run(logic);

    return 0;
}
