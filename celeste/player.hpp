#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

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

    Texture2D spriteSheetR;
    Texture2D spriteSheetL;
    Texture2D spriteSheetD;
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

    void Update();
    void Jump();
    void Dash();
    void Draw();
};

#endif
