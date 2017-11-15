//
// Created by Yiyang Zhao on 16/10/2017.
// Additional work by Ivan & Yosef
//

#include <SFML/Graphics.hpp>
#include "GameLogic.hpp"
#include "GameBoard.hpp"
#include "GameView.hpp"

int main(int argc, char** argv) {

    if (!sf::Shader::isAvailable()) {
        std::cerr << "Shaders are not available." << std::endl;
        return EXIT_FAILURE;
    }

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
