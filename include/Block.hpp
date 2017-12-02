#ifndef CLEAR_BLOCK_HPP
#define CLEAR_BLOCK_HPP

#include "Definitions.hpp"

static char directions[5] = "urdl";

class Block {
    private:
        const static int base_id = 0;
        int x;
        int y;
        int id;
    protected:
        int rotation = 0;
        bool can_combine;
        bool tabs[4];
        int move_restriction = 0;
        void set_id();
        void set_combine(bool can_combine);
        void set_position(int x, int y);
        void rotate();
        void reset_rotation();
    public:
        bool rotation_changes_id = false;
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
        int get_move_restriction();
        int get_rotation();
        char get_direction();
        void basic_init(int x, int y);
        unsigned long get_identity();
};

#endif //CLEAR_BLOCK_HPP
