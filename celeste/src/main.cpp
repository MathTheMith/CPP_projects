#include "raylib.h"
#include "../includes/player.hpp"
#include "../includes/map.hpp"
#include <iostream>
#include <cmath>

#define W_WIDTH GetScreenWidth()
#define W_HEIGHT GetScreenHeight()

void initWindow(void)
{
    InitWindow(0, 0, "temp");
    SetWindowPosition(0, 0); 
    int screenWidth = GetMonitorWidth(GetCurrentMonitor());
    int screenHeight = GetMonitorHeight(GetCurrentMonitor());

    SetWindowSize(screenWidth - 10, screenHeight - 40);
    SetTargetFPS(60);
}

int getAdaptiveTileSize()
{
    int h = GetMonitorHeight(GetCurrentMonitor());
    if (h >= 2160) return 64;
    if (h >= 1440) return 48;
    return 32;
}

Camera2D setCamera(Camera2D &camera)
{
    camera.target = {0.0f, 0.0f};
    camera.offset = { W_WIDTH / 2.0f, W_HEIGHT / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    return (camera);
}

int main(void)
{
    SetTraceLogLevel(LOG_NONE);
    initWindow();

    Camera2D camera = setCamera(camera);

    int TILE_SIZE = getAdaptiveTileSize();

    Map *map = new Map("map/map.txt", TILE_SIZE);
    Player *madeline = new Player();
    map->spawnPlayer(*madeline);
    
    madeline->InitCamera(GetMonitorWidth(GetCurrentMonitor()) / 2.0f);

    while (!WindowShouldClose())
    {
        madeline->Update(map);
        madeline->UpdateCamera(camera);

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);
        map->Draw();  
        madeline->Draw();
        EndMode2D();

        DrawText("For debug : H", 50, 20, 20, WHITE);
        if (IsKeyPressed(KEY_F11))
            ToggleFullscreen();

        EndDrawing();
    }

    delete map;
    CloseWindow();
    return 0;
}