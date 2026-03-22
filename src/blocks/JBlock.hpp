
#pragma once
#include "Blocks.hpp"

class JBlock:public Block{

    public:
        JBlock();

        const std::array<point,4>& getCells() const override;
        void rotateCW() override;
        void rotateCCW() override;

};