#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"

GameObject *player;
GameObject *enemy;

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

  player = new GameObject("../Resources/player.png", renderer, 0, 0);
  enemy = new GameObject("../Resources/enemy.png", renderer, 100, 100);
}

void Game::handleEvents()
{
  SDL_Event event;

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
  cnt++;
  player->update();
  enemy->update();
}

void Game::render()
{
  SDL_RenderClear(renderer);
  player->render();
  enemy->render();
  SDL_RenderPresent(renderer);
}

void Game::clean()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}