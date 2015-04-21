#include "Player.h"
#include "Pyramid.h"

Player::~Player()
{
}

void Player::Initialize(Graphics *graphics)
{
	_playerPyramid = new Pyramid();
	_playerPyramid->Initialize(graphics);
	laser = new Laser();
	laser->Initialize(graphics);
	laser->isAlive = false;


	_transform.scale = Vector3(1.0f, 1.0f, 1.0f);
	_transform.rotation = Vector3(2.0f, 2.0f, 0.0f);
	_playerSpeed = 10.0f;
	_playerTimeDead = 3.0f;
	
	laser->vector = Vector3(0, 1, 0);
	laser->approachSpeed = 10.0f;
}

void Player::Update(float dt)
{
	_playerPyramid->GetTransform().position = _transform.position;
	_playerPyramid->GetTransform().scale = _transform.scale;
	_playerPyramid->GetTransform().rotation = _transform.rotation;

	if (laser->isAlive)
	{
		laser->Update(dt);
	}

	if (!_playerAlive)
	{
		_playerTimeDead -= dt;
	}
	if (_playerTimeDead < 0.0f)
	{
		_playerAlive = true;
		_playerTimeDead = 3.0f;
		_changed = false;
		_transform.position = Vector3(0, -2.5, 0);
	}
}

void Player::Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt)
{
	if (!_changed)
	{
		if (!_playerAlive)
		{
			_playerPyramid->SetVertex(0, /*pos*/-0.5f, 0.5f, 0.5f,  /*color*/ 0.0f, 0.0f, 0.0f, 1.0f);
			_playerPyramid->SetVertex(1, /*pos*/0.5f, 0.5f, 0.5f,   /*color*/ 0.0f, 0.0f, 0.0f, 1.0f);
			_playerPyramid->SetVertex(2, /*pos*/-0.5f, -0.5f, 0.5f, /*color*/ 0.0f, 255, 0.0f, 1.0f);
			_playerPyramid->SetVertex(3, /*pos*/0.5f, -0.5f, 0.5f,  /*color*/ 0.0f, 0.0f, 0.0f, 1.0f);
			_playerPyramid->SetVertex(4, /*pos*/-0.5f, 0.5f, -0.5f, /*color*/ 0.0f, 0.0f, 0.0f, 1.0f);
		}
		else
		{

			_playerPyramid->SetVertex(0, /*pos*/-0.5f, 0.5f, 0.5f,  /*color*/ 1.0f, 0.0f, 0.0f, 1.0f);
			_playerPyramid->SetVertex(1, /*pos*/0.5f, 0.5f, 0.5f,   /*color*/ 1.0f, 1.0f, 0.0f, 1.0f);
			_playerPyramid->SetVertex(2, /*pos*/-0.5f, -0.5f, 0.5f, /*color*/ 1.0f, 0.0f, 1.0f, 1.0f);
			_playerPyramid->SetVertex(3, /*pos*/0.5f, -0.5f, 0.5f,  /*color*/ 0.0f, 1.0f, 0.0f, 1.0f);
			_playerPyramid->SetVertex(4, /*pos*/-0.5f, 0.5f, -0.5f, /*color*/ 0.0f, 0.0f, 1.0f, 1.0f);
		}
		_changed = true;
	}
	
	_playerPyramid->Draw(graphics, relativeTo, dt);
	if (laser->isAlive)
	{
		laser->Draw(graphics, relativeTo, dt);
	}
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
void Player::SetPlayerIsDead(bool isAlive)
{
	_playerAlive = isAlive;
}
bool Player::GetPlayerIsDead()
{
	return _playerAlive;
}
void Player::SetPlayerDeadTime(float time)
{
	_playerTimeDead = time;
}