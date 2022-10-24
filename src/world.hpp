
#ifndef WORLD_HPP
#define WORLD_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <functional>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <cmath>

#include "rendering/mesh.hpp"
#include "rendering/drawable.hpp"
#include "geomutils.hpp"
#include "storage/simChunk.hpp"

class World : public Drawable
{
private:
  /* The voxel field data */
  SimChunk data;
  /** A copy of the voxel field data which is used to edit the voxel field. */
  SimChunk buffer;
  /* The mesh associated with the voxel field. */
  Mesh mesh;
  
  /**
   * Creates the vertices and primitives of the mesh.
   */
  void updateMesh();

public:
  /**
   * Creates a voxel field with the given size.
   */
  World();
  /**
   * Destroys the voxel field.
   */
  ~World();
  /**
   * Randomize the voxel field data (place random voxels in the field).
   */
  void randomize();
  /**
   * Draw the voxel field.
   */
  void draw();
  /**
   * Set the value of a voxel.
  */
  void setVoxel(int x, int y, int z, float value);
  /**
   * Set the value of a voxel.
  */
  void setVoxel(vec3i pos, float value);
  /**
   * Get the value of a voxel.
   */
  float getVoxel(int x, int y, int z);
  /**
   * Get the value of a voxel.
   */
  float getVoxel(vec3i pos);
  /** 
   * Copy the buffer to the data.
  */
  void update();

  /**
   * Apply a function to each voxel in need of updating.
  */
  void apply(std::function<float(int, int, int, SimChunk)> f);
};

#endif