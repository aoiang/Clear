//
// Created by Yiyang Zhao on 18/10/2017
// Additional work by Ivan & Yosef
//

#ifndef CLEAR_GAMEVIEW_H
#define CLEAR_GAMEVIEW_H

#include <SFML/Graphics.hpp>
#include "Block.h"
#include "Normal_Block.h"
#include "GameLogic.h"

static char texture_filepaths[4][40] = {"../resources/up.png",
                                        "../resources/right.png",
                                        "../resources/down.png",
                                        "../resources/left.png"};

class GameView {
    private:
        sf::Texture texture[15];
        sf::RectangleShape * block_shapes;
        sf::RectangleShape * shadow_shapes;
        GameLogic * logic;
        int default_window_width = 600;
        int default_window_height = 600;
        int bottom_spacing = 50;
        int left_spacing = 50;
        bool clicked = false;
        int mouse_x_start;
        int mouse_y_start;
        int deadzone = 10;
    public:
        int block_size = 50;
        sf::RenderWindow App;
        GameView();
        void init();
        bool isOpen();
        void draw_shadows();
        void draw_blocks();
        void draw();
        void poll_event();
        sf::RectangleShape make_block_shape(int block_id);
        void load_texture(int);
        void load_textures();
        sf::RectangleShape make_shadow_shape();
        int BoardXToXPixel(int x);
        int BoardYToYPixel(int y);
        int XPixelToBoardX(int x);
        int YPixelToBoardY(int y);
        void check_mouse_position();
        void check_keyboard_in();
        sf::RenderWindow get_App();
        void draw_selected_block();
        void set_GameLogic(GameLogic &logic);
        void update();
};


#endif //CLEAR_GAMEVIEW_H
