#include <iostream>
#include <SDL.h>

using namespace std;

bool init();
void kill();
bool loop();

// Pointers to our window and renderer
SDL_Window *window;
SDL_Renderer *renderer;

int main(int argc, char **args)
{

  if (!init())
    return 1;

  while (loop())
  {
    // wait before processing the next frame
    // SDL_Delay(10);
  }

  kill();
  return 0;
}

void drawCircle(SDL_Renderer *renderer, int x0, int y0, int radius, vector<int> color = {255, 255, 255})
{
  int x = radius - 1;
  int y = 0;
  int tx = 1;
  int ty = 1;
  int error = tx - (radius << 1); // shifting bits left by 1 effectively
                                  // doubles the value. == tx - diameter

  // set color to red
  SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);

  while (x >= y)
  {
    //  Each of the following renders an octant of the circle
    SDL_RenderDrawPoint(renderer, x0 + x, y0 - y);
    SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
    SDL_RenderDrawPoint(renderer, x0 - x, y0 - y);
    SDL_RenderDrawPoint(renderer, x0 - x, y0 + y);
    SDL_RenderDrawPoint(renderer, x0 + y, y0 - x);
    SDL_RenderDrawPoint(renderer, x0 + y, y0 + x);
    SDL_RenderDrawPoint(renderer, x0 - y, y0 - x);
    SDL_RenderDrawPoint(renderer, x0 - y, y0 + x);

    if (error <= 0)
    {
      ++y;
      error += ty;
      ty += 2;
    }

    if (error > 0)
    {
      --x;
      tx += 2;
      error += tx - (radius << 1);
    }
  }
}

bool loop()
{
  static const unsigned char *keys = SDL_GetKeyboardState(NULL);

  SDL_Event e;
  SDL_Rect r;
  // mouse position as vector
  static vector<int> mousePosition{0, 0};
  // store all clicked mouse positions
  static vector<vector<int>> clickedMousePositions;

  // store if mouse is clicked
  static bool mouseIsClicked = false;
  // store all drawn (when mouse is clicked and moved) pixels
  static vector<vector<int>> drawnPixels;

  // array of connected pixel arrays
  static vector<vector<vector<int>>> connectedPixels;

  // Clear the window
  SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
  SDL_RenderClear(renderer);

  // Event loop
  while (SDL_PollEvent(&e) != 0)
  {
    switch (e.type)
    {
    case SDL_QUIT:
      return false;
    case SDL_MOUSEMOTION:
      // update mouse position
      mousePosition[0] = e.motion.x;
      mousePosition[1] = e.motion.y;

      // if mouse is clicked, store the current mouse position
      if (mouseIsClicked)
      {
        drawnPixels.push_back({e.motion.x, e.motion.y});
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      // store mouse position
      clickedMousePositions.push_back({e.button.x, e.button.y});
      // set mouseIsClicked to true
      mouseIsClicked = true;
      break;
    case SDL_MOUSEBUTTONUP:
      // store mouse position
      clickedMousePositions.push_back({e.button.x, e.button.y});
      // set mouseIsClicked to false
      mouseIsClicked = false;
      // store all drawn pixels in connectedPixels
      connectedPixels.push_back(drawnPixels);
      // clear drawnPixels
      drawnPixels.clear();
      break;
    // delete key
    case SDL_KEYDOWN:
      if (e.key.keysym.sym == SDLK_DELETE || e.key.keysym.sym == SDLK_BACKSPACE)
      {
        // clear all drawn pixels and clicked mouse positions
        drawnPixels.clear();
        clickedMousePositions.clear();
        connectedPixels.clear();
      }
      break;
    }
  }

  // draw a circle at the mouse position
  drawCircle(renderer, mousePosition[0], mousePosition[1], 20, {255, 255, 255});

  // draw small red circles at all clicked mouse positions
  for (auto &pos : clickedMousePositions)
  {
    drawCircle(renderer, pos[0], pos[1], 5, {255, 0, 0});
  }

  // set drawing color to green
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

  // draw the line that connects all pixels drawn while mouse was clicked
  if (drawnPixels.size() > 1)
  {
    for (int i = 0; i < drawnPixels.size() - 1; i++)
    {
      SDL_RenderDrawLine(renderer, drawnPixels[i][0], drawnPixels[i][1], drawnPixels[i + 1][0], drawnPixels[i + 1][1]);
    }
  }

  // draw all connected pixels (lines)
  for (auto &pixels : connectedPixels)
  {
    if (pixels.size() > 1)
    {
      for (int i = 0; i < pixels.size() - 1; i++)
      {
        SDL_RenderDrawLine(renderer, pixels[i][0], pixels[i][1], pixels[i + 1][0], pixels[i + 1][1]);
      }
    }
  }

  // Set drawing color to black
  // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  // Update window
  SDL_RenderPresent(renderer);

  return true;
}

bool init()
{
  // See last example for comments
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    cout << "Error initializing SDL: " << SDL_GetError() << endl;
    system("pause");
    return false;
  }

  SDL_DisplayMode screenMode;

  // calculate window dimensions
  float aspectRatio = 16.0f / 9.0f;
  SDL_GetDesktopDisplayMode(0, &screenMode);

  int desiredWidth = static_cast<int>(0.7f * screenMode.w);
  int desiredHeight = static_cast<int>(desiredWidth / aspectRatio);

  window = SDL_CreateWindow("WeDark game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, desiredWidth, desiredHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
  if (!window)
  {
    cout << "Error creating window: " << SDL_GetError() << endl;
    system("pause");
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer)
  {
    cout << "Error creating renderer: " << SDL_GetError() << endl;
    return false;
  }

  SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
  SDL_RenderClear(renderer);
  return true;
}

void kill()
{
  // Quit
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
