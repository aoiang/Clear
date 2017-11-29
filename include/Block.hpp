#ifndef CLEAR_BLOCK_HPP
#define CLEAR_BLOCK_HPP

class Block {
    protected:
        int x;
        int y;
        int id;
        bool can_combine;
        bool tabs[4];
        void set_id(int id);
        void set_combine(bool can_combine);
        void set_position(int x, int y);

        void move(int x, int y);
        bool has_tab;

    public:
        int get_id();
        int get_x();
        int get_y();
        int dir_to_index(char dir);
        void set_tab(char dir, bool tab);
        bool get_tab(char dir);
        void init_tabs();
        bool get_combine();
        virtual bool type_allows_movement(char direction);
};

#endif //CLEAR_BLOCK_HPP
