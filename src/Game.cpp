#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"

Map *map;
Manager manager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

auto &newPlayer(manager.addEntity());

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

  // player = new GameObject("../Resources/player.png", 0, 0);
  // enemy = new GameObject("../Resources/enemy.png", 100, 100);
  map = new Map();

  newPlayer.addComponent<TransformComponent>();
  newPlayer.addComponent<SpriteComponent>("../Resources/player.png");
  newPlayer.addComponent<KeyboardController>();
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
  // newPlayer.getComponent<TransformComponent>().position.Add(Vector2D(0.5f, 0.2f));
  // if (newPlayer.getComponent<TransformComponent>().position.x > 300)
  // {
  //   newPlayer.getComponent<SpriteComponent>().setTex("../Resources/enemy.png");
  // }
}

void Game::render()
{
  SDL_RenderClear(renderer);
  map->DrawMap();
  // player->render();
  manager.draw();
  // enemy->render();
  SDL_RenderPresent(renderer);
}

void Game::clean()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}