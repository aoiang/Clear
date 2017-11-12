#include "Clearboard.cpp"
#include "Block.cpp"
#include <iostream>

void print_board(Clearboard gameboard) {
    for(int y=0; y<10; y++) {
        for(int x=0; x<10; x++) {
            if(gameboard.get_block(x,y)==0) {std::cout<< true << " ";}
            else {std::cout<<gameboard.get_block(x,y)->get_id()<<' ';}
        }
        std::cout<<"\n";
    }
}

int main () {
    Clearboard gameboard;
    gameboard.init(10,10);
    Block one;
    one.init(3);
    gameboard.add_block(2,2,one);
    print_board(gameboard);
    gameboard.remove(2,2);
    std::cout<<"\n";
    print_board(gameboard);
    
    return 1;
}
