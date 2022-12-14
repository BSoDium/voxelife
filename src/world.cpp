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
  data = new SimChunk();
  buffer = new SimChunk();

  meshNeedsUpdate = true;
}

World::~World()
{
}

void World::updateMesh()
{

  std::vector<vertex> vertices;
  std::vector<primitive> primitives;

  // Create the vertices
  int i = 0;

  data->forEachActive([&](vec3i pos, float value)
                     {
    if (value > 0.0f) {
      float halfSize = value / 2.0f;
      
      vertex voxelCenter = vertex(pos.x + 0.5f, pos.y + 0.5f, pos.z + 0.5f);

      // Create the vertices
      for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
          for (int k = -1; k <= 1; k += 2) {
            vertex v = vertex(
              voxelCenter.x + i * halfSize, voxelCenter.y + j * halfSize, voxelCenter.z + k * halfSize, 
              halfSize, halfSize, halfSize,
              i, j, k
            );
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

  mesh = new Mesh(
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
  if (meshNeedsUpdate)
  {
    updateMesh();
    meshNeedsUpdate = false;
  }
  
  glPushMatrix();

  // Draw the mesh
  mesh->draw();

  glPopMatrix();
}

void World::setVoxel(int x, int y, int z, float value)
{
  buffer->set(vec3i(x, y, z), value);
}

void World::setVoxel(vec3i pos, float value)
{
  buffer->set(pos, value);
}

float World::getVoxel(int x, int y, int z)
{
  return data->get(vec3i(x, y, z));
}

float World::getVoxel(vec3i pos)
{
  return data->get(pos);
}

void World::update()
{
  // Update the voxel field
  data = buffer;
  buffer = new SimChunk();

  meshNeedsUpdate = true;
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

      setVoxel(pos + offset, 1.0f);
    }
  }

  // Update the data
  update();
}

void World::apply(std::function<float(int, int, int, SimChunk)> f)
{
  // Apply the function to the data
  data->forEach(
      [&](vec3i pos, float)
      {
        setVoxel(pos.x, pos.y, pos.z, f(pos.x, pos.y, pos.z, *data));
      });

  // Update the data
  update();
}

void World::print()
{
  data->forEachActive([&](vec3i pos, float value)
                     {
    if (value > 0.0f) {
      std::cout << "Voxel at " << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
    } });
}
