#include "Transition_Screen.hpp"
#include "Definitions.hpp"
#include "BoardState.hpp"
#include "BoardGenerator.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;
Transition_Screen::Transition_Screen()
{
  string joke;
  ifstream fileRead;
  fileRead.open("../resources/work_jokes.txt");
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
int Transition_Screen::animate_text(sf::Text text, sf::RenderWindow &window)
{
    int frame_count = 0;
    //count = 0;
    sf:: Event event;
    sf::Clock clock;
    sf::FloatRect textbox;
    textbox = text.getGlobalBounds();
    text.setOrigin(textbox.width / 2.0f, textbox.height / 2.0f);
    text.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    text.setFillColor(sf::Color(255, 255, 255, 0));

    while (frame_count <= 255) {
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {return -1;}
            if(event.type == sf::Event::KeyPressed) {return 1;}
        }
        if(clock.getElapsedTime().asSeconds() > 0.01f) {
            window.clear(sf::Color(40,140,240));
            text.setFillColor(sf::Color(255, 255, 255, frame_count));
            clock.restart();
            frame_count = frame_count + 2;
            window.draw(text);
            window.display();
        }
    }


}
/**Sets GameLogic*/
void Transition_Screen::set_GameLogic(GameLogic &logic)
{
    this->logic = &logic;
}
string Transition_Screen::print_message(vector<string> jokes)
{
        string random_string = jokes.at(count);
        count++;
        return random_string;
}

string Transition_Screen::randomize_message(vector<string> jokes)
{
        int index = (rand()%jokes.size()) + 1;
        cout<<"Random number is "<< index << endl;
        return jokes.at(index);
}
int Transition_Screen::run(sf::RenderWindow &window)
{
    sf::Clock clock;
    sf::Font font;
    font.loadFromFile(REGULARFONT_FILEPATH);
    int fontsize = 30;


    //message = new sf::Text(jokes.at(0), font, fontsize);
    //animate_text(*message, window);

    if(this->logic->get_cur_level() == 0)
    {

        string desired_string = randomize_message(this->jokes);
        message = new sf::Text(desired_string, font, fontsize);
        animate_text(*message, window);

    }
   else if(this->logic->get_cur_level()>=1)
    {
       string desired_string = print_message(this->jokes);
       message = new sf::Text(desired_string, font, fontsize);
       animate_text(*message, window);

    }
    bool running = true;
    sf::Event Event;
    while(running) {
        while (window.pollEvent(Event)) {
            if(Event.type == sf::Event::Closed) {
                running = false;
                return EXIT_GAME;
            if(Event.type == sf::Event::KeyPressed) {
              return SCREEN_GAMEVIEW;
            }
        }

      //  window.clear(sf::Color::Black);
        //window.draw(*message);
        window.display();
        if(clock.getElapsedTime().asSeconds() > 0.2f)
            return SCREEN_GAMEVIEW;

 }
}
return SCREEN_MAINMENU;
}
