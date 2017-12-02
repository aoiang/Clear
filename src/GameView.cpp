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
    curr_screen[0] = 0;
    curr_screen[1] = 0;




    screen2.set_GameLogic(logic);
    screens.push_back(&screen0);
    screens.push_back(&screen1);
    screens.push_back(&screen2);
    screens.push_back(&screen3);


    while(curr_screen[0] >=0 )
    {
        current_state = GameView::loadlevel(curr_screen[1]);
        //printf("xxxxxxxxxx!!!!!! level is %d\n", curr_screen[0]);
        screen2.set_board(current_state);
        curr_screen = screens[curr_screen[0]]->run(App);

    }
}


BoardState* GameView::loadlevel(int level) {
    switch (level){
        case 0: {
            return new BoardState(LEVEL_01);
        }
        case 1: {
            return new BoardState(LEVEL_01);
        }
        case 2: {
            return new BoardState(LEVEL_02);

        }
        case 3: {
            return new BoardState(LEVEL_01);

        }
        case 4: {
             return new BoardState(LEVEL_TEST);

        }
        case 5: {
            return new BoardState(LEVEL_01);

        }
        case 6: {
            return new BoardState(LEVEL_TEST);

        }
        default:break;
    }

}
