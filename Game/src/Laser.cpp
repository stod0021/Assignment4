#include "Laser.h"
#include "Pyramid.h"

Laser::Laser(){}
Laser::~Laser(){
	delete laserPyramid;
	laserPyramid = nullptr;
}

void Laser::Initialize(Graphics *graphics)
{
	laserPyramid = new Pyramid();
	laserPyramid->Initialize(graphics);

	_transform.scale = Vector3(0.1f, 0.1f, 0.1f);

	approachSpeed = 1.0f;
	fired = false;
}

void Laser::Update(float dt)
{
	//Position the enemy cube wherever the enemy is
	laserPyramid->GetTransform().position = _transform.position;
	laserPyramid->GetTransform().scale = _transform.scale;

	if (!isAlive)
	{

	}
	else
	{
		_transform.position.x += dt * approachSpeed * vector.x;
		_transform.position.y += dt * approachSpeed * vector.y;
	}


	if (_transform.position.y < -4.0 && isAlive)
	{
		isAlive = false;
	}




}

void Laser::Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt)
{
	if (isAlive)
	{
		laserPyramid->Draw(graphics, relativeTo, dt);
	}

}