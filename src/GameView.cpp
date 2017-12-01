#include "GameView.hpp"
#include "Screens.hpp"
#include <iostream>
#include <stdlib.h>


/**runs the window: creates the window and all screens*/
int GameView::run(GameLogic logic) {
    sf::RenderWindow App(sf::VideoMode(default_window_height, default_window_width, 32), GAME_TITLE,  sf::Style::Default);
    Title_Animation screen0;
    MainMenu_Screen screen1;
    GameView_Screen screen2;
    std::vector<Screen_Abstract*> screens;
    int curr_screen = 0;

    screen2.set_GameLogic(logic);
    screens.push_back(&screen0);
    screens.push_back(&screen1);
    screens.push_back(&screen2);

    while (curr_screen >= 0) {curr_screen = screens[curr_screen]->run(App);}
}
