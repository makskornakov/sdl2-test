#include "Game.h"
#include "TextureManager.h"

SDL_Texture *playerTex;
SDL_Rect srcR, destR;

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
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }

    isRunning = true;
  }

  playerTex = TextureManager::LoadTexture("../Resources/player.png", renderer);
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

  destR.h = 64;
  destR.w = 64;
  destR.x = cnt;
  destR.y = 200;

  std::cout << cnt << std::endl;
}

void Game::render()
{
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, playerTex, NULL, &destR);
  SDL_RenderPresent(renderer);
}

void Game::clean()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}