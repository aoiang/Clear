#ifndef CLEAR_GENERATOR_HPP
#define CLEAR_GENERATOR_HPP

#include <iostream>
#include <stdlib.h>
#include <algorithm>
using namespace std;

class Generator {
private:
    int block_num;
    int w;
    int h;
    int random_list[100];
    struct block_type{
        int exist;
        int direction;
        int block_rotation;
        int local_rotation;
        int tab[4];
    };

public:
    void init_random_list();
    block_type block_type_generator();
    block_type board[10][10];
    void board_generator(int centers);
    block_type init_block_type();
    bool solver(block_type boa[100][100]);
};

#endif //CLEAR_GENERATOR_HPP
