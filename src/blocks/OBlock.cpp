
#include "OBlock.hpp"


OBlock::OBlock():Block(ShapeType::O){

    positions={{
        {{{0,0},{0,1},{1,0},{1,1}}},
        {{{0,0},{0,1},{1,0},{1,1}}},
        {{{0,0},{0,1},{1,0},{1,1}}},
        {{{0,0},{0,1},{1,0},{1,1}}}
        }};
}

const std::array<point,4>& OBlock::getCells() const{
    return this->positions[this->rotation];
}

void OBlock::rotateCW(){
    this->rotation=(this->rotation+1)%4;
}

void OBlock::rotateCCW(){
    this->rotation=(this->rotation+3)%4;
}