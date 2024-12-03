#include <stdio.h>
#include <math.h>
#include <termios.h>
#include <unistd.h>

#define AREA_WIDTH 20
#define AREA_HEIGHT 20
#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 40
#define FIELD_OF_VIEW 80
#define ANGLE_OFFSET ((float)FIELD_OF_VIEW / SCREEN_WIDTH)
#define DEG_TO_RAD(angle) ((angle) * M_PI / 180.0)

char area[AREA_WIDTH * AREA_HEIGHT] =
"____________________"
"____________________"
"____________________"
"____________________"
"____________________"
"____________________"
"____________________"
"____________________"
"____________________"
"____________________"
"____________________"
"____________________"
"____________________"
"____________________"
"_____#####__________"
"____________________"
"____________________"
"____________________"
"____________________"
"____________________";

float playerAngle = 0;
float playerX = (float)AREA_WIDTH / 2;
float playerY = (float)AREA_HEIGHT / 2;
float distancesFromScreenToWalls[SCREEN_WIDTH];

char getTile(int x, int y){
    if(x < 0 || x >= AREA_WIDTH || y < 0 || y >= AREA_HEIGHT)
        return '#';
    return area[y * AREA_WIDTH + x];
}
void addAngle(float a){
    float result = playerAngle + a;
    if(result > 360.0f)
        result -= 360.0f;
    else if(result < 0.0f)
        result += 360.0f;

    playerAngle = result;
}

struct termios oldSettings;
void setInstantInputMode(char enable){
    if(enable){
		tcgetattr(STDIN_FILENO, &oldSettings);
        struct termios newSettings = oldSettings;
        newSettings.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
    }
    else{
        tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
    }
}

float toRad(float angle){
	return angle * M_PI / 180;
}
float castRay(float startX, float startY, float angle) {
    float rayPosX = startX;
    float rayPosY = startY;
    float rayDirX = cosf(toRad(angle));
    float rayDirY = sinf(toRad(angle));

    float mapX = rayPosX;
    float mapY = rayPosY;

    float deltaDistX = fabs(1 / rayDirX);
    float deltaDistY = fabs(1 / rayDirY);

    int stepX = (rayDirX < 0) ? -1 : 1;
    int stepY = (rayDirY < 0) ? -1 : 1;

    float sideDistX = (stepX > 0) ? (mapX + 1.0 - rayPosX) * deltaDistX : (rayPosX - mapX) * deltaDistX;
    float sideDistY = (stepY > 0) ? (mapY + 1.0 - rayPosY) * deltaDistY : (rayPosY - mapY) * deltaDistY;

    for(float sharpPart = 1; sharpPart < 5;){
		if (sideDistX < sideDistY) {
			float step = stepX / sharpPart;
			if (getTile((int)(mapX + step), (int)mapY) == '#'){
				sharpPart++;
				continue;
			}
            sideDistX += deltaDistX / sharpPart;
            mapX += step;
        }
		else{
			float step = stepY / sharpPart;
			if (getTile((int)mapX, (int)(mapY + step)) == '#'){
				sharpPart++;
				continue;
			}
            sideDistY += deltaDistY / sharpPart;
            mapY += step;
        }
    }

    return ((sideDistX < sideDistY) ? sideDistX - deltaDistX : sideDistY - deltaDistY) * cosf(toRad(angle - playerAngle));
}
void castRays(){
    for(int i = 0; i < SCREEN_WIDTH; i++){
        distancesFromScreenToWalls[i] = castRay(playerX, playerY, playerAngle + ANGLE_OFFSET * (i - (float)SCREEN_WIDTH/2));
    }
    for(int y = 0; y < SCREEN_HEIGHT; y++){
		for(int x = 0; x < SCREEN_WIDTH; x++){
			float sizeLine = (float)SCREEN_HEIGHT / distancesFromScreenToWalls[x];
			float wallTop = ((float)SCREEN_HEIGHT / 2) - (sizeLine / 2);
			float wallBottom = ((float)SCREEN_HEIGHT / 2) + (sizeLine / 2);

			if (y >= wallTop && y <= wallBottom)
				printf("█");
			else
				printf(" ");
		}
		printf("\n");
	}
}

void moveForward(float distance){
	playerX += cosf(toRad(playerAngle)) * distance;
	playerY += sinf(toRad(playerAngle)) * distance;
}
void moveSide(float distance){
	playerX += cosf(toRad(playerAngle + 90)) * distance;
	playerY += sinf(toRad(playerAngle + 90)) * distance;
}
int main(int argc, char* argv[]){
    setInstantInputMode(1);
    for(char ch = getchar(); ch != 27; ch = getchar()){
		if		(ch == 'w') moveForward(0.2);
		else if (ch == 's')	moveForward(-0.2);
		else if (ch == 'd') moveSide(0.2);
		else if (ch == 'a') moveSide(-0.2);
		else if (ch == 'q') addAngle(-10);
		else if (ch == 'e') addAngle(10);
		castRays();
    }
    setInstantInputMode(0);
    return 0;
}
