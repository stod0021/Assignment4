#include "Laser.h"
#include "Game.h"
#include <math.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

Laser::Laser() : GameObject()
{

}

Laser::~Laser()
{
	SDL_DestroyTexture(_LaserTexture);
}


void Laser::Initialize(SDL_Renderer * renderer, const char *fileName)
{
	_LaserTexture = IMG_LoadTexture(renderer, fileName);
	if (_LaserTexture == NULL){
		printf(SDL_GetError());
	}

	_LaserPosition =
	{
		_transform.position.x + 10,
		_transform.position.y + 10
	};

	_LaserOffSet =
	{
		10 * sinf(MathUtils::ToRadians(_transform.rotation.x + 90)), //direction correction 90 degrees
		-10 * cosf(MathUtils::ToRadians(_transform.rotation.x + 90))
	};

	_LaserStructure.h = 10;
	_LaserStructure.w = 54;
	_LaserLife = 3;
}

void Laser::Update(float dt)
{

	if (_LaserLive == true)
	{
		_LaserPosition.x += (_LaserOffSet.x * dt * 20);
		_LaserPosition.y += (_LaserOffSet.y * dt * 20);
	}
	if (_LaserLife == 0)
	{
		_LaserLive = false;
		_LaserFired = false;
	}

}

void Laser::Draw(SDL_Renderer *renderer, float dt)
{
	if (_LaserLive == true)
	{
		_centre = { _LaserStructure.w / 2, _LaserStructure.h / 2 };
		_LaserStructure.x = _LaserPosition.x + _LaserOffSet.x - _centre.x;
		_LaserStructure.y = _LaserPosition.y + _LaserOffSet.y - _centre.y;
		SDL_RenderCopyEx(renderer, _LaserTexture, NULL, &_LaserStructure, _transform.rotation.x, &_centre, SDL_FLIP_NONE);
	}

}


void Laser::SetPosition(Vector3 position)
{
	_transform.position = position;
}

Vector3 Laser::GetPosition()
{
	return this->_transform.position;
}


void Laser::SetRotation(float rotation)
{
	_transform.rotation.x = rotation;
}
Vector3 Laser::GetRotation()
{
	return this->_transform.rotation;
}
void Laser::SetLaserIsFired(bool isFired)
{
	_LaserFired = isFired;
}

bool Laser::GetLaserIsFired()
{
	return _LaserFired;
}

void Laser::SetLaserIsLive(bool isLive)
{
	_LaserLive = isLive;
}

bool Laser::GetLaserIsLive()
{
	return _LaserLive;
}

void Laser::SetLaserLife(int life)
{
	_LaserLife = life;
}

int Laser::GetLaserLife()
{
	return _LaserLife;
}

void Laser::SetLaserOffSet(Vector2 offset)
{
	_LaserOffSet = offset;
}
Vector2 Laser::GetLaserOffset()
{
	return _LaserOffSet;
}


Vector2 Laser::GetLaserPos()
{
	return _LaserPosition;
}
