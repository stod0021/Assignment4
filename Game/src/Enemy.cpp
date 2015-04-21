#include "Enemy.h"
#include "Pyramid.h"

Enemy::Enemy(){}
Enemy::~Enemy(){
	delete _enemyPyramid;
	_enemyPyramid = nullptr;
}

void Enemy::Initialize(Graphics *graphics)
{
	
	_enemyPyramid = new Pyramid();
	_enemyPyramid->Initialize(graphics);
	_laser = new Laser();
	_laser->Initialize(graphics);

	_transform.scale = Vector3(0.5f, 0.5f, 0.5f);
	
	_approachSpeed = 2.0f;
	fired = false;




}

void Enemy::Update(float dt)
{
	//Position the enemy cube wherever the enemy is.
	_enemyPyramid->GetTransform().position = _transform.position;
	_enemyPyramid->GetTransform().scale = _transform.scale;


	if (!isAlive)
	{
		spawnTimer -= dt;
	}
	else
	{
		_transform.position.y -= dt * _approachSpeed;
		_transform.position.x += dt* move.x * 0.25;
		moveTimer += _approachSpeed*dt;
	}

	if (spawnTimer < 0)
	{
		spawnTimer = 10;
		moveTimer = 0.0f;
		isAlive = true;
	}

	if (_transform.position.y < -4.0 && isAlive)
	{
		isAlive = false;
		moveTimer = 0.0f;
		_transform.position.y = 4.0;
		fired = false;
	}
	
	if (_laser->isAlive)
	{
		_laser->Update(dt);
	}



}

void Enemy::Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt)
{
	_enemyPyramid->Draw(graphics, relativeTo, dt);
	if (_laser->isAlive)
	{
		_laser->Draw(graphics, relativeTo, dt);
	}	
}