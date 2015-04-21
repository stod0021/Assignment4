#include "Game.h"
#include <GameObject.h>
#include <SDL.h>
#include <math.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <InputManager.h>
#include <Graphics/GraphicsOpenGL.h>

#include "Pyramid.h"
#include <Cameras/Camera.h>
#include <Cameras/PerspectiveCamera.h>
#include <Cameras/OrthographicCamera.h>

#include <Parallax/ParallaxLayer.h>
#include <Parallax/ParallaxSystem.h>
#include <time.h>

#include "Player.h"
#include "Enemy.h"

const char *spaceBackground = "res/space.png";
const char *asteroid = "res/asteroid.png";
// Initializing our static member pointer.
GameEngine* GameEngine::_instance = nullptr;

GameEngine* GameEngine::CreateInstance()
{
  if (_instance == nullptr)
  {
    _instance = new Game();
  }
  return _instance;
}

Game::Game() : GameEngine()
{

}

Game::~Game()
{
  // Clean up our pointers.
  delete _parallaxCamera;
  _parallaxCamera = nullptr;
  
  ParallaxLayer *layerToDelete = nullptr;
  while (_backgroundParallaxSystem->LayerCount() > 0)
  {
    // Delete all of the layers inside of our parallax system.
    layerToDelete = _backgroundParallaxSystem->PopLayer();

    delete layerToDelete;
    layerToDelete = nullptr;
  }

  delete _backgroundParallaxSystem;
  _backgroundParallaxSystem;
}

SDL_Renderer *_renderer;
SDL_Texture *_texture;

