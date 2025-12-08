#include "../includes/player.hpp"
#include <cmath>
void Player::InitCamera(float threshold)
{
    cameraState.isTransitioning = false;
    cameraState.timer = 0.0f;
    cameraState.duration = 1.0f;
    cameraState.threshold = threshold;
    cameraState.currentX = posX;
    cameraState.currentY = posY - 400;
}

void Player::UpdateCamera(Camera2D &camera)
{
    if (!cameraState.isTransitioning)
    {
        float distance = fabs(posX - cameraState.currentX);
        
        if (distance > cameraState.threshold)
        {
            cameraState.isTransitioning = true;
            cameraState.timer = 0.0f;
            cameraState.startX = cameraState.currentX;
            cameraState.targetX = posX;
        }
    }

    if (cameraState.isTransitioning)
    {
        cameraState.timer += GetFrameTime();
        float progress = cameraState.timer / cameraState.duration;
        
        if (progress >= 1.0f)
        {
            progress = 1.0f;
            cameraState.isTransitioning = false;
            cameraState.currentX = cameraState.targetX;
        }
        else
        {
            float t = progress;
            float easedProgress;
            if (t < 0.5f)
                easedProgress = 4.0f * t * t * t;
            else
            {
                float f = (2.0f * t - 2.0f);
                easedProgress = 0.5f * f * f * f + 1.0f;
            }
            cameraState.currentX = cameraState.startX + (cameraState.targetX - cameraState.startX) * easedProgress;
        }
    }
    
    camera.target.x = cameraState.currentX;
    camera.target.y = cameraState.currentY;
}