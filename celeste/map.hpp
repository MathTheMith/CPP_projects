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

    std::vector<std::string> tiles;

    Map(const char* filename, int tileSize);

    bool IsSolid(int tx, int ty) const;
    void Draw(Player& player) const;
};

extern Map* world;

#endif