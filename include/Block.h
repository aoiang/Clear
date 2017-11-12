//
// Created by Yiyang Zhao on 16/10/2017
// Additional work by Ivan Echevarria
//

#ifndef CLEAR_BLOCK_H
#define CLEAR_BLOCK_H
/**
 * The parameters of the basic block.
 */

class Block {
    protected:
        float row;
        float col;
        int id;
        bool can_combine;

    public:
        int get_id();
        void set_id(int id);
        void init(int id);
        void setPosition(float row, float col);
        float get_row();
        float get_col();
//        float get_length();
//        float get_width();
        void move(int row, int col);
        virtual bool get_combine();
        virtual void set_combine(bool can_combine);
};

#endif //CLEAR_BLOCK_H
