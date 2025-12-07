#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <iostream>
#include "../includes/map.hpp"

#define W_WIDTH 1920
#define W_HEIGHT 1080

class Player {
private:
    int direction;

    float speedX;
    float speedY;
    float gravity;
    float jumpForce;

    // Variables pour le saut variable
    bool isHoldingJump;
    int jumpHoldTimer;
    int maxJumpHoldTime;
    float jumpHoldForce;

    bool isDashing;
    int dashTimer;
    int dashDuration;
    float dashSpeed;
    int nbDash;

    Texture2D spriteSheetR;
    Texture2D spriteSheetL;
    Texture2D spriteSheetDR;
    Texture2D spriteSheetDL;
    Texture2D spriteSheetWR;
    Texture2D spriteSheetWL;
    Texture2D spriteSheetWDR;
    Texture2D spriteSheetWDL;
    Texture2D spriteSheetJL1;
    Texture2D spriteSheetJL2;
    Texture2D spriteSheetJR1;
    Texture2D spriteSheetJR2;
    int frameWidth;
    int frameHeight;
    int currentFrame;
    int frameCount;
    float frameTime;
    float frameTimer;
    bool isMoving;
    bool isTouchingGround;
    bool isOnAWall;

public:
    Player();
    ~Player();

    int posX;
    int posY;
    int frameCounter = 0;
    int showHitbox = 0;
    int lastInput = -1;
    void Update(Map *map);
    void Jump();
    void HandleJumpHold();
    void Dash();
    void Draw();
    void HandleDash();
    void HandleMovement();
    bool isOnGround(Map *map);
    void checkCollision(Map *map, int oldX, int oldY);
    bool checkCollisionAt(Map *map, float x, float y);
    void checkWallGrab(Map *map);
    bool isOnWall(Map *map);
    void priorityInput();
    bool isTouchingRightWall(Map* map);
    bool isTouchingLeftWall(Map* map);

};

#endif