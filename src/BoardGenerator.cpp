#include "BoardGenerator.hpp"
#include "BoardState.hpp"
#include <iostream>
#include <random>

BoardGenerator::BoardGenerator() {number_generator = get_random_num_generator();}

BoardState * BoardGenerator::make_board(int width, int height) {
    board = new BoardState(width, height);
    state = new GameState();
    generator_logic.set_GameState(*state);
    generator_logic.set_BoardState(*board);
    
    for (int i=0; i<(width*height*10); i++) {
        add_block_if_possible(pick_number_between(0, width-1), pick_number_between(0, height-1));        
    }
    remove_pointless_tabs();
    
    for (int i=0; i<(width*height*10); i++) {
        add_block_if_possible(pick_number_between(0, width-1), pick_number_between(0, height-1));        
    }
    remove_pointless_tabs();
    
    return board;
}

BoardState * BoardGenerator::make_board(int width, int height, std::string filepath) {
    make_board(width, height);
    board->export_board(filepath);
    return board;
}

void BoardGenerator::add_block_if_possible(int x, int y) {
    //note that sometimes, even if not blocked, any block could be locked in place by tabs. (possible for no block to be addable even if )
    //this is poc, it'll make a super easy board lol.
    if (!generator_logic.can_be_removed(Block::import_block("1,0,f,ffff,0", x, y))) {return;}
    while (!board->block_exists(x, y)) {
        Block * potential_block = Block::import_block(pick_config(), x, y);
        if (generator_logic.can_be_removed(potential_block)) {board->add_block(potential_block);}
    }
}

std::mt19937 BoardGenerator::get_random_num_generator() {
    //Adapted from https://stackoverflow.com/a/7560564/4710015
    std::random_device rd; //Obtain a random number from hardware
    std::mt19937 eng(rd()); //Seed the generator
    return eng;
}

std::string BoardGenerator::pick_config() {
    static const char* const configs[number_of_configs] = {"1,0,f,ffff,0","1,0,f,ffft,0","1,0,f,fftf,0","1,0,f,fftt,0","1,0,f,ftff,0","1,0,f,ftft,0","1,0,f,fttf,0","1,0,f,fttt,0","1,0,f,tfff,0","1,0,f,tfft,0","1,0,f,tftf,0","1,0,f,tftt,0","1,0,f,ttff,0","1,0,f,ttft,0","1,0,f,tttf,0","1,0,f,tttt,0","2,0,f,ffff,0","2,0,f,ffft,0","2,0,f,fftf,0","2,0,f,fftt,0","2,0,f,ftff,0","2,0,f,ftft,0","2,0,f,fttf,0","2,0,f,fttt,0","2,0,f,tfff,0","2,0,f,tfft,0","2,0,f,tftf,0","2,0,f,tftt,0","2,0,f,ttff,0","2,0,f,ttft,0","2,0,f,tttf,0","2,0,f,tttt,0","2,1,f,ffff,0","2,1,f,ffft,0","2,1,f,fftf,0","2,1,f,fftt,0","2,1,f,ftff,0","2,1,f,ftft,0","2,1,f,fttf,0","2,1,f,fttt,0","2,1,f,tfff,0","2,1,f,tfft,0","2,1,f,tftf,0","2,1,f,tftt,0","2,1,f,ttff,0","2,1,f,ttft,0","2,1,f,tttf,0","2,1,f,tttt,0","2,2,f,ffff,0","2,2,f,ffft,0","2,2,f,fftf,0","2,2,f,fftt,0","2,2,f,ftff,0","2,2,f,ftft,0","2,2,f,fttf,0","2,2,f,fttt,0","2,2,f,tfff,0","2,2,f,tfft,0","2,2,f,tftf,0","2,2,f,tftt,0","2,2,f,ttff,0","2,2,f,ttft,0","2,2,f,tttf,0","2,2,f,tttt,0","2,3,f,ffff,0","2,3,f,ffft,0","2,3,f,fftf,0","2,3,f,fftt,0","2,3,f,ftff,0","2,3,f,ftft,0","2,3,f,fttf,0","2,3,f,fttt,0","2,3,f,tfff,0","2,3,f,tfft,0","2,3,f,tftf,0","2,3,f,tftt,0","2,3,f,ttff,0","2,3,f,ttft,0","2,3,f,tttf,0","2,3,f,tttt,0","3,0,f,tfff,0","3,1,f,tfff,0","3,2,f,tfff,0","3,3,f,tfff,0","3,0,f,tftf,0","3,1,f,tftf,0","3,0,f,ttff,0","3,1,f,ttff,0","3,2,f,ttff,0","3,3,f,ttff,0","3,0,f,ttft,0","3,1,f,ttft,0","3,2,f,ttft,0","3,3,f,ttft,0"};
    return configs[pick_number_between(0, number_of_configs-1)];
}

int BoardGenerator::pick_number_between(int min, int max) {
    std::uniform_int_distribution<> distr(min, max);
    return distr(number_generator);
}


void BoardGenerator::remove_pointless_tabs() {
    for (int y=0; y<board->get_board_height(); y++) {
        for (int x=0; x<board->get_board_width(); x++) {
            if (board->block_exists(x, y)) {
                Block * block = board->get_block(x, y);
                if (block->get_simple_id()!=3) {
                    if (!board->block_exists(x, y+1)) {block->set_tab(U_DIR, false);}
                    if (!board->block_exists(x+1, y)) {block->set_tab(R_DIR, false);}
                    if (!board->block_exists(x, y-1)) {block->set_tab(D_DIR, false);}
                    if (!board->block_exists(x-1, y)) {block->set_tab(L_DIR, false);}
                }
            }
        }
    }
}
