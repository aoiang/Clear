#ifndef TRANSITION_SCREEN_HPP
#define TRANSITION_SCREEN_HPP

#include "Screen_Abstract.hpp"
#include "BoardState.hpp"
#include "GameLogic.hpp"
#include <SFML/Graphics.hpp>

class Transition_Screen : public Screen_Abstract {
    private:
        std::vector<std::string> jokes;
        sf::Text* message;
    public:
        int count = 0;
        Transition_Screen();
        int run();
        int animate_text(sf::Text text);
        std::string print_message(std::vector<std::string> jokes);
        std::string randomize_message(std::vector<std::string> jokes);
};
#endif
