/**
* \class Player.h
* \brief A player class that represents the player
* that can move a player, fire Lasers and die from enemy fire.
* \author David Stoddard
* \date April 19, 2015
*/
#pragma once

#include <GameObject.h>
#include <vector>
#include "Laser.h"

class Pyramid;
class Laser;

class Player : public GameObject
{
public:
	~Player();
	//Laser laser;

	/**
	* \fn void Game::Initialize()
	* \brief Initialize the player to display on screen.
	* \param Graphics *graphics is used to initialize the graphics
	*/
	void Initialize(Graphics *graphics);
	/**
	* \fn void Game::Update(float dt)
	* \brief Updates the player to display on screen.
	* \param Graphics *graphics is used to update the graphics
	*/
	void Update(float dt);
	/**
	* \fn void Game::(Graphics *graphics, Matrix4x4 relativeTo, float dt)
	* \brief Draw the player to display on screen.
	* \param Graphics *graphics draws the graphics to the screen , Matrix4x4 relativeTo
	*/
	void Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt);

	/**
	* \fn void Player::SetPlayerSpeed(int speed)
	* \brief A function that is used to set the speed of the player
	* \return speed The speed to set the player to.
	*/
	void SetPlayerSpeed(float speed);
	/**
	* \fn int Player::GetPlayerSpeed()
	* \brief A function that is used to set the speed of the player
	* \return int The speed the player is traveling at.
	*/
	float GetPlayerSpeed();
	/**
	* \fn Vector3 Player::GetDirectionVector()
	* \brief A function that is used to get the direction of the player
	* \return Vector3 The direction the player is traveling
	*/
	Vector2 GetDirectionVector();
	/**
	* \fn void Player::SetDirectionVector(Vector3 direction)
	* \brief A function that is used to set the direction the player is traveling
	* \return Vector3 The travel direction to set the player to
	*/
	void SetDirectionVector(Vector2 direction);
	/**
	* \fn void Player::SetPlayerIsDead(bool isDead)
	* \brief Sets the deathstate of the player.
	* \param Bool isDead sets player is dead or not.
	*/
	void SetPlayerIsDead(bool isDead);
	/**
	* \fn bool Player::GetPlayerIsDead()
	* \brief Checks if player is dead
	* \return boolean
	*/
	bool GetPlayerIsDead();
	/**
	* \fn void Player::SetPlayerDeadTime(float time)
	* \brief Sets Player time to be dead.
	* \param Float time is the duration of the player's death.
	*/
	void SetPlayerDeadTime(float time);

	//bool fired = false;
	Laser *laser;
	float _playerTimeDead;
	float _playerSpeed;
	bool _playerAlive = true;
	bool _changed = false;

protected:

	Vector2 _playerDirectionVector;

	Pyramid *_playerPyramid;
};