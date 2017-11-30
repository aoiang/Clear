#ifndef CLEAR_BLOCK_HPP
#define CLEAR_BLOCK_HPP

#include "Definitions.hpp"

static char directions[5] = "urdl";

class Block {
    protected:
        int rotation = 0;
        int x;
        int y;
        int id;
        bool can_combine;
        bool tabs[4];
        int move_restriction = 0;
        void set_id(int id);
        void set_combine(bool can_combine);
        void set_position(int x, int y);
        void rotate_clockwise();
        void reset_rotation();
    public:
        int get_id();
        int get_x();
        int get_y();
        int dir_to_index(char);
        void set_tab(char, bool);
        bool get_tab(char);
        void init_tabs();
        bool get_combine();
        virtual bool type_allows_movement(char);
        bool is_move_restricted(int);
        void set_move_restriction(int);
        int get_rotation();
        char get_direction();
};

#endif //CLEAR_BLOCK_HPP
