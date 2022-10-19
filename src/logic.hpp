#ifndef LOGIC_HPP
#define LOGIC_HPP

#include <algorithm>

#include "world.hpp"

float conway(int x, int y, int z, sparseChunk data);

float smoothConway(int x, int y, int z, sparseChunk data);

#endif // LOGIC_HPP