//
// Created by Yiyang Zhao on 02/12/2017.
//


#include "Infinite_Screen.hpp"

void Infinite_Screen::set(sf::RenderWindow &window) {
    unsigned int fontSize = 25;
    unsigned int buttonSize = 50;
    sf::Font font;
//    font.loadFromFile(REGULARFONT_FILEPATH);
//    if(!font.loadFromFile(REGULARFONT_FILEPATH))
//    {
//        sf::CircleShape circle;
//        circle.setRadius(20);
//        window.draw(circle);
//
//    }
//    this->ro_block_up_button = new sf::Text("+", font, buttonSize);
//    item_2_box = ro_block_up_button->getGlobalBounds();
//    ro_block_up_button->setOrigin(item_2_box.width/2.0f,item_2_box.height/2.0f);
//    ro_block_up_button->setPosition(sf::Vector2f(250, 250));

}

void Infinite_Screen::draw(sf::RenderWindow &window) {

    unsigned int fontSize = 25;
    unsigned int buttonSize = 50;
    sf::Font font;
    font.loadFromFile(REGULARFONT_FILEPATH);
    if(!font.loadFromFile(REGULARFONT_FILEPATH))
    {
        sf::CircleShape circle;
        circle.setRadius(20);
        window.draw(circle);

    }
    sf::Text title(MAINMENUITEM_3, font, 75);
    start =  sf::Text(MAINMENUITEM_0, font, 75);
    sf::FloatRect titlebox;
    titlebox = title.getGlobalBounds();
    title.setOrigin(titlebox.width/2.0f, titlebox.height/2.0f);
    title.setPosition(sf::Vector2f(window.getSize().x/2,(window.getSize().y/2)-230));

    titlebox = start.getGlobalBounds();
    start.setOrigin(titlebox.width/2.0f, titlebox.height/2.0f);
    start.setPosition(sf::Vector2f(window.getSize().x/2,(window.getSize().y/2)));



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


    nor_block_up_button = sf::Text("+", font, buttonSize);
    item_0_box = nor_block_up_button.getGlobalBounds();
    nor_block_up_button.setOrigin(item_0_box.width/2.0f,item_0_box.height/2.0f);
    nor_block_up_button.setPosition(sf::Vector2f(50, 250));

    nor_block_down_button = sf::Text("-", font, buttonSize);
    item_1_box = nor_block_down_button.getGlobalBounds();
    nor_block_down_button.setOrigin(item_1_box.width/2.0f,item_1_box.height/2.0f);
    nor_block_down_button.setPosition(sf::Vector2f(140, 250));

    ro_block_up_button = sf::Text("+", font, buttonSize);
    item_2_box = ro_block_up_button.getGlobalBounds();
    ro_block_up_button.setOrigin(item_2_box.width/2.0f,item_2_box.height/2.0f);
    ro_block_up_button.setPosition(sf::Vector2f(250, 250));

    ro_block_down_button = sf::Text("-", font, buttonSize);
    item_3_box = ro_block_down_button.getGlobalBounds();
    ro_block_down_button.setOrigin(item_3_box.width/2.0f,item_3_box.height/2.0f);
    ro_block_down_button.setPosition(sf::Vector2f(340, 250));


    dir_block_up_button = sf::Text("+", font, buttonSize);
    item_4_box = dir_block_up_button.getGlobalBounds();
    dir_block_up_button.setOrigin(item_4_box.width/2.0f,item_4_box.height/2.0f);
    dir_block_up_button.setPosition(sf::Vector2f(450, 250));

    dir_block_down_button = sf::Text("-", font, buttonSize);
    item_5_box = dir_block_down_button.getGlobalBounds();
    dir_block_down_button.setOrigin(item_5_box.width/2.0f,item_5_box.height/2.0f);
    dir_block_down_button.setPosition(sf::Vector2f(540, 250));

    nor_block_num = sf::Text(sf::String(std::to_string(num_of_nor)), font, fontSize);
    nor_block_num.setPosition(sf::Vector2f(95, 260));

    ro_block_num = sf::Text(sf::String(std::to_string(num_of_ro)), font, fontSize);
    ro_block_num.setPosition(sf::Vector2f(295, 260));

    dir_block_num = sf::Text(sf::String(std::to_string(num_of_dir)), font, fontSize);
    dir_block_num.setPosition(sf::Vector2f(495, 260));


    window.draw(nor_block_up_button);
    window.draw(nor_block_down_button);
    window.draw(ro_block_up_button);
    window.draw(ro_block_down_button);
    window.draw(dir_block_up_button);
    window.draw(dir_block_down_button);
    window.draw(ro_block_num);
    window.draw(nor_block_num);
    window.draw(dir_block_num);
    //window.draw(start);
    window.draw(normal_block);
    window.draw(rotating_block);
    window.draw(directional_block);
    window.draw(title);

}

bool Infinite_Screen :: check_clicked(sf::Vector2f mousePos, sf::Text desired_option, sf::RenderWindow &window)
{
    sf::FloatRect item_box = desired_option.getGlobalBounds();
    if(item_box.top < mousePos.y && (item_box.top + item_box.height) > mousePos.y && item_box.left < mousePos.x && (item_box.left + item_box.width) > mousePos.x)
    {
        //ro_block_up_button.setFillColor(sf::Color::Red);
        draw((window));
        window.display();
        return true;
    }
    else
        return false;

}


int *Infinite_Screen :: run(sf::RenderWindow &window, int cur_level)
{
    sf:: Event Event;
    bool running = true;
    int *re = new int[2];
    re[0] = 0;
    re[1] = cur_level;
    sf::Clock clock;
    float starttime;
    float endtime;
    //set(window);

    while(running)
    {

        while (window.pollEvent(Event))
        {
            if(Event.type == sf::Event::Closed)
            {
                running = false;
                re[0] = -1;
                return re;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            num_of_ro++;
        }


        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));


//            if (check_clicked(mousePosition, *ro_block_up_button, window)) {
//                num_of_ro ++;
//            }
//            if (check_clicked(mousePosition, window)) {
//                if(num_of_ro > 0){
//                    num_of_ro --;
//                }
//            }

//            if (check_clicked(mousePosition, *nor_block_up_button, window)) {
//                num_of_nor ++;
//            }
//            if (check_clicked(mousePosition, *menuItem_2, window)) {
//                re[0] = 3;
//                return re;
//            }
        }
        window.clear(sf::Color(40,140,240));
        draw(window);
        window.display();
    }
}
