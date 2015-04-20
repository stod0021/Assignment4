/**
* \class Game.h
* \brief A Game class that represents the interactions between game objects
* such as the enemy colliding with player, score points increasing per kill and hit,etc...
* \author David Stoddard
* \date April 19, 2015
*/
#pragma once

#include <GameEngine.h>
#include <SDL_mixer.h>

union SDL_Event;
class Graphics;
class Camera;
class ParallaxSystem;
class ParallaxLayer;
class Player;
class Enemy;


class Game : public GameEngine
{
  friend class GameEngine;

public:
  ~Game();

protected:
  Game();

  /**
  * \fn void Game::InitializeImpl()
  * \brief Initialize main game environment and players is drawn to the screen.
  * \param none.
  */
  void InitializeImpl();
  /**
  * \fn void Game::(float dt)
  * \brief Update the drawn object positions and states.
  * \param float dt is used to keep track of time
  */
  void UpdateImpl(float dt);
  /**
  * \fn void Game::DrawImpl(Graphics *graphics, float dt)
  * \brief Draw graphics implementation
  * \param Graphics *graphics is used to draw all objects on the screen and dt keeps track of time
  */
  void DrawImpl(Graphics *graphics, float dt);
  /**
  * \fn void Game::Reset()
  * \brief Reset the game
  * \param None
  */
  void Reset();
  /**
  * \fn void Game::CalculateDrawOrder(std::vector<GameObject *>& drawOrder)
  * \brief Calculate the order in which objects should be rendered
  * \param std::vector<GameObject *>& drawOrder is used to pass the drawOrder information
  */
  void CalculateDrawOrder(std::vector<GameObject *>& drawOrder);
  /**
  * \fn void Game::CalculateCameraViewpoint(Camera *camera)
  * \brief Calculate the distance of the player camera from the visual display of the game 
  * \param Camera object is passed in order to access special functions of the camera
  */
  void CalculateCameraViewpoint(Camera *camera);

  Camera *_gameCamera;
  Camera *_parallaxCamera;

  ParallaxSystem *_backgroundParallaxSystem;
  ParallaxLayer *_backgroundLayer;

  //The sound effects that will be used
  Mix_Chunk *_explosion;
  Mix_Chunk *_fireLaser;
  Mix_Music *_backgroundMusic;

  Player *_player;
  Enemy *_enemy;
};