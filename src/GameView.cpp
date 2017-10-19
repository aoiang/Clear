//
// Created by Yiyang Zhao on 18/10/2017.
//

#include "GameView.h"

/**
  GameView
  @param block is for the blocks we generated
  @param sf::RectectangleShape b is for the blocks in gameview, which is conresponding to @param block.
*/


/**
 * construction function
 * create the window
 */


GameView::GameView(int length, int width) :
    App(sf::VideoMode(length, width, 32), "Pong",  sf::Style::Default){}

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
    for(int i=0; i<4; i++){
       block[i].init(i);
    }
}

/**
 * @param i for id
 * Generate blocks in the game based on their properties(like direction)
 *
 * @return sf::RectangleShape
 */


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

/**
 * initialize the game, set all blocks.
 * @return sf::RectangleShape
 */
sf::RectangleShape* GameView::init() {
    block_init();
    sf::RectangleShape *b;
    b = new sf::RectangleShape[4];

    for(int i=0; i<4; i++) {
        b[i] = block_generator(i);
    }

    b[0].move(100,200);
    b[1].move(180,200);
    b[2].move(260,200);
    b[3].move(340,200);

    return b;

}

/**
 *
 * @param b for block in gameview mode
 * check the if mouse is clicked and get the selected block
 */
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
                            //printf("%f", b[be_selected].getPosition().x);
                            b[be_selected].setOutlineColor(sf::Color::Red);
                        }
                    }

                }
            }
        }
    }

}


/**
 * check if keyboard is pressed and which button it is
 * determine if this keyboard_in works based on the game rule(like direction, collision)
 * @param b for block in gameview mode
 */
void GameView::check_keyboard_in(sf::RectangleShape *b) {
    //printf("%d", (int)sizeof(b));
    for(int i=0; i<4; i++) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if(block[i].get_selected() && block[i].get_direction() == "up" && !collision_detector(b[i], b, block[i].get_direction())){
                b[i].move(0.0,  -1 * 30);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if(block[i].get_selected() && block[i].get_direction() == "down" && !collision_detector(b[i], b, block[i].get_direction())){
                b[i].move(0.0,  1 * 30);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(block[i].get_selected() && block[i].get_direction() == "left" && !collision_detector(b[i], b, block[i].get_direction())){
                b[i].move(-100,  0.01 * 30);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(block[i].get_selected() && block[i].get_direction() == "right" && !collision_detector(b[i], b, block[i].get_direction())){
                b[i].move(100.0,  0.01 * 30);
            }
        }

    }
}

/**
 * check if has collision.
 * @param b for blocks in gameview mode
 * @return bool
 */
bool GameView::collision_detector(sf::RectangleShape current_b, sf::RectangleShape *b, std::string direction) {
    if(direction == "up"){
        for(int i=0; i < 4; i++){
            if(b[i].getPosition().x == current_b.getPosition().x){
                if(b[i].getPosition().y < current_b.getPosition().y){
                    return true;
                }
            }
        }
    }
    if(direction == "down"){
        for(int i=0; i < 4; i++){
            if(b[i].getPosition().x == current_b.getPosition().x){
                if(b[i].getPosition().y > current_b.getPosition().y){
                    return true;
                }
            }
        }
    }
    if(direction == "left"){
        for(int i=0; i < 4; i++){
            if(b[i].getPosition().y == current_b.getPosition().y){
                if(b[i].getPosition().x < current_b.getPosition().x){
                    return true;
                }
            }
        }
    }
    if(direction == "right"){
        for(int i=0; i < 4; i++){
            if(b[i].getPosition().y == current_b.getPosition().y){
                if(b[i].getPosition().x > current_b.getPosition().x){
                    return true;
                }
            }
        }
    }
    return false;
    

}

/**
 * draw all blocks and mechanics
 * @param b for blocks in gameview mode
 */

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


