
#ifndef VOXELFIELD_HPP
#define VOXELFIELD_HPP

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

#include "mesh.hpp"
#include "drawable.hpp"
#include "geomutils.hpp"
#include "sparseChunk.hpp"

class World : public Drawable
{
private:
  /* The voxel field data */
  sparseChunk voxels;
  /* The mesh associated with the voxel field. */
  Mesh mesh;
  /**
   * Creates the vertices and primitives of the mesh.
   */
  void createMesh();

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
   * Get the value of a voxel.
   */
  float getVoxel(int x, int y, int z);
  /**
   * Apply a function to each voxel in need of updating.
  */
  void apply(std::function<float(int, int, int, sparseChunk)> f);
};

#endif