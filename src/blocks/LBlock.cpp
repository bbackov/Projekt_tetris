
#include "LBlock.hpp"

LBlock::LBlock():Block(ShapeType::L){
        positions = {{
        {{{2,0},{0,1},{1,1},{2,1}}},
        {{{1,0},{1,1},{1,2},{2,2}}},
        {{{0,1},{1,1},{2,1},{0,2}}},
        {{{0,0},{1,0},{1,1},{1,2}}}
    }};
}

const std::array<point,4>& LBlock::getCells() const{
    return this->positions[this->rotation];
}

void LBlock::rotateCW(){
    this->rotation=(this->rotation+1)%4;
}

void LBlock::rotateCCW(){
    this->rotation=(this->rotation+3)%4;
}

