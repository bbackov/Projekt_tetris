#pragma once

#include "../board/Board.hpp"
#include "../util/Timer.hpp"
#include "../util/common.hpp" 
#include <memory>
#include <queue>
#include <optional>
#include <functional>
#include <string>

class Block; 
 

class Game{

    public:
        Game();
        ~Game();
        void spawn();
        void tick(int deltaMS);


        void setMoveLeft(bool v);
        void setMoveRight(bool v);
        void setRotateCW(bool v);
        void setRotateCCW(bool v);
        void setHardDrop(bool v);
        void setSoftDrop(bool v);
        void setHoldUsed(bool v);
        void setPauseUsed(bool v);
        State getState();
        const Board& getBoard() const;
        const Block* getCurrent() const;
        const Block* getGhost() const;
        std::optional<ShapeType> getHold() const;
        const int getScore() const;
        const int getLevel() const;
        

        


    private:
        Board board;
        std::unique_ptr<Block> current;
        std::unique_ptr<Block> ghost;
        std::queue<ShapeType> next;
        std::optional<ShapeType> hold_block;
        std::optional<ShapeType> hold_spawn_block;
        bool spawn_from_hold=false;
        bool hold_used_this_turn=false;
        Timer gravity_timer;
        Timer soft_drop_timer;
        Timer das_timer;
        Timer arr_timer;
        Timer lock_timer;
        int gravityMS=550;//placholder
        int soft_gravityMS=gravityMS / 10;//placholder
        int lockMS=500;//placholder
        int dasMS=450;//placholder
        int arrMS=150;//placholder
        bool lock_timer_engadged=false;
        int score=0;
        int level=1;
        int sum_lines=0;
        State play_state=State::Playing;

        //input varijable
        bool rotateCW=false;
        bool rotateCCW=false;
        bool move_left=false;
        bool move_right=false;
        bool hard_drop=false;
        bool hold_used=false;
        bool soft_drop=false;
        bool pause_used=false;

        void addBlocks();
        void calculateScore(int lines_cleard=0);
        bool tryRotation(bool rotationCW);
        void hardDrop();
        void hold();
        void pause();
        void dropGhost();




};