
#pragma once
#include "Blocks.hpp"


class SBlock:public Block{
    public:
        SBlock();

        const std::array<point,4>& getCells() const override;
        void rotateCW() override;
        void rotateCCW() override;
};