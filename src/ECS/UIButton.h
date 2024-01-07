#pragma once

#include "ECS.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "../Game.h"
#include "Components.h"

class UIButton : public Component
{
public:
  // and optional callback function
  UIButton(std::string id, int x, int y, int width, int height, std::string text, std::string fontFamily, const SDL_Color &color, void (*callback)() = nullptr) : buttonId(id), position({x, y, width, height}), text(text), fontFamily(fontFamily), color(color), callback(callback)
  {
    isClicked = false;
  }

  ~UIButton()
  {
  }

  void init() override
  {
    transform = &entity->getComponent<TransformComponent>();
    // transform->position.x = position.x;
    // transform->position.y = position.y;
    // transform->width = position.w;
    // transform->height = position.h;

    label = &entity->addComponent<UILabel>(position.x + position.w / 4, position.y + position.h / 4, text, fontFamily, color);
  }

  // save the initial color and change it to green when hover
  void hover()
  {
    SDL_Color initialColor = color;
    color = {0, 255, 0, 255};
    label->changeColor(color);
    color = initialColor;
  }

  void reset()
  {
    label->changeColor(color);
  }

  void update() override
  {
    if (Game::event.type == SDL_MOUSEBUTTONDOWN)
    {
      if (Game::event.button.button == SDL_BUTTON_LEFT)
      {
        if (Game::event.button.x >= position.x && Game::event.button.x <= position.x + position.w &&
            Game::event.button.y >= position.y && Game::event.button.y <= position.y + position.h)
        {
          isClicked = true;
          // run the callback function if it exists
          if (callback != nullptr)
          {
            callback();
          }
        }
      }
    }
    else if (Game::event.type == SDL_MOUSEBUTTONUP)
    {
      if (Game::event.button.button == SDL_BUTTON_LEFT)
      {
        if (Game::event.button.x >= position.x && Game::event.button.x <= position.x + position.w &&
            Game::event.button.y >= position.y && Game::event.button.y <= position.y + position.h)
        {
          isClicked = false;
        }
      }
    }
    // if hover change color to green
    else if (Game::event.type == SDL_MOUSEMOTION)
    {
      if (Game::event.button.x >= position.x && Game::event.button.x <= position.x + position.w &&
          Game::event.button.y >= position.y && Game::event.button.y <= position.y + position.h)
      {
        hover();
      }
      else
      {
        reset();
      }
    }
  }

  void draw() override
  {
    if (isClicked)
    {
      SDL_SetRenderDrawColor(Game::renderer, 0, 0, 255, 255);
    }
    else
    {
      SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    }
    SDL_RenderFillRect(Game::renderer, &position);
  }

  bool getIsClicked()
  {
    return isClicked;
  }

  std::string getButtonId()
  {
    return buttonId;
  }

private:
  TransformComponent *transform;
  SDL_Rect position;
  std::string text;
  std::string fontFamily;
  SDL_Color color;
  bool isClicked;
  void (*callback)();
  std::string buttonId;
  UILabel *label;
};
