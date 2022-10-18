#include "logic.hpp"

#define DECAY 0.05f

float conway(int x, int y, int z, VoxelFieldData data) {
    int neighbors = 0;
    float value = data.at(x).at(y).at(z);
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            for (int k = -1; k <= 1; k++) {
                if (i == 0 && j == 0 && k == 0) {
                    continue;
                }
                try { // TODO: This is a hack, fix it
                    if (data.at(x + i).at(y + j).at(z + k) == 1.0f) {
                        neighbors++;
                    }
                } catch (std::out_of_range) {
                    continue;
                }
            }
        }
    }
    if (value == 1.0f) {
        if (neighbors == 3 || neighbors == 4) {
            return 1.0f;
        }
    } else {
        if (neighbors == 4) {
            return 1.0f;
        }
    }
    return std::max(value - DECAY, 0.0f);
}