#ifndef CLEAR_BLOCK_HPP
#define CLEAR_BLOCK_HPP

#include "Definitions.hpp"
#include <iostream>
#include <vector>

static char directions[5] = "urdl";

class Block {
    private:
        int x;
        int y;
        int id;
        int group;
        char bool_to_char(bool boolean);
        bool string_to_bool(std::string text);
    protected:
        int base_id = 0;
        int simple_id = 0;
        int rotation = 0;
        bool can_combine;
        bool tabs[4];
        int move_restriction = 0;
        void set_id();
        void set_combine(bool can_combine);
        void set_position(int x, int y);
        void set_group(int group);
        void set_move_restriction(int moves);
    public:
        int get_group();
        static Block * import_block(std::string identity, int x, int y);
        bool rotation_changes_id = false;
        int get_id();
        int get_simple_id();
        int get_x();
        bool is_move_restricted();
        void increase_move_restriction();
        void decrease_move_restriction();
        int get_y();
        int dir_to_index(char);
        void set_tab(char, bool);
        bool get_tab(char);
        int get_tab_count();
        void init_tabs();
        bool get_combine();
        virtual bool type_allows_movement(char);
        int get_move_restriction();
        void rotate();
        int get_rotation();
        void set_rotation(int rotation);
        char get_direction();
        void basic_init(int x, int y);
        std::string get_identity();
        static std::vector<std::string> split_string(const std::string &text, char delimiter);
        void import_init(std::string identity);
};

#endif //CLEAR_BLOCK_HPP
