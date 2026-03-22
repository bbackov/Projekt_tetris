#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include "../util/common.hpp"

//forward deklaracija
class Block;

class Board{
    public:
        //dimenzije
        static constexpr int EMPTY = 0;
        static constexpr int width=10;
        static constexpr int play_height=20;
        static constexpr int hidden_height=4;
        static constexpr int total_height=24;

        Board();//konstrktor koji je u cpp-u
        
        // upiti za plocu
        bool isInside(point p) const;
        bool isEmpty(point p) const;
        int getCell(point p) const;
        void setCell(point p, int value);

        //stavljanje elementa i zakljucavanje
        bool canPlace(const Block& block, point shift={0,0}) const;
        void lock(const Block& block);
        
        //brisanje
        int clearFullLines();
        void reset();


    private:

        std::array<int, width * total_height> grid{};//ploca
        //pomocne metode
        int idx(point p) const { return p.second*width + p.first; }
        bool isRowFull(int y) const;
        void clearRow(int y);
        void dropRowsAbove(int y);

};


#endif