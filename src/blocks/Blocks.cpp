

#include "Blocks.hpp"

Block::Block(ShapeType type) : shape(type), rotation(0), root_pos{0,0} {}

std::array<point,4> Block::getAbsoluteCells() const{
    const auto& relative = this->getCells();
    std::array<point,4> absolute;

    for(int i=0;i<4;i++){
        absolute[i].first=relative[i].first+this->root_pos.first;
        absolute[i].second=relative[i].second+this->root_pos.second;
    }

    return absolute;
}