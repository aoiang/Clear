//
// Created by Yiyang Zhao on 18/10/2017.
// Additional work by Ivan & Yosef
//


#include "GameView.h"


/**
  Create the game window
*/
GameView::GameView(float length, float width):
    App(sf::VideoMode(length, width, 32), "Clear",  sf::Style::Default){}


/**
  Check if window is open
  @return bool
*/
bool GameView::isOpen() {
    return App.isOpen();
}


/**
  Updates the view and logic at each frame
*/
void GameView::update() {
    check_mouse_position();
    check_keyboard_in();
    draw();
}


/**
  Assigns a GameLogic to this view
  @param logic is the GameLogic associated with this view
*/
void GameView::set_GameLogic(GameLogic &logic) {
    this -> logic = &logic;
}


/**
  Make block shapes based on their properties
  @param Normal_Block to draw
  @return sf::RectangleShape
*/
sf::RectangleShape GameView::make_block_shape(int block) {
    sf::RectangleShape block_shape(sf::Vector2f(block_size, block_size));
    block_shape.setFillColor(sf::Color::White);

    if (block >= 20) {
        if (block == 20) {
            texture[0].loadFromFile("../resources/up.png");
        } else if (block == 21) {
            texture[1].loadFromFile("../resources/right.png");
        } else if (block == 22) {
            texture[2].loadFromFile("../resources/down.png");
        } else if (block == 23) {
            texture[3].loadFromFile("../resources/left.png");
        }
        block_shape.setTexture(&texture[block % 20]);
    }

    return block_shape;
}


/**
  Initialize the GameView set all blocks shapes
  @return sf::RectangleShape
*/
void GameView::init() {
    sf::RectangleShape * shapes;
    shapes = new sf::RectangleShape[logic->get_board_width()];
    for (int i = 0; i < logic -> get_board_width(); i++) {
        if (logic -> get_block(0, i) != 0) {
            shapes[i] = make_block_shape(logic -> get_block(0, i));
        }
    }
    this -> block_shapes = shapes;
}


/**
  Checks if mouse has clicked on a block
*/
void GameView::check_mouse_position() {
    int current_y = App.getSize().y;
    int current_x = App.getSize().x;
    int mouse_x = sf::Mouse::getPosition(App).x;
    int mouse_y = sf::Mouse::getPosition(App).y;

    for (int i = 0; i < logic->get_board_width(); i++) {
        if ((mouse_x >= i * block_size + left_spacing)
            && (mouse_x <= i * block_size + block_size + left_spacing)) {
            if ((mouse_y >= 0 + top_spacing)
                && (mouse_y <= 0 + block_size + top_spacing)) {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    logic -> set_selected_position(0, i);
                    std::cout << logic -> get_selected_col();
                }
            }
        }
    }
}


/**
  Draws an outline around a block if it is selected
  @param board_array is the array of blocks
*/
void GameView::draw_selected_block() {
    if (logic -> get_selected_col() != -1 && logic -> get_block(0, logic -> get_selected_col()) != 0) {
        block_shapes[logic -> get_selected_col()].setOutlineThickness(3.5);
        block_shapes[logic -> get_selected_col()].setOutlineColor(sf::Color::Red);
        App.draw(block_shapes[logic -> get_selected_col()]);
    }
}


/**
  Draw all blocks, movements, and selections
  @param board_array for array of blocks
*/
void GameView::draw() {
    poll_event();
    App.clear(sf::Color(80, 160, 250));
    for (int i = 0; i < logic -> get_board_width(); i++) {
        if (logic -> get_block(0, i) != 0) {
            block_shapes[i].setOutlineThickness(0);
            block_shapes[i].setPosition(i * block_size + left_spacing, 0 * block_size + top_spacing);
            App.draw(block_shapes[i]);
        }
    }
    draw_selected_block();
    App.display();
}


/**
  Checks keyboard input, sends input to logic for handling
*/
void GameView::check_keyboard_in() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        logic -> try_move("up");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        logic -> try_move("down");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        logic -> try_move("left");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        logic -> try_move("right");
    }
}


/**
  Check events
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
