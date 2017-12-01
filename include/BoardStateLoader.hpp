#ifndef CLEAR_BOARDSTATELOADER_HPP
#define CLEAR_BOARDSTATELOADER_HPP

#include "BoardState.hpp"

class BoardStateLoader {
    private:
        BoardStateLoader() {}
    public:
        static BoardState * loadBoardState(std::string);
};

#endif //CLEAR_BOARDSTATELOADER_HPP