void Game::InitializeImpl()
{
	srand(time(NULL));
	int w = 600;
	int h = 600;
	_score = 0;
	_lives = 3;
	SDL_SetWindowTitle(_window, "Raidenish Game - Lives: 0 \t\t Score: 0\t\t");
  SDL_SetWindowSize(_window, w, h);
  float nearPlane = 0.01f;
  float farPlane = 100.0f;
  Vector4 position(0.0f, 0.0f, 3.5f, 0.0f);
  Vector4 lookAt = Vector4::Normalize(Vector4::Difference(Vector4(0.0f, 0.0f, 0.0f, 0.0f), position));
  Vector4 up(0.0f, 1.0f, 0.0f, 0.0f);

  _gameCamera = new PerspectiveCamera(100.0f, 1.0f, nearPlane, farPlane, position, lookAt, up);
 // _gameCamera = new OrthographicCamera(-10.0f, 10.0f, 10.0f, -10.0f, nearPlane, farPlane, position, lookAt, up);

  position = Vector4(0.0f, 0.0f, 3.5f, 0.0f);

  lookAt = Vector4::Normalize(Vector4::Difference(Vector4(0.0f, 0.0f, 0.0f, 0.0f), position));
 // _parallaxCamera = new OrthographicCamera(-10.0f, 10.0f, 10.0f, -10.0f, nearPlane, farPlane, position, lookAt, up);
  _parallaxCamera = new  PerspectiveCamera(100.0f, 1.0f, nearPlane, farPlane, position, lookAt, up);
  _backgroundParallaxSystem = new ParallaxSystem();
  _backgroundParallaxSystemClone = new ParallaxSystem();
  _backgroundParallaxSystemClone2 = new ParallaxSystem();

 Vector3 positionBackground(-0.1f, 0.0f, 0.0f); // Fixes background alignment problem

 Vector2 paralaxSpeed(0.0f, 1.0f);

  _backgroundLayer = new ParallaxLayer(spaceBackground, paralaxSpeed);
  _backgroundLayerClone = new ParallaxLayer(spaceBackground, paralaxSpeed);
  _backgroundLayerClone2 = new ParallaxLayer(spaceBackground, paralaxSpeed);
  _backgroundLayer->GetTransform().position = positionBackground;
  _backgroundLayerClone->GetTransform().position = positionBackground;
  _backgroundLayerClone2->GetTransform().position = positionBackground;
  //for (int i = 0; i < 10; i++){
	  _backgroundParallaxSystem->PushLayer(_backgroundLayer);
	  
		  _backgroundParallaxSystemClone->PushLayer(_backgroundLayerClone);
		  _backgroundLayerClone->GetTransform().position.y = 10;
		  _backgroundParallaxSystemClone2->PushLayer(_backgroundLayerClone2);
		  _backgroundLayerClone2->GetTransform().position.y = 5;
 // _backgroundLayer->GetTransform().position = positionBackground;
  //_backgroundLayer->GetTransform().scale = scaleImage;
  //Generating Player and Enemy
  _player = new Player();
  _enemy = new Enemy[5]();

  _objects.push_back(_player);
  for (int i = 0; i < 5; i++)
  {
	  _objects.push_back(&_enemy[i]);
	  _enemy[i].GetTransform().position.y = 4;
	  _enemy[i].GetTransform().position.x = rand() % 6 - 3;
	  _enemy[i].isAlive = false;
	  _enemy[i].spawnTimer = rand() % 10;
	  if (_enemy[i].GetTransform().position.x < 0) 
	  {
		  _enemy[i].move.x = rand() % 5;
	  }
	  else
	  {
		  _enemy[i].move.x = -(rand() % 5);
	  }
	 
  }


  printf("x%d,y%d\n", _backgroundLayer->GetTransform().position.x, _backgroundLayer->GetTransform().position.y);

  for (auto itr = _objects.begin(); itr != _objects.end(); itr++)
  {
    (*itr)->Initialize(_graphicsObject);
  }
  
  _backgroundParallaxSystem->Initialize(_graphicsObject);
  _backgroundParallaxSystemClone->Initialize(_graphicsObject);
  _backgroundParallaxSystemClone2->Initialize(_graphicsObject);
  //Initialize Sound and Music
  Mix_Init(MIX_INIT_MP3);
 
  int success = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == 0;
  if (success){
	  
	 
		  _explosion = Mix_LoadWAV("res/SoundsCrate-SciFi-Explosion1.wav");
		  if (_explosion == nullptr)
		  {
			  printf("Failed to load %s", _explosion);
			  exit(0);
		  }

		  _fireLaser = Mix_LoadWAV("res/SoundsCrate-SciFi-Laser2.wav");
		  if (_fireLaser == nullptr)
		  {
			  printf("Failed to load %s", _fireLaser);
			  exit(0);
		  }

		  _backgroundMusic = Mix_LoadMUS("res/sc2LostVikings.mp3");
			  if (_backgroundMusic == nullptr)
		  {
			  printf("Failed to load %s", _backgroundMusic);
			  exit(0);
		  }

	Mix_PlayMusic(_backgroundMusic, -1);
	
  }
}

