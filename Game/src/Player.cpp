#include "Player.h"
#include "Pyramid.h"

Player::~Player()
{
}

void Player::Initialize(Graphics *graphics)
{
	_playerPyramid = new Pyramid();
	_playerPyramid->Initialize(graphics);
	_transform.scale = Vector3(1.0f, 1.0f, 1.0f);
	_transform.rotation = Vector3(2.0f, 2.0f, 0.0f);
	_playerSpeed = 10.0f;
	

}

void Player::Update(float dt)
{
	_playerPyramid->GetTransform().position = _transform.position;
	_playerPyramid->GetTransform().scale = _transform.scale;
	_playerPyramid->GetTransform().rotation = _transform.rotation;
}

void Player::Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt)
{
	_playerPyramid->Draw(graphics, relativeTo, dt);
}

void Player::SetPlayerSpeed(float speed)
{
	_playerSpeed = speed;
}

float Player::GetPlayerSpeed()
{
	return _playerSpeed;
}

Vector2 Player::GetDirectionVector()
{
	return _playerDirectionVector;
}

void Player::SetDirectionVector(Vector2 direction)
{
	_playerDirectionVector = direction;
}
void Player::SetPlayerIsDead(bool isDead)
{
	_playerIsDead = isDead;
}
bool Player::GetPlayerIsDead()
{
	return _playerIsDead;
}
void Player::SetPlayerDeadTime(float time)
{
	_playerTimeDead = time;
}