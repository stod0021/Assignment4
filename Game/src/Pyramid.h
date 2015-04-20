/**
* \class Pyramid.h
* \brief A Pyramid class that represents the shape of the vehicle
* which can be used for Player and Enemy class.
* \author David Stoddard
* \date April 19, 2015
*/
#pragma once

#include <GameObject.h>

struct Vertex;

class Pyramid : public GameObject
{
public:
	Pyramid();
	Pyramid(Vector3 position);

  void Initialize(Graphics *graphics);
  void Update(float dt);
  void Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt);

protected:

  Vector3 *vertices;
  Vector4 *colours;

  int size;
  int offset;

  unsigned int* indices;

  void SetVertex(int index, float x, float y, float z, float r, float g, float b, float a);
};