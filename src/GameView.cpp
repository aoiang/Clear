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
* Updates the view at each frame
*/
void GameView::update() {
  check_mousePosition(state -> get_board_array());
  check_keyboard_in();
  draw(state -> get_board_array());
}

/**
 * initialize all blocks, set all parameters for blocks
 */
void GameView::block_init() {
    for(int i=0; i<5; i++){
       block[i].init(i);
    }
}

void GameView::set_GameState(GameState &state) {
    this -> state = &state;
}

/**
 * Draw blocks in the game based on their properties (like direction)
 * @param i for id
 * @return sf::RectangleShape
 */
sf::RectangleShape GameView::directed_block_generator(Normal_Block *board_array, int i) {
    if(board_array[i].get_has_direction()){
        if(board_array[i].get_direction() == "up"){
            texture[board_array[i].get_id()].loadFromFile("../resources/up.png");
        }
        if(board_array[i].get_direction() == "down"){
            texture[board_array[i].get_id()].loadFromFile("../resources/down.png");
        }
        if(board_array[i].get_direction() == "left"){
            texture[board_array[i].get_id()].loadFromFile("../resources/left.png");
        }
        if(board_array[i].get_direction() == "right"){
            texture[board_array[i].get_id()].loadFromFile("../resources/right.png");
        }

        sf::RectangleShape c(sf::Vector2f(board_array[i].get_length(), board_array[i].get_width()));
        c.setFillColor(sf::Color::White);
        c.setTexture(&texture[board_array[i].get_id()]);
        return c;
    }
    else{
        sf::RectangleShape c(sf::Vector2f(board_array[i].get_length(), board_array[i].get_width()));
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
        b[i] = directed_block_generator(state->get_board_array(), i);
        b[i].setPosition(state->get_board_array()[i].getX(), state->get_board_array()[i].getY());
    }
    this -> block_shapes = b;
}

/**
* Checks if mouse has clicked on a block
*/
void GameView::check_mousePosition(Normal_Block * board_array) {
    int current_y = App.getSize().y;
    int current_x = App.getSize().x;
    for(int i=0; i<5; i++) {
        if (sf::Mouse::getPosition(App).x >= int((board_array[i].getX() / 800) * current_x) && sf::Mouse::getPosition(App).x <= int(((board_array[i].getX()+100) / 800) * current_x)){
            if (sf::Mouse::getPosition(App).y >= int((board_array[i].getY() / 600) * current_y) && sf::Mouse::getPosition(App).y <= int(((board_array[i].getY()+100) / 600) * current_y)){
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    for(int be_selected=0; be_selected<5; be_selected++){
                        if(be_selected==i){
                            continue;
                        }
                        board_array[be_selected].set_selected(false);
                    }
                    board_array[i].set_selected(true);
                }
            }
        }
    }
}


/**
* Draws an outline around a block if it is selected
* @param board_array is the array of blocks
*/
int GameView::draw_selected_block(Normal_Block * board_array) {
    int selected_block = 0;
    for(int be_selected=0; be_selected<5; be_selected++){
        if(!board_array[be_selected].get_selected()){
            block_shapes[be_selected].setOutlineThickness(0);
        }
        else{
            block_shapes[be_selected].setOutlineThickness(3.5);
            block_shapes[be_selected].setOutlineColor(sf::Color::Red);
            selected_block = be_selected;
        }
    }
    return selected_block;
}


/**
* Draw animation for blocks leaving screen
* @param board_array for array of blocks
*/
void GameView::draw_movement(Normal_Block * board_array) {
    for(int i=0; i < 5; i++){
        block_shapes[i].setPosition(board_array[i].getX(),board_array[i].getY());
    }
}


/**
 * Draw all blocks, movements, and selections
 * @param board_array for array of blocks
 */
void GameView::draw(Normal_Block * board_array) {
    poll_event();
    App.clear(sf::Color(66, 150, 246));
    for (int i = 0; i < 5; i++) {
      App.draw(block_shapes[i]);
    }
    // Draw outlined selected block on top so the outline is on top
    int selected_block = draw_selected_block(board_array);
    draw_movement(board_array);
    App.draw(block_shapes[selected_block]);
    App.display();
}

/**
* Checks keyboard input, sends input to state for handling
*/
void GameView::check_keyboard_in() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        state -> try_move("up");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        state -> try_move("down");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        state -> try_move("left");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        state -> try_move("right");
    }
}

/**
 * Check events
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
}
