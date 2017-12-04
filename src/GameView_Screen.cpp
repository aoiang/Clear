#include "GameView_Screen.hpp"
#include "BoardGenerator.hpp"

/**Create the game window*/
GameView_Screen::GameView_Screen() = default;

/**Check if window is open*/
bool GameView_Screen::isOpen() {return running;}

/**Assigns a GameLogic to this view*/
void GameView_Screen::set_GameLogic(GameLogic &logic) {this->logic = &logic;}

/**Make block shapes based on their properties*/
sf::RectangleShape GameView_Screen::make_block_shape(int block_id) {
    sf::RectangleShape block_shape(sf::Vector2f(block_size, block_size));
    block_shape.setFillColor(sf::Color(235, 235, 235));
    if (block_id>=20 && block_id < 30) {block_shape.setTexture(&texture[block_id%20]);}//TODO probably a bug here; didn't seem intended to do anything with block>23
    else if (block_id>=30 && block_id < 40) {block_shape.setTexture(&texture[(block_id%30)+4]);}
    return block_shape;
}

/**Makes shapes for effects*/
sf::RectangleShape GameView_Screen::make_alpha_rectangle_shape(int width, int height, int red, int green, int blue, int alpha) {
    sf::RectangleShape shape(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color(red, green, blue, alpha));
    return shape;
}

/**Load textures from files*/
void GameView_Screen::load_texture(int texture_index) {
    texture[texture_index].loadFromFile(texture_filepaths[texture_index]);
    texture[texture_index].setSmooth(true);
}

/**Loads all textures*/
void GameView_Screen::load_textures() {
    for (int i=0; i<8; i++) {load_texture(i);}
}

/**Makes single tab shape*/
sf::RectangleShape GameView_Screen::make_tab_shape() {
    sf::RectangleShape tab_shape(sf::Vector2f(tab_size, tab_size));
    tab_shape.setFillColor(sf::Color(235, 235, 235));
    tab_shape.setOutlineThickness(1);
    tab_shape.setOutlineColor(sf::Color(100, 100, 100));
    return tab_shape;
}

/**Create all of the shapes*/
void GameView_Screen::init() {

    int board_width = logic->get_board_width();
    int board_height = logic->get_board_height();

    load_textures();

    sf::RectangleShape * blocks;
    sf::RectangleShape * paths;
    sf::RectangleShape * tabs;

    blocks = new sf::RectangleShape[board_width * board_height]();
    tabs = new sf::RectangleShape[4 * board_width * board_height]();
    paths = new sf::RectangleShape[2]();

    animation_ms = new float * [board_width];
    animation_dir = new char * [board_width];

    for (int x=0; x<board_width; x++) {
        animation_ms[x] = new float[board_height];
        animation_dir[x] = new char[board_height];

        for (int y=0; y<board_height; y++) {
            animation_ms[x][y] = -1;
            if (logic->block_exists(x, y)) {
                animation_ms[x][y] = 0;
                animation_dir[x][y] = DEFAULT_DIR;

                blocks[(y*board_width)+x] = make_block_shape(logic->get_block(x, y)->get_id());
                tabs[4 * ((y * board_width) + x)] = make_tab_shape();
                tabs[4 * ((y * board_width) + x) + 1] = make_tab_shape();
                tabs[4 * ((y * board_width) + x) + 2] = make_tab_shape();
                tabs[4 * ((y * board_width) + x) + 3] = make_tab_shape();
            }
        }
    }

    paths[0] = make_alpha_rectangle_shape(block_size*0.98, App->getSize().y, 255, 255, 255, 120);
    paths[1] = make_alpha_rectangle_shape(App->getSize().x, block_size*0.98, 255, 255, 255, 120);

    this->shadow_shape = make_alpha_rectangle_shape(block_size*0.98, block_size*0.98, 0, 0, 0, 60);
    this->restriction_shape = make_alpha_rectangle_shape(block_size*0.98, block_size*0.98, 255, 0, 0, 180);
    this->path_shapes = paths;

    this->block_shapes = blocks;
    this->tab_shapes = tabs;
}


int GameView_Screen::BoardToPixel(int board_axis_index, int board_axis_length, int screen_axis_length, bool y_axis) {
    int current_window_center = screen_axis_length/2;
    if (y_axis) {current_window_center += block_size/2;}
    else {current_window_center -= block_size/2;}
    int board_center = board_axis_length/2;
    int starting_edge = current_window_center - board_center*block_size;
    return starting_edge + board_axis_index*block_size;
    //return current_window_center + (board_axis_index-board_center)*block_size;
}

//TODO patrick: fix these conversions for resizing etc.
/**Convert board x coordinate to drawing x coordinate*/
int GameView_Screen::BoardXToXPixel(int x) {
    return BoardToPixel(x, logic->get_board_width(), App->getSize().x, false);
}

/**Convert board y coordinate to drawing y coordinate*/
int GameView_Screen::BoardYToYPixel(int y) {
    return App->getSize().y - BoardToPixel(y, logic->get_board_height(), App->getSize().y, true);
}

