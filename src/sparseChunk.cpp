#include "sparseChunk.hpp"

vec3i::vec3i(int x, int y, int z) : x(x), y(y), z(z) {}

bool vec3i::operator<(const struct vec3i& other) const
{
    return x < other.x || (x == other.x && (y < other.y || (y == other.y && z < other.z)));
}

vec3i vec3i::operator+(const struct vec3i& other) const
{
    return vec3i(x + other.x, y + other.y, z + other.z);
}

sparseChunk::sparseChunk()
{
}

sparseChunk::~sparseChunk()
{
}

void sparseChunk::set(vec3i pos, float value)
{
  if (value == 0.0f) {
    voxels.erase(pos);
  } else {
    voxels[pos] = value;
  }
}

void sparseChunk::set(int x, int y, int z, float value)
{
    set(vec3i(x, y, z), value);
}

float sparseChunk::get(vec3i pos)
{
  if (voxels.find(pos) == voxels.end()) {
    return 0.0f;
  } else {
    return voxels[pos];
  }
}

float sparseChunk::get(int x, int y, int z)
{
    return get(vec3i(x, y, z));
}

bool sparseChunk::has(vec3i pos)
{
    return voxels.find(pos) != voxels.end();
}

bool sparseChunk::has(int x, int y, int z)
{
    return has(vec3i(x, y, z));
}

int sparseChunk::size()
{
    return voxels.size();
}

void sparseChunk::clear()
{
    voxels.clear();
}

void sparseChunk::forEach(std::function<void(vec3i, float)> f)
{
    for (auto it = voxels.begin(); it != voxels.end(); it++)
    {
        f(it->first, it->second);
    }
}
