#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>

class Player;

class Map {
public:
    int width;
    int height;
    int tileSize;

    std::vector<std::string> map;

    Map(const char* filename, int tileSize);
    void spawnPlayer(Player &player) const;
    bool IsSolid(int tx, int ty) const;
    void Draw(void) const;
};

#endif