int GameView_Screen::PixelToBoard(int pixel_index, int board_axis_length, int screen_axis_length) {
    int current_window_center = screen_axis_length/2 - block_size/2;
    int board_center = board_axis_length/2;
    int starting_edge = current_window_center - board_center*block_size;
    return (pixel_index-starting_edge)/block_size;
}

/**Convert pixel x coordinate to board x coordinate*/
int GameView_Screen::XPixelToBoardX(int x_pixel) {
    return PixelToBoard(x_pixel, logic->get_board_width(), App->getSize().x);
}

/**Convert pixel y coordinate to board y coordinate*/
int GameView_Screen::YPixelToBoardY(int y_pixel) {
    return PixelToBoard((App->getSize().y - y_pixel), logic->get_board_height(), App->getSize().y);
}

/**Checks if mouse has clicked on a block*/
void GameView_Screen::check_mouse_input() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!clicked) {
            mouse_x_start = sf::Mouse::getPosition(*App).x;
            mouse_y_start = sf::Mouse::getPosition(*App).y;
            logic->set_selected_position(XPixelToBoardX(mouse_x_start), YPixelToBoardY(mouse_y_start));
            clicked = true;
        } else {
            int dx = mouse_x_start - sf::Mouse::getPosition(*App).x;
            int dy = mouse_y_start - sf::Mouse::getPosition(*App).y;

            if (abs(dx) > deadzone || abs(dy) > deadzone) {
                if (abs(dx) > abs(dy)) {
                    if (dx>0) {dir = L_DIR;}
                    else {dir = R_DIR;}
                } else {
                    if (dy>0) {dir = U_DIR;}
                    else {dir = D_DIR;}
                }
            } else {dir = DEFAULT_DIR;}
        }
    } else {
        if (clicked) {
            clicked = false;
            int sel_x = logic->get_selected_x();
            int sel_y = logic->get_selected_y();
            if (dir != DEFAULT_DIR && logic->selected_block_exists() && !logic->selected_block_is_move_restricted()) {
                if (logic->try_move_selected(dir)) {
                    animation_ms[sel_x][sel_y] = 1;
                    animation_dir[sel_x][sel_y] = dir;
                }
            } else if (logic->tap_selected()) {
                // Changes BlockRotating texture on tap
                int i = sel_y * logic->get_board_width() + sel_x;
                block_shapes[i].setTexture(&texture[(logic->get_block(sel_x, sel_y)->get_id() % 30) + 4]);
            }
            dir = DEFAULT_DIR;
            logic->set_selected_position(-1, -1);
        }
    }
}

/**Draws selected block and shadow under it*/
void GameView_Screen::draw_selected_block() {
    if (logic->selected_block_exists() && !logic->selected_block_is_move_restricted()) {
        int index = (logic->get_selected_y() * logic->get_board_width()) + logic->get_selected_x();
        block_shapes[index].setSize(sf::Vector2f(block_size*1.1, block_size*1.1));
        block_shapes[index].setFillColor(sf::Color::White);
        block_shapes[index].move(-0.05*block_size, -0.05*block_size);
        App->draw(block_shapes[index]);
    }
}

/**Highlights path that the block will take*/
void GameView_Screen::draw_path_highlighting() {
    if (logic->selected_block_exists() && !logic->selected_block_is_move_restricted()) {

        int path_shape_i = 0;
        int x_pos = BoardXToXPixel(logic->get_selected_x());
        int y_pos = BoardYToYPixel(logic->get_selected_y());

        switch (dir) {
            case U_DIR: y_pos -= default_window_height;
            case D_DIR: break;
            case L_DIR: x_pos -= default_window_width;
            case R_DIR: path_shape_i++;
                break;
            case DEFAULT_DIR:
                return;
            default:break;
        }
        path_shapes[path_shape_i].setPosition(sf::Vector2f(x_pos, y_pos));
        App->draw(path_shapes[path_shape_i]);
    }
}

/**Draws shadows under blocks*/
void GameView_Screen::draw_shadows() {
    int width = logic->get_board_width();
    int height = logic->get_board_height();
    for (int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {
            if (logic->block_exists(x, y)) {
                shadow_shape.setPosition(BoardXToXPixel(x) + 10, BoardYToYPixel(y) + 10);
                App->draw(shadow_shape);
            }
        }
    }
}

