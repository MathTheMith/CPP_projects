
#include "../includes/player.hpp"

void Player::Draw()
{
    int displayFrame;

    if((!isMoving && !isDashing )|| (!isTouchingGround && !isDashing)) {
        displayFrame = 100;
    } else {
        displayFrame = currentFrame;
        if(displayFrame == 1) displayFrame = 2;
    }

    int x = 0;
    int w = 15;
    int h = 18;

    if(direction == 1) {
        switch(displayFrame) {
            case 100:  x = 0;   w = 15; break;
            case 2:  x = 15;  w = 15; break;
            case 3:  x = 32;  w = 15; break;
            case 4:  x = 48;  w = 15; break;
            case 5:  x = 65;  w = 15; break;
            case 6:  x = 82;  w = 15; break;
            case 7:  x = 99;  w = 15; break;
            case 8:  x = 116; w = 15; break;
            case 9:  x = 133; w = 16; break;
            case 10: x = 150; w = 15; break;
            case 11: x = 168; w = 15; break;
            case 12: x = 185; w = 15; break;
            default: x = 15;   w = 15; break;
        }
    }
    else {
        switch(displayFrame) {
            case 100:  x = 204; w = 13; break;
            case 1:  x = 187; w = 15; break;
            case 2:  x = 170; w = 15; break;
            case 3:  x = 154; w = 15; break;
            case 4:  x = 137; w = 16; break;
            case 5:  x = 120; w = 15; break;
            case 6:  x = 103;  w = 15; break;
            case 7:  x = 86;  w = 15; break;
            case 8:  x = 68;  w = 15; break;
            case 9:  x = 52;  w = 15; break;
            case 10: x = 34;  w = 15; break;
            case 11: x = 18;  w = 14; break;
            case 12: x = 0;   w = 15; break;
        }
    }
    Rectangle sourceRec = { (float)x, 0, (float)w, (float)h };
    Rectangle destRec = { (float)(posX - 2), (float)posY, (float)w * 4, (float)h * 4 };
    Texture2D tex;

    if (isOnAWall)
    {
        if (nbDash)
            tex = (direction == 1) ? spriteSheetWR : spriteSheetWL;
        else
            tex = (direction == 1) ? spriteSheetWDR : spriteSheetWDL;

        sourceRec = {0,0,10,16};
        x = (direction == 1) ? 18 : -2;
        destRec = { (float)(posX + x), (float)posY, 10*4, 16*4 };
    }
    else if (!isTouchingGround && nbDash == 0)
    {
        tex = (direction == 1) ? spriteSheetDR : spriteSheetDL;

            displayFrame = 6;

            if (direction == 1) {x = 82; w = 15;} 
            else { x = 103;w = 15;}

            sourceRec = { (float)x, 0, (float)w, (float)h };
            destRec   = { (float)posX, (float)posY, (float)w * 4, (float)h * 4 };
    }
    else if (!isTouchingGround)
    {
        bool altJump = ((frameCounter / 8) % 2) == 0;
        tex = (direction == 1) ? (altJump ? spriteSheetJR1 : spriteSheetJR2)
                                : (altJump ? spriteSheetJL1 : spriteSheetJL2);

        sourceRec = {0,0,14,18};
        destRec = { (float)posX, (float)posY, 14*4, 18*4 };
    }
    else if (nbDash == 0)
    {
        tex = (direction == 1) ? spriteSheetDR : spriteSheetDL;
    }
    else
    {
        tex = (direction == 1) ? spriteSheetR : spriteSheetL;
    }


    DrawTexturePro(tex, sourceRec, destRec, (Vector2){0,0}, 0.0f, WHITE);
}
