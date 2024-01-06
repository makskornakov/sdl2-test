#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char *textureSheet, int x, int y)
{
  objectTexture = TextureManager::LoadTexture(textureSheet);
  xPosition = x;
  yPosition = y;
}

void GameObject::update()
{
  xPosition++;
  yPosition++;

  srcRect.h = 64;
  srcRect.w = 64;
  srcRect.x = 0;
  srcRect.y = 0;

  destRect.x = xPosition;
  destRect.y = yPosition;
  destRect.w = srcRect.w * 2;
  destRect.h = srcRect.h * 2;
}

void GameObject::render()
{
  SDL_RenderCopy(Game::renderer, objectTexture, &srcRect, &destRect);
}