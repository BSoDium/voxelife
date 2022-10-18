#ifndef SPARSEVOXELFIELD_HPP
#define SPARSEVOXELFIELD_HPP

#include <map>
#include <glm/glm.hpp>

class sparseChunk
{
  private:
    std::map<glm::vec3, float> voxels;

  public:
    sparseChunk();
    ~sparseChunk();
    void setVoxel(glm::vec3 pos, float value);
    float getVoxel(glm::vec3 pos);
};

#endif