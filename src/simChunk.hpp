#ifndef SIMCHUNK_HPP
#define SIMCHUNK_HPP

#include <set>
#include <stdexcept>

#include "sparseChunk.hpp"

struct VoxelState {
  /** The neighbours that cause this voxel to be monitored, if any. */
  std::set<vec3i> culprits;
  /** Constructor. */
  VoxelState();
  /** Add a neighbour that causes this voxel to be monitored. */
  void addCulprit(vec3i neighbour);
  /** Remove a neighbour that causes this voxel to be monitored. */
  void removeCulprit(vec3i neighbour);
  /** Check if this voxel has a neighbour that causes it to be monitored. */
  bool hasCulprit(vec3i neighbour);
  /** Check if this voxel has any neighbours that cause it to be monitored. */
  bool hasCulprits();
  /** Get the number of neighbours that cause this voxel to be monitored. */
  int culpritCount();
};

class SimChunk : public SparseChunk
{
private:
  /** The voxel state data. */
  std::map<vec3i, VoxelState> stateData;

public:
  SimChunk();
  SimChunk(SparseChunk data);
  ~SimChunk();

  /**
   * Set a voxel at a position.
   */
  void set(vec3i pos, float value);
  /**
   * Set a voxel at a position.
  */
  void set(int x, int y, int z, float value);
  /**
   * Set the state of a voxel at a position.
  */
  void setState(vec3i pos, VoxelState state);
  /**
   * Set the state of a voxel at a position.
  */
  void setState(int x, int y, int z, VoxelState state);
  /**
   * Delete the state of a voxel at a position.
  */
  void delState(vec3i pos);
  /**
   * Delete the state of a voxel at a position.
  */
  void delState(int x, int y, int z);
  /**
   * Get the state of a voxel at a position.
  */
  VoxelState getState(vec3i pos);
  /**
   * Get the state of a voxel at a position.
  */
  VoxelState getState(int x, int y, int z);

  /**
   * Check if a voxel exists at a position.
   */
  bool hasState(vec3i pos);
  /**
   * Check if a voxel exists at a position.
   */
  bool hasState(int x, int y, int z);

  /**
   * Get the number of voxels in the chunk.
   */
  int stateSize();

  /**
   * Iterate over all monitored voxels in the chunk.
  */
  void forEach(std::function<void(vec3i, float)> f, bool includeMonitored = false);
};

#endif