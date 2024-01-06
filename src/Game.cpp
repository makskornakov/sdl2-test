#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map *map;
Manager manager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent *> Game::colliders;

bool Game::isRunning = false;
SDL_Rect Game::camera = {0, 0, 800, 640};

auto &newPlayer(manager.addEntity());
auto &wall(manager.addEntity());

const char *mapFile = "../Resources/terrain_ss.png";

enum groupLabels : std::size_t
{
  groupMap,
  groupPlayers,
  groupEnemies,
  groupColliders
};

auto &tiles(manager.getGroup(groupMap));
auto &players(manager.getGroup(groupPlayers));
auto &enemies(manager.getGroup(groupEnemies));

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

  map = new Map();
  // load map from file
  // map->LoadMap("../Resources/p16x16.txt", 16, 16);
  Map::LoadMap("../Resources/map.map", 25, 20, executablePath);

  // ECS implementation

  newPlayer.addComponent<TransformComponent>(4);
  newPlayer.addComponent<SpriteComponent>("../Resources/player_anims.png", true);
  newPlayer.addComponent<KeyboardController>();
  newPlayer.addComponent<ColliderComponent>("player");
  newPlayer.addGroup(groupPlayers);
}

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

  manager.refresh();
  manager.update();

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
  for (auto &p : players)
  {
    p->draw();
  }
  for (auto &e : enemies)
  {
    e->draw();
  }

  SDL_RenderPresent(renderer);
}

void Game::clean()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

void Game::AddTile(int srcX, int srcY, int xPos, int yPos)
{
  auto &tile(manager.addEntity());
  tile.addComponent<TileComponent>(srcX, srcY, xPos, yPos, mapFile);
  tile.addGroup(groupMap);
}