#include "../includes/player.hpp"
#include "raylib.h"
#include <cmath>
Player::Player()
    : direction(1),
      speedX(0),
      speedY(0),
      gravity(0.8f),
      jumpForce(-8),
      isHoldingJump(false),
      jumpHoldTimer(0),
      maxJumpHoldTime(10),
      jumpHoldForce(-0.8f),
      isDashing(false),
      dashTimer(0),
      dashDuration(10),
      dashSpeed(14),
      nbDash(1),
      spriteSheetR(LoadTexture("images/spritesheet.png")),
      spriteSheetL(LoadTexture("images/spritesheet_reverse.png")),
      spriteSheetDR(LoadTexture("images/spritesheet_dash.png")),
      spriteSheetDL(LoadTexture("images/spritesheet_dash_reverse.png")),
      spriteSheetWR(LoadTexture("images/celeste_climb.png")),
      spriteSheetWL(LoadTexture("images/celeste_climb_reverse.png")),
      spriteSheetWDR(LoadTexture("images/celeste_climb_dash.png")),
      spriteSheetWDL(LoadTexture("images/celeste_climb_dash_reverse.png")),
      spriteSheetJL1(LoadTexture("images/celeste_jumpL1.png")),
      spriteSheetJL2(LoadTexture("images/celeste_jumpL2.png")),
      spriteSheetJR1(LoadTexture("images/celeste_jumpR1.png")),
      spriteSheetJR2(LoadTexture("images/celeste_jumpR2.png")),
      frameWidth(17),
      frameHeight(18),
      currentFrame(0),
      frameCount(13),
      frameTime(0.05f),
      frameTimer(0),
      isMoving(false),
      isTouchingGround(true),
      isOnAWall(0),
      posX(0),
      posY(0)
{}

Player::~Player() {
    UnloadTexture(spriteSheetR);
    UnloadTexture(spriteSheetL);
    UnloadTexture(spriteSheetDR);
    UnloadTexture(spriteSheetDL);
}

bool Player::checkCollisionAt(Map *map, float x, float y)
{
    int tileSize = map->tileSize;
    float scale = tileSize / 32.0f;
    
    int w = 45 * scale;
    int h = 72 * scale;
    int offsetX = 10 * scale;

    int minTileX = (int)(x + offsetX) / tileSize;
    int maxTileX = (int)(x + w) / tileSize;
    int minTileY = (int)y / tileSize;
    int maxTileY = (int)(y + h) / tileSize;

    if (showHitbox)
        DrawRectangle((int)(x + 5 * scale), (int)y, w, h, GRAY);

    for (int ty = minTileY; ty <= maxTileY; ty++) {
        for (int tx = minTileX; tx <= maxTileX; tx++) {
            if (ty < 0 || ty >= map->height || 
                tx < 0 || tx >= map->width) {
                return true;
            }
            
            if (map->map[ty][tx] == '#') {
                return true;
            }
        }
    }
    return false;
}

bool Player::isTouchingRightWall(Map* map)
{
    int tileSize = map->tileSize;
    float scale = tileSize / 32.0f;
    
    int w = 60 * scale;
    int h = 60 * scale;
    int offsetY = 25 * scale;

    int rightX = (int)(posX + w);
    int topY   = (int)(posY + offsetY);
    int botY   = (int)(posY + h - 1);

    if (showHitbox)
        DrawLine(rightX, topY, rightX, botY, BLUE);

    int tileX = rightX / tileSize;

    for (int ty = topY / tileSize; ty <= botY / tileSize; ty++) {
        if (map->map[ty][tileX] == '#' && direction == 1)
            return true;
    }
    return false;
}

bool Player::isTouchingLeftWall(Map* map)
{
    int tileSize = map->tileSize;
    float scale = tileSize / 32.0f;
    
    int h = 60 * scale;
    int offsetX = 10 * scale;
    int offsetY = 25 * scale;
    
    int leftX = (int)(posX - offsetX);
    int topY  = (int)(posY + offsetY);
    int botY  = (int)(posY + h + 1);

    if (showHitbox)
        DrawLine(leftX, topY, leftX, botY, RED);
    
    int tileX = leftX / tileSize;

    for (int ty = topY / tileSize; ty <= botY / tileSize; ty++) {
        if (map->map[ty][tileX] == '#' && direction == 0)
            return true;
    }
    return false;
}

