#include "player.h"
#include "math.h"
#include "utils.h"

static float playerX = 0;
static float playerY = 0;
static float playerAngle = 0;

void playerInit(float x, float y, float angle){
	playerX = x;
	playerY = y;
	playerAngle = angle;
}

void addAngle(float a){
    float result = playerAngle + a;
    if(result > 360.0f)
        result -= 360.0f;
    else if(result < 0.0f)
        result += 360.0f;

    playerAngle = result;
}
void movePlayerForward(float distance){
	playerX += cosf(degToRad(playerAngle)) * distance;
	playerY += sinf(degToRad(playerAngle)) * distance;
}
void movePlayerSide(float distance){
	playerX += cosf(degToRad(playerAngle + 90)) * distance;
	playerY += sinf(degToRad(playerAngle + 90)) * distance;
}

float getPlayerX(){
	return playerX;
}
float getPlayerY(){
	return playerY;
}
float getPlayerAngle(){
	return playerAngle;
}
