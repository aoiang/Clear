#include "Transition_Screen.hpp"
#include "Definitions.hpp"
#include "BoardState.hpp"
#include "BoardGenerator.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <fstream>

Transition_Screen::Transition_Screen() {
    std::string joke;
    std::ifstream fileRead(JOKES_FILE);
    if (!fileRead) {
        std::cerr << "Unable to open find the work jokes file.";
        exit(1);
    }
    while (getline(fileRead, joke)) {jokes.push_back(joke);}
    fileRead.close();
}

std::string Transition_Screen::get_message(int current_level) {
    if (current_level<1) {return "";}
    else {return jokes.at(current_level-1);}
}

int Transition_Screen::run() {
    load_font(REGULARFONT_FILEPATH);

    message_text = get_message(logic->get_cur_level());
    if (message_text=="") {return SCREEN_GAMEVIEW;}
    message = make_text(message_text, 30, 0, 0);

    frame_count = 0;
    sf::Clock clock;

    while (true) {
        while (window->pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {return EXIT_GAME;}
            if (Event.type == sf::Event::KeyPressed || Event.type == sf::Event::MouseButtonPressed) {return SCREEN_GAMEVIEW;}
        }
        if (clock.getElapsedTime().asSeconds() > 0.01f) {
            clock.restart();
            frame_count += 1;
            if (frame_count <= 85) {
                clear_window();
                message.setFillColor(sf::Color(255, 255, 255, frame_count*3));
                window->draw(message);
                window->display();
            }
            else if (frame_count <= 200) {window->display();}
            else {
                if (logic->get_cur_level()<=20) {return SCREEN_GAMEVIEW;}
                else {return SCREEN_MAINMENU;}
            }
        }
    }
}
