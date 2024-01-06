#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include <string>

class AssetManager;
// class ColliderComponent;
class Game
{
public:
  Game();
  ~Game();

  void init(const char *title, int width, int height, bool fullscreen, const std::string &executablePath);

  void handleEvents();
  void update();
  bool running() { return isRunning; }
  void render();
  void clean();

  static SDL_Renderer *renderer;
  static AssetManager *assets;

  static SDL_Event event;
  static bool isRunning;
  static SDL_Rect camera;

  enum groupLabels : std::size_t
  {
    groupMap,
    groupPlayers,
    // groupEnemies,
    groupColliders,
    groupProjectiles
  };

private:
  int cnt = 0;
  SDL_Window *window;
};