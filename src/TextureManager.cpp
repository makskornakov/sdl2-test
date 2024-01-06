#include "TextureManager.h"

SDL_Texture *TextureManager::LoadTexture(const char *fileName, SDL_Renderer *ren)
{
  SDL_Surface *tmpSurface = IMG_Load(fileName);
  SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, tmpSurface);
  SDL_FreeSurface(tmpSurface);

  return tex;
}