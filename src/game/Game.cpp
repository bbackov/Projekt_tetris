
#include "Game.hpp"
#include "../blocks/Blocks.hpp"
#include <vector>
#include <cmath>
#include "../blocks/Factory.hpp"
#include "../util/SRS.hpp"


Game::Game(){
    srand(static_cast<unsigned>(time(nullptr)));
    addBlocks();

}

void Game::addBlocks(){

    std::vector<ShapeType> blocks = {
        ShapeType::I,
        ShapeType::O,
        ShapeType::T,
        ShapeType::S,
        ShapeType::Z,
        ShapeType::J,
        ShapeType::L
    };

    for(int i=0;i<7;i++){
        int rand_num=rand()%(blocks.size());
        this->next.push(blocks[rand_num]);
        blocks.erase(blocks.begin()+rand_num);
    }
    
}

void Game::spawn(){


    
    if(this->next.size()<=4){
        addBlocks();
    }
    
    if(spawn_from_hold){
        this->current=makeBlock(hold_spawn_block.value());
        if (!current) { play_state=State::Game_over; return; }
        this->current->setRoot({4,0});
        this->ghost=makeBlock(hold_spawn_block.value());
        this->dropGhost();
        spawn_from_hold=false;
    }
    else{
        this->current=makeBlock(this->next.front());
        if (!current) { play_state=State::Game_over; return; }
        this->current->setRoot({4,0});
        this->ghost=makeBlock(this->next.front());
        this->next.pop();
        this->dropGhost();
    }

    
    if(!this->board.canPlace(*current)){
        this->play_state=State::Game_over;
        return;
    }

    this->gravity_timer.reset();
    this->lock_timer.reset();
    this->lock_timer_engadged = false;
    
}

void Game::tick(int deltaMS){

    if(this->pause_used) {
        pause();

        this->move_right=false;
        this->move_left=false;
        this->rotateCW=false;
        this->rotateCCW=false;
        this->hard_drop=false;
        this->pause_used=false;
        this->hold_used=false;
        this->soft_drop=false;

        return;
    }
    
    if(this->move_right){
        if(this->das_timer.elapsedTime() >= this->dasMS){
            if(this->arr_timer.elapsedTime() >= this->arrMS){
                if(this->board.canPlace(*this->current,{1,0})){
                    this->current->moveRight();
                    this->dropGhost();

                    if(!this->board.canPlace(*this->current, {0,1})){
                        lock_timer.reset();
                        lock_timer_engadged = true;
                    }
                    else{
                        lock_timer_engadged = false;
                    }
                }   
                this->arr_timer.reset();
            }
        }
    }

    if(this->move_left){
        if(this->das_timer.elapsedTime() >= this->dasMS){ 
            if(this->arr_timer.elapsedTime() >= this->arrMS){ 
                if(this->board.canPlace(*this->current,{-1,0})){
                    this->current->moveLeft();
                    this->dropGhost();

                    if(!this->board.canPlace(*this->current, {0,1})){
                        lock_timer.reset();
                        lock_timer_engadged = true;
                    }
                    else{
                        lock_timer_engadged = false;
                    }
                }
                this->arr_timer.reset();
            }
        }
    }
 
    if(this->rotateCW){
        this->tryRotation(true);
        this->dropGhost();
    }
    if(this->rotateCCW){
        this->tryRotation(false);
        this->dropGhost();
    }
    if(this->hard_drop) this->hardDrop();
    if(this->hold_used && !this->hold_used_this_turn) this->hold();

    if(this->gravity_timer.elapsedTime() >= this->gravityMS){
        if(!this->board.canPlace(*this->current, {0,1})){
            if(!this->lock_timer_engadged){
                this->lock_timer.reset();
                this->lock_timer_engadged = true;
            }
        }
        else{
            this->current->moveDown();
            this->lock_timer_engadged = false;
        }
        this->gravity_timer.reset();
    }

    
    if(this->soft_drop && this->board.canPlace(*this->current, {0,1})){
        if(this->soft_drop_timer.elapsedTime() >= this->soft_gravityMS){
            this->current->moveDown();
            this->score+=1;
            this->soft_drop_timer.reset();
            this->gravity_timer.reset(); 
        }
    }
    if(this->lock_timer_engadged  && this->lock_timer.elapsedTime()>=this->lockMS){
        this->board.lock(*this->current);
        int lines_cleard=board.clearFullLines();
        this->calculateScore(lines_cleard);
        this->lock_timer_engadged=false;
        this->hold_used_this_turn=false;
        this->spawn();
        return;
    }

    this->move_right=false;
    this->move_left=false;
    this->rotateCW=false;
    this->rotateCCW=false;
    this->hard_drop=false;
    this->pause_used=false;
    this->hold_used=false;
}

