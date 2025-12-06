#include "player.hpp"
#include "raylib.h"

Player::Player()
    : direction(1),
      speedX(0),
      speedY(0),
      gravity(0.3f),
      jumpForce(-8),
      isDashing(false),
      dashTimer(0),
      dashDuration(8),
      dashSpeed(20),
      nbDash(1),
      spriteSheetR(LoadTexture("images/spritesheet.png")),
      spriteSheetL(LoadTexture("images/spritesheet_reverse.png")),
      spriteSheetDR(LoadTexture("images/spritesheet_dash.png")),
      spriteSheetDL(LoadTexture("images/spritesheet_dash_reverse.png")),
      frameWidth(17),
      frameHeight(18),
      currentFrame(0),
      frameCount(13),
      frameTime(0.05f),
      frameTimer(0),
      isMoving(false),
      isTouchingGround(true),
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
    int w = 50;
    int h = 72;

    int minTileX = (int)(x + 5)/ map->tileSize;
    int maxTileX = (int)(x + w - 1) / map->tileSize;
    int minTileY = (int)y / map->tileSize;
    int maxTileY = (int)(y + h - 1) / map->tileSize;

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

bool Player::isOnGround(Map *map)
{

    int feetY = (int)(posY + 72) / map->tileSize;
    
    int leftX  = (int)posX / map->tileSize;
    int rightX = (int)(posX + 55) / map->tileSize;

    if (map->map[feetY][leftX] == '#')
            return true;
    if (map->map[feetY][rightX] == '#')
            return true;
      

    return false;
}

void Player::Update(Map *map)
{
    float oldX = posX;
    float oldY = posY;
    HandleDash();
    HandleMovement();

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
            nbDash = 1;
        }
        else if (speedY < 0) {
            posY = oldY;
            speedY = 0;
        }
    } else {
        isTouchingGround = false;
    }
    if (posY >= W_HEIGHT - 172) {
        posY = W_HEIGHT - 172;
        speedY = 0;
        isTouchingGround = true;
        nbDash = 1;
    }

    frameTimer += GetFrameTime();
    if (frameTimer >= frameTime) {
        currentFrame++;
        if (currentFrame >= frameCount) currentFrame = 0;
        frameTimer = 0;
    }
    if (isOnGround(map))
    {
        isTouchingGround = 1;
        // std::cout << isTouchingGround << std::endl;
    }
    // std::cout << posY << ' ' << posX << std::endl;
}

void Player::Jump()
{
    if (isTouchingGround) {
        speedY = jumpForce;
        isTouchingGround = false;
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
    nbDash--;
}