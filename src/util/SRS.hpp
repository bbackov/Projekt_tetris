
#pragma once
#include "common.hpp"
#include <array>
#include <unordered_map>


namespace SRS{

    using KickTable =std::array<point,5>;
    


    const std::unordered_map<point,KickTable,PointHash> JLTSZ ={ 
        {{0,1},{ point{0, 0},point{-1, 0},point{-1,1}, point{0,-2},point{-1,-2}}}, 
        {{1,0},{ point{0, 0},point{1, 0},point{1,-1},point{0,2},point{1,2}}}, 
        {{1,2},{ point{0, 0},point{1, 0},point{1,-1},point{0,2},point{1,2}}}, 
        {{2,1},{ point{0, 0},point{-1, 0},point{-1,1}, point{0,-2},point{-1,-2}}}, 
        {{2,3},{ point{0, 0},point{1, 0},point{1,1}, point{0,-2},point{1,-2}}}, 
        {{3,2},{ point{0, 0},point{-1, 0},point{-1,-1},point{0,2},point{-1,2}}}, 
        {{3,0},{ point{0, 0},point{-1, 0},point{-1,-1},point{0,2},point{-1,2}}}, 
        {{0,3},{ point{0, 0},point{1, 0},point{1,1}, point{0,-2},point{1,-2}}} 
        };


    const std::unordered_map<point, KickTable,PointHash> I = {
        {{0,1},  { point{0,0}, point{-2,0}, point{ 1,0}, point{-2,-1}, point{ 1, 2} }},
        {{1,0},  { point{0,0}, point{ 2,0}, point{-1,0}, point{ 2, 1}, point{-1,-2} }}, 
        {{1,2},  { point{0,0}, point{-1,0}, point{ 2,0}, point{-1,-2}, point{ 2,-1} }}, 
        {{2,1},  { point{0,0}, point{ 1,0}, point{-2,0}, point{ 1, 2}, point{-2, 1} }}, 
        {{2,3},  { point{0,0}, point{ 2,0}, point{-1,0}, point{ 2,-1}, point{-1,-2} }}, 
        {{3,2},  { point{0,0}, point{-2,0}, point{ 1,0}, point{-2, 1}, point{ 1, 2} }},
        {{3,0},  { point{0,0}, point{ 1,0}, point{-2,0}, point{ 1,-2}, point{-2, 1} }}, 
        {{0,3},  { point{0,0}, point{-1,0}, point{ 2,0}, point{-1, 2}, point{ 2,-1} }}  
    };
}

