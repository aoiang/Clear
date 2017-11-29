#include "GameBoardLoader.hpp"
#include "Normal_Block.hpp"
#include "Directional_Block.hpp"
#include "Rotating_Block.hpp"

GameBoard * GameBoardLoader::loadGameBoard(std::string filepath) {
    std::cout << "Loading level from " << filepath << std::endl << std::endl;

    GameBoard * board = new GameBoard();
    board->init();

    int width = board->get_board_width();
    int height = board->get_board_height();

    for(int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {
            //TODO need way to delete these objects. put that in the remove?
            Block * block;
            if (y%5 == 0) {
                block = new Rotating_Block(x, y);
                // block = new Normal_Block(x, y);
                // tabs set here
                block->set_tab('u', true);
                block->set_tab('r', true);
                // block->set_tab('d', true);
                // block->set_tab('l', true);
                board->add_block(block);

            } else if ((x+y)%3) {
              block = new Directional_Block(x, y, y%4);
              board->add_block(block);
            }
        }
    }

    return board;
}
