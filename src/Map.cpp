#include "Map.h"
#include "Game.h"
#include <fstream>
#include "ECS/ECS.h"
#include "ECS/Components.h"
// #include "TextureManager.h"

extern Manager manager;

Map::Map(const char *mapFilePath, int mapScale, int tileSize, const std::string &executablePath) : mapFilePath(mapFilePath), mapScale(mapScale), tileSize(tileSize), executablePath(executablePath)
{
  scaledSize = mapScale * tileSize;
}

Map::~Map()
{
}

void Map::LoadMap(std::string path, int sizeX, int sizeY, const std::string &executablePath)
{
  char c;
  std::fstream mapFile;
  std::string fullPath = executablePath + "/" + path;
  mapFile.open(fullPath);

  int srcX, srcY;

  // print file contents
  // while (mapFile.get(c))
  // {
  //   std::cout << "Character: " << c << std::endl;
  // }

  for (int y = 0; y < sizeY; y++)
  {
    for (int x = 0; x < sizeX; x++)
    {
      mapFile.get(c);
      srcY = atoi(&c) * tileSize;
      mapFile.get(c);
      srcX = atoi(&c) * tileSize;

      AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
      mapFile.ignore();
    }
    mapFile.ignore();
  }

  mapFile.ignore(); // ignore the break line between the map and the colliders
  mapFile.ignore(); // ignore the first line of the colliders

  for (int y = 0; y < sizeY; y++)
  {
    for (int x = 0; x < sizeX; x++)
    {
      mapFile.get(c);
      if (c == '1')
      {
        auto &collider(manager.addEntity());
        collider.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
        collider.addGroup(Game::groupColliders);
        // mapFile.ignore();
      }
      mapFile.ignore();
    }
    mapFile.ignore();
  }

  mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xPos, int yPos)
{
  auto &tile(manager.addEntity());
  tile.addComponent<TileComponent>(srcX, srcY, xPos, yPos, tileSize, mapScale, mapFilePath);
  tile.addGroup(Game::groupMap);
}
