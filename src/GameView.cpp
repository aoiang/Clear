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
    int level_keeper = 0;
    curr_screen[0] = 0;
    curr_screen[1] = 0;




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
        printf("current level is %d\n", level_keeper);
        current_state = GameView::loadlevel(level_keeper);
        screen2.set_board(current_state);
        curr_screen = screens[curr_screen[0]]->run(App, level_keeper);

    }
}


BoardState* GameView::loadlevel(int level) {
    std::string levels[13] = {LEVEL_01, LEVEL_02, LEVEL_03, LEVEL_04, LEVEL_05, LEVEL_TEST, LEVEL_06};
    return new BoardState(levels[level-1]);

}
