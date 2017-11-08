#include "Clearboard.cpp"
#include "Block.cpp"
#include <iostream>

void print_board(Clearboard gameboard)
{
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            if(gameboard.get_block(i,j)==0)
            {
                std::cout<< true << " ";
            }
            else 
            {
                std::cout<<gameboard.get_block(i,j)->get_id()<<' ';
            
            }
        }
        std::cout<<"\n";
    }
}

int main ()
{
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
