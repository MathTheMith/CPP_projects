#include "player.hpp"
#include "raylib.h"

void Player::HandleMovement()
{
    if (isDashing) return;

    if ((IsKeyUp(KEY_RIGHT) && IsKeyUp(KEY_LEFT)) ||
        (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_LEFT)))
    {
        isMoving = false;
        return;
    }

    if (IsKeyDown(KEY_RIGHT)) {
        posX += 5;
        direction = 1;
        isMoving = true;
    }

    if (IsKeyDown(KEY_LEFT)) {
        posX -= 5;
        direction = 0;
        isMoving = true;
    }
}


void Player::HandleDash()
{
    if (isTouchingGround)
        nbDash = 1;

    if (isDashing)
    {
        posX += speedX;
        dashTimer--;

        if (dashTimer <= 0) {
            isDashing = false;
            speedX = 0;
        }
        isMoving = true;
        nbDash = 0;
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
