//
// Created by Yiyang Zhao on 16/10/2017.
//

#ifndef CLEAR_BLOCK_H
#define CLEAR_BLOCK_H
#include <SFML/Graphics.hpp>
/**
 * The parameters of the basic block.
 */

class Block {
    protected:
        float x;
        float y;
        float length=80;
        float width=80;
        float speed=30;
        bool is_selected=false;
        int id;
        bool can_combine;





    public:

        float get_length();
        float get_width();
        float get_speed();
        float getX();
        float getY();
        int get_id();
        bool get_selected();

        void setX(float x);
        void setY(float y);
        void setPosition(float x, float y);
        void set_length(float length);
        void set_width(float width);
        void set_speed(float speed);
        void set_id(int id);
        void init(int id);
        void set_selected(bool is_selected);
        void move(float x, float y);
        virtual bool get_combine();
        virtual void set_combine(bool can_combine);


};


#endif //CLEAR_BLOCK_H
