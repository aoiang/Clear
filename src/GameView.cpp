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
    int curr_screen = 0;




    screen2.set_GameLogic(logic);

    screens.push_back(&screen0);
    screens.push_back(&screen1);
    screens.push_back(&screen2);
    screens.push_back(&screen3);

    while(curr_screen >=0)
    {
        switch (curr_screen){
            case 1: {
                screen2.set_board(screen1.get_Board());
                break;
            }
            case 2:{
                screen2.set_board(BoardStateLoader::loadBoardState(LEVEL_01));
                break;
            }
            case 3:  {
                screen2.set_board(screen3.get_Board());
                break;
            }
            default:{
                break;
            }
        }
        //screen2.set_board(screen3.get_Board());
        curr_screen = screens[curr_screen]->run(App);
    }
}
