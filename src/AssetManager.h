#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/ECS.h"
#include "SDL.h"

class AssetManager
{
public:
  AssetManager(Manager *man);

  ~AssetManager();

  // Game objects
  void CreateProjectile(Vector2D pos, Vector2D velocity, int range, int speed, std::string id);

  // Texture management
  void AddTexture(std::string id, const char *path);
  SDL_Texture *GetTexture(std::string id);

private:
  Manager *manager;
  std::map<std::string,
           SDL_Texture *>
      textures;
};