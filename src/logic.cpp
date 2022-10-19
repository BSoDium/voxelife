#include "logic.hpp"

#define DECAY 0.05f

float conway(int x, int y, int z, sparseChunk data)
{
    int neighbors = 0;
    float value = data.get(x, y, z);
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            for (int k = -1; k <= 1; k++)
            {
                if (i == 0 && j == 0 && k == 0)
                {
                    continue;
                }
                if (data.get(x + i, y + j, z + k) == 1.0f)
                {
                    neighbors++;
                }
            }
        }
    }
    if (value == 1.0f)
    {
        if (neighbors == 3 || neighbors == 4)
        {
            return 1.0f;
        }
    }
    else
    {
        if (neighbors == 4)
        {
            return 1.0f;
        }
    }
    return std::max(value - DECAY, 0.0f);
}


float smoothConway(int x, int y, int z, sparseChunk data)
{
    float neighbors = 0;
    float value = data.get(x, y, z);
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            for (int k = -1; k <= 1; k++)
            {
                if (i == 0 && j == 0 && k == 0)
                {
                    continue;
                }
                if (data.has(x + i, y + j, z + k))
                {
                    neighbors += data.get(x + i, y + j, z + k);
                }
            }
        }
    }
    if (value != 0.0f)
    {
        if (neighbors >= 3 && neighbors <= 4)
        {
            return std::min(value + DECAY, 1.0f);
        }
    }
    else
    {
        if (neighbors >= 3.5 && neighbors <= 4)
        {
            return std::min(value + DECAY, 1.0f);
        }
    }
    return std::max(value - DECAY, 0.0f);
}