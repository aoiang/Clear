//
// Created by Yiyang Zhao on 18/10/2017.
// Additional work by Ivan & Yosef
//

#include "GameView.h"
#include <iostream>
#include <stdlib.h>

/**Create the game window*/
GameView::GameView():
    App(sf::VideoMode(default_window_height, default_window_width, 32), "Clear",  sf::Style::Default){}

/**Check if window is open*/
bool GameView::isOpen() {return App.isOpen();}

/**Updates the view and logic at each frame*/
void GameView::update() {
    check_mouse_position();
    check_keyboard_in();
    draw();
}

/**Assigns a GameLogic to this view*/
void GameView::set_GameLogic(GameLogic &logic) {this->logic = &logic;}

/**
  Make block shapes based on their properties
  @param Normal_Block to draw
  @return sf::RectangleShape
*/
sf::RectangleShape GameView::make_block_shape(int block_id) {
    sf::RectangleShape block_shape(sf::Vector2f(block_size, block_size));
    block_shape.setFillColor(sf::Color(235, 235, 235));
    if (block_id>=20) {block_shape.setTexture(&texture[block_id%20]);}//TODO probably a bug here; didn't seem intended to do anything with block>23
    return block_shape;
}

/**Makes shapes for paths*/
sf::RectangleShape GameView::make_path_shape(int w, int h) {
  sf::RectangleShape path_shape(sf::Vector2f(w, h));
  path_shape.setFillColor(sf::Color(255, 255, 255, 120));
  return path_shape;
}

/**Load textures from files*/
void GameView::load_texture(int texture_index) {
    if (!texture[texture_index].loadFromFile(texture_filepaths[texture_index])) {
        texture[texture_index].loadFromFile(texture_filepaths[texture_index]+1);
        //Converts ../* to ./*
    }
}

/**Loads all textures*/
void GameView::load_textures() {
    for (int i=0; i<4; i++) {load_texture(i);}
}

/**
  Make shadow shapes
  @return sf::RectangleShape shadow_shape
*/
sf::RectangleShape GameView::make_shadow_shape() {
    sf::RectangleShape shadow_shape(sf::Vector2f(block_size*0.98, block_size*0.98));
    shadow_shape.setFillColor(sf::Color(0, 0, 0, 60));
    return shadow_shape;
}

/**
  Make the circular shadow that's under selected block
  From https://github.com/SFML/SFML/wiki/Source:-Radial-Gradient-Shader
*/
void GameView::make_selected_shadow() {
    selected_shadow.setRadius(60.f);
    selected_shadow.setOrigin(selected_shadow.getRadius(), selected_shadow.getRadius());
    selected_shadow.setPosition(sf::Vector2f(300, 300));
    selected_shadow.setFillColor(sf::Color::Transparent);

    selected_shader.loadFromMemory("void main(){"
                                  	   "gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"
                                  	   "gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
                                  	   "gl_FrontColor = gl_Color;"
                                   "}",
                                   "uniform vec4 color;"
                                   "uniform vec2 center;"
                                   "uniform float radius;"
                                   "uniform float expand;"
                                   "uniform float windowHeight;"
                                   "void main(void) {"
                                       "vec2 centerFromSfml = vec2(center.x, windowHeight - center.y);"
                                       "vec2 p = (gl_FragCoord.xy - centerFromSfml) / radius;"
                                       "float r = sqrt(dot(p, p));"
                                  	"if (r < 1.0) {"
                                  		 "gl_FragColor = mix(color, gl_Color, (r - expand) / (1 - expand));"
                                  	"} else {"
                                  		 "gl_FragColor = gl_Color;"
                                  	"}"
                                  "}");
    selected_shader.setParameter("windowHeight", static_cast<float>(App.getSize().y));
    selected_shader.setParameter("color", sf::Color::Black);
    selected_shader.setParameter("radius", selected_shadow.getRadius());
    selected_shader.setParameter("expand", 0.f);
}

/**Create all of the shapes*/
void GameView::init() {
    App.setFramerateLimit(60);

    int board_width = logic->get_board_width();
    int board_height = logic->get_board_height();

    load_textures();

    sf::RectangleShape * shapes;
    sf::RectangleShape * shadows;
    sf::RectangleShape * paths;

    shapes = new sf::RectangleShape[board_width*board_height]();
    shadows = new sf::RectangleShape[board_width*board_height]();
    paths = new sf::RectangleShape[2]();

    for (int x=0; x<board_width; x++) {
        for (int y=0; y<board_height; y++) {
            if (logic->block_exists(x, y)) {
                shapes[(y*board_width)+x] = make_block_shape(logic->get_block(x, y)->get_id());
                shadows[(y*board_width)+x] = make_shadow_shape();
            }
        }
    }

    paths[0] = make_path_shape(block_size, App.getSize().y);
    paths[1] = make_path_shape(App.getSize().x, block_size);

    this->block_shapes = shapes;
    this->shadow_shapes = shadows;
    this->path_shapes = paths;

    make_selected_shadow();
}

//TODO patrick: fix these conversions for resizing etc.
/**Convert board x coordinate to drawing x coordinate*/
int GameView::BoardXToXPixel(int x) {return left_spacing + (x*block_size);}

/**Convert board y coordinate to drawing y coordinate*/
int GameView::BoardYToYPixel(int y) {
    int current_window_height = App.getSize().y;
    return current_window_height - (bottom_spacing + (y*block_size)) - block_size;
}