/**Draws blocks*/
void GameView_Screen::draw_blocks(int deltaTime) {
    int width = logic->get_board_width();
    int height = logic->get_board_height();
    int i;
    for (int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {
            i = (y*width)+x;
            if (logic->block_exists(x, y) && (animation_ms[x][y] == 0)) {
                block_shapes[i].setSize(sf::Vector2f(block_size*0.98, block_size*0.98));
                block_shapes[i].setFillColor(sf::Color(235, 235, 235));
                block_shapes[i].setPosition(BoardXToXPixel(x), BoardYToYPixel(y));
                App->draw(block_shapes[i]);

                if (logic->block_is_move_restricted(x, y)) {
                    //TODO: fix this extremely sloppy text hack
                    sf::Text text1;
                    sf::Font font;
                    font.loadFromFile(REGULARFONT_FILEPATH);
                    text1.setFont(font);
                    text1.setPosition(BoardXToXPixel(x) + block_size/2.5, BoardYToYPixel(y) + block_size/3);
                    text1.setString(std::to_string(logic->get_block(x, y)->get_move_restriction() - logic->get_blocks_removed_ct()));
                    text1.setCharacterSize(20);

                    restriction_shape.setPosition(BoardXToXPixel(x), BoardYToYPixel(y)) ;
                    App->draw(restriction_shape);
                    App->draw(text1);
                }
            } else if (animation_ms[x][y] == 1) {
                block_shapes[i].setOrigin(block_size / 2, block_size / 2);
                block_shapes[i].move(block_size / 2, block_size / 2);
                block_shapes[i].setSize(sf::Vector2f(block_size*0.98, block_size*0.98));
                block_shapes[i].setFillColor(sf::Color(235, 235, 235));
                animation_ms[x][y] += deltaTime;
                App->draw(block_shapes[i]);
            } else if ((animation_ms[x][y] < 2000000) && (animation_ms[x][y] > 1)) {
                animation_ms[x][y] += deltaTime;
                if (animation_dir[x][y] == D_DIR) { block_shapes[i].move(0, 0.001 * deltaTime); }
                else if (animation_dir[x][y] == U_DIR) { block_shapes[i].move(0, -0.001 * deltaTime); }
                else if (animation_dir[x][y] == L_DIR) { block_shapes[i].move(-0.001 * deltaTime, 0); }
                else if (animation_dir[x][y] == R_DIR) { block_shapes[i].move(0.001 * deltaTime, 0); }
                block_shapes[i].rotate(0.0005 * deltaTime);
                App->draw(block_shapes[i]);
            }
        }
    }
}

/**Draws an individual single tab*/
void GameView_Screen::draw_tab(int tab_index, int x, int y) {
    int pixel_x = BoardXToXPixel(x) + block_size/2 - tab_size/2;
    int pixel_y = BoardYToYPixel(y) + block_size/2 - tab_size/2;

    int offset = block_size/2 + tab_size/2;
    switch (tab_index%4) {
        case 0://UP
            pixel_y -= offset+1;
            break;
        case 1://RIGHT
            pixel_x += offset;
            break;
        case 2://DOWN
            pixel_y += offset;
            break;
        case 3://LEFT
            pixel_x -= offset+1;
            break;
        default:break;
    }

    tab_shapes[tab_index].setFillColor(sf::Color(235, 235, 235));
    tab_shapes[tab_index].setPosition(pixel_x, pixel_y);
    App->draw(tab_shapes[tab_index]);
}

/**Draws all tabs*/
void GameView_Screen::draw_tabs() {
    int width = logic->get_board_width();
    int height = logic->get_board_height();
    int tab_index;
    for (int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {
            if (logic->block_exists(x, y)) {
                tab_index = 4*((y*width)+x);
                Block * block = logic->get_block(x, y);
                if (block->get_tab(U_DIR)) {draw_tab(tab_index, x, y);}
                if (block->get_tab(R_DIR)) {draw_tab(tab_index+1, x, y);}
                if (block->get_tab(D_DIR)) {draw_tab(tab_index+2, x, y);}
                if (block->get_tab(L_DIR)) {draw_tab(tab_index+3, x, y);}
            }
        }
    }
}

/**Draw all blocks, shadows, movements, and selections*/
void GameView_Screen::draw(int deltaTime) {
    App->clear(sf::Color(40,140,240));
    draw_shadows();
    draw_blocks(deltaTime);
    draw_tabs();
    draw_path_highlighting();
    draw_selected_block();
    App->display();
}

/**Checks keyboard input, sends input to logic for handling*/
void GameView_Screen::check_keyboard_input() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {logic->try_move_selected(U_DIR);}
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {logic->try_move_selected(D_DIR);}
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {logic->try_move_selected(L_DIR);}
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {logic->try_move_selected(R_DIR);}
}

int *GameView_Screen::run(sf::RenderWindow &window, int curr_level) {
    int *re = new int[2];
    re[0] = 1;
    re[1] = curr_level;

    sf::Clock draw_clock;
    this->App = &window;

    //BoardState * board = new BoardState(levels[re[1]-1]);
    BoardGenerator * generator = new BoardGenerator();
    BoardState * board = generator->make_board(9, 9);

    logic->set_BoardState(*board);
    init();
    int time_since_completion = 0;

    sf:: Event Event;
    while(running) {
        while (window.pollEvent(Event)) {
            if(Event.type == sf::Event::Closed) {
                running = false;
                re[0] = -1;
                return re;
            }
            if(Event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    re[0] = 1;
                    return re;
            }
        }

        //TODO: move this into GameView
        if (logic->get_is_clear()) {
            time_since_completion += draw_clock.getElapsedTime().asMicroseconds();
            if (time_since_completion > 750000) {
                re[1]++;
                BoardState * board = new BoardState(levels[re[1]-1]);
                logic->set_BoardState(*board);
                init();
                time_since_completion = 0;
            }
        }

        check_mouse_input();
        check_keyboard_input();
        draw(draw_clock.restart().asMicroseconds());
    }
    return re;
}
