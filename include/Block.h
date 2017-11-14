#ifndef CLEAR_BLOCK_H
#define CLEAR_BLOCK_H

/**The parameters of the basic block.*/
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
    public:
        int get_id();
        int get_x();
        int get_y();
        int dir_to_index(char dir);
        void set_tab(char dir, bool tab);
        bool get_tab(char dir);
        bool get_tab(int dir);
        bool get_combine();
        virtual bool type_allows_movement(char direction);
};

#endif //CLEAR_BLOCK_H
