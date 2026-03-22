#pragma once
#include "Blocks.hpp"

class LBlock:public Block{

    public:
        LBlock();

        const std::array<point,4>& getCells() const override;
        void rotateCW() override;
        void rotateCCW() override;

};