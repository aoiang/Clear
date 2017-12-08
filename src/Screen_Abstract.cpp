#include "Screen_Abstract.hpp"


/**Sets GameLogic*/
void Screen_Abstract::set_GameLogic(GameLogic &logic) {this->logic = &logic;}

void Screen_Abstract::set_window(sf::RenderWindow &window) {this->window = &window;}

void Screen_Abstract::clear_window() {window->clear(sf::Color(40,140,240));}

/**Check when mouse is in an area*/
bool Screen_Abstract::is_mouse_over(sf::FloatRect bounds) {
    sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
    return bounds.top < mousePosition.y
        && (bounds.top+bounds.height) > mousePosition.y
        && bounds.left < mousePosition.x
        && (bounds.left+bounds.width) > mousePosition.x;
}

/**Check when mouse is over an sf::Text object*/
bool Screen_Abstract::is_mouse_over_text(sf::Text desired_option) {
    return is_mouse_over(desired_option.getGlobalBounds());
}

void Screen_Abstract::load_font(std::string filepath) {
    if (!font.loadFromFile(filepath)) {}//TODO
}

void Screen_Abstract::move_off_center(sf::Text * text, int x, int y) {
    sf::FloatRect bounds = text->getGlobalBounds();
    text->setOrigin(bounds.width/2.0f, bounds.height/2.0f);
    text->setPosition(sf::Vector2f((window->getSize().x/2)+x,(window->getSize().y/2)-y));
}

sf::Text Screen_Abstract::make_text(std::string text, unsigned int font_size, int x_offset, int y_offset) {
    sf::Text text_object = sf::Text(text, font, font_size);
    move_off_center(&text_object, x_offset, y_offset);
    return text_object;
}

sf::Text Screen_Abstract::make_title(std::string text) {
    return make_text(text, 100, 0, 260);
}


void Screen_Abstract::play_sound(std::string filepath) {
    if(!sound_buffer.loadFromFile(filepath)) {}//TODO
    sound.setBuffer(sound_buffer);
    if (play_audio) {sound.play();}
}