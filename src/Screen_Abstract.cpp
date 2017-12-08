#include "Screen_Abstract.hpp"


/**Sets GameLogic*/
void Screen_Abstract::set_GameLogic(GameLogic &logic) {this->logic = &logic;}

void Screen_Abstract::set_window(sf::RenderWindow &window) {this->window = &window;}

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

/*
void Screen_Abstract::play_sound(std::string filepath) {
    if(!sound_buffer.loadFromFile(filepath)) {}//TODO
    sound.setBuffer(sound_buffer);
    sound.play();
}*/