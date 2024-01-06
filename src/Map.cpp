#include "Map.h"
#include "Game.h"
#include <fstream>
#include <iostream>
#include <string>
// #include "TextureManager.h"

Map::Map()
{
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
      srcY = atoi(&c) * 32;
      mapFile.get(c);
      srcX = atoi(&c) * 32;

      Game::AddTile(srcX, srcY, x * 64, y * 64);
      mapFile.ignore();
    }
    mapFile.ignore();
  }

  mapFile.close();
}

// void Map::DrawMap()
// {
//   int type = 0;

//   for (int row = 0; row < 20; row++)
//   {
//     for (int column = 0; column < 25; column++)
//     {
//       type = map[row][column];

//       dest.x = column * 32;
//       dest.y = row * 32;

//       switch (type)
//       {
//       case 0:
//         TextureManager::Draw(water, src, dest);
//         break;
//       case 1:
//         TextureManager::Draw(dirt, src, dest);
//         break;
//       case 2:
//         TextureManager::Draw(grass, src, dest);
//         break;
//       default:
//         break;
//       }
//     }
//   }
// }