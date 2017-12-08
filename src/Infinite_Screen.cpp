#include "Infinite_Screen.hpp"
#include "GameView_Screen.hpp"

Infinite_Screen::Infinite_Screen() {
    normal_frequency = 1;
    rotating_frequency = 1;
    directional_frequency = 1;
    width = 5;
    height = 5;
}

void Infinite_Screen::draw() {
    clear_window();
    
    for (int i=0; i<10; i++) {window->draw(button[i]);}
    
    unsigned int fontSize = 25;
    window->draw(make_text(std::to_string(width), fontSize, -100, -100));
    window->draw(make_text(std::to_string(height), fontSize, 100, -100));
    static const std::string options[3] = {"none", "some", "many"};
    window->draw(make_text(options[normal_frequency], fontSize, -200, 50));
    window->draw(make_text(options[rotating_frequency], fontSize, 0, 50));
    window->draw(make_text(options[directional_frequency], fontSize, 200, 50));
    
    window->draw(normal_block);
    window->draw(rotating_block);
    window->draw(directional_block);
    window->draw(title);
    window->draw(board_size);
    window->draw(start);
    window->display();
}

int Infinite_Screen::run() {
    sf::Clock clock;
    load_font(REGULARFONT_FILEPATH);
    
    GameView_Screen::load_textures();
    normal_block = GameView_Screen::make_block_shape(ID_NORMAL);
    rotating_block = GameView_Screen::make_block_shape(ID_ROTATE_0);
    directional_block = GameView_Screen::make_block_shape(ID_U_DIR);
    
    normal_block.setPosition(75, 180);
    rotating_block.setPosition(275,180);
    directional_block.setPosition(475,180);

    title = make_title("Infinite");
    start = make_text("Start", 50, 0, -200);
    board_size = make_text("Size", 35, 0, -50);
    
    
    
    static const char* const signs[2] = {"+", "-"};
    
    for (int i=0; i<10; i++) {
        int x, y;
        switch (i) {
            case 0: case 1: x = -200; y = 50; break;
            case 2: case 3: x = 0; y = 50; break;
            case 4: case 5: x = 200; y = 50; break;
            case 6: case 7: x = -100; y = -100; break;
            case 8: case 9: x = 100; y = -100; break;
        }
        button[i] = make_text(signs[i%2], 75, x+(35-((i%2)*80)), y+(5*(i%2))+30);
    }
    
    
    while (true) {
        while (window->pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {return EXIT_GAME;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {return SCREEN_MAINMENU;}
        }
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (!clicked) {
                clicked = true;
                if (is_mouse_over_text(start)) {
                    logic->set_generated_board_size(width, height);
                    logic->set_cur_level(0);
                    logic->set_nums_of_blocks(normal_frequency, rotating_frequency, directional_frequency);
                    return SCREEN_GAMEVIEW;
                } else {
                    for (int i=0; i<10; i++) {
                        if (is_mouse_over_text(button[i])) {
                            int type_remains = normal_frequency + rotating_frequency + directional_frequency;
                            switch (i) {
                                case 0: if (normal_frequency<2) {normal_frequency++;} break;
                                case 1: if (type_remains>1 && normal_frequency>0) {normal_frequency--;} break;
                                case 2: if (rotating_frequency<2) {rotating_frequency++;} break;
                                case 3: if (type_remains>1 && rotating_frequency>0) {rotating_frequency--;} break;
                                case 4: if (directional_frequency<2) {directional_frequency++;} break;
                                case 5: if (type_remains>1 && directional_frequency>0) {directional_frequency--;} break;
                                case 6: if (width<9) {width++;} break;
                                case 7: if (width>1) {width--;} break;
                                case 8: if (height<9) {height++;} break;
                                case 9: if (height>1) {height--;} break;
                            }
                        }
                    }
                }
            }
        } else if (clicked) {clicked = false;}
        draw();
    }
}
