
#pragma once
#include "Blocks.hpp"

class ZBlock: public Block{
    public:
        ZBlock();

        const std::array<point,4>& getCells() const override;
        void rotateCW() override;
        void rotateCCW() override;

};