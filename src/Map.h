#pragma once
#include <string>

class Map
{
public:
  Map(const char *mapFilePath, int mapScale, int tileSize, const std::string &executablePath);
  ~Map();

  void LoadMap(std::string path, int sizeX, int sizeY, const std::string &executablePath);
  void AddTile(int srcX, int srcY, int xPos, int yPos);

private:
  const char *mapFilePath;
  int mapScale;
  int tileSize;
  int scaledSize;
  const std::string &executablePath;
};
