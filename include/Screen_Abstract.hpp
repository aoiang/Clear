#ifndef CLEAR_SCREEN_ABSTRACT_HPP
#define CLEAR_SCREEN_ABSTRACT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Definitions.hpp"
#include "GameLogic.hpp"

class Screen_Abstract {
    protected:
        bool play_audio = true;
        GameLogic * logic;
        sf::RenderWindow * window;
        sf::Font font;
        sf::SoundBuffer sound_buffer;
        sf::Sound sound;
        sf::Event Event;
        bool is_mouse_over(sf::FloatRect bounds);
        bool is_mouse_over_text(sf::Text desired_option);
        bool is_mouse_over(sf::Vector2f mousePos, sf::FloatRect bounds);
        bool is_mouse_over_text(sf::Vector2f mousePos, sf::Text desired_option);
        void clear_window();
    public:
        void set_GameLogic(GameLogic &logic);
        void set_window(sf::RenderWindow &window);
        virtual int run() = 0;
        void load_font(std::string filepath);
        void move_off_center(sf::Text * text, int x, int y);
        sf::Text make_text(std::string text, unsigned int font_size, int x_offset, int y_offset);
        sf::Text make_title(std::string text);
        void play_sound(std::string filepath);
};

#endif //CLEAR_SCREEN_ABSTRACT_HPP
