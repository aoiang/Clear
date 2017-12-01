#include "BoardStateLoader.hpp"
#include "BlockNormal.hpp"
#include "BlockDirectional.hpp"
#include "BlockRotating.hpp"
#include <fstream>
#include <string>

/**
  Loads BoardState from file
  @param filepath to load from
  @return BoardState built from file
*/
BoardState * BoardStateLoader::loadBoardState(std::string filepath) {
    BoardState * board = new BoardState();
    board->init();
    
    std::ifstream inFile;
    inFile.open(filepath);
    
    int entry_ct = 0;
    int block_ct = 0;
    std::string entry;
    
    while(inFile >> entry) {
        if (entry != "0") {
            Block * block;
            
            int x = entry_ct%9;
            int y = 8-(entry_ct/9);
            
            int direction = 0;
            switch (std::stoi(entry.substr(0, 2))) {
                case 10:
                    block = new BlockNormal(x, y);
                    break;
                case ID_L_DIR: direction++;
                case ID_D_DIR: direction++;
                case ID_R_DIR: direction++;
                case ID_U_DIR:
                    block = new BlockDirectional(x, y, direction);
                    break;
                case ID_ROTATE_0:
                    block = new BlockRotating(x, y);
                    break;
                default:
                    std::cout << "Invalid block at " << x << ", " << entry_ct/9 << std::endl;
            }
            
            if (entry.substr(3, 1) == "1") {block->set_tab('u', true);}
            if (entry.substr(4, 1) == "1") {block->set_tab('r', true);}
            if (entry.substr(5, 1) == "1") {block->set_tab('d', true);}
            if (entry.substr(6, 1) == "1") {block->set_tab('l', true);}
            
            block->set_move_restriction(std::stoi(entry.substr(8, 2)));
            
            board->add_block(block);
        }
        entry_ct++;
    }
    
    std::cout << "Level loaded from " << filepath << std::endl << std::endl;
    inFile.close();
    return board;
}
