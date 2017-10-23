//
// Created by Yiyang Zhao on 18/10/2017.
// Additional work by Ivan & Yosef
//

#include "GameView.h"


/**
 * constructor function
 * create the window
 */
GameView::GameView(float length, float width) :
    App(sf::VideoMode(length, width, 32), "Clear",  sf::Style::Default){}


/**
 * check it window is open
 * @return bool
 */
bool GameView::isOpen() {
    return App.isOpen();
}

/**
 * initialize all blocks, set all parameters for blocks
 */
void::GameView::block_init() {
    for(int i=0; i<5; i++){
       block[i].init(i);
    }
}

void GameView::set_GameState(GameState &state) {
    this -> state = &state;
}

/**
 * @param i for id
 * Generate blocks in the game based on their properties(like direction)
 *
 * @return sf::RectangleShape
 */
sf::RectangleShape GameView::directed_block_generator(Normal_Block *normal_block, int i) {
    if(normal_block[i].get_has_direction()){
        if(normal_block[i].get_direction() == "up"){
            texture[normal_block[i].get_id()].loadFromFile("../resources/up.png");
        }
        if(normal_block[i].get_direction() == "down"){
            texture[normal_block[i].get_id()].loadFromFile("../resources/down.png");
        }
        if(normal_block[i].get_direction() == "left"){
            texture[normal_block[i].get_id()].loadFromFile("../resources/left.png");
        }
        if(normal_block[i].get_direction() == "right"){
            texture[normal_block[i].get_id()].loadFromFile("../resources/right.png");
        }

        sf::RectangleShape c(sf::Vector2f(normal_block[i].get_length(), normal_block[i].get_width()));
        c.setFillColor(sf::Color::White);
        c.setTexture(&texture[normal_block[i].get_id()]);
        return c;
    }
    else{
        sf::RectangleShape c(sf::Vector2f(normal_block[i].get_length(), normal_block[i].get_width()));
        c.setFillColor(sf::Color::White);
        return c;
    }
}


/**
 * initialize the game, set all blocks.
 * @return sf::RectangleShape
 */
void GameView::init() {
    block_init();
    sf::RectangleShape * b;
    b = new sf::RectangleShape[5];
    for(int i=0; i<5; i++) {
        b[i] = directed_block_generator(state->get_Normal_Block(), i);
        b[i].setPosition(state->get_Normal_Block()[i].getX(), state->get_Normal_Block()[i].getY());
    }
    this -> block_shapes = b;
}


void GameView::check_mousePosition(Normal_Block * normal_block) {
    sf::Clock timer;
    float d = timer.restart().asSeconds();
    int current_y = App.getSize().y;
    int current_x = App.getSize().x;
    for(int i=0; i<5; i++) {
        if (sf::Mouse::getPosition(App).x >= int((normal_block[i].getX() / 800) * current_x) && sf::Mouse::getPosition(App).x <= int(((normal_block[i].getX()+100) / 800) * current_x)){
            if (sf::Mouse::getPosition(App).y >= int((normal_block[i].getY() / 600) * current_y) && sf::Mouse::getPosition(App).y <= int(((normal_block[i].getY()+100) / 600) * current_y)){
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    for(int be_selected=0; be_selected<5; be_selected++){
                        if(be_selected==i){
                            continue;
                        }
                        normal_block[be_selected].set_selected(false);
                    }
                    normal_block[i].set_selected(true);
                }
            }
        }
    }
}


/**
* draws an outline around a block if it is selected
*/
void GameView::draw_selected_block(Normal_Block * normal_block) {
    for(int be_selected=0; be_selected<5; be_selected++){
        if(!normal_block[be_selected].get_selected()){
            block_shapes[be_selected].setOutlineThickness(0);
        }
        else{
            block_shapes[be_selected].setOutlineThickness(3.5);
            block_shapes[be_selected].setOutlineColor(sf::Color::Red);
        }
    }
}


/**
* draw animation for blocks leaving screen
* @param normal_block for blocks
*/
void GameView::draw_movement(Normal_Block * normal_block) {
    for(int i=0; i < 5; i++){
        block_shapes[i].setPosition(normal_block[i].getX(),normal_block[i].getY());
    }
}


/**
 * draw all blocks and mechanics
 * @param b for blocks in gameview mode
 */
void GameView::draw(Normal_Block *normal_block) {
    poll_event();
    App.clear(sf::Color(66, 150, 246));

    draw_selected_block(normal_block);
    draw_movement(normal_block);
    App.draw(block_shapes[0]);
    App.draw(block_shapes[1]);
    App.draw(block_shapes[2]);
    App.draw(block_shapes[3]);
    App.draw(block_shapes[4]);
    App.display();
}

void GameView::check_keyboard_in() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        this->state->try_move("up");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        this->state->try_move("down");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        this->state->try_move("left");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        this->state->try_move("right");
    }
}

/**
 * Poll event
 */
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
