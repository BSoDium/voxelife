#include "logic.hpp"

#define DECAY 0.05f

float conway(int x, int y, int z, SimChunk data)
{
    int neighbourCount = 0;
    float value = data.get(x, y, z);
    for (vec3i neighbour : getNeighbours(vec3i(x, y, z)))
    {
        if (data.get(neighbour) == 1.0f)
        {
            neighbourCount++;
        }
    }
    if (value == 1.0f)
    {
        if (neighbourCount == 2 || neighbourCount == 3)
        {
            return 1.0f;
        }
    }
    else
    {
        if (neighbourCount == 3)
        {
            return 1.0f;
        }
    }
    return 0.0f;
}

float smoothConway(int x, int y, int z, SimChunk data)
{
    int neighbourCount = 0;
    float value = data.get(x, y, z);
    for (vec3i neighbour : getNeighbours(vec3i(x, y, z)))
    {
        if (data.get(neighbour) == 1.0f)
        {
            neighbourCount++;
        }
    }
    if (value == 1.0f)
    {
        if (neighbourCount == 2 || neighbourCount == 3)
        {
            return 1.0f;
        }
    }
    else
    {
        if (neighbourCount == 3)
        {
            return 1.0f;
        }
    }
    return std::max(0.0f, value - DECAY);
}

float analogConway(int x, int y, int z, SimChunk data)
{
    float neighbourCount = 0;
    float value = data.get(x, y, z);
    for (vec3i neighbour : getNeighbours(vec3i(x, y, z)))
    {
        if (data.has(neighbour))
        {
            neighbourCount += data.get(neighbour);
        }
    }
    if (value != 0.0f)
    {
        if (neighbourCount >= 2 && neighbourCount <= 3)
        {
            return value;
        }
    }
    else
    {
        if (neighbourCount >= 2.5 && neighbourCount <= 3)
        {
            return std::min(value + DECAY, 1.0f);
        }
    }
    return std::max(value - DECAY, 0.0f);
}

float naive(int x, int y, int z, SimChunk data)
{
    float neighbourCount = 0;
    float value = data.get(x, y, z);
    for (vec3i neighbour : getNeighbours(vec3i(x, y, z)))
    {
        if (data.has(neighbour))
        {
            neighbourCount += data.get(neighbour);
        }
    }
    if (neighbourCount > 0)
    {
        return std::min(value + neighbourCount, 1.0f);
    }
    else
    {
        return std::min(value - DECAY, 0.0f);
    }
}