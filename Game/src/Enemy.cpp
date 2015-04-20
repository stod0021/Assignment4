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

	_transform.scale = Vector3(0.5f, 0.5f, 0.5f);
	float _approachProximity = 0.0f; // how close before we stop.
	float _approachSpeed = 0.0f; // units / second
}

void Enemy::Update(float dt)
{
	//Position the enemy cube wherever the enemy is.
	_enemyPyramid->GetTransform().position = _transform.position;
	_enemyPyramid->GetTransform().scale = _transform.scale;

}

void Enemy::Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt)
{
	_enemyPyramid->Draw(graphics, relativeTo, dt);
}
//
//void Enemy::SetApproachSpeed(float speed){
//
//	_approachSpeed = speed;
//}
//
//void Enemy::SetApproachProximity(float proximity)
//{
//	_approachProximity = proximity;
//}

//bool Enemy::Approach(Vector3 destination, float dt)
//{
//	bool didApproach = false;
//	//Find the distance from our destination 
//	Vector3 distanceVector = Vector3::Difference(destination, _transform.position); //destination and starting point
//
//	Vector3 directionVector = distanceVector;
//
//	float distance = Vector3::Magnitude(distanceVector);
//
//	//If we're further out than our approach proximity, move closer.
//	if (distance > _approachProximity){
//
//		if (distance - _approachProximity > 1.0f)
//		{
//			directionVector = Vector3::Normalize(distanceVector);
//		}
//
//		//Calculate how fast we should go based on how far away we are.
//		directionVector.x *= _approachSpeed * dt;
//		directionVector.y *= _approachSpeed * dt;
//		directionVector.z *= _approachSpeed * dt;
//
//		// Adding our direction to our position
//		_transform.position.x += directionVector.x;
//		_transform.position.y += directionVector.y;
//		_transform.position.z += directionVector.z;
//
//		//More readable than just returning here
//		didApproach = true;
//	}
//
//	return didApproach;
//}