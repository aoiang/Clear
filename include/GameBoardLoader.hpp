#ifndef CLEAR_GAMEBOARDLOADER_HPP
#define CLEAR_GAMEBOARDLOADER_HPP

#include "GameBoard.hpp"

class GameBoardLoader {
    private:
        GameBoardLoader() {}
    public:
        static GameBoard * loadGameBoard(std::string);
};

#endif //CLEAR_GAMEBOARDLOADER_HPP
