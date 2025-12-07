#include "raylib.h"
#include "../includes/player.hpp"
#include "../includes/map.hpp"

int main(void)
{
    SetTraceLogLevel(LOG_NONE);
    
    InitWindow(W_WIDTH, W_HEIGHT, "Celeste Like");
    Map *map;
    map = new Map("map/map.txt", 32);
    Player *madeline = new Player();
    map->spawnPlayer(*madeline);
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        
        madeline->Update(map);
        map->Draw();
        madeline->Draw();
        DrawText("For debug : H", 50, 20, 20, WHITE);
        EndDrawing();
    }

    delete map; 
    CloseWindow();
    return 0;
}