#pragma once
#include "Blocks.hpp"

class OBlock:public Block{

    public:
        OBlock();
        const std::array<point,4>& getCells() const override;
        void rotateCW() override;
        void rotateCCW() override;
};