#ifndef MESH_HPP
#define MESH_HPP

#include "drawable.hpp"
#include "material.hpp"

#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <tuple>
#include <thread>
#include <iostream>

/**
 * A vertex is a point in 3D space.
 */
struct vertex
{
  float x, y, z;
  float r, g, b;
  float nx, ny, nz;
  vertex() : x(0.0f), y(0.0f), z(0.0f), r(0.0f), g(0.0f), b(0.0f), nx(0.0f), ny(0.0f), nz(0.0f) {}
  vertex(float x, float y, float z) : x(x), y(y), z(z), r(1.0f), g(1.0f), b(1.0f), nx(0.0f), ny(1.0f), nz(0.0f) {}
  vertex(float x, float y, float z, float r, float g, float b) : x(x), y(y), z(z), r(r), g(g), b(b), nx(0.0f), ny(1.0f), nz(0.0f) {}
  vertex(float x, float y, float z, float r, float g, float b, float nx, float ny, float nz) : x(x), y(y), z(z), r(r), g(g), b(b), nx(nx), ny(ny), nz(nz) {}
  bool equals(vertex v)
  {
    return x == v.x && y == v.y && z == v.z;
  }
  std::vector<float> getAttributes()
  {
    return {x, y, z, r, g, b, nx, ny, nz};
  }
  void setAttributes(std::vector<float> attributes)
  {
    x = attributes[0];
    y = attributes[1];
    z = attributes[2];
    r = attributes[3];
    g = attributes[4];
    b = attributes[5];
    nx = attributes[6];
    ny = attributes[7];
    nz = attributes[8];
  }
  vertex operator+(vertex v)
  {
    return vertex(x + v.x, y + v.y, z + v.z, r + v.r, g + v.g, b + v.b, nx + v.nx, ny + v.ny, nz + v.nz);
  }
};

/**
 * A primitive is a set of linked vertices forming a face or a set of faces.
 * It can only contain three vertices for now (triangle primitive).
 */
struct primitive
{
  int a, b, c;
  primitive() : a(-1), b(-1), c(-1) {}
  primitive(int a, int b, int c) : a(a), b(b), c(c) {}
};

/**
 * A mesh is a collection of vertices and primitives.
 */
class Mesh : public Drawable
{
private:
  /* The mesh's position */
  vertex position = vertex(0.0f, 0.0f, 0.0f);
  /* Polygon mode set to wireframe or fill */
  bool wireframe = false;
  /* The buffer containing the vertices. */
  GLuint vertex_buffer;
  /* The buffer containing the primitives. */
  GLuint primitive_buffer;
  /* The material associated with the mesh. */
  Material material;
  /* Vertices define the position of each point in the mesh. */
  std::vector<vertex> vertices;
  /* Primitives define the topology of the mesh. */
  std::vector<primitive> primitives;
  /* Whether the GL buffers are up to date with the vertices and primitives. */
  bool outOfDate = true;
  /* Updates the vertex and primitive buffers. */
  void updateGLBuffers();

public:
  /**
   * Creates an empty mesh.
   */
  Mesh();
  /**
   * Create a mesh with the given number of vertices and primitives.
   */
  Mesh(int vertices, int primitives, Material material = Material());
  /**
   * Creates a mesh from the given vertices and primitives.
   */
  Mesh(std::vector<vertex> vertices, std::vector<primitive> primitives, Material material = Material());
  /**
   * Destroy the mesh.
   */
  ~Mesh();
  /**
   * Draw the mesh.
   */
  void draw();
  /**
   * Set the vertices of the mesh.
   */
  void setVertices(std::vector<vertex> vertices);
  /**
   * Set the primitives of the mesh.
   */
  void setPrimitives(std::vector<primitive> primitives);
  /**
   * Set the position of a vertex.
   */
  void setVertex(int index, vertex v);
  /**
   * Set the position of a primitive.
   */
  void setPrimitive(int index, primitive p);
  /**
   * Switch polygon mode (wireframe or fill).
   */
  void setWireframe(bool wireframe);
  /**
   * Get polygon mode (true = wireframe, false = fill).
   */
  bool getWireframe();
  /**
   * Set the material of the mesh.
   */
  void setMaterial(Material material);
  /**
   * Get the position of the mesh.
   */
  vertex getPosition();
  /**
   * Set the position of the mesh.
   */
  void setPosition(vertex position);
  /**
   * Apply a modidier to the mesh.
   */
  void apply(std::tuple<std::vector<vertex>, std::vector<primitive>> (*algorithm)(std::vector<vertex> vertices, std::vector<primitive> primitives), int iterations);
};

#endif // MESH_HPP