#include "Pyramid.h"
#include <SDL_opengl.h>
#include <iostream>
#include <InputManager.h>

struct Vertex
{
  Vector3 position;
  Vector4 color;
};

Pyramid::Pyramid()
{
  _transform.position = Vector3::Zero();
  _transform.rotation = Vector3::Zero();
  _transform.scale = Vector3::One();
}

Pyramid::Pyramid(Vector3 position)
{
  _transform.position = position;
  _transform.rotation = Vector3::Zero();
  _transform.scale = Vector3::One();
}

//Vertex *vertices = nullptr;

void Pyramid::Initialize(Graphics *graphics)
{
  size = 0;

  //vertices = new Vertex[8]();
  vertices = new Vector3[5]();
  colours = new Vector4[5]();

  SetVertex(0, /*pos*/-0.5f, 0.5f, 0.5f,  /*color*/ 1.0f, 0.0f, 0.0f, 1.0f);
  SetVertex(1, /*pos*/0.5f, 0.5f, 0.5f,   /*color*/ 1.0f, 1.0f, 0.0f, 1.0f);
  SetVertex(2, /*pos*/-0.5f, -0.5f, 0.5f, /*color*/ 1.0f, 0.0f, 1.0f, 1.0f);
  SetVertex(3, /*pos*/0.5f, -0.5f, 0.5f,  /*color*/ 0.0f, 1.0f, 0.0f, 1.0f);
  SetVertex(4, /*pos*/-0.5f, 0.5f, -0.5f, /*color*/ 0.0f, 0.0f, 1.0f, 1.0f);

  indices = new unsigned int[6];

  glFrontFace(GL_CW);
  glCullFace(GL_BACK);

  // front
  indices[0] = 0;
  indices[1] = 1;
  indices[2] = 2;

  indices[3] = 3;
  indices[4] = 4;
  indices[5] = 5;

  //indices[6] = 1;
  //indices[7] = 4;
  //indices[8] = 3;

  //indices[9] = 4;
  //indices[10] = 2;
  //indices[11] = 1;
}

void Pyramid::Update(float dt)
{
}

void Pyramid::Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt)
{ 
  GLenum error = glGetError();

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glEnableClientState(GL_INDEX_ARRAY);

  glPushMatrix();
  glTranslatef(_transform.position.x, _transform.position.y, _transform.position.z);
  glRotatef(_transform.rotation.x, 1.0f, 0.0f, 0.0f);
  glRotatef(_transform.rotation.y, 0.0f, 1.0f, 0.0f);
  glRotatef(_transform.rotation.z, 0.0f, 0.0f, 1.0f);

  glScalef(_transform.scale.x, _transform.scale.y, _transform.scale.z);

  glVertexPointer(3, GL_FLOAT, 0, vertices);
  //glVertexPointer(3, GL_FLOAT, sizeof(Vertex), vertices);

  glColorPointer(4, GL_FLOAT, 0, colours);
  //glColorPointer(4, GL_FLOAT, sizeof(Vertex), vertices + sizeof(Vector3));

  int indexCount = sizeof(indices) / sizeof(unsigned int);
  indexCount = 30;
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, indices);

  glPopMatrix();

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_INDEX_ARRAY);
}

void Pyramid::SetVertex(int index, float x, float y, float z, float r, float g, float b, float a)
{
  /*vertices[index].position.x = x;
  vertices[index].position.y = y;
  vertices[index].position.z = z;
  vertices[index].color.x = r;
  vertices[index].color.y = g;
  vertices[index].color.z = b;
  vertices[index].color.w = a;*/

  vertices[index] = Vector3(x, y, z);

  colours[index].x = r;
  colours[index].y = g;
  colours[index].z = b;
  colours[index].w = a;
}