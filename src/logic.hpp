#ifndef LOGIC_HPP
#define LOGIC_HPP

#include <algorithm>

#include "world.hpp"

float conway(int x, int y, int z, SimChunk data);

float smoothConway(int x, int y, int z, SimChunk data);

float analogConway(int x, int y, int z, SimChunk data);

float naive(int x, int y, int z, SimChunk data);

#endif // LOGIC_HPP