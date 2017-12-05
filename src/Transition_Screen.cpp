#include "Transition_Screen.hpp"
#include "Definitions.hpp"
#include "BoardState.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;
Transition_Screen::Transition_Screen()
{
  string joke;
  ifstream fileRead;
  fileRead.open("/home/f85/ytejigu/Clear/resources/work_jokes.txt");
  if(!fileRead)
  {
      cerr << "Unable to open find work_jokes.txt";
      exit(1);
  }
  while (getline(fileRead, joke))// >> joke)
  {
    jokes.push_back(joke);  
  }
  fileRead.close();
    
}
/**Sets GameLogic*/
void Transition_Screen::set_GameLogic(GameLogic &logic) 
{
    this->logic = &logic;
}

string Transition_Screen::randomize_message(vector<string> jokes)
{
        string random_string = jokes.at(0);
        return random_string;
}
int Transition_Screen::run(sf::RenderWindow &window)
{       
    sf::Clock clock;
    sf::Font font;
    font.loadFromFile(HANDWRITTENFONT_FILEPATH);
    int fontsize = 30;
    if(true)//logic->get_cur_level() == 0)
    {
        
        string desired_string = randomize_message(this->jokes);
        message = new sf::Text(desired_string, font, fontsize);
    }
    else //if(logic->get_cur_level() == 0)
    {
        return SCREEN_MAINMENU;
        
    }
    bool running = true;
    sf::Event Event;
    while(running) {
        while (window.pollEvent(Event)) {
            if(Event.type == sf::Event::Closed) {
                running = false;
                return EXIT_GAME;
            }
        }
        
        window.clear(sf::Color::Black);
        window.draw(*message);
        window.display();
        if(clock.getElapsedTime().asSeconds() > 1.0f)
            return SCREEN_GAMEVIEW;
    }
    //return 3;
}
