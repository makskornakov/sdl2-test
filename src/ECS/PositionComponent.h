#pragma once
#include "Components.h"

class PositionComponent : public Component
{
private:
  int xPos;
  int yPos;

public:
  PositionComponent()
  {
    xPos = 0;
    yPos = 0;
  }

  PositionComponent(int x, int y)
  {
    xPos = x;
    yPos = y;
  }

  int x() { return xPos; }
  int y() { return yPos; }

  // void init() override
  // {
  //   xPos = 0;
  //   yPos = 0;
  // }

  void update() override
  {
    xPos++;
    yPos++;
  }

  void setPos(int x, int y)
  {
    xPos = x;
    yPos = y;
  }
};