void Game::UpdateImpl(float dt)
{
	InputManager *im = InputManager::GetInstance();
	im->Update(dt);
	//printf("x%f,y%f\n", _backgroundLayer->GetTransform().position.x, _backgroundLayer->GetTransform().position.y);
	_backgroundParallaxSystem->LayerCount();
	
		if (_backgroundLayer[0].GetTransform().position.y < -4 )
		{
			_backgroundLayer[0].GetTransform().position.y =10;
		}
		if (_backgroundLayer[1].GetTransform().position.y < -6)
		{
			_backgroundLayer[1].GetTransform().position.y = 8;
		}
		if (_backgroundLayer[2].GetTransform().position.y < -7)
		{
			_backgroundLayer[2].GetTransform().position.y = 7;
		}
		if (_backgroundLayer[4].GetTransform().position.y < -8)
		{
			_backgroundLayer[4].GetTransform().position.y = 6;
		}
		if (_backgroundLayer[5].GetTransform().position.y < -9)
		{
			_backgroundLayer[5].GetTransform().position.y = 15;
		}
		if (_backgroundLayer[6].GetTransform().position.y < -10)
		{
			_backgroundLayer[6].GetTransform().position.y = 5;
		}



		if (_backgroundLayerClone[0].GetTransform().position.y < -4)
		{
			_backgroundLayerClone[0].GetTransform().position.y = 10;
		}
		if (_backgroundLayerClone[1].GetTransform().position.y < -6)
		{
			_backgroundLayerClone[1].GetTransform().position.y = 8;
		}
		if (_backgroundLayerClone[2].GetTransform().position.y < -7)
		{
			_backgroundLayerClone[2].GetTransform().position.y = 7;
		}
		if (_backgroundLayerClone[4].GetTransform().position.y < -8)
		{
			_backgroundLayerClone[4].GetTransform().position.y = 6;
		}
		if (_backgroundLayerClone[5].GetTransform().position.y < -9)
		{
			_backgroundLayerClone[5].GetTransform().position.y = 15;
		}
		if (_backgroundLayerClone[6].GetTransform().position.y < -10)
		{
			_backgroundLayerClone[6].GetTransform().position.y = 5;
		}

		if (_backgroundLayerClone2[0].GetTransform().position.y < -4)
		{
			_backgroundLayerClone2[0].GetTransform().position.y = 10;
		}
		if (_backgroundLayerClone2[1].GetTransform().position.y < -6)
		{
			_backgroundLayerClone2[1].GetTransform().position.y = 8;
		}
		if (_backgroundLayerClone2[2].GetTransform().position.y < -7)
		{
			_backgroundLayerClone2[2].GetTransform().position.y = 7;
		}
		if (_backgroundLayerClone2[4].GetTransform().position.y < -8)
		{
			_backgroundLayerClone2[4].GetTransform().position.y = 6;
		}
		if (_backgroundLayerClone2[5].GetTransform().position.y < -9)
		{
			_backgroundLayerClone2[5].GetTransform().position.y = 15;
		}
		if (_backgroundLayerClone2[6].GetTransform().position.y < -10)
		{
			_backgroundLayerClone2[6].GetTransform().position.y = 5;
		}

		//printf("y: %.2f\n", _backgroundLayer[0].GetTransform().position.y);
	
	
  //if (_player1.GetTankIsDead() == false){

	 // // Check for user input.
	  if (im->IsKeyDown(SDLK_UP) == true) // move forward towards the positive direction
	  {
		  if (_player->_playerAlive)
		  {
			  printf("PositionY:%f\n", _player->GetTransform().position.y);
			  //_player->GetTransform().position.z += _player->GetPlayerSpeed() * dt;
			  _player->GetTransform().position.y += _player->GetPlayerSpeed() * dt;
		  }
		 
	  }
	  if (im->IsKeyDown(SDLK_DOWN) == true) // move forward towards the negative direction
	  {
		  if (_player->_playerAlive)
		  {
			  printf("PositionY:%f\n", _player->GetTransform().position.y);
			  //_player->GetTransform().position.z -= _player->GetPlayerSpeed() * dt;
			  _player->GetTransform().position.y -= _player->GetPlayerSpeed() * dt;
		  }
	  }
	  if (im->IsKeyDown(SDLK_LEFT) == true) // rotate 10 degrees to the left
	  {
		  if (_player->_playerAlive)
		  {
			  printf("PositionZ:%f\n", _player->GetTransform().position.z);
			  //  _player->GetTransform().position.z += _player->GetPlayerSpeed() * dt;
			  _player->GetTransform().position.x -= _player->GetPlayerSpeed() * dt;
		  }


	  }
	  if (im->IsKeyDown(SDLK_RIGHT) == true) // rotate 10 degrees to the right
	  {
		  if (_player->_playerAlive)
		  {
			  printf("PositionZ:%f\n", _player->GetTransform().position.z);
			  //  _player->GetTransform().position.z -= _player->GetPlayerSpeed() * dt;
			  _player->GetTransform().position.x += _player->GetPlayerSpeed() * dt;
		  }
	  }

	  if (_player->GetTransform().position.x > 3.5)
	  {
		  _player->GetTransform().position.x = 3.5;
	  }
	  if (_player->GetTransform().position.x < -3.5)
	  {
		  _player->GetTransform().position.x = -3.5;
	  }
	  if (_player->GetTransform().position.y > 3.0)
	  {
		  _player->GetTransform().position.y = 3.0;
	  }
	  if (_player->GetTransform().position.y < -3.0)
	  {
		  _player->GetTransform().position.y = -3.0;
	  }


	  if (_player->_playerAlive){
		  if (im->IsKeyDown(SDLK_SPACE) == true)
		  {
			  if (!_player->laser->isAlive)
			  {
				  _player->laser->isAlive = true;
				  _player->laser->GetTransform().position = _player->GetTransform().position;
				  Mix_PlayChannel(-1, _fireLaser, 0);
			  }	
		  }
	  }

	  //Enemy Fire
	  for (int i = 0; i < 5; i++)
	  {
		  if (_enemy[i].isAlive)
		  {
			  if (!_enemy[i]._laser->isAlive && _enemy[i].moveTimer > 3.0f && !_enemy[i].fired)
			  {
				  _enemy[i].fired = true;
				  _enemy[i]._laser->GetTransform().position = _enemy[i].GetTransform().position;
				  _enemy[i]._laser->isAlive = true;
				  _enemy[i]._laser->vector =
					  Vector3
					  (
					  _player->GetTransform().position.x - _enemy[i].GetTransform().position.x,
					  _player->GetTransform().position.y - _enemy[i].GetTransform().position.y,
					  0
					  );
				  Mix_PlayChannel(-1, _fireLaser, 0);
				  printf("fire!\n");
			  }
		  }
		  
	  }

	  if (_player->laser->isAlive && _player->laser->GetTransform().position.y > 4)
	  {
		  _player->laser->isAlive = false;
	  }

	 
	  
		  for (int i = 0; i < 5; i++)
		  {
			  //Enemy laser vs Player
			  if (_player->_playerAlive)
			  {
				  if (_enemy[i]._laser->isAlive)
				  {
					  if (
						  ((_enemy[i]._laser->GetTransform().position.x - _player->GetTransform().position.x) < 0.01f) &&
						  ((_enemy[i]._laser->GetTransform().position.y - _player->GetTransform().position.y) < 0.01f)
						  )
					  {
						  Mix_PlayChannel(-1, _explosion, 0);
						  _player->_playerAlive = false;
						  _enemy[i]._laser->isAlive = false;
						  _lives--;
						  sprintf(_buffer, "Raidenish Game - Lives: %d \t\t Score: %d\t\t", _lives, _score);
						  SDL_SetWindowTitle(_window, _buffer);
						  _player->_changed = false;
					  }
				  }
			  }

			  //Player laser vs Enemy
			  if (_player->laser->isAlive)
			  {
				  if (_enemy[i].isAlive)
				  {
					  if (
						  ((_player->laser->GetTransform().position.x - _enemy[i].GetTransform().position.x) < 0.01f) &&
						  ((_player->laser->GetTransform().position.y - _enemy[i].GetTransform().position.y) < 0.01f)
						  )
					  {

						  _enemy[i].isAlive = false;
						  _player->laser->isAlive = false;
						  _score += 10;
						  sprintf(_buffer, "Raidenish Game - Lives: %d \t\t Score: %d\t\t", _lives, _score);
						  SDL_SetWindowTitle(_window, _buffer);
						  _enemy[i].GetTransform().position.y = 4;
						  _enemy[i].GetTransform().position.x = rand() % 6 - 3;
					  }
				  }
				 
			  }


		  }
		  //gameover scenario
		  if (_lives == 0)
		  {
			  sprintf(_buffer, "Raidenish Game - Lives: %d \t\t Score: %d\t\t", _lives, _score);
			  SDL_SetWindowTitle(_window, _buffer);
			  printf("Game Over! Would you like to play again? [Y/N]\n");
			  while (_again == false)
			  {
				  scanf("%c", &_playAgain);
				  if (_playAgain == 'Y' || _playAgain == 'y')
				  {
					  _lives = 5;
					  _score = 0;
					  _again = true;
				  }
				  else if (_playAgain == 'N' || _playAgain == 'n')
				  {
					  exit(EXIT_SUCCESS);
				  }
				  else
				  {
					  printf("Would you like to play again? [Y/N]\n");
				  }
				  scanf("%c", &_playAgain);
			  }

			  _again = false;
		  }








	  for (auto itr = _objects.begin(); itr != _objects.end(); itr++)
  {
    (*itr)->Update(dt);
  }
  _backgroundParallaxSystem->Update(Vector2::Zero(), dt);
  _backgroundParallaxSystemClone->Update(Vector2::Zero(), dt);
  _backgroundParallaxSystemClone2->Update(Vector2::Zero(), dt);
}

