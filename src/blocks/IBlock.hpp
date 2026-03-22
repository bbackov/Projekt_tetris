
#pragma once
#include "Blocks.hpp"

class IBlock:public Block{

    public:
        IBlock();

        const std::array<point,4>& getCells() const override;
        void rotateCW() override;
        void rotateCCW() override;

};