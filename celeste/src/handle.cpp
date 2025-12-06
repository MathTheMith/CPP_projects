#include "../includes/player.hpp"
#include "raylib.h"

void Player::HandleMovement()
{
    if(IsKeyPressed(KEY_UP)) 
        Jump();
    if(IsKeyPressed(KEY_LEFT_SHIFT)) 
        Dash();
    
    if (isDashing) return;

    if (!isTouchingGround && momentumDuration > 0 && dashMomentum != 0) {
        float momentumMultiplier = (float)momentumTimer / 40.0f;
        if (momentumMultiplier < 0) momentumMultiplier = 0;
        
        posX += dashMomentum * momentumMultiplier;
    }

    if ((IsKeyUp(KEY_RIGHT) && IsKeyUp(KEY_LEFT)) ||
        (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_LEFT)))
    {
        if (isTouchingGround) {
            isMoving = false;
        }
        return;
    }

    if (IsKeyDown(KEY_RIGHT)) {
        posX += 5;
        if (isDashing) posX -= 10;
        direction = 1;
        isMoving = true;
    }
    else if (IsKeyDown(KEY_LEFT)) {
        posX -= 5;
        direction = 0;
        isMoving = true;
    }
}
void Player::HandleDash()
{
    if (isDashing) {
        float targetMomentum = dashSpeed * (direction == 1 ? 1 : -1);
        float accel = 2.5f;
        
        if (direction == 1 && dashMomentum < targetMomentum) {
            dashMomentum += accel;
            if (dashMomentum > targetMomentum) dashMomentum = targetMomentum;
        } else if (direction == 0 && dashMomentum > targetMomentum) {
            dashMomentum -= accel;
            if (dashMomentum < targetMomentum) dashMomentum = targetMomentum;
        }
        
        posX += dashMomentum;
        speedY = 0;
        
        if (momentumTimer > 0) {
            momentumTimer--;
        }
        momentumDuration--;
        
        dashTimer--;
        if (dashTimer <= 0) {
            isDashing = false;
        }
    }
}

void Player::HandleGravity()
{
    // Non utilisée
}