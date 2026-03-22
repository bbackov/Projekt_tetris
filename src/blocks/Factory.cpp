#include "Factory.hpp"
#include "IBlock.hpp"
#include "JBlock.hpp"
#include "LBlock.hpp"
#include "OBlock.hpp"
#include "SBlock.hpp"
#include "TBlock.hpp"
#include "ZBlock.hpp"

#include <unordered_map>
#include <functional>
#include <memory>

std::unique_ptr<Block> makeBlock(ShapeType type) {
    static const std::unordered_map<ShapeType, std::function<std::unique_ptr<Block>()>> table = {
        {ShapeType::I, []() { return std::make_unique<IBlock>(); }},
        {ShapeType::J, []() { return std::make_unique<JBlock>(); }},
        {ShapeType::L, []() { return std::make_unique<LBlock>(); }},
        {ShapeType::O, []() { return std::make_unique<OBlock>(); }},
        {ShapeType::S, []() { return std::make_unique<SBlock>(); }},
        {ShapeType::T, []() { return std::make_unique<TBlock>(); }},
        {ShapeType::Z, []() { return std::make_unique<ZBlock>(); }},
    };

    auto it = table.find(type);
    if (it != table.end()) {
        return it->second();
    }
    return nullptr; 
}