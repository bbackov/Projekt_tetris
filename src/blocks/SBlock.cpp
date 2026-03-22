
#include "SBlock.hpp"


SBlock::SBlock():Block(ShapeType::S){

    positions={{
        {{{1,0},{2,0},{0,1},{1,1}}},  
        {{{0,0},{0,1},{1,1},{1,2}}}, 
        {{{1,0},{2,0},{0,1},{1,1}}},  
        {{{0,0},{0,1},{1,1},{1,2}}}   
    }};
}

const std::array<point,4>& SBlock::getCells()const{
    return this->positions[this->rotation];
}

void SBlock::rotateCW(){
    this->rotation=(this->rotation+1)%4;
}

void SBlock::rotateCCW(){
    this->rotation=(this->rotation+3)%4;
}