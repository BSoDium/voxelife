#ifndef SPARSEVOXELFIELD_HPP
#define SPARSEVOXELFIELD_HPP

#define HASH_CONSTANT 0x9e3779b9

#include <map>
#include <string>
#include <limits>
#include <vector>
#include <functional>
#include <glm/glm.hpp>

struct vec3i {
  int x;
  int y;
  int z;
  vec3i(int x, int y, int z);
  bool operator<(const struct vec3i& other) const;
  vec3i operator+(const struct vec3i& other) const;
  std::string toString();
};

class SparseChunk
{
protected:
  /** The voxel field data. */
  std::map<vec3i, float> data;

public:
  SparseChunk();
  ~SparseChunk();

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
   * Retrieve the raw voxel data.
  */
  std::map<vec3i, float> getData();

  /**
   * Iterate over all voxels in the chunk.
   */
  void forEach(std::function<void(vec3i, float)> f);
};

/**
 * Get a vector containing the positions of all neighbors of a position.
*/
std::vector<vec3i> getNeighbours(vec3i pos, bool includeSelf = false);

#endif