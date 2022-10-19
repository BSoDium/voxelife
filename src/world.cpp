#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#define GEN_BOUND 50
#define GEN_CLUSTER_COUNT 7
#define GEN_CLUSTER_SIZE 4
#define GEN_CLUSTER_BOUND 5

#include "world.hpp"

World::World()
{
  // Create the voxel field data
  voxels = sparseChunk();

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

  voxels.forEach([&](vec3i pos, float value)
                 {
    if (value > 0.0f) {
      float halfSize = value / 2.0f;
      
      vertex voxelCenter = vertex(pos.x + 0.5f, pos.y + 0.5f, pos.z + 0.5f);

      // Create the vertices
      for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
          for (int k = -1; k <= 1; k += 2) {
            vertex v = vertex(voxelCenter.x + i * halfSize, voxelCenter.y + j * halfSize, voxelCenter.z + k * halfSize, 
            halfSize, halfSize, halfSize,
            i, j, k);
            vertices.push_back(v);
          }
        }
      }
      
      // Create the primitives
      primitives.push_back(primitive(i + 0, i + 1, i + 2));
      primitives.push_back(primitive(i + 1, i + 2, i + 3));
      primitives.push_back(primitive(i + 4, i + 5, i + 6));
      primitives.push_back(primitive(i + 5, i + 6, i + 7));
      primitives.push_back(primitive(i + 0, i + 1, i + 4));
      primitives.push_back(primitive(i + 1, i + 4, i + 5));
      primitives.push_back(primitive(i + 2, i + 3, i + 6));
      primitives.push_back(primitive(i + 3, i + 6, i + 7));
      primitives.push_back(primitive(i + 0, i + 2, i + 4));
      primitives.push_back(primitive(i + 2, i + 4, i + 6));
      primitives.push_back(primitive(i + 1, i + 3, i + 5));
      primitives.push_back(primitive(i + 3, i + 5, i + 7));

      i += 8;
    } });

  mesh = Mesh(
      vertices,
      primitives,
      Material(
          glm::vec3(1.0f, 1.0f, 1.0f),
          glm::vec3(1.0f, 1.0f, 1.0f),
          glm::vec3(1.0f, 1.0f, 1.0f),
          0.0f));
}

void World::draw()
{
  glPushMatrix();

  // Draw the mesh
  mesh.draw();

  glPopMatrix();
}

void World::randomize()
{
  // Add a random number of voxels to the field
  for (int i = 0; i < GEN_CLUSTER_COUNT; i++)
  {
    // Create a random position
    vec3i pos = vec3i(
        rand() % GEN_BOUND - GEN_BOUND / 2,
        rand() % GEN_BOUND - GEN_BOUND / 2,
        rand() % GEN_BOUND - GEN_BOUND / 2);
    
    // Generate GEN_CLUSTER_SIZE voxels around the position
    for (int j = 0; j < GEN_CLUSTER_SIZE; j++)
    {
      vec3i offset = vec3i(
          rand() % GEN_CLUSTER_BOUND - GEN_CLUSTER_BOUND / 2,
          rand() % GEN_CLUSTER_BOUND - GEN_CLUSTER_BOUND / 2,
          rand() % GEN_CLUSTER_BOUND - GEN_CLUSTER_BOUND / 2);
      
      voxels.set(pos + offset, 1.0f);      
    }
  }

  // Update the mesh
  createMesh();
}

void World::apply(std::function<float(int, int, int, sparseChunk)> f)
{
  // Make a copy of the data
  sparseChunk data = sparseChunk();

  // Apply the function to the data
  voxels.forEach(
      [&](vec3i pos, float)
      {
        for (int i = -1; i <= 1; i++)
        {
          for (int j = -1; j <= 1; j++)
          {
            for (int k = -1; k <= 1; k++)
            {
              if (!data.has(pos.x + i, pos.y + j, pos.z + k))
              {
                data.set(pos.x + i, pos.y + j, pos.z + k, f(pos.x + i, pos.y + j, pos.z + k, voxels));
              }
            }
          }
        }
      });

  // Update the data
  voxels = data;

  // Update the mesh
  createMesh();
}