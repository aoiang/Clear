//
// Created by Yosef Ejigu 10/21/17
// Additional work by Ivan Echevarria
//

#include <Clearboard.hpp>

/**
  Sets properties of the board
  @param width for width of board
  @param height for the height of the board
  @param x for x position of a specific block on the board
  @param y for y position of a specific block on the board
*/


/**
  Initializes board
*/
void Clearboard::init()
{
    for(int i = 0; i < this->height; i++)
        for (int j = 0; j < this->width; j++)
            this->board[i][j] = NULL;
}


/**
  Sets board dimensions
  @param h for height
  @param w for width
*/
void Clearboard::init(int h, int w)
{
    this->height = h;
    this->width = w;
    for(int i=0; i<this->height; i++)
        for (int j=0; j<this->width; j++)
            this->board[i][j] = NULL;
}


/**
  Removes element from board
  @param x coordinate to remove
  @param y coordinate to remove
  @return bool to indicate successful removal
*/
bool Clearboard::remove(int x, int y)
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


bool Clearboard::add_block(int x, int y, Block *block)
{
    if(board[x][y] != NULL)
    {
      return false;
    } else {
      board[x][y] = block;
      return true;
    }
}


Block Clearboard::get_block(int x, int y)
{
    if(board[x][y] != NULL)
    {
      Block to_return = *board[x][y];
      return to_return;
    }
}
