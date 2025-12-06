
#include "player.hpp"

void Player::Draw()
{
    int displayFrame;

    if(!isMoving) {
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
    Rectangle sourceRec;
    sourceRec = { (float)x, 0, (float)w, (float)h };
    Rectangle destRec = { (float)(posX - 2), (float)posY, (float)w * 4, (float)h * 4 };


    Texture2D tex = (direction == 1) ? spriteSheetR : spriteSheetL;
	if (nbDash == 0)
		tex = (direction == 1) ? spriteSheetDR : spriteSheetDL;

    DrawTexturePro(tex, sourceRec, destRec, (Vector2){0,0}, 0.0f, WHITE);
}