void Game::DrawImpl(Graphics *graphics, float dt)
{
  std::vector<GameObject *> renderOrder = _objects;
  //CalculateDrawOrder(renderOrder);

  // Draw parallax backgrounds
  glPushMatrix();
  {
    CalculateCameraViewpoint(_parallaxCamera);

    _backgroundParallaxSystem->Draw(graphics, _gameCamera->GetProjectionMatrix(), dt);
	_backgroundParallaxSystemClone->Draw(graphics, _gameCamera->GetProjectionMatrix(), dt);
	_backgroundParallaxSystemClone2->Draw(graphics, _gameCamera->GetProjectionMatrix(), dt);
  }
  glPopMatrix();

  // Draw scenery on top.
  glPushMatrix();
  {
    glClear(GL_DEPTH_BUFFER_BIT);
    CalculateCameraViewpoint(_gameCamera);

    for (auto itr = renderOrder.begin(); itr != renderOrder.end(); itr++)
    {
      (*itr)->Draw(graphics, _gameCamera->GetProjectionMatrix(), dt);
    }
  }
  glPopMatrix();
}

void Game::CalculateDrawOrder(std::vector<GameObject *>& drawOrder)
{
  // SUPER HACK GARBAGE ALGO.
  drawOrder.clear();

  auto objectsCopy = _objects;
  auto farthestEntry = objectsCopy.begin();
  while (objectsCopy.size() > 0)
  {
    bool entryFound = true;
    for (auto itr = objectsCopy.begin(); itr != objectsCopy.end(); itr++)
    {
      if (farthestEntry != itr)
      {
        if ((*itr)->GetTransform().position.y < (*farthestEntry)->GetTransform().position.y)
        {
          entryFound = false;
          farthestEntry = itr;
          break;
        }
      }
    }

    if (entryFound)
    {
      GameObject *farthest = *farthestEntry;

      drawOrder.push_back(farthest);
      objectsCopy.erase(farthestEntry);
      farthestEntry = objectsCopy.begin();
    }
  }
}

void Game::CalculateCameraViewpoint(Camera *camera)
{
  camera->Apply();

  Vector4 xAxis(1.0f, 0.0f, 0.0f, 0.0f);
  Vector4 yAxis(0.0f, 1.0f, 0.0f, 0.0f);
  Vector4 zAxis(0.0f, 0.0f, 1.0f, 0.0f);

  Vector3 cameraVector(camera->GetLookAtVector().x, camera->GetLookAtVector().y, camera->GetLookAtVector().z);
  Vector3 lookAtVector(0.0f, 0.0f, -1.0f);

  Vector3 cross = Vector3::Normalize(Vector3::Cross(cameraVector, lookAtVector));
  float dot = MathUtils::ToDegrees(Vector3::Dot(lookAtVector, cameraVector));

  glRotatef(cross.x * dot, 1.0f, 0.0f, 0.0f);
  glRotatef(cross.y * dot, 0.0f, 1.0f, 0.0f);
  glRotatef(cross.z * dot, 0.0f, 0.0f, 1.0f);

  glTranslatef(-camera->GetPosition().x, -camera->GetPosition().y, -camera->GetPosition().z);
}