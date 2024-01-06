// #pragma once
// #include <SDL.h>
// #include <string>
// #include <vector>

// class Window {
// public:
//   Window() {
//     SDL_Init(SDL_INIT_VIDEO);
//     SDL_DisplayMode screenMode;

//     // calculate window dimensions
//     float aspectRatio = 16.0f / 9.0f;
//     SDL_GetDesktopDisplayMode(0, &screenMode);

//     int desiredWidth = static_cast<int>(windowRelativeWidth * screenMode.w);
//     int desiredHeight = static_cast<int>(desiredWidth / aspectRatio);

//     SDLWindow = SDL_CreateWindow(
//       "Hello Window",
//       SDL_WINDOWPOS_UNDEFINED,
//       SDL_WINDOWPOS_UNDEFINED,
//       desiredWidth,
//       desiredHeight,
//       SDL_WINDOW_RESIZABLE
//     );

//     SDLWindowSurface = SDL_GetWindowSurface(SDLWindow);

//   }

//   void Update() {
//     SDL_FillRect(
//       SDLWindowSurface,
//       nullptr,
//       SDL_MapRGB(
//         SDLWindowSurface->format,
//         bgRed, bgGreen, bgBlue
//       )
//     );
//     // draw outlined rectangle above the mouse
//     SDL_Rect rect {
//       mousePosition[0] - 10,
//       mousePosition[1] - 10,
//       20, 20
//     };
//     SDL_FillRect(
//       SDLWindowSurface,
//       &rect,
//       SDL_MapRGB(
//         SDLWindowSurface->format,
//         255, 255, 255
//       )
//     );
//   }

//   void RenderFrame() {
//     SDL_UpdateWindowSurface(SDLWindow);
//   }

//   void SetMousePosition(int x, int y) {
//     // https://wiki.libsdl.org/SDL_WarpMouseInWindow
//     mousePosition[0] = x;
//     mousePosition[1] = y;
//   }

//   // void SetBackgroundColor(int R, int G, int B) {
//   //   bgRed = R;
//   //   bgGreen = G;
//   //   bgBlue = B;
//   // }

//   void SetTitle(std::string NewTitle) {
//     // https://wiki.libsdl.org/SDL_SetWindowTitle
//     SDL_SetWindowTitle(
//       SDLWindow, NewTitle.c_str()
//     );
//   }

//   // void ChangeWindowSize(int Amount) {
//   //   // https://wiki.libsdl.org/SDL_SetWindowSize
//   //   SDL_SetWindowSize(
//   //     SDLWindow,
//   //     windowWidth += Amount,
//   //     windowHeight += Amount
//   //   );
//   // }

//   // [[nodiscard]]
//   // int GetWindowWidth() const {
//   //   return windowWidth;
//   // }

//   // [[nodiscard]]
//   // int GetWindowHeight() const {
//   //   return windowHeight;
//   // }

//   // int MoveRelative(int x, int y) {
//   //   // https://wiki.libsdl.org/SDL_GetWindowPosition
//   //   int CurrentX; int CurrentY;
//   //   SDL_GetWindowPosition(
//   //     SDLWindow, &CurrentX, &CurrentY
//   //   );

//   //   // https://wiki.libsdl.org/SDL_SetWindowPosition
//   //   SDL_SetWindowPosition(
//   //     SDLWindow, CurrentX + x, CurrentY + y
//   //   );
//   // }

//   void GrabMouse() {
//     // https://wiki.libsdl.org/SDL_SetWindowMouseGrab
//     SDL_SetWindowMouseGrab(SDLWindow, SDL_TRUE);
//   }

//   void FreeMouse() {
//     // https://wiki.libsdl.org/SDL_SetWindowMouseGrab
//     SDL_SetWindowMouseGrab(SDLWindow, SDL_FALSE);
//   }

// private:
//   SDL_Window* SDLWindow { nullptr };
//   SDL_Surface* SDLWindowSurface { nullptr };
//   float windowRelativeWidth { 0.7f };

//   int bgRed { 40 };
//   int bgGreen { 40 };
//   int bgBlue { 40 };
//   std::vector<int> mousePosition { 0, 0 };
// };