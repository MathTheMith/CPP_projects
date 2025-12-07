#include "../includes/player.hpp"
#include "raylib.h"

void Player::priorityInput()
{
    bool left  = IsKeyDown(KEY_LEFT);
    bool right = IsKeyDown(KEY_RIGHT);

    if (!left && !right)
    {
        isMoving = false;
        return;
    }
    if (lastInput == 1 && right)
    {
        posX += 5;
        direction = 1;
        isMoving = true;
    }
    else if (lastInput == 0 && left)
    {
        posX -= 5;
        direction = 0;
        isMoving = true;
    }
    else if (right)
    {
        posX += 5;
        direction = 1;
        isMoving = true;
    }
    else if (left)
    {
        posX -= 5;
        direction = 0;
        isMoving = true;
    }
    else
        isMoving = false;
}

void Player::HandleMovement()
{
    if (IsKeyPressed(KEY_UP)) Jump();
    if (IsKeyPressed(KEY_LEFT_SHIFT)) Dash();
    if (isDashing) return;

    if (IsKeyPressed(KEY_RIGHT)) lastInput = 1;
    if (IsKeyPressed(KEY_LEFT))  lastInput = 0;

    priorityInput();

    if (IsKeyDown(KEY_DOWN) && !isTouchingGround)
        speedY++;
}


void Player::HandleDash()
{
    if (isDashing) {
        posX += speedX;
        speedY = 0;
        
        dashTimer--;
        if (dashTimer <= 0) {
            isDashing = false;
            speedX = 0;
        }
    }
}