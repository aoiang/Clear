//
// Created by Yiyang Zhao on 22/10/2017.
// Additional work by Ivan & Yosef
//

#include "GameState.h"


void GameState::block_init() {
    for(int i=0; i<5; i++){
        normal_block[i].init(i);
        normal_block[i].setPosition(100+80*i, 200);
    }
}

void GameState::init() {
    block_init();
}

Normal_Block* GameState::get_Normal_Block() {
    return normal_block;
}

void GameState::set_Normal_Block(Normal_Block *normal_block) {
    for(int i =0; i<5; i++){
        this->normal_block[i] = normal_block[i];
    }

}

bool GameState::collision_detector(Normal_Block current_block, std::string direction) {
    if(direction == "up"){
        for(int i=0; i < 5; i++){
            if(normal_block[i].getX() == current_block.getX()){
                if(normal_block[i].getY() < current_block.getY()){
                    if(normal_block[i].getX() > 0 && normal_block[i].getX() < 800 && normal_block[i].getY() > 0 && normal_block[i].getY() < 600){
                        return true;
                    }
                }
            }
        }
    }
    if(direction == "down"){
        for(int i=0; i < 5; i++){
            if(normal_block[i].getX() == current_block.getX()){
                if(normal_block[i].getY()> current_block.getY()){
                    if(normal_block[i].getX() > 0 && normal_block[i].getX() < 800 && normal_block[i].getY() > 0 && normal_block[i].getY() < 600){
                        return true;
                    }
                }
            }
        }
    }
    if(direction == "left"){
        for(int i=0; i < 5; i++){
            if(normal_block[i].getY() == current_block.getY()){
                if(normal_block[i].getX() < current_block.getX()){
                    if(normal_block[i].getX() > 0 && normal_block[i].getX() < 800 && normal_block[i].getY() > 0 && normal_block[i].getY() < 600){
                        return true;
                    }

                }
            }
        }
    }
    if(direction == "right"){
        for(int i=0; i < 5; i++){
            if(normal_block[i].getY() == current_block.getY()){
                if(normal_block[i].getX() > current_block.getX()){
                    if(normal_block[i].getX() > 0 && normal_block[i].getX() < 800 && normal_block[i].getY() > 0 && normal_block[i].getY() < 600){
                        return true;
                    }
                }
            }
        }
    }
    return false;

}


void GameState::try_move(std::string dir) {
    for(int i = 0; i < 5; i++) {
        if (normal_block[i].get_selected()) {
            if(dir == "up") {
                if(normal_block[i].get_direction() == "up" && !collision_detector(normal_block[i], normal_block[i].get_direction())){
                    normal_block[i].move(0.0,  -1 * 30);
                }
                if(!normal_block[i].get_has_direction() && !collision_detector(normal_block[i], "up")){
                    normal_block[i].move(0.0,  -1 * 30);
                }
            }
            if(dir == "down"){
                if(normal_block[i].get_direction() == "down" && !collision_detector(normal_block[i], normal_block[i].get_direction())){
                    normal_block[i].move(0.0,  1 * 30);
                }
                if(!normal_block[i].get_has_direction() && !collision_detector(normal_block[i], "down")){
                    normal_block[i].move(0.0,  1 * 30);
                }
            }
            if(dir == "left"){
                if(normal_block[i].get_direction() == "left" && !collision_detector(normal_block[i], normal_block[i].get_direction())){
                    normal_block[i].move(-30,  0);
                }
                if(!normal_block[i].get_has_direction() && !collision_detector(normal_block[i], "left")){
                    normal_block[i].move(-30,  0);
                }
            }
            if(dir == "right"){
                if(normal_block[i].get_direction() == "right" && !collision_detector(normal_block[i], normal_block[i].get_direction())){
                    normal_block[i].move(30.0,  0);
                }
                if(!normal_block[i].get_has_direction() && !collision_detector(normal_block[i], "right")){
                    normal_block[i].move(30.0,  0);
                }
            }
        }
    }
}
