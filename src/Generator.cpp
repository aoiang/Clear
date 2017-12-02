//
// Created by Yiyang Zhao on 28/11/2017.
//

#include "Generator.hpp"

Generator::block_type Generator::init_block_type() {
    Generator::block_type block;
    block.direction = 0;
    block.block_rotation = 0;
    block.local_rotation = 0;
    block.exist = 0;
    for (int i = 0; i <= 3; i++ ) {
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
    for (int i = 0; i <= 3; i++ ) {
        block.tab[i] = 0;
    }
    //printf("%d, %d\n",random_list[block_num], block_num);
    int magic_num_type = random_list[block_num]%9;
    if (magic_num_type <= -1) {
        block.local_rotation = 1;
    }
    else if (magic_num_type <= 2) {
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
        if (block.tab[0] + block.tab[1] + block.tab[2] + block.tab[3] == 0) {
            block.tab[rand()%4] = 1;
        }
        //printf("%d,%d,%d,%d\n", block.tab[0], block.tab[1],block.tab[2],  block.tab[3]);
        if (block.tab[0] + block.tab[1] + block.tab[2] + block.tab[3] == 4) {
            block.tab[rand()%4] = 0;
        }
    } else if (magic_num_type <= 8) {
        int magic_num_direction = rand()%4;
        if (magic_num_direction == 0) {
            block.direction = 1;
        }
        if (magic_num_direction == 1) {
            block.direction = 2;
        }
        if (magic_num_direction == 2) {
            block.direction = 3;
        }
        if (magic_num_direction == 3) {
            block.direction = 4;
        }
    }
    return block;
}

void Generator::board_generator(int centers) {
    bool solvable = false;
    while (!solvable) {
        for (auto &x : board) {
            for (auto &y : x) {
                y = init_block_type();
            }
        }
        int adj_point[81];
        for (int j=0; j<centers; j++) {
            block_num = rand() % 17 + 10;
            //printf("%d\n", block_num);
            int num = rand() % 80;
            if (centers == 1) {
                num = rand() % 80;
            }
            if (centers == 2) {
                if (j == 0) {
                    num = rand() % 20;
                }
                if (j == 1) {
                    num = rand() % 20 + 60;
                }
            }
            for (int &i : adj_point) {
                i = 0;
            }
            int sum_adj;
            bool in_list_flag;
            while (block_num) {

                in_list_flag = false;
                sum_adj = 0;
                for (int i : adj_point) {
                    sum_adj += i;
                }
                if (sum_adj != 0) {
                    random_shuffle(&adj_point[0], &adj_point[81]);
                    for (int &i : adj_point) {
                        if (i != 0) {
                            num = i;
                            i = 0;
                            break;
                        }
                    }
                }
                //printf("%d\n",num);
                w = num % 9;
                h = num / 9;
                if (board[w][h].exist == 0) {
                    //printf("w is %d, h is %d\n",w,h);
                    board[w][h] = block_type_generator();
                }
                //board[w][h] = block_type_generator();



                for (int i : adj_point) {
                    if (num - 9 == i) {
                        in_list_flag = true;
                        break;
                    }
                }
                if (num - 9 >= 0 && !in_list_flag) {
                    for (int &i : adj_point) {
                        if (i == 0) {
                            i = num - 9;
                            break;
                        }
                    }
                }
                in_list_flag = false;

                for (int i : adj_point) {
                    if (num + 9 == i) {
                        in_list_flag = true;
                        break;
                    }
                }
                if (num + 9 >= 80 && !in_list_flag) {
                    for (int &i : adj_point) {
                        if (i == 0) {
                            i = num + 9;
                            break;
                        }
                    }
                }
                in_list_flag = false;

                for (int i : adj_point) {
                    if (num - 1 == i) {
                        in_list_flag = true;
                        break;
                    }
                }
                if (num - 1 >= 0 && !in_list_flag) {
                    for (int &i : adj_point) {
                        if (i == 0) {
                            i = num - 1;
                            break;
                        }
                    }
                }
                in_list_flag = false;

                for (int i : adj_point) {
                    if (num + 1 == i) {
                        in_list_flag = true;
                        break;
                    }
                }
                if (num + 1 >= 80 && !in_list_flag) {
                    for (int &i : adj_point) {
                        if (i == 0) {
                            i = num + 1;
                            break;
                        }
                    }
                }
                block_num--;
            }
        }
        int total = 0;
        for(int x = 0; x < 9; x++) {
            for (int y = 0; y < 9; y++) {
                copy[x][y] = board[x][y];
                if (copy[x][y].exist == 1) {
                    total += 1;
                }
            }
        }
        solvable = Generator::solver();
    }
}

void Generator::init_random_list() {
    srand((unsigned)time(nullptr));
    int index;
    int temp;
    for (int i = 0; i < 81; i++) {
        random_list[i] = i;
    }
    for (int &i : random_list) {
        index = rand()%81;
        temp = i;
        i = random_list[index];
        random_list[index] = temp;
    }
}

bool Generator::solver() {
    bool blocked = false;
    int round = 0;

    while (true) {
        int total = 0;
        for (int x=0; x < 9; x++) {
            for (int y = 0; y < 9; y++) {
                if (copy[x][y].exist == 1) {
                    total++;
                    printf ("round%d, x is %d, y is %d\n",round, x, y );
                }
            }
        }

        for (int x = 0; x < 9; x++) {
            for (int y = 0; y < 9; y++) {
                if (copy[x][y].exist == 1) {Generator::move_block(x, y);}
            }
        }

        for (int x = 0; x < 9; x++) {
            for (int y = 0; y < 9; y++) {
                blocked = false;
                if (copy[x][y].block_rotation == 1) {
                    for (int times = 0; times <= 3; times ++) {
                        Generator::try_rotate(x, y);
                        Generator::move_block(x, y);
                        if (x - 1 >= 0) {
                            blocked = Generator::move_block(x - 1, y);
                            if (!blocked) {break;}
                            if (copy[x-1][y].block_rotation == 1) {
                                for (int sub_times = 0; sub_times <=3; sub_times ++) {
                                    Generator::try_rotate(x - 1, y);
                                    Generator::move_block(x - 1, y);
                                }
                            }
                        }
                        if (x + 1 < 9) {
                            blocked = Generator::move_block(x + 1, y);
                            if (!blocked) {break;}
                            if (copy[x+1][y].block_rotation == 1) {
                                for (int sub_times = 0; sub_times <=3; sub_times ++) {
                                    Generator::try_rotate(x + 1, y);
                                    Generator::move_block(x + 1, y);
                                }
                            }
                        }
                        if (y - 1 >= 0) {
                            blocked = Generator::move_block(x, y - 1);
                            if (!blocked) {break;}
                            if (copy[x][y-1].block_rotation == 1) {
                                for (int sub_times = 0; sub_times <=3; sub_times ++) {
                                    Generator::try_rotate(x , y - 1);
                                    Generator::move_block(x, y - 1);
                                }
                            }
                        }
                        if (y + 1 < 9) {
                            blocked = Generator::move_block(x, y + 1);
                            if (!blocked) {break;}
                            if (copy[x][y+1].block_rotation == 1) {
                                for (int sub_times = 0; sub_times <=3; sub_times ++) {
                                    Generator::try_rotate(x, y+1);
                                    Generator::move_block(x, y+1);
                                }
                            }
                        }
                    }
                }
            }
        }
        int current_total = 0;
        for (auto &x : copy) {
            for (auto &y : x) {
                if (y.exist==1) {current_total++;}
            }
        }
        if (current_total == total || current_total == 0) {
            printf("remaining %d blocks!!!\n", current_total);
            return current_total == 0;
        }
    }
}

bool Generator::move_block(int x, int y) {
     bool blocked;
     if (copy[x][y].exist == 1) {
         if (copy[x][y].direction != 0) {
             switch (copy[x][y].direction) {
                 case 1: {
                     printf("up, %d,%d\n", x,y);
                     blocked = Generator::move_up(x, y);
                     break;
                 }
                 case 2: {
                     printf("right, %d,%d\n", x,y);
                     blocked = Generator::move_right(x, y);
                     break;
                 }
                 case 3: {
                     printf("down, %d,%d\n", x,y);
                     blocked = Generator::move_down(x, y);
                     break;
                 }
                 case 4: {
                     printf("left, %d,%d\n", x,y);
                     blocked = Generator::move_left(x, y);
                     break;
                 }
                 default: break;
             }
         }

         if (copy[x][y].block_rotation != 0) {
             while (true) {
                 blocked = Generator::move_up(x, y);
                 if (!blocked) {break;}
                 blocked = Generator::move_down(x, y);
                 if (!blocked) {break;}
                 blocked = Generator::move_left(x, y);
                 if (!blocked) {break;}
                 blocked = Generator::move_right(x, y);
                 if (!blocked) {break;}
                 break;
             }
         }
     }
     return blocked;
 }

bool Generator::move_up(int x, int y) {
    bool blocked = false;
    for (int up = y + 1; up < 9; up ++) {
        if (copy[x][up].exist == 1) {
            if (copy[x][y].direction == 1) {printf("%d, %d blocked by %d, %d\n", x, y, x, up);}
            blocked = true;
            break;
        }
    }
    if (x + 1 < 9) {
        if (copy[x][y].tab[3] != 0 && copy[x+1][y].exist == 1) {
            printf("%d, %d blocked by %d, %d\n", x, y, x+1,y);
            blocked = true;
        }
        if (copy[x+1][y].tab[2] != 0) {
            printf("%d, %d blocked by %d, %d\n", x, y, x+1,y);
            blocked = true;
        }
    }
    if (x - 1 >= 0) {
        if (copy[x][y].tab[2] != 0 && copy[x-1][y].exist == 1) {
            printf("%d, %d blocked by %d, %d\n", x, y, x-1,y);
            blocked =true;
        }
        if (copy[x-1][y].tab[3] != 0) {
            printf("%d, %d blocked by %d, %d\n", x, y, x-1,y);
            blocked =true;
        }
    }


    if (!blocked) {
        printf("%d, %d, moved up\n", x, y);
        copy[x][y] = init_block_type();
    }
    return blocked;
}

bool Generator::move_down(int x, int y) {
    bool blocked = false;
    for (int down = y - 1; down >= 0; down --) {
        if (copy[x][down].exist == 1) {
            if (copy[x][y].direction == 3) {printf("%d, %d blocked by %d, %d\n", x, y, x, down);}
            blocked = true;
            break;
        }
    }
    if (x + 1 < 9) {
        if (copy[x][y].tab[3] != 0 && copy[x+1][y].exist == 1) {
            printf("%d, %d blocked by %d, %d\n", x, y, x+1,y);
            blocked =true;
        }
        if (copy[x+1][y].tab[2] != 0) {
            printf("%d, %d blocked by %d, %d\n", x, y, x+1,y);
            blocked = true;
        }
    }
    if (x - 1 >= 0) {
        if (copy[x][y].tab[2] != 0 && copy[x-1][y].exist == 1) {
            printf("%d, %d blocked by %d, %d\n", x, y, x-1,y);
            blocked =true;
        }
        if (copy[x-1][y].tab[3] != 0) {
            printf("%d, %d blocked by %d, %d\n", x, y, x-1,y);
            blocked =true;
        }
    }
    if (!blocked) {
        printf("%d, %d, moved down\n", x, y);
        copy[x][y] = init_block_type();
    }
    return blocked;
}

bool Generator::move_left(int x, int y) {
    bool blocked = false;
    for (int left = x - 1; left >= 0; left --) {
        if (copy[left][y].exist == 1) {
            if (copy[x][y].direction == 4) {printf("%d, %d blocked by %d, %d\n", x, y, left, y);}
            blocked = true;
            break;
        }
    }
    if (y + 1 < 9) {
        if (copy[x][y].tab[0] != 0 && copy[x][y+1].exist == 1) {
            printf("%d, %d blocked by %d, %d\n", x, y, x,y+1);
            blocked =true;
        }
        if (copy[x][y+1].tab[1] != 0) {
            printf("%d, %d blocked by %d, %d\n", x, y, x,y+1);
            blocked =true;
        }
    }
    if (y - 1 >= 0) {
        if (copy[x][y].tab[1] != 0 && copy[x][y-1].exist == 1) {
            printf("%d, %d blocked by %d, %d\n", x, y, x,y-1);
            blocked =true;
        }
        if (copy[x][y-1].tab[0] != 0) {
            printf("%d, %d blocked by %d, %d\n", x, y, x,y-1);
            blocked =true;
        }
    }
    if (!blocked) {
        printf("%d, %d, moved left\n", x, y);
        copy[x][y] = init_block_type();
    }
    return blocked;
}

bool Generator::move_right(int x, int y) {
    bool blocked = false;
    for (int right = x + 1; right < 9; right ++) {
        if (copy[right][y].exist == 1) {
            if (copy[x][y].direction == 2) {printf("%d, %d blocked by %d, %d\n", x, y, right, y);}
            blocked = true;
            break;
        }
    }
    if (y-1 >= 0) {
        if (copy[x][y].tab[1] != 0 && copy[x][y-1].exist == 1) {
            printf("%d, %d blocked by %d, %d\n", x, y, x,y-1);
            blocked =true;
        }
        if (copy[x][y-1].tab[0] != 0) {
            printf("%d, %d blocked by %d, %d\n", x, y, x,y-1);
            blocked =true;
        }
    }
    if (y +1 < 9) {
        if (copy[x][y].tab[0] != 0 && copy[x][y+1].exist == 1) {
            printf("%d, %d blocked by %d, %d\n", x, y, x,y+1);
            blocked =true;
        }
        if (copy[x][y+1].tab[1] != 0) {
            printf("%d, %d blocked by %d, %d\n", x, y, x,y+1);
            blocked =true;
        }
    }
    if (!blocked) {
        printf("%d, %d, moved right\n", x, y);
        copy[x][y] = init_block_type();
    }
    return blocked;
}

bool Generator::try_rotate(int x, int y) {
    if (copy[x][y].block_rotation != 1) {return false;}
    int temp[4];
    for (int i=0; i<=3; i++) {
        temp[i] = copy[x][y].tab[i];
        copy[x][y].tab[i] = 0;
    }

    if (temp[0] == 1) {copy[x][y].tab[3] = 1;}
    if (temp[1] == 1) {copy[x][y].tab[2] = 1;}
    if (temp[2] == 1) {copy[x][y].tab[0] = 1;}
    if (temp[3] == 1) {copy[x][y].tab[1] = 1;}
    printf("%d, %d rotate 1 times\n", x, y);
}