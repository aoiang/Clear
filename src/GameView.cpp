#include "GameView.hpp"
#include "Screens.hpp"
#include <iostream>
#include <stdlib.h>
#include <Levels_Screen.hpp>


/**runs the window: creates the window and all screens*/
int GameView::run(GameLogic logic)
{
    sf::RenderWindow App(sf::VideoMode(default_window_height, default_window_width, 32), GAME_TITLE,  sf::Style::Default);
    Title_Animation screen0;
    MainMenu_Screen screen1;
    GameView_Screen screen2;
    Levels_Screen screen3;
    std::vector<Screen_Abstract*> screens;
    int *curr_screen = new int[2];
    int level_keeper = 1;
    curr_screen[0] = 0;
    curr_screen[1] = 1;

    screen2.set_GameLogic(logic);
    screens.push_back(&screen0);
    screens.push_back(&screen1);
    screens.push_back(&screen2);
    screens.push_back(&screen3);

    while(curr_screen[0] >=0 )
    {
        if (curr_screen[1] < 99){
            level_keeper = curr_screen[1];
        }
        curr_screen = screens[curr_screen[0]]->run(App, level_keeper);
    }
}
