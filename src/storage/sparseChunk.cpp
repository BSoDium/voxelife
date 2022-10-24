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

std::string vec3i::toString()
{
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}

SparseChunk::SparseChunk()
{
}

SparseChunk::~SparseChunk()
{
}

void SparseChunk::set(vec3i pos, float value)
{
  if (value == 0.0f) {
    data.erase(pos);
  } else {
    data[pos] = value;
  }
}

void SparseChunk::set(int x, int y, int z, float value)
{
    set(vec3i(x, y, z), value);
}

float SparseChunk::get(vec3i pos)
{
  if (data.find(pos) == data.end()) {
    return 0.0f;
  } else {
    return data[pos];
  }
}

float SparseChunk::get(int x, int y, int z)
{
    return get(vec3i(x, y, z));
}

bool SparseChunk::has(vec3i pos)
{
    return data.find(pos) != data.end();
}

bool SparseChunk::has(int x, int y, int z)
{
    return has(vec3i(x, y, z));
}

int SparseChunk::size()
{
    return data.size();
}

void SparseChunk::clear()
{
    data.clear();
}

std::map<vec3i, float> SparseChunk::getData()
{
    return data;
}

void SparseChunk::forEach(std::function<void(vec3i, float)> f)
{
    for (auto it = data.begin(); it != data.end(); it++)
    {
        f(it->first, it->second);
    }
}

std::vector<vec3i> getNeighbours(vec3i pos, bool includeSelf)
{
    std::vector<vec3i> neighbors;
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            for (int z = -1; z <= 1; z++)
            {
                if (x == 0 && y == 0 && z == 0 && !includeSelf)
                {
                    continue;
                }
                neighbors.push_back(vec3i(x, y, z) + pos);
            }
        }
    }
    return neighbors;
}