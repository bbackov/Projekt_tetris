#pragma once
#include "Blocks.hpp"
#include <memory>

std::unique_ptr<Block> makeBlock(ShapeType type);