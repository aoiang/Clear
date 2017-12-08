#ifndef TRANSITION_SCREEN_HPP
#define TRANSITION_SCREEN_HPP

#include "Screen_Abstract.hpp"
#include "BoardState.hpp"
#include "GameLogic.hpp"
#include <SFML/Graphics.hpp>

class Transition_Screen : public Screen_Abstract {
    private:
        std::vector<std::string> jokes;
        std::string message_text;
        sf::Text message;
        int frame_count;
        std::string get_message(int current_level);
    public:
        Transition_Screen();
        int run();
};
#endif
