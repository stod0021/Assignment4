/**
* \class Laser.h
* \brief A Laser class that represents the Laser
* that is fired from the player or enemy.
* \author David Stoddard
* \date April 19, 2015
*/
#pragma once 
#include <GameObject.h>

class Pyramid;

class Laser :public GameObject
{
public:
	Laser();
	~Laser();
	/**
	* \fn void Game::Initialize()
	* \brief Initialize the laser to display on screen.
	* \param Graphics *graphics is used to initialize the graphics
	*/
	void Initialize(Graphics *graphics);
	/**
	* \fn void Laser::Update(float dt)
	* \brief Updates the laser to display on screen.
	* \param Graphics *graphics is used to update the graphics
	*/
	void Update(float dt);
	/**
	* \fn void Laser::(Graphics *graphics, Matrix4x4 relativeTo, float dt)
	* \brief Draw the laser to display on screen.
	* \param Graphics *graphics draws the graphics to the screen , Matrix4x4 relativeTo
	*/
	void Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt);



	bool isAlive = false;
	float spawnTimer;
	bool fired = false;
	float moveTimer;
	Pyramid *laserPyramid;
	Vector3 vector;
	float approachSpeed; // units / second
	float approachProximity; // how close before we stop.	
};
