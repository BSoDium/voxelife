
#ifndef VOXELFIELD_HPP
#define VOXELFIELD_HPP

#include "mesh.hpp"
#include "drawable.hpp"
#include "geomutils.hpp"

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

typedef std::vector<std::vector<std::vector<float>>> VoxelFieldData;

class World : public Drawable
{
private:
  /* The size of the voxel field */
  int size;
  /* The voxel field data */
  VoxelFieldData voxels;
  /* The mesh associated with the voxel field. */
  Mesh mesh;
  /** The grid associated with the voxel field. */
  Mesh grid;
  /**
   * Creates the vertices and primitives of the grid mesh.
  */
  void createGrid();
  /**
   * Creates the vertices and primitives of the mesh.
   */
  void createMesh();

public:
  /**
   * Creates a voxel field with the given size.
   */
  World(int size);
  /**
   * Destroys the voxel field.
   */
  ~World();
  /**
   * Randomize the voxel field data.
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
   * Apply a function to each voxel.
  */
  void apply(std::function<float(int, int, int, VoxelFieldData)> f);
};

#endif