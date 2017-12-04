#include "Infinite_Screen.hpp"

void Infinite_Screen::init() {
    for(int i = 0; i < 5; i++){
        num_of_blocks[i] = 0;
    }
}

void Infinite_Screen::draw(sf::RenderWindow &window) {
    unsigned int fontSize = 25;
    unsigned int buttonSize = 75;
    sf::Font font;
    font.loadFromFile(REGULARFONT_FILEPATH);
    if(!font.loadFromFile(REGULARFONT_FILEPATH)) {
        sf::CircleShape circle;
        circle.setRadius(20);
        window.draw(circle);
    }

    sf::Text title(MAINMENUITEM_3, font, 75);
    start =  sf::Text("Start", font, 50);
    sf::FloatRect titlebox;
    titlebox = title.getGlobalBounds();
    title.setOrigin(titlebox.width/2.0f, titlebox.height/2.0f);
    title.setPosition(sf::Vector2f(window.getSize().x/2,(window.getSize().y/2)-230));

    sf::Text board_size("Size", font, 35);
    titlebox = board_size.getGlobalBounds();
    board_size.setOrigin(titlebox.width/2.0f, titlebox.height/2.0f);
    board_size.setPosition(sf::Vector2f(window.getSize().x/2,(window.getSize().y/2)+50));

    titlebox = start.getGlobalBounds();
    start.setOrigin(titlebox.width/2.0f, titlebox.height/2.0f);
    start.setPosition(sf::Vector2f(window.getSize().x/2,(window.getSize().y/2)+200));

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

    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {button[i] = sf::Text("+", font, buttonSize);}
        else {button[i] = sf::Text("-", font, buttonSize);}
        item_box[i] = button[i].getGlobalBounds();
        button[i].setOrigin(item_box[i].width/2.0f,item_box[i].height/2.0f);
        if (i < 6) {
            if (i % 2 == 0) {button[i].setPosition(sf::Vector2f(50+(200 * i / 2), 250));}
            else {button[i].setPosition(sf::Vector2f(140+(200 * (i / 2)), 250));}
        } else {
            if (i % 2 == 0) {button[i].setPosition(sf::Vector2f(150+(200 * (i / 8)), 400));}
            else {button[i].setPosition(sf::Vector2f(240+(200 * (i / 8)), 400));}
        }
        window.draw(button[i]);
    }

    for (int i = 0; i < 5; i++){
        block_num[i] = sf::Text(sf::String(std::to_string(num_of_blocks[i])), font, fontSize);
        if (i < 3) {block_num[i].setPosition(sf::Vector2f(95 + (200 * i), 270));}
        else {block_num[i].setPosition(sf::Vector2f(195 + (200 * (i-3)), 420));}
        window.draw(block_num[i]);
    }

    window.draw(normal_block);
    window.draw(rotating_block);
    window.draw(directional_block);
    window.draw(title);
    window.draw(board_size);
    window.draw(start);
}

void Infinite_Screen::set_GameLogic(GameLogic &logic) {this->logic = &logic;}

bool Infinite_Screen :: check_clicked(sf::Vector2f mousePos, int cur_button, sf::RenderWindow &window) {
    sf::FloatRect item_box = button[cur_button].getGlobalBounds();
    return item_box.top < mousePos.y && (item_box.top + item_box.height) > mousePos.y && item_box.left < mousePos.x && (item_box.left + item_box.width) > mousePos.x;
}

bool Infinite_Screen ::start_clicked(sf::Vector2f mousePos, sf::RenderWindow &window) {
    sf::FloatRect item_box = start.getGlobalBounds();
    return item_box.top < mousePos.y && (item_box.top + item_box.height) > mousePos.y && item_box.left < mousePos.x && (item_box.left + item_box.width);
}

int Infinite_Screen::run(sf::RenderWindow &window) {
    init();
    sf:: Event Event;
    bool running = true;
    sf::Clock clock;
    float starttime;
    float endtime;

    while(running) {
        while (window.pollEvent(Event)) {
            if(Event.type == sf::Event::Closed) {
                running = false;
                return EXIT_GAME;
            }
        }

        if(Event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                return SCREEN_MAINMENU;
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
            for (int butt = 0; butt < 10; butt++){
                if (check_clicked(mousePosition, butt, window)){
                    if(butt % 2 == 0){
                        if (num_of_blocks[butt/2] < 9){
                            num_of_blocks[butt/2] ++;
                        }
                    }
                    else{
                        if (num_of_blocks[butt/2] > 0){
                            num_of_blocks[butt/2] --;
                        }
                    }
                }
            }

            if (start_clicked(mousePosition, window)){
                logic->set_generated_board_size(num_of_blocks[3], num_of_blocks[4]);
                logic->set_cur_level(0);
                return SCREEN_GAMEVIEW;
            }
        }

        window.clear(sf::Color(40,140,240));
        draw(window);
        window.display();
    }
}
