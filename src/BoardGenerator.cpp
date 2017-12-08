#include "BoardGenerator.hpp"

int BoardGenerator::type_ratio[6];
BoardGenerator::BoardGenerator() {
    number_generator = get_random_num_generator();
}

BoardState * BoardGenerator::make_board(GameLogic logic) {
    this->width = logic.get_generated_board_x();
    this->height = logic.get_generated_board_y();
    board = new BoardState(width, height);
    state = new GameState();
    generator_logic.set_GameState(*state);
    generator_logic.set_BoardState(*board);
    
    for (int i=0; i<6; i++) {
        int typeval = 0;
        int frequency = 0;
        switch (i) {
            case 0: case 1: frequency = logic.get_nums_of_nor(); break;
            case 2: case 3: frequency = logic.get_nums_of_dir(); break;
            case 4: case 5: frequency = logic.get_nums_of_rot(); break;
        }
        if (i%2 < frequency) {typeval = (i/2)+1;}
        type_ratio[i] = typeval;
    }
    
    int poten_locs = potential_locations();
    while (poten_locs) {
        while (poten_locs) {
            //std::cout << poten_locs << "potential locations left!!\n";
            add_block_if_possible();
            poten_locs = potential_locations();
        }
        remove_pointless_tabs();
        poten_locs = potential_locations();
    }
    
    return board;
}

BoardState * BoardGenerator::make_board(GameLogic logic, std::string filepath) {
    make_board(logic);
    board->export_board(filepath);
    return board;
}

void BoardGenerator::add_block_if_possible(int x, int y) {
    //note that sometimes, even if not blocked, any block could be locked in place by tabs. (possible for no block to be addable even if )
    //this is poc, it'll make a super easy board lol.
    while (potential_location(x, y)) {
        Block * potential_block = Block::import_block(pick_config(), x, y);
        if (generator_logic.potentially_removable(potential_block)) {
            board->add_block(potential_block);
        }
    }
}

void BoardGenerator::add_block_if_possible() {
    int x, y;
    std::tie(x, y) = pick_location();
    add_block_if_possible(x, y);
}

std::mt19937 BoardGenerator::get_random_num_generator() {
    //Adapted from https://stackoverflow.com/a/7560564/4710015
    std::random_device rd; //Obtain a random number from hardware
    std::mt19937 eng(rd()); //Seed the generator
    return eng;
}

int BoardGenerator::pick_type() {
    int type = 0;
    while (type==0) {
        type = type_ratio[pick_number_between(0, 5)];
    }
    for (int i=0; i<6; i++) {
        //std::cerr << type_ratio[i];
    }
    //std::cerr << std::endl;
    return type;
}

