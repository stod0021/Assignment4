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
	int w = 800;
	int h = 600;
  SDL_SetWindowTitle(_window, "Raidenish Game");
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

 /* Vector3 scaleImage(2.0f, 2.0f, 0.0f);
  Vector3 positionBackground(0.0f, 0.0f ,0.0f);*/
  Vector2 paralaxSpeed(10.0f, 5.0f);

  _backgroundLayer = new ParallaxLayer(spaceBackground, paralaxSpeed);
 // _backgroundLayer->GetTransform().position = positionBackground;
  //_backgroundLayer->GetTransform().scale = scaleImage;
  _backgroundParallaxSystem->PushLayer(_backgroundLayer);

  //Generating Player and Enemy
  _player = new Player();
//  _enemy = new Enemy();

  _objects.push_back(_player);
  //_objects.push_back(_enemy);

  printf("x%d,y%d\n", _backgroundLayer->GetTransform().position.x, _backgroundLayer->GetTransform().position.y);

  for (auto itr = _objects.begin(); itr != _objects.end(); itr++)
  {
    (*itr)->Initialize(_graphicsObject);
  }
  
  _backgroundParallaxSystem->Initialize(_graphicsObject);
  //Initialize Sound and Music
  Mix_Init(MIX_INIT_MP3);
 
  int success = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == 0;
  if (success){
	  
	//  _explosion = Mix_LoadWAV("");
	///*  if (_explosion == nullptr)
	//  {
	//	  printf("Failed to load %s", _explosion);
	//	  exit(0);
	//  }*/
	  
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
	printf("x%d,y%d\n", _backgroundLayer->GetTransform().position.x, _backgroundLayer->GetTransform().position.y);

  //if (_player1.GetTankIsDead() == false){

	 // // Check for user input.
	  if (im->IsKeyDown(SDLK_UP) == true) // move forward towards the positive direction
	  {
		  printf("PositionY:%f\n", _player->GetTransform().position.y);
		  //_player->GetTransform().position.z += _player->GetPlayerSpeed() * dt;
		  _player->GetTransform().position.y += _player->GetPlayerSpeed() * dt;
	  }
	  if (im->IsKeyDown(SDLK_DOWN) == true) // move forward towards the negative direction
	  {
		  printf("PositionY:%f\n", _player->GetTransform().position.y);
		  //_player->GetTransform().position.z -= _player->GetPlayerSpeed() * dt;
		  _player->GetTransform().position.y -= _player->GetPlayerSpeed() * dt;
	  }
	  if (im->IsKeyDown(SDLK_LEFT) == true) // rotate 10 degrees to the left
	  {
		  printf("PositionZ:%f\n",_player->GetTransform().position.z);
		//  _player->GetTransform().position.z += _player->GetPlayerSpeed() * dt;
		  _player->GetTransform().position.x -= _player->GetPlayerSpeed() * dt;


	  }
	  if (im->IsKeyDown(SDLK_RIGHT) == true) // rotate 10 degrees to the right
	  {
		  printf("PositionZ:%f\n", _player->GetTransform().position.z);
		//  _player->GetTransform().position.z -= _player->GetPlayerSpeed() * dt;
		  _player->GetTransform().position.x += _player->GetPlayerSpeed() * dt;
	  }

	  if (_player->GetPlayerIsDead() == false){
		  if (im->IsKeyDown(SDLK_KP_0) == true)
		  {
		//	  _player->L
		  }
	  }
  //}
	//_backgroundLayer->
  for (auto itr = _objects.begin(); itr != _objects.end(); itr++)
  {
    (*itr)->Update(dt);
  }
  _backgroundParallaxSystem->Update(Vector2::Zero(), dt);
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