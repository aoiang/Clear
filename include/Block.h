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
    float length=80;
    float width=80;
    float speed=30;
    bool is_selected=false;
    int id;
    float x;
    float y;




public:

    float get_length();
    float get_width();
    float get_speed();
    int get_id();
    bool get_selected();

    void set_length(float length);
    void set_width(float width);
    void set_speed(float speed);
    void set_id(int id);
    void init(int id);
    void set_selected(bool is_selected);
    void setX(float x);
    void setY(float y);
    void setPosition(float x, float y);
    float getX();
    float getY();
    void move(float x, float y);




};


#endif //CLEAR_BLOCK_H
