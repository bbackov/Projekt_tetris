

#include "TBlock.hpp"

TBlock::TBlock():Block(ShapeType::T){

    positions={{
        {{{1,0},{0,1},{1,1},{2,1}}},
        {{{1,0},{1,1},{2,1},{1,2}}},
        {{{0,1},{1,1},{2,1},{1,2}}},
        {{{1,0},{0,1},{1,1},{1,2}}}
    }};
}

const std::array<point,4>& TBlock::getCells() const{
    return this->positions[this->rotation];
}

void TBlock::rotateCW(){
    this->rotation=(this->rotation+1)%4;
}

void TBlock::rotateCCW(){
    this->rotation=(this->rotation+3)%4;
}