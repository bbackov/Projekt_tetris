
#pragma once
#include "Blocks.hpp"

class TBlock: public Block{
    public:
        TBlock();

        const std::array<point,4>& getCells() const override;
        void rotateCW() override;
        void rotateCCW() override;

};