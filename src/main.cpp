#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{

  const int FPS = 60;
  const int frameDelay = 1000 / FPS;

  Uint32 frameStart;
  int frameTime;

  const std::string executablePath = argv[0];

  // file path to executable (not on all OS's its nice out of the box)
  const std::string executableDir = executablePath.substr(0, executablePath.find_last_of("\\/"));

  game = new Game();
  game->init("WeDark Game", 800, 640, false, executableDir);

  while (game->running())
  {
    frameStart = SDL_GetTicks();

    game->handleEvents();
    game->update();
    game->render();

    frameTime = SDL_GetTicks() - frameStart;

    if (frameDelay > frameTime)
    {
      SDL_Delay(frameDelay - frameTime);
    }
  }

  game->clean();
  return 0;
}