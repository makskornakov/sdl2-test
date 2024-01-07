#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>

Map *map;
Manager manager;

SDL_Renderer *Game::renderer = nullptr;

SDL_Event Game::event;

AssetManager *Game::assets = new AssetManager(&manager);

// std::vector<ColliderComponent *> Game::colliders;

SDL_Rect Game::camera = {0, 0, 800, 640};

bool Game::isRunning = false;

auto &newPlayer(manager.addEntity());
auto &label(manager.addEntity());
auto &button(manager.addEntity());

// player colider display
// auto &playerCollider(manager.addEntity());

// auto &wall(manager.addEntity());

// const char *mapFile = "../Resources/terrain_ss.png";

// auto &tiles(manager.getGroup(groupMap));
// auto &players(manager.getGroup(groupPlayers));
// auto &enemies(manager.getGroup(groupEnemies));

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char *title, int width, int height, bool fullScreen, const std::string &executablePath)
{
  int flags = 0;

  if (fullScreen)
  {
    flags = SDL_WINDOW_FULLSCREEN;
  }

  if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
  {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer)
    {
      SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
    }

    isRunning = true;
  }

  if (TTF_Init() == -1)
  {
    std::cout << "Error : SDL_TTF" << std::endl;
  }

  assets->AddTexture("terrain", "../Resources/terrain_ss.png");
  assets->AddTexture("player", "../Resources/player_anims.png");
  assets->AddTexture("projectile", "../Resources/projectile.png");

  assets->AddFont("Tektur", "../Resources/Tektur-static.ttf", 16);

  map = new Map("terrain", 2, 32, executablePath);
  // load map from file
  // map->LoadMap("../Resources/p16x16.txt", 16, 16);
  map->LoadMap("../Resources/map.map", 25, 20, executablePath);

  // ECS implementation

  // TransformComponent(float x, float y, int h, int w, float sc)
  newPlayer.addComponent<TransformComponent>(780, 350, 32, 32, 2.5f);
  newPlayer.addComponent<SpriteComponent>("player", true);
  newPlayer.addComponent<KeyboardController>();
  newPlayer.addComponent<ColliderComponent>("player");
  newPlayer.addGroup(Game::groupPlayers);

  SDL_Color setTextColor = {255, 255, 255, 255};

  label.addComponent<UILabel>(10, 10, "Test String", "Tektur", setTextColor);

  SDL_Color setButtonColor = {255, 0, 0, 255};
  button.addComponent<UIButton>("stop", 280, 20, 60, 30, "Stop", "Tektur", setButtonColor, []()
                                { Game::isRunning = false; });
  button.getComponent<UIButton>().init();

  assets->CreateProjectile(Vector2D(600, 100), Vector2D{2, 0}, 200, 2, "projectile");

  // TileComponent(int srcX, int srcY, int xPos, int yPos, int tSize, int tScale, const char *path)
  // playerCollider.addComponent<TileComponent>(0, 0, 0, 0, 32, 1, "../Resources/collider.png");
  // playerCollider.addComponent<ColliderComponent>("terrain");
  // playerCollider.addComponent<ColliderComponent>("player");
}

auto &tiles(manager.getGroup(Game::groupMap));
auto &players(manager.getGroup(Game::groupPlayers));
auto &colliders(manager.getGroup(Game::groupColliders));
auto &projectiles(manager.getGroup(Game::groupProjectiles));

void Game::handleEvents()
{

  SDL_PollEvent(&event);

  switch (event.type)
  {
  case SDL_QUIT:
    isRunning = false;
    break;
  default:
    break;
  }
}

void Game::update()
{

  SDL_Rect playerCol = newPlayer.getComponent<ColliderComponent>().collider;
  Vector2D playerPos = newPlayer.getComponent<TransformComponent>().position;

  std::stringstream ss;
  ss << "Player position: " << playerPos;
  label.getComponent<UILabel>().setLabelText(ss.str(), "Tektur");

  manager.refresh();
  manager.update();

  // button management (if clicked, quit game)
  button.getComponent<UIButton>().update();

  // set colider position to player position
  // playerCollider.getComponent<TransformComponent>().position = playerPos;
  // draw player colider
  // playerCollider.update();
  // playerCollider.draw();

  for (auto &c : colliders)
  {
    SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
    if (Collision::AABB(cCol, playerCol))
    {
      newPlayer.getComponent<TransformComponent>().position = playerPos;
    }
  }

  for (auto &p : projectiles)
  {
    if (Collision::AABB(playerCol, p->getComponent<ColliderComponent>().collider))
    {
      std::cout << "Hit player !" << std::endl;
      p->destroy();
    }
  }

  // camera follows player
  camera.x = newPlayer.getComponent<TransformComponent>().position.x - 400;
  camera.y = newPlayer.getComponent<TransformComponent>().position.y - 320;

  if (camera.x < 0)
  {
    camera.x = 0;
  }
  if (camera.y < 0)
  {
    camera.y = 0;
  }
  if (camera.x > camera.w)
  {
    camera.x = camera.w;
  }
  if (camera.y > camera.h)
  {
    camera.y = camera.h;
  }

  // for (auto cc : colliders)
  // {
  //   Collision::AABB(newPlayer.getComponent<ColliderComponent>(), *cc);
  // }
}

// auto &colliders(manager.getGroup(groupColliders));

void Game::render()
{
  SDL_RenderClear(renderer);
  // define the order in which entities are drawn (tiles at the back, etc.)
  for (auto &t : tiles)
  {
    t->draw();
  }
  for (auto &c : colliders)
  {
    c->draw();
  }
  for (auto &p : players)
  {
    p->draw();
  }

  for (auto &pr : projectiles)
  {
    pr->draw();
  }

  label.draw();

  button.draw();

  // print if game is running or not
  std::cout << "Game is running: " << isRunning << std::endl;

  SDL_RenderPresent(renderer);
}

void Game::clean()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}