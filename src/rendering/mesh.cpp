#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#include "mesh.hpp"

Mesh::Mesh()
{
  // Create vertex buffer
  glGenBuffers(1, &vertex_buffer);
  // Create primitive buffer
  glGenBuffers(1, &primitive_buffer);
}

Mesh::Mesh(std::vector<vertex> vertices, std::vector<primitive> primitives, Material material) : Mesh()
{
  this->vertices = vertices;
  this->primitives = primitives;
  this->material = material;
  outOfDate = true;
}

Mesh::Mesh(int vertices, int primitives, Material material) : Mesh(std::vector<vertex>(vertices), std::vector<primitive>(primitives), material)
{
}

Mesh::~Mesh()
{
}

void Mesh::updateGLBuffers()
{
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, primitive_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, primitives.size() * sizeof(primitive), &primitives[0], GL_STATIC_DRAW);
}

void Mesh::draw()
{
  if (outOfDate)
  {
    updateGLBuffers();
    outOfDate = false;
  }
  
  if (this->wireframe)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // activate wireframe mode
  }
  glPushMatrix();
  {
    // Apply the material
    material.apply();

    // Apply the position
    glTranslatef(position.x, position.y, position.z);

    // Draw the colored vertices and primitives
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, primitive_buffer);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(vertex), 0);
    glColorPointer(3, GL_FLOAT, sizeof(vertex), (char *)NULL + sizeof(float) * 3);
    glNormalPointer(GL_FLOAT, sizeof(vertex), (char *)NULL + sizeof(float) * 6);
    glDrawElements(GL_TRIANGLES, primitives.size() * 3, GL_UNSIGNED_INT, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    if (this->wireframe)
    {      
      // draw the normals
      for (int i = 0; i < (int)vertices.size(); i++)
      {
        glBegin(GL_LINES);
        {
          glColor3f(1.0f, 0.0f, 0.0f);
          glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
          glVertex3f(vertices[i].x + vertices[i].nx, vertices[i].y + vertices[i].ny, vertices[i].z + vertices[i].nz);
        }
        glEnd();
      }
    }
  }
  glPopMatrix();
  if (this->wireframe)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Mesh::setVertices(std::vector<vertex> vertices)
{
  this->vertices = vertices;
  outOfDate = true;
}

void Mesh::setPrimitives(std::vector<primitive> primitives)
{
  this->primitives = primitives;
  outOfDate = true;
}

void Mesh::setVertex(int index, vertex v)
{
  vertices[index] = v;
  outOfDate = true;
}

void Mesh::setPrimitive(int index, primitive p)
{
  primitives[index] = p;
  outOfDate = true;
}

void Mesh::setWireframe(bool wireframe)
{
  this->wireframe = wireframe;
}

bool Mesh::getWireframe()
{
  return wireframe;
}

void Mesh::setMaterial(Material material)
{
  this->material = material;
}

vertex Mesh::getPosition()
{
  return position;
}

void Mesh::setPosition(vertex position)
{
  this->position = position;
}

void Mesh::apply(std::tuple<std::vector<vertex>, std::vector<primitive>> (*algorithm)(std::vector<vertex> vertices, std::vector<primitive> primitives), int iterations)
{
  for (int i = 0; i < iterations; i++)
  {
    std::tuple<std::vector<vertex>, std::vector<primitive>> result = algorithm(vertices, primitives);
    this->vertices = std::get<0>(result);
    this->primitives = std::get<1>(result);
    std::cout << "Iteration " << i + 1 << " out of " << iterations << std::endl;
  }
  outOfDate = true;
}