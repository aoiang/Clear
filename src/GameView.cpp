//
// Created by Yiyang Zhao on 18/10/2017.
//

#include "GameView.h"




GameView::GameView(int length, int width) :
    App(sf::VideoMode(length, width, 32), "Pong",  sf::Style::Default){}

bool GameView::isOpen() {
    return App.isOpen();
}

void::GameView::block_init() {
    for(int i=0; i<4; i++){
       block[i].init(i);
    }
}


sf::RectangleShape GameView::block_generator(int i) {


    if(block[i].get_direction() == "up"){
        texture[block[i].get_id()].loadFromFile("../resources/up.png");
    }
    if(block[i].get_direction() == "down"){
        texture[block[i].get_id()].loadFromFile("../resources/down.png");
    }
    if(block[i].get_direction() == "left"){
        texture[block[i].get_id()].loadFromFile("../resources/left.png");
    }
    if(block[i].get_direction() == "right"){
        printf("%s", block[i].get_direction().c_str());
        texture[block[i].get_id()].loadFromFile("../resources/right.png");
    }

    sf::RectangleShape c(sf::Vector2f(block[i].get_length(), block[i].get_width()));
    c.setFillColor(sf::Color::White);
    c.setTexture(&texture[block[i].get_id()]);
    return c;
}

sf::RectangleShape* GameView::init() {
    block_init();
    sf::RectangleShape *b;
    b = new sf::RectangleShape[4];

    for(int i=0; i<4; i++) {
        b[i] = block_generator(i);
    }

    b[0].move(100,200);
    b[1].move(500,400);
    b[2].move(300,400);
    b[3].move(600,100);

    return b;

}

void GameView::check_mousePosition(sf::RectangleShape *b) {
    sf::Clock timer;
    float d = timer.restart().asSeconds();
    int current_y = App.getSize().y;
    int current_x = App.getSize().x;
    for(int i=0; i<4; i++) {
        if (sf::Mouse::getPosition(App).x >= int((b[i].getPosition().x / 800) * current_x) && sf::Mouse::getPosition(App).x <= int(((b[i].getPosition().x+100) / 800) * current_x)){
            if (sf::Mouse::getPosition(App).y >= int((b[i].getPosition().y / 600) * current_y) && sf::Mouse::getPosition(App).y <= int(((b[i].getPosition().y+100) / 600) * current_y)){
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    for(int be_selected=0; be_selected<4; be_selected++){
                        if(be_selected==i){
                            continue;
                        }
                        block[be_selected].set_selected(false);
                    }
                    block[i].set_selected(true);
                    for(int be_selected=0; be_selected<4; be_selected++){
                        if(!block[be_selected].get_selected()){
                            b[be_selected].setOutlineThickness(0);
                        }
                        else{
                            b[be_selected].setOutlineThickness(3.5);
                            b[be_selected].setOutlineColor(sf::Color::Red);
                        }
                    }

                }
            }
        }
    }

}

void GameView::check_keyboard_in(sf::RectangleShape *b) {
    for(int i=0; i<4; i++) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if(block[i].get_selected() && block[i].get_direction() == "up"){
                b[i].move(0.0,  -1 * 30);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if(block[i].get_selected() && block[i].get_direction() == "down"){
                b[i].move(0.0,  1 * 30);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(block[i].get_selected() && block[i].get_direction() == "left"){
                b[i].move(-100,  0.01 * 30);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(block[i].get_selected() && block[i].get_direction() == "right"){
                b[i].move(100.0,  0.01 * 30);
            }
        }

    }


}



void GameView::draw(sf::RectangleShape b[]) {
    poll_event();
    App.clear(sf::Color(66, 150, 246));


    check_mousePosition(b);
    check_keyboard_in(b);

    App.draw(b[0]);
    App.draw(b[1]);
    App.draw(b[2]);
    App.draw(b[3]);
    //printf("%f,",c.getPosition().x);


    App.display();
}



void GameView::poll_event(){
    sf::Event Event;
    while(App.pollEvent(Event)){
        switch (Event.type)
        {
            case sf::Event::Closed:
                App.close();
                break;
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                    App.close();
                    break;
                }
            default: break;
        }
        // Exit
        if(Event.type == sf::Event::Closed)
            App.close();
    }
    //draw();

}


