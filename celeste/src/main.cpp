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
        if(IsKeyPressed(KEY_UP)) 
            madeline->Jump();
        if(IsKeyPressed(KEY_LEFT_SHIFT)) 
            madeline->Dash();

        madeline->Update(map);

        BeginDrawing();
        ClearBackground(BLACK);

        map->Draw();

        DrawRectangle(0, W_HEIGHT - 100, W_WIDTH, 100, GRAY);

        madeline->Draw();

        EndDrawing();
    }

    delete map; 
    CloseWindow();
    return 0;
}