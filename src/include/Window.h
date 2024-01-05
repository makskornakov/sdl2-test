#pragma once
#include <SDL.h>

class Window {
public:
  Window() {
    SDL_Init(SDL_INIT_VIDEO);

    SDLWindow = SDL_CreateWindow(
      "WeDark Platformer",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      600, 150, 0
    );

    SDLWindowSurface = SDL_GetWindowSurface(SDLWindow);
    Update();
  }

  void Update() {
    SDL_FillRect(
      SDLWindowSurface,
      nullptr,
      SDL_MapRGB(SDLWindowSurface->format, 40, 40, 40)
    );
  }

  void RenderFrame() {
    SDL_UpdateWindowSurface(SDLWindow);
  }

  SDL_Surface* GetSurface() {
    return SDLWindowSurface;
  }

private:
  SDL_Window* SDLWindow { nullptr };
  SDL_Surface* SDLWindowSurface { nullptr };
};