bool Player::isOnWall(Map* map)
{
    return isTouchingLeftWall(map) || isTouchingRightWall(map);
}

bool Player::isOnGround(Map *map)
{
    int tileSize = map->tileSize;
    float scale = tileSize / 32.0f;
    
    int feetY = (int)(posY + 75 * scale);
    int leftX  = (int)(posX + 5 * scale);
    int rightX = (int)(posX + 50 * scale);

    if (showHitbox)
        DrawLine(leftX, feetY, rightX, feetY, GREEN);

    int tileY = feetY / tileSize;
    int tileL = leftX / tileSize;
    int tileR = rightX / tileSize;

    if (tileY >= 0 && tileY < map->height) {
        if (tileL >= 0 && tileL < map->width && map->map[tileY][tileL] == '#')
            return true;
        if (tileR >= 0 && tileR < map->width && map->map[tileY][tileR] == '#')
            return true;
    }
    return false;
}

void Player::checkCollision(Map *map, int oldX, int oldY)
{
    if (checkCollisionAt(map, posX, oldY)) {
        posX = oldX;
        if (isDashing) {
            isDashing = false;
            speedX = 0;
        }
    }

    speedY += gravity;
    posY += speedY;

    if (checkCollisionAt(map, posX, posY)) {
        if (speedY > 0) {
            posY = oldY;
            speedY = 0;
            isTouchingGround = true;
            if (!isDashing)
                nbDash = 1;
        }
        else if (speedY < 0) {
            posY = oldY;
            speedY = 0;
            isHoldingJump = false;
        }
    } else {
        isTouchingGround = false;
    }
}

void Player::checkWallGrab(Map *map)
{
    if (isOnWall(map))
    {
        if (IsKeyDown(KEY_SPACE))
        {
            if (IsKeyDown(KEY_UP))
                speedY = -3;
            else if (IsKeyDown(KEY_DOWN))
                speedY = 3;
            else
                speedY = 0;
            isOnAWall = 1;
        }
        else
            isOnAWall = 0;
    }
    else
        isOnAWall = 0;
}

void Player::HandleJumpHold()
{
    if (IsKeyDown(KEY_UP) && isHoldingJump && jumpHoldTimer < maxJumpHoldTime && speedY < 0)
    {
        speedY += jumpHoldForce;
        jumpHoldTimer++;
    }
    
    if (IsKeyReleased(KEY_UP) || jumpHoldTimer >= maxJumpHoldTime || speedY >= 0)
    {
        isHoldingJump = false;
    }
}

void Player::Update(Map *map)
{
    if (cameraState.isTransitioning)
        return;
        
    float oldX = posX;
    float oldY = posY;
    HandleDash();
    HandleMovement();
    HandleJumpHold();
    checkCollision(map, oldX, oldY);
    checkWallGrab(map);
    
    float scale = map->tileSize / 32.0f;
    
    if (isOnAWall && isTouchingGround && direction != 1)
    {
        posY -= 30 * scale;
        posX -= 5 * scale;
        isTouchingGround = 0;
    }

    if (IsKeyPressed(KEY_H))
        showHitbox = (showHitbox == 0) ? 1 : 0;

    frameTimer += GetFrameTime();
    if (frameTimer >= frameTime) {
        currentFrame++;
        if (currentFrame >= frameCount) currentFrame = 0;
        frameTimer = 0;
    }
    frameCounter = (frameCounter + 1) % 1000000;
    if (isOnGround(map))
        isTouchingGround = true;
}

void Player::Jump()
{
    if (isTouchingGround) {
        speedY = jumpForce;
        isTouchingGround = false;
        isHoldingJump = true;
        jumpHoldTimer = 0;
        
        if (isDashing) {
            isDashing = false;
        }
    }
}

void Player::Dash()
{
    if (isDashing || nbDash == 0)
        return;
        
    isDashing = true;
    dashTimer = dashDuration;
    speedX = (direction == 1 ? dashSpeed : -dashSpeed);
    speedY = 0;
    nbDash = 0;
}
