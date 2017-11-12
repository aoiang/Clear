//
// Created by Yiyang Zhao on 16/10/2017
// Additional work by Ivan Echevarria
//

#ifndef CLEAR_BLOCK_H
#define CLEAR_BLOCK_H
#include <string>

/**The parameters of the basic block.*/
class Block {
    protected:
        float x;
        float y;
        int id;
        bool can_combine;

    public:
        int get_id();
        void set_id(int id);
        void init(int id);
        void setPosition(float x, float y);
        float get_x();
        float get_y();
//        float get_length();
//        float get_width();
        void move(int x, int y);
        virtual bool get_combine();
        virtual void set_combine(bool can_combine);
        virtual bool type_allows_movement(std::string direction);
};

#endif //CLEAR_BLOCK_H
