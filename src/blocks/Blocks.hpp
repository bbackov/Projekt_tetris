#ifndef BLOCKS_HPP
#define BLOCKS_HPP

#include "../util/common.hpp"
#include <vector>
#include <array>



class Block{

    public:
        //destruktor
        virtual ~Block() = default;
        //konstruktor
        Block(ShapeType type);

        //rotacija dohvacanje točka i pozicija
        virtual const std::array<point, 4>& getCells() const = 0;
        virtual void rotateCW()=0;
        virtual void rotateCCW()=0;
        int getRotation() const {return rotation;}
        ShapeType getShape() const {return shape;}
        point getRoot() const {return root_pos;}
        void setRoot(point p) { root_pos = p; }
        void setRotation(int rot){rotation=rot;}
        std::array<point,4> getAbsoluteCells() const;

        // pomicanje blokova
        void moveBy(point offset){
            root_pos.first+=offset.first;
            root_pos.second+=offset.second;
        }  
        void moveLeft()  { moveBy({-1, 0});}
        void moveRight() {moveBy({1, 0});}
        void moveDown()  {moveBy({0, 1});}

    protected:
        //deklaracija varijabli
        point root_pos={0,0};
        ShapeType shape;
        std::array<std::array<point,4>,4> positions;
        int rotation=0;

};

#endif