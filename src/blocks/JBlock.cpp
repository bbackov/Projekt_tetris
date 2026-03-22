
#include "JBlock.hpp"

JBlock::JBlock():Block(ShapeType::J){
        positions = {{
        {{{0,0}, {0,1}, {1,1}, {2,1}}},
        {{{1,0}, {1,1}, {1,2}, {2,0}}},
        {{{0,1}, {1,1}, {2,1}, {2,2}}},
        {{{1,0}, {1,1}, {1,2}, {0,2}}}
    }};
}

const std::array<point,4>& JBlock::getCells() const{
    return this->positions[this->rotation];
}

void JBlock::rotateCW(){
    this->rotation=(this->rotation+1)%4;
}

void JBlock::rotateCCW(){
    this->rotation=(this->rotation+3)%4;
}

