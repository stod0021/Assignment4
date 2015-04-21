/**
* \class Enemy.h
* \brief A Enemy class that represents the Enemy
* that will spawn,track the player and fire once in range.
* \author David Stoddard
* \date April 19, 2015
*/
#pragma once 
#include <GameObject.h>
#include "Laser.h"

class Pyramid;

class Enemy :public GameObject
{
public:
	Enemy();
	~Enemy();
	/**
	* \fn void Game::Initialize()
	* \brief Initialize the enemy to display on screen.
	* \param Graphics *graphics is used to initialize the graphics
	*/
	void Initialize(Graphics *graphics);
	/**
	* \fn void Game::Update(float dt)
	* \brief Updates the enemy to display on screen.
	* \param Graphics *graphics is used to update the graphics
	*/
	void Update(float dt);
	/**
	* \fn void Game::(Graphics *graphics, Matrix4x4 relativeTo, float dt)
	* \brief Draw the enemy to display on screen.
	* \param Graphics *graphics draws the graphics to the screen , Matrix4x4 relativeTo 
	*/
	void Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt);


	bool isAlive;
	float spawnTimer;
	bool fired;
	float moveTimer;
	Laser *_laser;

	Vector3 move;

protected:
	
	Pyramid *_enemyPyramid;
	float _approachProximity; // how close before we stop.
	float _approachSpeed; // units / second

};
