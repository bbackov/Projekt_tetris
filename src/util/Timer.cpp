
#include "Timer.hpp"

Timer::Timer(){reset();}

void Timer::reset(){
    start=std::chrono::steady_clock::now();
}

long long Timer::elapsedTime() const{

    auto now=std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now-start).count();

}