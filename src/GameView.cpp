//
// Created by Yiyang Zhao on 18/10/2017.
// Additional work by Ivan & Yosef
//


#include "GameView.h"

#include <iostream>

/**Create the game window*/
GameView::GameView():
    App(sf::VideoMode(default_window_height, default_window_width, 32), "Clear",  sf::Style::Default){}


/**
  Check if window is open
  @return bool
*/
bool GameView::isOpen() {return App.isOpen();}


/**Updates the view and logic at each frame*/
void GameView::update() {
    check_mouse_position();
    check_keyboard_in();
    draw();
}


/**
  Assigns a GameLogic to this view
  @param logic is the GameLogic associated with this view
*/
void GameView::set_GameLogic(GameLogic &logic) {this->logic = &logic;}


/**
  Make block shapes based on their properties
  @param Normal_Block to draw
  @return sf::RectangleShape
*/
sf::RectangleShape GameView::make_block_shape(int block) {
    sf::RectangleShape block_shape(sf::Vector2f(block_size, block_size));
    block_shape.setFillColor(sf::Color::White);
    if (block>=20) {block_shape.setTexture(&texture[block%20]);}//TODO probably a bug here; didn't seem intended to do anything with block>23
    return block_shape;
}

void GameView::load_texture(int texture_index) {
    if (!texture[texture_index].loadFromFile(texture_filepaths[texture_index])) {
        texture[texture_index].loadFromFile(texture_filepaths[texture_index]+1);
        //Converts ../* to ./*
    }
}

void GameView::load_textures() {
    for (int i=0; i<4; i++) {load_texture(i);}
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


/**Create all of the shapes*/
void GameView::init() {
    int board_width = logic->get_board_width();
    int board_height = logic->get_board_height();
    
    load_textures();

    sf::RectangleShape * shapes;
    sf::RectangleShape * shadows;

    shapes = new sf::RectangleShape[board_width*board_height];
    shadows = new sf::RectangleShape[board_width*board_height];

    for (int x=0; x<board_width; x++) {
        for (int y=0; y<board_height; y++) {
            if (logic->get_block(x, y) != 0) {
                shapes[(y*board_width)+x] = make_block_shape(logic->get_block(x, y));
                shadows[(y*board_width)+x] = make_shadow_shape();
            }
        }
    }
    this->block_shapes = shapes;
    this->shadow_shapes = shadows;
}


//TODO patrick: fix these conversions for resizing etc.
int GameView::BoardXToXPixel(int x) {return left_spacing + (x*block_size);}


int GameView::BoardYToYPixel(int y) {
    int current_window_height = App.getSize().y;
    return current_window_height - (bottom_spacing + (y*block_size)) - block_size;
}


int GameView::XPixelToBoardX(int x_pixel) {
    if (x_pixel<left_spacing) {return -1;}
    else {return (x_pixel-left_spacing)/block_size;}
}


int GameView::YPixelToBoardY(int y_pixel) {
    int current_window_height = App.getSize().y;
    int flipped_y_pixel = current_window_height - y_pixel;
    if (flipped_y_pixel<bottom_spacing) {return -1;}
    else {return (flipped_y_pixel-bottom_spacing)/block_size;}
}



/**Checks if mouse has clicked on a block*/
void GameView::check_mouse_position() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        int mouse_x_in_window = sf::Mouse::getPosition(App).x;
        int mouse_y_in_window = sf::Mouse::getPosition(App).y;
        logic->set_selected_position(XPixelToBoardX(mouse_x_in_window), YPixelToBoardY(mouse_y_in_window));
    }
}


/**Draws an outline around a block if it is selected*/
void GameView::draw_selected_block() {
    if (logic->get_selected_block()!=0) {
        int index = (logic->get_selected_y() * logic->get_board_width()) + logic->get_selected_x();
        block_shapes[index].setOutlineThickness(3.5);
        block_shapes[index].setOutlineColor(sf::Color::Red);
        App.draw(block_shapes[index]);
    }
}

void GameView::draw_shadows() {
    int width = logic->get_board_width();
    int height = logic->get_board_height();
    int i;
    for (int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {
            if (logic->get_block(x, y) != 0) {
                i = (y*width)+x;
                shadow_shapes[i].setPosition(BoardXToXPixel(x) + 10, BoardYToYPixel(y) + 10);
                App.draw(shadow_shapes[i]);
            }
        }
    }
}

void GameView::draw_blocks() {
    int width = logic->get_board_width();
    int height = logic->get_board_height();
    int i;
    for (int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {
            if (logic->get_block(x, y) != 0) {
            block_shapes[i].setOutlineThickness(0);
                i = (y*width)+x;
                block_shapes[i].setOutlineThickness(0);
                block_shapes[i].setPosition(BoardXToXPixel(x), BoardYToYPixel(y));
                App.draw(block_shapes[i]);
            }
        }
    }
}


/**Draw all blocks, shadows, movements, and selections*/
void GameView::draw() {//TODO split this into functions for drawing each thing.
    poll_event();
    App.clear(sf::Color(120, 180, 255));
    draw_shadows();
    draw_blocks();
    draw_selected_block();
    App.display();
}


/**Checks keyboard input, sends input to logic for handling*/
void GameView::check_keyboard_in() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {logic->try_move("up");}
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {logic->try_move("down");}
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {logic->try_move("left");}
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {logic->try_move("right");}
}


/**Check events*/
void GameView::poll_event(){
    sf::Event Event;
    while(App.pollEvent(Event)){
        switch (Event.type) {
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){App.close();}
                break;
            case sf::Event::Closed:
                App.close();
                break;
            default: break;
        }
    }
}
