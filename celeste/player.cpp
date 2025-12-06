#include "player.hpp"
#include "raylib.h"

Player::Player()
    : posX(0), posY(0),
      speedX(0), speedY(0),
      gravity(0.3f), jumpForce(-8),
      direction(1),
      isDashing(false),
      dashTimer(0),
      dashDuration(8),
      dashSpeed(20),
      currentFrame(0),
      frameCount(13),
      frameTime(0.05f),
      frameTimer(0)
{
    spriteSheetR = LoadTexture("images/spritesheet.png");
    spriteSheetL = LoadTexture("images/spritesheet_reverse.png");
    spriteSheetD = LoadTexture("images/spritesheet_dash.png");
    frameWidth  = 17;
    frameHeight = 18;
	isMoving = false;
	isTouchingGround = true;
}

Player::~Player() {
    UnloadTexture(spriteSheetR);
    UnloadTexture(spriteSheetL);
}

void Player::Update()
{

	if(isDashing) {
	    posX += speedX;
	    dashTimer--;
	    if(dashTimer <= 0) {
	        isDashing = false;
	        speedX = 0;
	    }
	    isMoving = true;
	}
	else if ((IsKeyUp(KEY_RIGHT) && IsKeyUp(KEY_LEFT) )||
			(IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_LEFT)) )
	{isMoving = false;}
	else {
	    if(IsKeyDown(KEY_RIGHT)) {
	        posX += 5;
	        direction = 1;
	        isMoving = true;
	    }
	    if(IsKeyDown(KEY_LEFT)) {
	        posX -= 5;
	        direction = 0;
	        isMoving = true;
	    }
	}

    speedY += gravity;
    posY += speedY;
    if(posY >= W_HEIGHT - 172) {
        posY = W_HEIGHT - 172;
        speedY = 0;
		isTouchingGround = true;
    }
	else
		isTouchingGround = false;

    frameTimer += GetFrameTime();
    if(frameTimer >= frameTime) {
        currentFrame++;
        if(currentFrame >= frameCount) currentFrame = 0;
        frameTimer = 0;
    }
}

void Player::Jump()
{
    if(posY >= W_HEIGHT - 172) {
        speedY = jumpForce;
		isTouchingGround = false;
    }
}

void Player::Dash()
{
    if(isDashing) return;
    isDashing = true;
    dashTimer = dashDuration;
    speedX = (direction == 1 ? dashSpeed : -dashSpeed);
    speedY = 0;
}
