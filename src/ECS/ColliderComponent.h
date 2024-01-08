#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"
#include "../TextureManager.h"

class ColliderComponent : public Component
{
public:
  SDL_Rect collider;
  std::string tag;

  SDL_Texture *texture;
  SDL_Rect srcRect, destRect;

  TransformComponent *transform;

  ColliderComponent(std::string t)
  {
    tag = t;
  }

  ColliderComponent(std::string t, int xPos, int yPos, int size)
  {
    tag = t;
    collider.x = xPos;
    collider.y = yPos;
    collider.w = collider.h = size;
  }

  void init() override
  {
    if (!entity->hasComponent<TransformComponent>())
    {
      entity->addComponent<TransformComponent>();
    }
    transform = &entity->getComponent<TransformComponent>();

    texture = TextureManager::LoadTexture("../Resources/collider.png");
    // if entity is a player, make the collider smaller in width
    srcRect = {0, 0, 32, 32};
    destRect = {collider.x, collider.y, collider.w, collider.h};

    // Game::colliders.push_back(this);
  }

  void update() override
  {
    if (tag != "terrain")
    {
      collider.x = static_cast<int>(transform->position.x);
      collider.y = static_cast<int>(transform->position.y);
      collider.w = transform->width * transform->scale;
      collider.h = transform->height * transform->scale;
    }
    // if player, make the collider smaller in width
    // if (tag == "player")
    // {
    //   collider.w -= 32;
    //   collider.x += 16;
    // }

    destRect.x = collider.x - Game::camera.x;
    destRect.y = collider.y - Game::camera.y;
  }

  void draw() override
  {
    TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
  }
};