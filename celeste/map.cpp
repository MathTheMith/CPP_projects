#include "map.hpp"
#include "raylib.h"
#include "player.hpp"
#include <fstream>

Map::Map(const char* filename, int tsize) : tileSize(tsize)
{
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line))
    {
        if (!line.empty()) {
            map.push_back(line);
        }
    }
    file.close();

    height = map.size();
    width  = map[0].size();
}

bool Map::IsSolid(int tx, int ty) const
{
    if (tx < 0 || ty < 0 || ty >= height || tx >= width)
        return true;

    return map[ty][tx] == '#';
}

void Map::spawnPlayer(Player &player) const
{
    bool playerSpawned = false;
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < (int)map[y].size(); x++) {
            if (map[y][x] == 'P' && !playerSpawned)
            {
                player.posX = x * tileSize;
                player.posY = y * tileSize;
                playerSpawned = true;
            }
        }
    }
}

void Map::Draw() const
{
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < (int)map[y].size(); x++) {
            if (map[y][x] == '#') {
                DrawRectangle(
                    x * tileSize, 
                    y * tileSize, 
                    tileSize, 
                    tileSize, 
                    DARKGRAY
                );
                DrawRectangleLines(
                    x * tileSize, 
                    y * tileSize, 
                    tileSize, 
                    tileSize, 
                    LIGHTGRAY
                );
            }
        }
    }
}