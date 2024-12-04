#ifndef PLAYER_H
#define PLAYER_H

void playerInit(float x, float y, float angle);

void addAngle(float a);
void movePlayerForward(float distance);
void movePlayerSide(float distance);

float getPlayerX();
float getPlayerY();
float getPlayerAngle();

#endif//PLAYER_H
