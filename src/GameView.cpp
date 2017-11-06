//
// Created by Yiyang Zhao on 18/10/2017.
// Additional work by Ivan & Yosef
//

#include "GameView.h"


/**
 * Create the game window
 */
GameView::GameView(float length, float width) :
    App(sf::VideoMode(length, width, 32), "Clear",  sf::Style::Default){}


/**
 * Check if window is open
 * @return bool
 */
bool GameView::isOpen() {
    return App.isOpen();
}


/**
* Updates the view and state at each frame
*/
void GameView::update() {
  check_mouse_position();
  check_keyboard_in();
  draw();
}


/**
* Assigns a GameState to this view
* @param state is the GameState associated with this view
*/
void GameView::set_GameState(GameState &state) {
    this -> state = &state;
}


/**
* Make block shapes based on their properties
* @param Normal_Block to draw
* @return sf::RectangleShape
*/
sf::RectangleShape GameView::make_block_shape(Normal_Block block) {
    sf::RectangleShape block_shape(sf::Vector2f(block.get_length(), block.get_width()));
    block_shape.setFillColor(sf::Color::White);

    if (block.get_has_direction()) {
        if (block.get_direction() == "up") {
            texture[block.get_id()].loadFromFile("../resources/up.png");
        } else if (block.get_direction() == "down") {
            texture[block.get_id()].loadFromFile("../resources/down.png");
        } else if (block.get_direction() == "left") {
            texture[block.get_id()].loadFromFile("../resources/left.png");
        } else if (block.get_direction() == "right") {
            texture[block.get_id()].loadFromFile("../resources/right.png");
        }
        block_shape.setTexture(&texture[block.get_id()]);
    }

    return block_shape;
}


/**
 * Initialize all blocks, set all parameters for blocks
 */
void GameView::block_init() {
    for(int i=0; i<5; i++){
       block[i].init(i);
    }
}


/**
 * Initialize the game, set all blocks shapes
 * @return sf::RectangleShape
 */
void GameView::init() {
    block_init();
    sf::RectangleShape * shapes;
    shapes = new sf::RectangleShape[5];
    for(int i=0; i<5; i++) {
        shapes[i] = make_block_shape(state -> get_board_array()[i]);
        shapes[i].setPosition(state -> get_board_array()[i].getX(), state -> get_board_array()[i].getY());
    }
    this -> block_shapes = shapes;
}


/**
* Checks if mouse has clicked on a block
*/
void GameView::check_mouse_position() {
    int current_y = App.getSize().y;
    int current_x = App.getSize().x;
    for(int i=0; i<5; i++) {
        if (sf::Mouse::getPosition(App).x >= int((state -> get_board_array()[i].getX() / 800) * current_x) && sf::Mouse::getPosition(App).x <= int(((state -> get_board_array()[i].getX()+100) / 800) * current_x)){
            if (sf::Mouse::getPosition(App).y >= int((state -> get_board_array()[i].getY() / 600) * current_y) && sf::Mouse::getPosition(App).y <= int(((state -> get_board_array()[i].getY()+100) / 600) * current_y)){
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    for(int is_selected=0; is_selected<5; is_selected++){
                        if(is_selected==i){
                            continue;
                        }
                        state -> get_board_array()[is_selected].set_selected(false);
                    }
                    state -> get_board_array()[i].set_selected(true);
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
    for(int is_selected=0; is_selected<5; is_selected++){
        if(!board_array[is_selected].get_selected()){
            block_shapes[is_selected].setOutlineThickness(0);
        }
        else{
            block_shapes[is_selected].setOutlineThickness(3.5);
            block_shapes[is_selected].setOutlineColor(sf::Color::Red);
            selected_block = is_selected;
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
void GameView::draw() {
    poll_event();
    App.clear(sf::Color(66, 150, 246));
    for (int i = 0; i < 5; i++) {
      App.draw(block_shapes[i]);
    }
    // Draw outlined selected block on top so the outline is on top
    int selected_block = draw_selected_block(state -> get_board_array());
    draw_movement(state -> get_board_array());
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