bool Game::tryRotation(bool rotationCW){

    int past_rot=this->current->getRotation();
    const auto& table = (current->getShape() == ShapeType::I) ? SRS::I : SRS::JLTSZ;
    
    if(rotationCW){
        this->current->rotateCW();
    }
    else{
        this->current->rotateCCW();
    }
    int current_rot=this->current->getRotation();


    auto it = table.find(point{past_rot, current_rot});
    if (it == table.end()) return false;

    for(auto& offset:it->second){

        if(board.canPlace(*this->current,offset)){
            current->moveBy(offset);

            if(!board.canPlace(*this->current, {0,1})){
                lock_timer.reset();
                lock_timer_engadged = true;
            }
            else{
                lock_timer_engadged = false;
            }

            return true;
        }
    }

    if(rotationCW){
        this->current->rotateCCW();
    }
    else{
        this->current->rotateCW();
    }
    this->dropGhost();
    return false;
}

void Game::hardDrop(){
    
    while (board.canPlace(*this->current, {0, 1})) {
        this->current->moveDown();
    }
    
    board.lock(*this->current);
    int lines = board.clearFullLines();
    calculateScore(lines);          
    hold_used_this_turn = false;  
    lock_timer_engadged = false;
    spawn();    
    
}

void Game::hold(){

    if(!this->hold_block.has_value()){
        this->hold_block=this->current->getShape();
        hold_used_this_turn=true;
    }
    else{
        this->hold_spawn_block=this->hold_block;
        this->hold_block=this->current->getShape();
        spawn_from_hold=true;
        hold_used_this_turn=true;
    }
    
    
    spawn();
}

void Game::pause(){

    if(this->play_state==State::Playing){
        this->play_state=State::Paused;
    }
    else{
        this->play_state=State::Playing;
    }
}

void Game::dropGhost(){

    this->ghost->setRoot(current->getRoot());
    this->ghost->setRotation(current->getRotation());    
    while (board.canPlace(*this->ghost, {0, 1})) {
        this->ghost->moveDown();
    }
}

void Game::setMoveLeft(bool v){ move_left = v; }
void Game::setMoveRight(bool v){ move_right = v; }
void Game::setRotateCW(bool v){ rotateCW = v; }
void Game::setRotateCCW(bool v){ rotateCCW = v; }
void Game::setHardDrop(bool v){ hard_drop = v; }
void Game::setSoftDrop(bool v){ soft_drop = v; }
void Game::setHoldUsed(bool v){ hold_used = v; }
void Game::setPauseUsed(bool v){ pause_used = v; }

State Game::getState(){
    return this->play_state;
}

Game::~Game() = default;

void Game::calculateScore(int lines_cleard){

    switch (lines_cleard)
    {
    case 1:
        this->score+=level*100;
        break;
    case 2:
        this->score+=level*300;
        break;
    case 3:
        this->score+=level*500;
        break;
    case 4:
        this->score+=level*800;
        break;
    default:
        break;
    }

    this->sum_lines+=lines_cleard;

    if(sum_lines>=10){
        level+=1;
        sum_lines-=10;
        this->gravityMS = (int)(1000.0f * std::pow(0.8f, level - 1));
        this->soft_gravityMS = this->gravityMS / 20;
    }
    
}

const Board& Game::getBoard() const{

    return this->board;
}

const Block* Game::getCurrent() const{

    return this->current.get();
}

const Block* Game::getGhost() const{

    return this->ghost.get();
}

std::optional<ShapeType> Game::getHold() const{
    return this->hold_block;
}


const int Game::getScore() const{

    return this->score;    
}


const int Game::getLevel() const{

    return this->level;    
}
