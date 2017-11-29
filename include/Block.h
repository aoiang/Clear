#ifndef CLEAR_BLOCK_H
#define CLEAR_BLOCK_H

/**The parameters of the basic block.*/
class Block {
    protected:
        int x;
        int y;
        int id;
        bool can_combine;
        void set_id(int id);
        void set_combine(bool can_combine);
        void set_position(int x, int y);
        void move(int x, int y);
        bool has_tab;
    public:
        int get_id();
        int get_x();
        int get_y();
        bool get_combine();
        virtual bool type_allows_movement(char direction);
};

#endif //CLEAR_BLOCK_H
