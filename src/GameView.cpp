//
// Created by Yiyang Zhao on 18/10/2017.
// Additional work by Ivan & Yosef
//


#include "GameView.h"

#include <iostream>

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

    // TODO: fix this kludgey implementation

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
  Make shadow shapes
  @return sf::RectangleShape shadow_shape
*/
sf::RectangleShape GameView::make_shadow_shape() {
    sf::RectangleShape shadow_shape(sf::Vector2f(block_size, block_size));
    shadow_shape.setFillColor(sf::Color(0, 0, 0, 60));
    return shadow_shape;
}


/**
  Create all of the shapes
*/
void GameView::init() {
    int board_height = logic -> get_board_height();
    int board_width = logic -> get_board_width();

    sf::RectangleShape * shapes;
    sf::RectangleShape * shadows;

    shapes = new sf::RectangleShape[board_width * board_height];
    shadows = new sf::RectangleShape[board_width * board_height];

    for (int i = 0; i < board_width * board_height; i++) {
        if (logic -> get_block(i / board_height, i % board_width) != 0) {
            shapes[i] = make_block_shape(logic -> get_block(i / board_height, i % board_width));
            shadows[i] = make_shadow_shape();
        }
    }
    this -> block_shapes = shapes;
    this -> shadow_shapes = shadows;
}


/**
  Checks if mouse has clicked on a block
*/
void GameView::check_mouse_position() {
    int current_y = App.getSize().y;
    int current_x = App.getSize().x;
    int mouse_x = sf::Mouse::getPosition(App).x;
    int mouse_y = sf::Mouse::getPosition(App).y;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        logic->set_selected_position(((mouse_y - top_spacing) * 600 / block_size) / current_y,
                                     ((mouse_x - left_spacing) * 800 / block_size) / current_x);
    }

}


/**
  Draws an outline around a block if it is selected
*/
void GameView::draw_selected_block() {
    if (logic->get_selected_block() != 0) {
        int index = (logic->get_selected_row() * logic->get_board_width()) + logic->get_selected_col();
        block_shapes[index].setOutlineThickness(3.5);
        block_shapes[index].setOutlineColor(sf::Color::Red);
        App.draw(block_shapes[index]);
    }
}


/**
  Draw all blocks, shadows, movements, and selections
*/
void GameView::draw() {
    poll_event();
    App.clear(sf::Color(120, 180, 255));
    int height = logic->get_board_height();
    int width = logic->get_board_width();
    // shadow drawing pass
    for (int i = 0; i < height * width; i++) {
        if (logic -> get_block(i / height, i % width) != 0) {
            shadow_shapes[i].setPosition((i % width) * block_size + left_spacing + (block_size / 5), (i / height) * block_size + top_spacing + (block_size / 5));
            App.draw(shadow_shapes[i]);
        }
    }
    // block drawing pass
    for (int i = 0; i < logic->get_board_width() * logic->get_board_height(); i++) {
        if (logic -> get_block(i / height, i % width) != 0) {
            block_shapes[i].setOutlineThickness(0);
            block_shapes[i].setPosition((i % width) * block_size + left_spacing, (i / height) * block_size + top_spacing);
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
