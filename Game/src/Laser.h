/**
* \class Laser.h
* \brief A Laser class that represents the Laser
* that is fired from the player or enemy.
* \author David Stoddard
* \date April 19, 2015
*/
#pragma once
#include "GameObject.h"
#include <SDL.h>

struct SDL_Surface;
struct SDL_Window;
struct SDL_Texture;

class Laser : public GameObject
{
public:
	Laser();
	~Laser();
	
	/**
	* \fn void Laser::Initialize(SDL_Renderer * renderer, const char *fileName)
	* \brief Initializes Laser for player 1 or 2.
	* \param SDL_Renderer is used to draw the laser, while the fileName is the path to the bitmap applied to the texture.
	*/
	void Initialize(SDL_Renderer * renderer, const char *fileName);
	/**
	* \fn void Laser::Update(float dt)
	* \brief Checks if Laser is alive and updates the Laser accordingly
	* \param Float delta time keeps track of time passed.
	*/
	void Update(float dt);
	/**
	* \fn void Laser::Draw(SDL_Renderer *renderer, float dt)
	* \brief Draws the Laser
	* \param SDL_Renderer is used to draw the laser, float is delta time.
	*/
	 void Draw(SDL_Renderer *renderer, float dt);
	/**
	* \fn void Laser::SetPosition(Vector3 position)
	* \brief Set the current position of Laser
	* \param Vector3 position applied.
	*/
	void SetPosition(Vector3 position);
	/**
	* \fn Vector3 Laser::GetPosition()
	* \brief Gets the current position of Laser
	* \param n/a
	*/
	Vector3 GetPosition();
	/**
	* \fn void Laser::SetLaserIsLive(SDL_Renderer *renderer, float dt)
	* \brief Draws the Laser
	* \param SDL_Renderer is used to draw the laser, float is delta time.
	*/
	void SetLaserIsLive(bool isLive);
	/**
	* \fn bool Laser::GetLaserIsLive()
	* \brief Check if Laser is alive.
	* \param n/a
	*/
	bool GetLaserIsLive();
	/**
	* \fn void Laser::SetLaserLife(int life)
	* \brief Sets Laser life is set.
	* \param Int life is applied.
	*/
	void SetLaserLife(int life);
	/**
	* \fn int Laser::GetLaserLife(SDL_Renderer *renderer, float dt)
	* \brief Gets the remaining life of the Laser
	* \param n/a
	*/
	int GetLaserLife();
	/**
	* \fn void Laser::SetLaserIsFired(bool isFired)
	* \brief Sets Laser isFired or not fired.
	* \param Bool isFired applies true or false.
	*/
	void SetLaserIsFired(bool isFired);
	/**
	* \fn bool Laser::GetLaserIsFired()
	* \brief Check if Laser is fired.
	* \param n/a
	*/
	bool GetLaserIsFired();
	/**
	* \fn void Laser::SetRotation(float rotation)
	* \brief Set rotation of the Laser
	* \param Float rotation applied.
	*/
	void SetRotation(float rotation);
	/**
	* \fn Vector3 Laser::GetRotation()
	* \brief Get rotation of Laser
	* \param n/a
	*/
	Vector3 GetRotation();
	/**
	* \fn void Laser::SetLaserOffSet(Vector2 offset)
	* \brief Set Laser offset
	* \param Vector2 offset being applied.
	*/
	void SetLaserOffSet(Vector2 offset);
	/**
	* \fn Vector2 Laser::GetLaserOffset()
	* \brief Gets the Laser offset.
	* \param n/a
	*/
	Vector2 GetLaserOffset();
	/**
	* \fn Vector2 Laser::GetLaserPos()
	* \brief Gets the Laser position
	* \param n/a
	*/
	Vector2 GetLaserPos();


protected:
	Vector2 _LaserPosition;
	Vector2 _LaserOffSet;
	SDL_Texture *_LaserTexture;
	SDL_Rect _LaserStructure;
	SDL_Point _centre;
	int _LaserLife;
	bool _LaserFired = false;
	bool _LaserLive = false;
};