#include "GameBoardLoader.hpp"
#include "Normal_Block.hpp"
#include "Directional_Block.hpp"
#include "Rotating_Block.hpp"
#include <fstream>
using namespace std;

GameBoard * GameBoardLoader::loadGameBoard(std::string filepath) {
    GameBoard * board = new GameBoard();
    board->init();

    ifstream inFile;
    inFile.open(filepath);

    int ct = 0;
    string entry;

    while(inFile >> entry) {
        if (entry == "0") {}
        else {
            Block * block;

            if (entry.substr(0, 2) == "10") {block = new Normal_Block(ct % 9, 8 - (ct / 9));}
            else if (entry.substr(0, 2) == to_string(ID_U_DIR)) {block = new Directional_Block(ct % 9, 8 - (ct / 9), 0);}
            else if (entry.substr(0, 2) == to_string(ID_R_DIR)) {block = new Directional_Block(ct % 9, 8 - (ct / 9), 1);}
            else if (entry.substr(0, 2) == to_string(ID_D_DIR)) {block = new Directional_Block(ct % 9, 8 - (ct / 9), 2);}
            else if (entry.substr(0, 2) == to_string(ID_L_DIR)) {block = new Directional_Block(ct % 9, 8 - (ct / 9), 3);}
            else if (entry.substr(0, 2) == to_string(ID_ROTATE_0)) {block= new Rotating_Block(ct % 9, 8 - (ct / 9));}
            else {
                cout << "Invalid block at " << ct%9 << ", " << ct/9 << endl;
                break;
            }

            if (entry.substr(2, 1) == "1") {block->set_tab('u', true);}
            if (entry.substr(3, 1) == "1") {block->set_tab('r', true);}
            if (entry.substr(4, 1) == "1") {block->set_tab('d', true);}
            if (entry.substr(5, 1) == "1") {block->set_tab('l', true);}

            board->add_block(block);
        }
        ct ++;
    }

    cout << "Level loaded from " << filepath << endl << endl;
    inFile.close();
    return board;
}
