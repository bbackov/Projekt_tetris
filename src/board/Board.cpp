#include "Board.hpp"
#include "../blocks/Blocks.hpp"
Board::Board()=default;

bool Board::isInside(point p) const{

    if(p.first<0 || p.first>=this->width || p.second<0 || p.second>=this->total_height){
        return false;
    }
    return true;
}

bool Board::isEmpty(point p) const{

    if(this->isInside(p) && this->grid[this->idx(p)]==EMPTY){
        return true;
    }
    return false;
}


int Board::getCell(point p) const {

    if(!this->isInside(p)){
        return -1;
    }
    return this->grid[idx(p)];
}

void Board::setCell(point p, int value){

    if(this->isInside(p)){
        this->grid[idx(p)]=value;
    }
    
}

bool Board::canPlace(const Block& block, point shift) const{

    std::array<point,4> absolute=block.getAbsoluteCells();
    for(point p:absolute){
        if(!this->isEmpty(p+shift)){
            return false;
        }
    }
    return true;

}

void Board::lock(const Block& block){

    const auto absolute=block.getAbsoluteCells();
    const int value=static_cast<int>(block.getShape());
    for(const auto& p:absolute){
           setCell(p,value);
    }
    

}

bool Board::isRowFull(int y) const{

    for(int i=0;i<this->width;i++){
        if(grid[idx({i,y})]==EMPTY){
            return false;
        }
    }

    return true;
}

void Board::clearRow(int y){

    for(int i=0;i<this->width;i++){
        grid[idx({i,y})]=EMPTY;
    }
}

void Board::dropRowsAbove(int y){

    for(int j=y; j>=hidden_height;j--){
        for(int i=0;i<this->width;i++){
            if(j==hidden_height){
                grid[idx({i,j})]=EMPTY;
            }
            else{
                grid[idx({i,j})]=grid[idx({i,j-1})];
            }
        }
    }
}

void Board::reset(){
    grid.fill(EMPTY);
}

int Board::clearFullLines(){

    int cleared=0;

    for(int y=total_height-1;y>=hidden_height;--y){
        if(isRowFull(y)){
            clearRow(y);
            dropRowsAbove(y);
            cleared++;
            y++;
        }
    }
    return cleared;
}