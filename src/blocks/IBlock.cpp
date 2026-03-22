
#include "IBlock.hpp"

IBlock::IBlock():Block(ShapeType::I){
        positions = {{
        {{ {0,1}, {1,1}, {2,1}, {3,1} }}, 
        {{ {2,0}, {2,1}, {2,2}, {2,3} }},  
        {{ {0,2}, {1,2}, {2,2}, {3,2} }}, 
        {{ {1,0}, {1,1}, {1,2}, {1,3} }}   
    }};
}

const std::array<point,4>& IBlock::getCells() const{
    return this->positions[this->rotation];
}

void IBlock::rotateCW(){
    this->rotation=(this->rotation+1)%4;
}

void IBlock::rotateCCW(){
    this->rotation=(this->rotation+3)%4;
}

