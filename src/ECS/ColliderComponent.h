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

  ColliderComponent(std::string t, int xPos, int yPos, int xSize, int ySize)
  {
    tag = t;
    collider.x = xPos;
    collider.y = yPos;
    collider.w = xSize;
    collider.h = ySize;
  }

  void init() override
  {
    if (!entity->hasComponent<TransformComponent>())
    {
      entity->addComponent<TransformComponent>();
    }
    transform = &entity->getComponent<TransformComponent>();

    texture = TextureManager::LoadTexture("../Resources/collider.png");

    srcRect = {0, 0, 32, 32};
    destRect = {collider.x, collider.y, collider.w, collider.h};
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
    // if entity is a player, update collider.x and add difference between x and y sizes
    // if (tag == "player")
    // {
    //   collider.x += (collider.w - destRect.w) / 2;
    //   collider.w = destRect.w;
    // }

    destRect.x = collider.x - Game::camera.x;
    destRect.y = collider.y - Game::camera.y;
  }

  void draw() override
  {
    TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
  }
};