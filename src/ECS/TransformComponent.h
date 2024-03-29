#pragma once
#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{

public:
  Vector2D position;
  Vector2D velocity;

  int height = 32;
  int width = 32;
  float scale = 1.0f;

  float speed = 2.0f;

  TransformComponent()
  {
    position.Zero();
  }

  TransformComponent(float sc)
  {
    position.x = 400;
    position.y = 320;
    scale = sc;
  }

  TransformComponent(float x, float y)
  {
    position.x = x;
    position.y = y;
  }

  TransformComponent(float x, float y, int h, int w, float sc)
  {
    position.x = x;
    position.y = y;
    height = h;
    width = w;
    scale = sc;
  }

  void init() override
  {
    velocity.Zero();
  }

  void update() override
  {
    position.x += static_cast<int>(velocity.x * speed);
    position.y += static_cast<int>(velocity.y * speed);
  }
};
