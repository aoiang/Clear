//
// Created by Yiyang Zhao on 28/11/2017.
//

#include "Generator.h"

Generator::block_type Generator::init_block_type() {
    Generator::block_type block;
    block.direction = 0;
    block.block_rotation = 0;
    block.local_rotation = 0;
    block.exist = 0;
    for (int i = 0; i <= 3; i++ ){
        block.tab[i] = 0;
    }
    return block;
}

Generator::block_type Generator::block_type_generator() {
    Generator::block_type block;
    block.exist = 1;
    block.direction = 0;
    block.block_rotation = 0;
    block.local_rotation = 0;
    for (int i = 0; i <= 3; i++ ){
        block.tab[i] = 0;
    }
    //printf("%d, %d\n",random_list[block_num], block_num);
    int magic_num_type = random_list[block_num]%9;
    if (magic_num_type <= 0){
        block.local_rotation = 1;
    }
    else if (magic_num_type <= 2){
        block.block_rotation = 1;
        int magic_num_tab = rand()%7;

        if (magic_num_tab <= 2) {
            block.tab[rand()%4] = 1;
        }
        magic_num_tab = rand()%7;

        if (magic_num_tab <= 2) {
            block.tab[rand()%4] = 1;
        }
        magic_num_tab = rand()%7;

        if (magic_num_tab <= 2) {
            block.tab[rand()%4] = 1;
        }
        magic_num_tab = rand()%7;
        if (magic_num_tab <= 2) {
            block.tab[rand()%4] = 1;
        }
        if (block.tab[0] + block.tab[1] + block.tab[2] + block.tab[3] == 0){
            block.tab[rand()%4] = 1;
        }
        printf("%d,%d,%d,%d\n", block.tab[0], block.tab[1],block.tab[2],  block.tab[3]);
        if (block.tab[0] + block.tab[1] + block.tab[2] + block.tab[3] == 4){
            block.tab[rand()%4] = 0;
        }
    } else if (magic_num_type <= 7){
        int magic_num_direction = rand()%4;
        if (magic_num_direction == 0){
            block.direction = 1;
        }
        if (magic_num_direction == 1){
            block.direction = 2;
        }
        if (magic_num_direction == 2){
            block.direction = 3;
        }
        if (magic_num_direction == 3){
            block.direction = 4;
        }
    }
    return block;
}

void Generator::board_generator(int centers) {
    for(int x = 0; x < 10; x++){
        for(int y = 0; y < 10; y++){
            board[x][y] = init_block_type();
        }
    }
    int adj_point[100];
    for (int j =0; j < centers; j++){
        block_num = rand() % 47 + 10;
        int num = rand() % 99;
        for (int i = 0; i < 100; i++){
            adj_point[i] = 0;
        }
        int sum_adj;
        bool in_list_flag;
        while (block_num){
            in_list_flag = false;
            sum_adj = 0;
            for (int i = 0; i < 100; i++){
                sum_adj += adj_point[i];
            }
            if (sum_adj != 0){
                random_shuffle(&adj_point[0], &adj_point[100]);
                for (int i = 0; i < 100; i++){
                    if (adj_point[i] != 0){
                        num = adj_point[i];
                        adj_point[i] = 0;
                        break;
                    }
                }
            }
            //printf("%d\n",num);
            w = num / 10;
            h = num % 10;
            if (board[w][h].exist == 0){
                board[w][h] = block_type_generator();
            }
            //board[w][h] = block_type_generator();



            for (int i = 0; i < 100; i++){
                if (num - 10 == adj_point[i]){
                    in_list_flag = true;
                }
            }
            if (num - 10 >= 0 && !in_list_flag){
                for (int i = 0; i < 100; i++){
                    if (adj_point[i] == 0){
                        adj_point[i] = num - 10;
                        break;
                    }
                }
            }
            in_list_flag = false;

            for (int i = 0; i < 100; i++){
                if (num + 10 == adj_point[i]){
                    in_list_flag = true;
                }
            }
            if (num + 10 >= 99 && !in_list_flag){
                for (int i = 0; i < 100; i++){
                    if (adj_point[i] == 0){
                        adj_point[i] = num + 10;
                        break;
                    }
                }
            }
            in_list_flag = false;

            for (int i = 0; i < 100; i++){
                if (num - 1 == adj_point[i]){
                    in_list_flag = true;
                }
            }
            if (num - 1 >= 0 && !in_list_flag){
                for (int i = 0; i < 100; i++){
                    if (adj_point[i] == 0){
                        adj_point[i] = num - 1;
                        break;
                    }
                }
            }
            in_list_flag = false;

            for (int i = 0; i < 100; i++){
                if (num + 1 == adj_point[i]){
                    in_list_flag = true;
                }
            }
            if (num + 1 >= 99 && !in_list_flag){
                for (int i = 0; i < 100; i++){
                    if (adj_point[i] == 0){
                        adj_point[i] = num + 1;
                        break;
                    }
                }
            }
            block_num--;
        }

    }
}

void Generator::init_random_list() {
    srand((unsigned)time(NULL));
    int index;
    int temp;
    for (int i = 0; i < 100; i++){
        random_list[i] = i;
    }
    for (int i = 0; i < 100; i++){
        index = rand()%100;
        temp = random_list[i];
        random_list[i] = random_list[index];
        random_list[index] = temp;
    }
}
