#pragma once

#include "ECS.h"
#include "../AssetManager.h"
#include "../TextureManager.h"
#include "../Game.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UILabel : public Component
{
public:
  UILabel(int xPos, int yPos, std::string text, std::string fontFamily, const SDL_Color &color) : labelText(text), fontFamily(fontFamily), labelColor(color)
  {
    position.x = xPos;
    position.y = yPos;

    setLabelText(text, fontFamily);
  }

  ~UILabel()
  {
  }

  void setLabelText(std::string text, std::string fontFamily, const SDL_Color &color = {255, 255, 255, 255})
  {
    SDL_Surface *surface = TTF_RenderText_Blended(Game::assets->GetFont(fontFamily), text.c_str(), labelColor);
    labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
  }

  void changeColor(const SDL_Color &color)
  {
    labelColor = color;
    setLabelText(labelText, fontFamily);
  }

  void draw() override
  {
    SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
  }

private:
  SDL_Rect position;
  std::string labelText;
  std::string fontFamily;
  SDL_Color labelColor;
  SDL_Texture *labelTexture;
};
