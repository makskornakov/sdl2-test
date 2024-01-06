#pragma once
#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
  TransformComponent *transform;

  void init() override
  {
    transform = &entity->getComponent<TransformComponent>();
  }

  // actions on key press arrow down left right up
  void update() override
  {
    if (Game::event.type == SDL_KEYDOWN)
    {
      switch (Game::event.key.keysym.sym)
      {
        // arrow down
      case SDLK_DOWN:
        transform->velocity.y = 1;
        break;
        // arrow left
      case SDLK_LEFT:
        transform->velocity.x = -1;
        break;
        // arrow right
      case SDLK_RIGHT:
        transform->velocity.x = 1;
        break;
        // arrow up
      case SDLK_UP:
        transform->velocity.y = -1;
        break;
      default:
        break;
      }
    }

    if (Game::event.type == SDL_KEYUP)
    {
      switch (Game::event.key.keysym.sym)
      {
        // arrow down
      case SDLK_DOWN:
        transform->velocity.y = 0;
        break;
        // arrow left
      case SDLK_LEFT:
        transform->velocity.x = 0;
        break;
        // arrow right
      case SDLK_RIGHT:
        transform->velocity.x = 0;
        break;
        // arrow up
      case SDLK_UP:
        transform->velocity.y = 0;
        break;
      default:
        break;
      }
    }
  }
};
