#ifndef CLEAR_GAMEVIEW_HPP
#define CLEAR_GAMEVIEW_HPP

#include <SFML/Graphics.hpp>
#include "GameLogic.hpp"
#include "Screens.hpp"

class GameView {
    private:
        sf::RenderWindow *App;
        int default_window_width = 600;
        int default_window_height = 600;
    public:
        int run(GameLogic logic);
};

#endif //CLEAR_GAMEVIEW_HPP
