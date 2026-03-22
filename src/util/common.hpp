
#pragma once

#include <utility>
#include <functional>

// blokovi
enum class ShapeType {
    I=1, O, T, S, Z, J, L
};

//klasificiranje točke
using point = std::pair<int,int>;

struct PointHash {
    std::size_t operator()(const point& p) const noexcept {

        std::size_t h1 = std::hash<int>{}(p.first);
        std::size_t h2 = std::hash<int>{}(p.second);
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};

inline point operator+(const point& a, const point& b) {
    return { a.first + b.first, a.second + b.second };
}

enum class State {
    Playing,Paused,Game_over
};

struct Color {
    float r;
    float g;
    float b;
};

inline Color getColorForShape(ShapeType shape)
{
    switch(shape)
    {
        case ShapeType::I: return {0.0f, 1.0f, 1.0f}; // cyan
        case ShapeType::O: return {1.0f, 1.0f, 0.0f}; // yellow
        case ShapeType::T: return {0.6f, 0.0f, 0.8f}; // purple
        case ShapeType::S: return {0.0f, 1.0f, 0.0f}; // green
        case ShapeType::Z: return {1.0f, 0.0f, 0.0f}; // red
        case ShapeType::J: return {0.0f, 0.0f, 1.0f}; // blue
        case ShapeType::L: return {1.0f, 0.5f, 0.0f}; // orange
        default: return {1.0f, 1.0f, 1.0f};
    }
}
