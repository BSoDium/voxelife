#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#include "world.hpp"

World::World(int size)
{
  this->size = size;

  // Create the voxel field data
  voxels = VoxelFieldData(size, std::vector<std::vector<float>>(size, std::vector<float>(size, 0.0f)));

  createGrid();
  createMesh();
}

World::~World()
{
}

void World::createMesh()
{

  std::vector<vertex> vertices;
  std::vector<primitive> primitives;

  // Create the vertices
  int i = 0;
  for (int x = 0; x < size; x++)
  {
    for (int y = 0; y < size; y++)
    {
      for (int z = 0; z < size; z++)
      {
        float voxelValue = voxels.at(x).at(y).at(z) * 0.5f;
        if (voxelValue > 0.0f)
        {
          vertex voxelCenter = vertex(x + 0.5f, y + 0.5f, z + 0.5f, voxelValue, voxelValue, voxelValue);

          // Create the vertices
          vertices.push_back(voxelCenter + vertex(-voxelValue, -voxelValue, -voxelValue));
          vertices.push_back(voxelCenter + vertex(voxelValue, -voxelValue, -voxelValue));
          vertices.push_back(voxelCenter + vertex(voxelValue, voxelValue, -voxelValue));
          vertices.push_back(voxelCenter + vertex(-voxelValue, voxelValue, -voxelValue));
          vertices.push_back(voxelCenter + vertex(-voxelValue, -voxelValue, voxelValue));
          vertices.push_back(voxelCenter + vertex(voxelValue, -voxelValue, voxelValue));
          vertices.push_back(voxelCenter + vertex(voxelValue, voxelValue, voxelValue));
          vertices.push_back(voxelCenter + vertex(-voxelValue, voxelValue, voxelValue));

          // Create the primitives
          primitives.push_back(primitive(i + 0, i + 1, i + 2));
          primitives.push_back(primitive(i + 0, i + 2, i + 3));
          primitives.push_back(primitive(i + 0, i + 1, i + 5));
          primitives.push_back(primitive(i + 0, i + 5, i + 4));
          primitives.push_back(primitive(i + 0, i + 3, i + 7));
          primitives.push_back(primitive(i + 0, i + 7, i + 4));
          primitives.push_back(primitive(i + 1, i + 2, i + 6));
          primitives.push_back(primitive(i + 1, i + 6, i + 5));
          primitives.push_back(primitive(i + 2, i + 3, i + 7));
          primitives.push_back(primitive(i + 2, i + 7, i + 6));
          primitives.push_back(primitive(i + 3, i + 4, i + 7));
          primitives.push_back(primitive(i + 4, i + 5, i + 6));
          primitives.push_back(primitive(i + 4, i + 6, i + 7));

          i += 8;
        }
      }
    }
  }

  mesh = Mesh(
      vertices,
      primitives,
      Material(
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    0.0f));
  mesh.setPosition(vertex(-size / 2.0f, -size / 2.0f, -size / 2.0f));

}

void World::createGrid()
{

  std::vector<vertex> vertices;
  std::vector<primitive> primitives;

  // Create the vertices
  for (int x = 0; x < size + 1; x++)
  {
    for (int y = 0; y < size + 1; y++)
    {
      for (int z = 0; z < size + 1; z++)
      {
        vertices.push_back(vertex(x, y, z, 0.5f, 0.5f, 0.5f));
      }
    }
  }

  // Create the primitives
  for (int x = 0; x < size; x++)
  {
    for (int y = 0; y < size; y++)
    {
      for (int z = 0; z < size; z++)
      {
        // Get the index of the vertices
        int a = x + y * (size + 1) + z * (size + 1) * (size + 1);
        int b = a + 1;
        int c = a + (size + 1);
        int d = c + 1;
        int e = a + (size + 1) * (size + 1);
        int f = e + 1;
        int g = e + (size + 1);
        int h = g + 1;

        // Create the primitives
        primitives.push_back(primitive(a, b, c));
        primitives.push_back(primitive(b, d, c));
        primitives.push_back(primitive(b, f, d));
        primitives.push_back(primitive(f, h, d));
        primitives.push_back(primitive(f, e, h));
        primitives.push_back(primitive(e, g, h));
        primitives.push_back(primitive(e, a, g));
        primitives.push_back(primitive(a, c, g));
        primitives.push_back(primitive(c, d, g));
        primitives.push_back(primitive(d, h, g));
        primitives.push_back(primitive(e, f, a));
        primitives.push_back(primitive(f, b, a));
      }
    }
  }

  grid = Mesh(
      vertices,
      primitives,
      Material(
          glm::vec3(1.0f, 1.0f, 1.0f),
          glm::vec3(1.0f, 1.0f, 1.0f),
          glm::vec3(1.0f, 1.0f, 1.0f),
          0.0f));

  grid.setWireframe(true);
  grid.setPosition(vertex(-size / 2.0f, -size / 2.0f, -size / 2.0f));
}

void World::draw()
{
  glPushMatrix();

  // Draw the mesh
  mesh.draw();

  // Draw the grid
  // grid.draw();

  glPopMatrix();
}

void World::randomize()
{
  // Randomize the data (either 0 or 1)
  for (int x = 0; x < size; x++)
  {
    for (int y = 0; y < size; y++)
    {
      for (int z = 0; z < size; z++)
      {
        voxels.at(x).at(y).at(z) = rand() % 2;
      }
    }
  }

  // Update the mesh
  createMesh();
}

void World::apply(std::function<float(int, int, int, VoxelFieldData)> f)
{
  // Make a copy of the data
  VoxelFieldData data = VoxelFieldData(size, std::vector<std::vector<float>>(size, std::vector<float>(size, 0.0f)));

  // Apply the function to the data
  for (int x = 0; x < size; x++)
  {
    for (int y = 0; y < size; y++)
    {
      for (int z = 0; z < size; z++)
      {
        data.at(x).at(y).at(z) = f(x, y, z, voxels);
      }
    }
  }

  // Update the data
  voxels = data;

  // Update the mesh
  createMesh();
}