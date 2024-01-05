#include <SDL.h>
#include "Window.h"
#include "Layer.h"
#include "Button.h"
#include "Application.h"

int main() {
  Window GameWindow;
  Application App { &GameWindow };
  Layer UI;
  Button ExampleButton { &App };
  UI.SubscribeToEvents(&ExampleButton);

  SDL_Event Event;
  while(true) {
    while(SDL_PollEvent(&Event)) {
      if (Event.type == SDL_QUIT) {
        SDL_Quit();
        return 0;
      }
      if (UI.HandleEvent(&Event)) {
        continue;
      }
    }
    GameWindow.RenderFrame();
  }
}