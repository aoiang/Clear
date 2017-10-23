//
//created by Yosef Ejigu 10/21/17

#include <Clearboard.hpp>

/**
  Sets properties of the board
  @param width for width of board 
  @param height for the height of the board
  @param x for x position of a specific block on the board
  @param y for y position of a specific block on the board
*/

void Clearboard::init()
{
    for(int i=0; i<this->height; i++)
        for (int j=0; j<this->width; j++)
            this->board[i][j] = NULL;
}
void Clearboard::init(int h, int w)
{
    this->height = h;
    this->width = w;
    for(int i=0; i<this->height; i++)
        for (int j=0; j<this->width; j++)
            this->board[i][j] = NULL;
    
}
bool Clearboard:: remove(int x, int y)
{
    if (x> this->width || y > this->height)
    {
        return false;
    }
    else
    {
        this->board[x][y] = NULL;
        return true;
    }
}
