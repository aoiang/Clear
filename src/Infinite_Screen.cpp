#include "Infinite_Screen.hpp"

void Infinite_Screen::init() {
    for(int i=0; i<3; i++) {num_of_blocks[i] = 1;}
    num_of_blocks[3] = 5;
    num_of_blocks[4] = 5;
}

void Infinite_Screen::counts_of_block() {
    static const char* const options[3] = {"none", "some", "many"};
    for (int i=0; i<3; i++) {
        block_counts[i] = options[num_of_blocks[i]];
    }
}

void Infinite_Screen::draw() {
    unsigned int fontSize = 25;
    unsigned int buttonSize = 75;
    load_font(REGULARFONT_FILEPATH);

    sf::Text title("Infinite", font, 75);
    start = sf::Text("Start", font, 50);
    sf::FloatRect titlebox;
    titlebox = title.getGlobalBounds();
    title.setOrigin(titlebox.width/2.0f, titlebox.height/2.0f);
    title.setPosition(sf::Vector2f(window->getSize().x/2,(window->getSize().y/2)-230));

    sf::Text board_size("Size", font, 35);
    titlebox = board_size.getGlobalBounds();
    board_size.setOrigin(titlebox.width/2.0f, titlebox.height/2.0f);
    board_size.setPosition(sf::Vector2f(window->getSize().x/2,(window->getSize().y/2)+50));

    titlebox = start.getGlobalBounds();
    start.setOrigin(titlebox.width/2.0f, titlebox.height/2.0f);
    start.setPosition(sf::Vector2f(window->getSize().x/2,(window->getSize().y/2)+200));

    sf::RectangleShape rotating_block;
    sf::RectangleShape directional_block;
    sf::RectangleShape normal_block;
    sf::Texture ro_texture;
    sf::Texture dir_texture;
    sf::Texture nor_texture;
    sf::CircleShape triangle(12.5, 3);

    rotating_block.setSize(sf::Vector2f(block_size,block_size));
    directional_block.setSize(sf::Vector2f(block_size,block_size));
    normal_block.setSize(sf::Vector2f(block_size,block_size));
    dir_texture.loadFromFile(UP_TEXTURE);
    dir_texture.setSmooth(true);
    ro_texture.loadFromFile(ROTATING_0_TEXTURE);
    ro_texture.setSmooth(true);
    rotating_block.setTexture(&ro_texture);
    directional_block.setTexture(&dir_texture);
    normal_block.setPosition(75, 180);
    rotating_block.setPosition(275,180);
    directional_block.setPosition(475,180);

    for (int i=0; i<10; i++) {
        if (i%2 == 0) {button[i] = sf::Text("+", font, buttonSize);}
        else {button[i] = sf::Text("-", font, buttonSize);}
        item_box[i] = button[i].getGlobalBounds();
        button[i].setOrigin(item_box[i].width/2.0f,item_box[i].height/2.0f);
        if (i<6) {
            if (i%2 == 0) {button[i].setPosition(sf::Vector2f(50+(200 * i / 2), 250));}
            else {button[i].setPosition(sf::Vector2f(140+(200 * (i / 2)), 250));}
        } else {
            if (i%2 == 0) {button[i].setPosition(sf::Vector2f(150+(200 * (i / 8)), 400));}
            else {button[i].setPosition(sf::Vector2f(240+(200 * (i / 8)), 400));}
        }
        window->draw(button[i]);
    }

    for (int i=0; i<5; i++){
        if (i>=3) {
            block_num[i] = sf::Text(sf::String(std::to_string(num_of_blocks[i])), font, fontSize);
            block_num[i].setPosition(sf::Vector2f(195 + (200 * (i-3)), 420));
        } else {
            counts_of_block();
            block_num[i] = sf::Text(sf::String(block_counts[i]), font, fontSize);
            block_num[i].setPosition(sf::Vector2f(75 + (200 * i), 270));
        }
        window->draw(block_num[i]);
    }
    window->draw(normal_block);
    window->draw(rotating_block);
    window->draw(directional_block);
    window->draw(title);
    window->draw(board_size);
    window->draw(start);
}

int Infinite_Screen::run() {
    init();
    sf::Clock clock;
    float starttime;
    float endtime;

    while (true) {
        while (window->pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {return EXIT_GAME;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {return SCREEN_MAINMENU;}
        }
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (!clicked) {clicked = true;}
            if (is_mouse_over_text(start)) {
                logic->set_generated_board_size(num_of_blocks[3], num_of_blocks[4]);
                logic->set_cur_level(0);
                logic->set_nums_of_blocks(block_counts[0], block_counts[1], block_counts[2]);
                return SCREEN_GAMEVIEW;
            }
        } else if (clicked) {
            clicked = false;
            for (int butt = 0; butt < 10; butt++){
                if (is_mouse_over(button[butt].getGlobalBounds())){
                    if (butt < 6) {
                        if ((butt % 2 == 0) && (num_of_blocks[butt/2] < 2)) {num_of_blocks[butt/2]++;}
                        else if (num_of_blocks[butt/2] > 0) {num_of_blocks[butt/2]--;}
                    } else {
                        if ((butt % 2 == 0) && (num_of_blocks[butt/2] < 9)) {num_of_blocks[butt/2]++;}
                        else if (num_of_blocks[butt/2] > 0) {num_of_blocks[butt/2] --;}
                    }
                }
            }
        }
        window->clear(sf::Color(40,140,240));
        draw();
        window->display();
    }
}
