
#include "ZBlock.hpp"

ZBlock::ZBlock():Block(ShapeType::Z){
    
    positions={{
        {{{0,0},{1,0},{1,1},{2,1}}}, 
        {{{2,0},{1,1},{2,1},{1,2}}},  
        {{{0,0},{1,0},{1,1},{2,1}}},  
        {{{2,0},{1,1},{2,1},{1,2}}}   
    }};
}

const std::array<point,4>& ZBlock::getCells() const{
    return this->positions[this->rotation];
}

void ZBlock::rotateCW(){
    this->rotation=(this->rotation+1)%4;
}

void ZBlock::rotateCCW(){
    this->rotation=(this->rotation+3)%4;
}
