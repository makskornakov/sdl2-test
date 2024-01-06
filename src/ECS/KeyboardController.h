#pragma once
#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
  TransformComponent *transform;
  SpriteComponent *sprite;

  void init() override
  {
    transform = &entity->getComponent<TransformComponent>();
    sprite = &entity->getComponent<SpriteComponent>();
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
        sprite->Play("Walk");
        break;
        // arrow left
      case SDLK_LEFT:
        transform->velocity.x = -1;
        sprite->Play("Walk");
        sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
        break;
        // arrow right
      case SDLK_RIGHT:
        transform->velocity.x = 1;
        sprite->Play("Walk");
        sprite->spriteFlip = SDL_FLIP_NONE;
        break;
        // arrow up
      case SDLK_UP:
        transform->velocity.y = -1;
        sprite->Play("Walk");
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
        sprite->Play("Idle");
        break;
        // arrow left
      case SDLK_LEFT:
        transform->velocity.x = 0;
        sprite->Play("Idle");
        break;
        // arrow right
      case SDLK_RIGHT:
        transform->velocity.x = 0;
        sprite->Play("Idle");
        break;
        // arrow up
      case SDLK_UP:
        transform->velocity.y = 0;
        sprite->Play("Idle");
        break;
      case SDLK_ESCAPE:
        Game::isRunning = false;
        break;
      default:
        break;
      }
    }
  }
};
