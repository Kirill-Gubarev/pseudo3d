#include "rendering.h"

#include "utils.h"
#include "area.h"
#include "player.h"
#include "terminal.h"

#include <stdio.h>
#include <math.h>
#include <float.h>

#define SCREEN_WIDTH 190
#define SCREEN_HEIGHT 50

#define FIELD_OF_VIEW 80
#define ANGLE_OFFSET ((float)FIELD_OF_VIEW / SCREEN_WIDTH)

static float distancesFromScreenToWalls[SCREEN_WIDTH];

static float castRay(float startX, float startY, float angle) {
    float rayPosX = startX;
    float rayPosY = startY;
    float rayDirX = cosf(degToRad(angle));
    float rayDirY = sinf(degToRad(angle));

    int mapX = (int)rayPosX;
    int mapY = (int)rayPosY;

    float deltaDistX = fabs(1 / rayDirX);
    float deltaDistY = fabs(1 / rayDirY);

    int stepX = (rayDirX < 0) ? -1 : 1;
    int stepY = (rayDirY < 0) ? -1 : 1;

    float sideDistX = (rayDirX < 0) ? (rayPosX - mapX) * deltaDistX : (mapX + 1.0 - rayPosX) * deltaDistX;
    float sideDistY = (rayDirY < 0) ? (rayPosY - mapY) * deltaDistY : (mapY + 1.0 - rayPosY) * deltaDistY;

    int side = 0;

    while (1) {
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }

        if (getAreaTile(mapX, mapY) == '#')
			break;
    }

    float distance = (side == 0) ? sideDistX - deltaDistX : sideDistY - deltaDistY;
    return distance * cosf(degToRad(angle - getPlayerAngle()));
}
static void castRays(){
    for(int i = 0; i < SCREEN_WIDTH; i++){
        distancesFromScreenToWalls[i] = castRay(getPlayerX(), getPlayerY(), getPlayerAngle() + ANGLE_OFFSET * (i - (float)SCREEN_WIDTH/2));
    }
	clearTerminal();
    for(int y = 0; y < SCREEN_HEIGHT; y++){
		for(int x = 0; x < SCREEN_WIDTH; x++){
			float distance = distancesFromScreenToWalls[x];
			float sizeLine = (float)SCREEN_HEIGHT / distance;
			float wallTop = ((float)SCREEN_HEIGHT / 2) - (sizeLine / 2);
			float wallBottom = ((float)SCREEN_HEIGHT / 2) + (sizeLine / 2);

			if (y >= wallTop && y <= wallBottom && distance * 15 < 200){
				setColor(subtractRGB((RGB){200,200,200}, (uint8_t)(distance * 15)));
				printf("█");
			}
			else
				printf(" ");
		}
		printf("\n");
	}
}
void render(){
	castRays();
}

