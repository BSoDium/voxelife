#include "simChunk.hpp"

VoxelState::VoxelState()
{
}

void VoxelState::addCulprit(vec3i neighbour)
{
  culprits.insert(neighbour);
}

void VoxelState::removeCulprit(vec3i neighbour)
{
  culprits.erase(neighbour);
}

bool VoxelState::hasCulprit(vec3i neighbour)
{
  return culprits.find(neighbour) != culprits.end();
}

bool VoxelState::hasCulprits()
{
  return culprits.size() > 0;
}

int VoxelState::culpritCount()
{
  return culprits.size();
}

SimChunk::SimChunk()
{
}

SimChunk::SimChunk(SparseChunk data)
{
  this->data = data.getData();
}

SimChunk::~SimChunk()
{
}

void SimChunk::set(vec3i pos, float value)
{
#pragma omp critical
  {
    SparseChunk::set(pos, value);

    if (value == 0.0f)
    {
      for (vec3i neighbour : getNeighbours(pos))
      {
        if (hasState(neighbour))
        {
          VoxelState neighbourState = getState(neighbour);
          // If the neighbour is monitored only due to this voxel, remove it.
          if (neighbourState.culpritCount() == 1)
          {
            delState(neighbour);
          }
          else
          {
            // Otherwise, remove this voxel from the culprit's list.
            neighbourState.removeCulprit(pos);
          }
        }
      }
      delState(pos);
    }
    else if (!hasState(pos))
    {
      for (vec3i neighbour : getNeighbours(pos))
      {
        // If the neighbour isn't registered, register it.
        if (!hasState(neighbour))
        {
          setState(neighbour, VoxelState());
        }
        // Add this voxel as a culprit.
        getState(neighbour).addCulprit(pos);
      }
      setState(pos, VoxelState());
    }
  }
}

void SimChunk::set(int x, int y, int z, float value)
{
  set(vec3i(x, y, z), value);
}

void SimChunk::setState(vec3i pos, VoxelState state)
{
  stateData[pos] = state;
}

void SimChunk::setState(int x, int y, int z, VoxelState state)
{
  setState(vec3i(x, y, z), state);
}

void SimChunk::delState(vec3i pos)
{
  stateData.erase(pos);
}

void SimChunk::delState(int x, int y, int z)
{
  delState(vec3i(x, y, z));
}

VoxelState SimChunk::getState(vec3i pos)
{
  if (stateData.find(pos) != stateData.end())
  {
    return stateData[pos];
  }
  else
  {
    throw std::runtime_error("No state data for voxel at " + pos.toString());
  }
}

VoxelState SimChunk::getState(int x, int y, int z)
{
  return getState(vec3i(x, y, z));
}

bool SimChunk::hasState(vec3i pos)
{
  return stateData.find(pos) != stateData.end();
}

bool SimChunk::hasState(int x, int y, int z)
{
  return hasState(vec3i(x, y, z));
}

int SimChunk::stateSize()
{
  return stateData.size();
}

void SimChunk::forEach(std::function<void(vec3i, float)> f)
{
#pragma omp parallel
#pragma omp single
  {
    for (std::map<vec3i, VoxelState>::iterator it = stateData.begin(); it != stateData.end(); ++it)
    {
#pragma omp task firstprivate(it)
      f(it->first, get(it->first));
    }
#pragma omp taskwait
  }
}

void SimChunk::forEachActive(std::function<void(vec3i, float)> f)
{
  for (std::map<vec3i, float>::iterator it = data.begin(); it != data.end(); ++it)
  {
    f(it->first, get(it->first));
  }
}
