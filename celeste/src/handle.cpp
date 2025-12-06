#include "../includes/player.hpp"
#include "raylib.h"

void Player::HandleMovement()
{
    if (isDashing) return;

    if ((IsKeyUp(KEY_RIGHT) && IsKeyUp(KEY_LEFT)) ||
        (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_LEFT)))
    {
        if (isTouchingGround)
        {
            isMoving = false;
            speedX = 0;
        }
        return;
    }

    if (IsKeyDown(KEY_RIGHT)) {
        posX += 5 + speedX;
        direction = 1;
        isMoving = true;
    }
    if (speedX > 0)
        speedX--;
    else
        speedX++;
    if (IsKeyDown(KEY_LEFT)) {
        posX -= 5 - speedX;
        direction = 0;
        isMoving = true;
    }
}


void Player::HandleDash()
{
    if (isDashing) {
        posX += speedX;
        dashTimer--;
        if (dashTimer <= 0) {
            isDashing = false;
        }
    }
}



void Player::HandleGravity()
{
    speedY += gravity;
    posY += speedY;

    if (posY >= W_HEIGHT - 172)
    {
        posY = W_HEIGHT - 172;
        speedY = 0;
        isTouchingGround = true;
    }
    else
    {
        isTouchingGround = false;
    }
}
