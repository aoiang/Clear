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
        float x;
        float y;
        int id;
        bool can_combine;

    public:
        float get_length();
        float get_width();
        float getX();
        float getY();
        int get_id();

        void setX(float x);
        void setY(float y);
        void setPosition(float x, float y);
        void set_id(int id);
        void init(int id);
        void move(float x, float y);
        virtual bool get_combine();
        virtual void set_combine(bool can_combine);
};

#endif //CLEAR_BLOCK_H
