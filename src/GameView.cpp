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
            //printf("%s", block[i].get_direction().c_str());
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
sf::RectangleShape* GameView::init(Normal_Block *normal_block) {
    block_init();
    sf::RectangleShape *b;
    b = new sf::RectangleShape[5];

    for(int i=0; i<5; i++) {
        b[i] = directed_block_generator(normal_block, i);
        b[i].setPosition(normal_block[i].getX(), normal_block[i].getY());
    }

    return b;

}




Normal_Block* GameView::check_mousePosition(Normal_Block *normal_block) {

    sf::Clock timer;
    float d = timer.restart().asSeconds();
    int current_y = App.getSize().y;
    int current_x = App.getSize().x;
    for(int i=0; i<5; i++) {
        //printf("%f\n", normal_block[i].getX());
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
//                    for(int be_selected=0; be_selected<5; be_selected++){
//                        if(!block[be_selected].get_selected()){
//                            b[be_selected].setOutlineThickness(0);
//                        }
//                        else{
//                            b[be_selected].setOutlineThickness(3.5);
//                            //printf("%f", b[be_selected].getPosition().x);
//                            b[be_selected].setOutlineColor(sf::Color::Red);
//                        }
//                    }

                }
            }
        }
    }
    return normal_block;
}


/**
 * check if keyboard is pressed and which button it is
 * determine if this keyboard_in works based on the game rule(like direction, collision)
 * @param b for block in gameview mode
 */
void GameView::check_keyboard_in(sf::RectangleShape *b) {
    //printf("%d", (int)sizeof(b));
    for(int i=0; i<5; i++) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if(block[i].get_selected() && block[i].get_direction() == "up" && !collision_detector(b[i], b,  block[i].get_direction())){
                b[i].move(0.0,  -1 * 30);
            }
            if(block[i].get_selected() && !block[i].get_has_direction() && !collision_detector(b[i], b, "up")){
                b[i].move(0.0,  -1 * 30);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if(block[i].get_selected() && block[i].get_direction() == "down" && !collision_detector(b[i], b,  block[i].get_direction())){
                b[i].move(0.0,  1 * 30);
            }
            if(block[i].get_selected() && !block[i].get_has_direction() && !collision_detector(b[i], b, "down")){
                b[i].move(0.0,  1 * 30);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(block[i].get_selected() && block[i].get_direction() == "left" && !collision_detector(b[i], b, block[i].get_direction())){
                b[i].move(-30,  0);
            }
            if(block[i].get_selected() && !block[i].get_has_direction() && !collision_detector(b[i], b, "left")){
                b[i].move(-30,  0);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(block[i].get_selected() && block[i].get_direction() == "right" && !collision_detector(b[i], b, block[i].get_direction())){
                b[i].move(30.0,  0);
            }
            if(block[i].get_selected() && !block[i].get_has_direction() && !collision_detector(b[i], b, "right")){
                b[i].move(30.0,  0);
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
        for(int i=0; i < 5; i++){
            if(b[i].getPosition().x == current_b.getPosition().x){
                if(b[i].getPosition().y < current_b.getPosition().y){
                    if(b[i].getPosition().x > 0 && b[i].getPosition().x < 800 && b[i].getPosition().y > 0 && b[i].getPosition().y < 600){
                        return true;
                    }
                }
            }
        }
    }
    if(direction == "down"){
        for(int i=0; i < 5; i++){
            if(b[i].getPosition().x == current_b.getPosition().x){
                if(b[i].getPosition().y > current_b.getPosition().y){
                    if(b[i].getPosition().x > 0 && b[i].getPosition().x < 800 && b[i].getPosition().y > 0 && b[i].getPosition().y < 600){
                        return true;
                    }
                }
            }
        }
    }
    if(direction == "left"){
        for(int i=0; i < 5; i++){
            if(b[i].getPosition().y == current_b.getPosition().y){
                if(b[i].getPosition().x < current_b.getPosition().x){
                    if(b[i].getPosition().x > 0 && b[i].getPosition().x < 800 && b[i].getPosition().y > 0 && b[i].getPosition().y < 600){
                        return true;
                    }

                }
            }
        }
    }
    if(direction == "right"){
        for(int i=0; i < 5; i++){
            if(b[i].getPosition().y == current_b.getPosition().y){
                if(b[i].getPosition().x > current_b.getPosition().x){
                    if(b[i].getPosition().x > 0 && b[i].getPosition().x < 800 && b[i].getPosition().y > 0 && b[i].getPosition().y < 600){
                        return true;
                    }
                }
            }
        }
    }
    return false;
    

}


void GameView::draw_selected_block(Normal_Block *normal_block, sf::RectangleShape *b){
    for(int be_selected=0; be_selected<5; be_selected++){
        if(!normal_block[be_selected].get_selected()){
            b[be_selected].setOutlineThickness(0);
        }
        else{
            b[be_selected].setOutlineThickness(3.5);
            //printf("%f", b[be_selected].getPosition().x);
            b[be_selected].setOutlineColor(sf::Color::Red);
        }
    }
}

void GameView::draw_movement(Normal_Block *normal_block, sf::RectangleShape *b) {
    for(int i=0; i < 5; i++){
        b[i].setPosition(normal_block[i].getX(),normal_block[i].getY());
    }
}


/**
 * draw all blocks and mechanics
 * @param b for blocks in gameview mode
 */



void GameView::draw(Normal_Block *normal_block, sf::RectangleShape b[]) {
    poll_event();
    App.clear(sf::Color(66, 150, 246));


    //check_mousePosition(b);
    check_keyboard_in(b);

    draw_selected_block(normal_block, b);
    draw_movement(normal_block, b);
    printf("%f\n", b[0].getPosition().x);
    App.draw(b[0]);
    App.draw(b[1]);
    App.draw(b[2]);
    App.draw(b[3]);
    App.draw(b[4]);
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