std::string BoardGenerator::pick_config() {
    std::string config = "0";
    std::string type = std::to_string(pick_type());
    static const char* const configs[number_of_configs] = {"1,0,0,ffff,0","1,0,0,ffft,0","1,0,0,fftf,0","1,0,0,fftt,0","1,0,0,ftff,0","1,0,0,ftft,0","1,0,0,fttf,0","1,0,0,fttt,0","1,0,0,tfff,0","1,0,0,tfft,0","1,0,0,tftf,0","1,0,0,tftt,0","1,0,0,ttff,0","1,0,0,ttft,0","1,0,0,tttf,0","1,0,0,tttt,0","2,0,0,ffff,0","2,0,0,ffft,0","2,0,0,fftf,0","2,0,0,fftt,0","2,0,0,ftff,0","2,0,0,fttt,0","2,0,0,fttf,0","2,0,0,fttt,0","2,0,0,tfff,0","2,0,0,tfft,0","2,0,0,tftf,0","2,0,0,tftt,0","2,0,0,ttff,0","2,0,0,ttft,0","2,0,0,tttf,0","2,0,0,tttt,0","2,1,0,ffff,0","2,1,0,ffft,0","2,1,0,fftf,0","2,1,0,fftt,0","2,1,0,ftff,0","2,1,0,ftft,0","2,1,0,fttf,0","2,1,0,fttt,0","2,1,0,tfff,0","2,1,0,tfft,0","2,1,0,tftf,0","2,1,0,tftt,0","2,1,0,ttff,0","2,1,0,ttft,0","2,1,0,tttf,0","2,1,0,tttt,0","2,2,0,ffff,0","2,2,0,ffft,0","2,2,0,fftf,0","2,2,0,fftt,0","2,2,0,ftff,0","2,2,0,ftft,0","2,2,0,fttf,0","2,2,0,fttt,0","2,2,0,tfff,0","2,2,0,tfft,0","2,2,0,tftf,0","2,2,0,tftt,0","2,2,0,ttff,0","2,2,0,ttft,0","2,2,0,tttf,0","2,2,0,tttt,0","2,3,0,ffff,0","2,3,0,ffft,0","2,3,0,fftf,0","2,3,0,fftt,0","2,3,0,ftff,0","2,3,0,ftft,0","2,3,0,fttf,0","2,3,0,fttt,0","2,3,0,tfff,0","2,3,0,tfft,0","2,3,0,tftf,0","2,3,0,tftt,0","2,3,0,ttff,0","2,3,0,ttft,0","2,3,0,tttf,0","2,3,0,tttt,0","3,0,0,tftf,0","3,1,0,tftf,0","3,0,0,ttff,0","3,1,0,ttff,0","3,2,0,ttff,0","3,3,0,ttff,0","3,0,0,ttft,0","3,1,0,ttft,0","3,2,0,ttft,0","3,3,0,ttft,0"};
    //"3,0,0,ffff,0","3,0,0,tttt,0",
    //"3,0,0,tfff,0","3,1,0,tfff,0","3,2,0,tfff,0","3,3,0,tfff,0",
    while (config.compare(0, 1, type) != 0) {
        config = configs[pick_number_between(0, number_of_configs-1)];
    }
    return config;
}

int BoardGenerator::pick_number_between(int min, int max) {
    std::uniform_int_distribution<> distr(min, max);
    return distr(number_generator);
}

int BoardGenerator::random_x() {return pick_number_between(0, width-1);}
int BoardGenerator::random_y() {return pick_number_between(0, height-1);}

std::tuple<int, int> BoardGenerator::pick_location() {
    int current_valid_locations = potential_locations();
    int current_removeable = potentially_removable_blocks();
    int minimum_removeable = potentially_removable_blocks();
    int x, y, score, best_x, best_y;
    int best_score = -999;//can't be 0 to start.
    bool found_location = false;
    Block * block;
    //std::cout << "checking\n";
    for (int i=0; i<(width*height); i++) {
        x = random_x();
        y = random_y();
        //std::cerr << x << "," << y << std::endl;
        if (!board->block_exists(x, y) && potential_location(x, y)) {
            block = Block::import_block("1,0,0,ffff,0", x, y);
            board->add_block(block);
            score = potential_locations()-potentially_removable_blocks();
            if (score>=best_score) {
                best_x = x;
                best_y = y;
                best_score = score;
            }
            board->remove_block(x, y);
        }
    }
    return std::make_tuple(best_x, best_y);
}

bool BoardGenerator::potential_location(int x, int y) {
    return !board->block_exists(x, y)
        && board->is_valid_location(x, y)
        && generator_logic.potentially_removable(Block::import_block("1,0,0,ffff,0", x, y));
}

int BoardGenerator::potential_locations() {
    int potential_location_count = 0;
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            if (potential_location(x, y)) {potential_location_count++;}
        }
    }
    return potential_location_count;
}

int BoardGenerator::removable_blocks() {
    int removable_block_count = 0;
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            if (board->block_exists(x, y) && generator_logic.can_be_removed(x, y)) {removable_block_count++;}
        }
    }
    return removable_block_count;
}

int BoardGenerator::potentially_removable_blocks() {
    int potentially_removable_block_count = 0;
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            if (board->block_exists(x, y) && generator_logic.potentially_removable(x, y)) {potentially_removable_block_count++;}
        }
    }
    return potentially_removable_block_count;
}


void BoardGenerator::remove_pointless_tabs() {
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
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
