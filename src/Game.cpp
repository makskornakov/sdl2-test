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

auto &newPlayer(manager.addEntity());
auto &wall(manager.addEntity());

auto &tile0(manager.addEntity());
auto &tile1(manager.addEntity());
auto &tile2(manager.addEntity());

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char *title, int width, int height, bool fullScreen)
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

  // ECS implementation

  tile0.addComponent<TileComponent>(200, 200, 32, 32, 0);
  tile0.addComponent<ColliderComponent>("water");
  tile1.addComponent<TileComponent>(250, 250, 32, 32, 1);
  tile1.addComponent<ColliderComponent>("dirt");
  tile2.addComponent<TileComponent>(300, 300, 32, 32, 2);
  tile2.addComponent<ColliderComponent>("grass");

  wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
  wall.addComponent<SpriteComponent>("../Resources/tiles/dirt.png");
  wall.addComponent<ColliderComponent>("wall");

  newPlayer.addComponent<TransformComponent>(2);
  newPlayer.addComponent<SpriteComponent>("../Resources/player.png");
  newPlayer.addComponent<KeyboardController>();
  newPlayer.addComponent<ColliderComponent>("player");
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

  // if (Collision::AABB(newPlayer.getComponent<ColliderComponent>().collider, wall.getComponent<ColliderComponent>().collider))
  // {
  //   newPlayer.getComponent<TransformComponent>().velocity * -1;
  //   std::cout << "player hit wall" << std::endl;
  // }

  for (auto cc : colliders)
  {
    Collision::AABB(newPlayer.getComponent<ColliderComponent>(), *cc);
  }
}

void Game::render()
{
  SDL_RenderClear(renderer);
  // map->DrawMap();

  manager.draw();

  SDL_RenderPresent(renderer);
}

void Game::clean()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}