#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <iostream>
#include "map.hpp"

#define W_WIDTH 1920
#define W_HEIGHT 1080

class Player {
private:
    int direction;

    float speedX;
    float speedY;
    float gravity;
    float jumpForce;

    bool isDashing;
    int dashTimer;
    int dashDuration;
    float dashSpeed;
    int nbDash;

    Texture2D spriteSheetR;
    Texture2D spriteSheetL;
    Texture2D spriteSheetDR;
    Texture2D spriteSheetDL;
    int frameWidth;
    int frameHeight;
    int currentFrame;
    int frameCount;
    float frameTime;
    float frameTimer;

    bool isMoving;
    bool isTouchingGround;

public:
    Player();
    ~Player();

    int posX;
    int posY;

    void Update(Map *map);
    void Jump();
    void Dash();
    void Draw();
    void HandleDash();
    void HandleGravity();
    void HandleMovement();
    bool isOnGround(Map *map);
    bool checkCollisionAt(Map *map, float x, float y);
};

#endif
