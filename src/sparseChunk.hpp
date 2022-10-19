#ifndef SPARSEVOXELFIELD_HPP
#define SPARSEVOXELFIELD_HPP

#define HASH_CONSTANT 0x9e3779b9

#include <map>
#include <limits>
#include <functional>
#include <glm/glm.hpp>

struct vec3i {
  int x;
  int y;
  int z;
  vec3i(int x, int y, int z);
  bool operator<(const struct vec3i& other) const;
  vec3i operator+(const struct vec3i& other) const;
};

class sparseChunk
{
private:
  std::map<vec3i, float> voxels;

public:
  sparseChunk();
  ~sparseChunk();

  /**
   * Set a voxel at a position.
   */
  void set(vec3i pos, float value);
  /**
   * Set a voxel at a position.
  */
  void set(int x, int y, int z, float value);
  
  /**
   * Get a voxel at a position.
   */
  float get(vec3i pos);
  /**
   * Get a voxel at a position.
   */
  float get(int x, int y, int z);

  /**
   * Check if a voxel exists at a position.
   */
  bool has(vec3i pos);
  /**
   * Check if a voxel exists at a position.
   */
  bool has(int x, int y, int z);

  /**
   * Get the number of voxels in the chunk.
  */
  int size();

  /**
   * Iterate over all voxels in the chunk.
   */
  void clear();
  /**
   * Iterate over all voxels in the chunk.
   */
  void forEach(std::function<void(vec3i, float)> f);
};

#endif