/**Convert pixel x coordinate to board x coordinate*/
int GameView::XPixelToBoardX(int x_pixel) {
    if (x_pixel<left_spacing) {return -1;}
    else {return (x_pixel-left_spacing)/block_size;}
}

/**Convert pixel y coordinate to board y coordinate*/
int GameView::YPixelToBoardY(int y_pixel) {
    int current_window_height = App.getSize().y;
    int flipped_y_pixel = current_window_height - y_pixel;
    if (flipped_y_pixel<bottom_spacing) {return -1;}
    else {return (flipped_y_pixel-bottom_spacing)/block_size;}
}

//TODO make it care if the mouse leaves the original block when dragging.
/**Checks if mouse has clicked on a block*/
void GameView::check_mouse_position() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!clicked) {
            mouse_x_start = sf::Mouse::getPosition(App).x;
            mouse_y_start = sf::Mouse::getPosition(App).y;
            logic->set_selected_position(XPixelToBoardX(mouse_x_start), YPixelToBoardY(mouse_y_start));
            clicked = true;
        } else {
            int dx = mouse_x_start - sf::Mouse::getPosition(App).x;
            int dy = mouse_y_start - sf::Mouse::getPosition(App).y;

            if (dx < -deadzone && abs(dx) > abs(dy)) {dir = 'r';}
            else if (dx > deadzone && abs(dx) > abs(dy)) {dir = 'l';}
            else if (dy < -deadzone && abs(dy) > abs(dx)) {dir = 'd';}
            else if (dy > deadzone && abs(dy) > abs(dx)) {dir = 'u';}
            else {dir = 'n';}
        }
    } else {
        if (clicked) {
            clicked = false;
            if (dir != 'n') {
                logic->try_move_selected(dir);
            }
            dir = 'n';
            logic->set_selected_position(-1,-1);
        }
    }
}

/**Draws selected block and shadow under it*/
void GameView::draw_selected_block() {
    if (logic->selected_block_exists()) {
        // selection shadow
        selected_shadow.setPosition(sf::Vector2f(BoardXToXPixel(logic->get_selected_x()) + (block_size / 2),
                                                 BoardYToYPixel(logic->get_selected_y()) + (block_size / 2)));
        selected_shader.setParameter("center", selected_shadow.getPosition());
        App.draw(selected_shadow, &selected_shader);

        // selected block
        int index = (logic->get_selected_y() * logic->get_board_width()) + logic->get_selected_x();
        block_shapes[index].setSize(sf::Vector2f(block_size*1.1, block_size*1.1));
        block_shapes[index].setFillColor(sf::Color::White);
        block_shapes[index].move(-0.05*block_size, -0.05*block_size);
        App.draw(block_shapes[index]);
    }
}

/**Highlights path that the block will take*/
void GameView::draw_path_highlighting() {
    if (logic->selected_block_exists()) {
        if (dir == 'u') {
            path_shapes[0].setPosition(sf::Vector2f(BoardXToXPixel(logic->get_selected_x()),
                                                    BoardYToYPixel(logic->get_selected_y()) - default_window_height));
            App.draw(path_shapes[0]);
        } else if (dir == 'd') {
            path_shapes[0].setPosition(sf::Vector2f(BoardXToXPixel(logic->get_selected_x()),
                                                    BoardYToYPixel(logic->get_selected_y())));
            App.draw(path_shapes[0]);
        } else if (dir == 'l') {
            path_shapes[1].setPosition(sf::Vector2f(BoardXToXPixel(logic->get_selected_x()) - default_window_width,
                                                    BoardYToYPixel(logic->get_selected_y())));
            App.draw(path_shapes[1]);
        } else if (dir == 'r') {
            path_shapes[1].setPosition(sf::Vector2f(BoardXToXPixel(logic->get_selected_x()),
                                                    BoardYToYPixel(logic->get_selected_y())));
            App.draw(path_shapes[1]);
        }
    }
}

/**Draws shadows under blocks*/
void GameView::draw_shadows() {
    int width = logic->get_board_width();
    int height = logic->get_board_height();
    int i;
    for (int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {
            if (logic->block_exists(x, y)) {
                i = (y*width)+x;
                shadow_shapes[i].setPosition(BoardXToXPixel(x) + 10, BoardYToYPixel(y) + 10);
                App.draw(shadow_shapes[i]);
            }
        }
    }
}

/**Draws blocks*/
void GameView::draw_blocks() {
    int width = logic->get_board_width();
    int height = logic->get_board_height();
    int i;
    for (int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {
            if (logic->block_exists(x, y)) {
                i = (y*width)+x;
                block_shapes[i].setSize(sf::Vector2f(block_size*0.98, block_size*0.98));
                block_shapes[i].setFillColor(sf::Color(235, 235, 235));
                block_shapes[i].setPosition(BoardXToXPixel(x), BoardYToYPixel(y));
                App.draw(block_shapes[i]);
            }
        }
    }
}

/**Draw all blocks, shadows, movements, and selections*/
void GameView::draw() {
    poll_event();
    App.clear(sf::Color(40,140,240));
    draw_shadows();
    draw_blocks();
    draw_path_highlighting();
    draw_selected_block();
    App.display();
}

/**Checks keyboard input, sends input to logic for handling*/
void GameView::check_keyboard_in() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {logic->try_move_selected('u');}
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {logic->try_move_selected('d');}
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {logic->try_move_selected('l');}
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {logic->try_move_selected('r');}
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
