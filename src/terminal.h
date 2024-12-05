#ifndef TERMINAL_H
#define TERMINAL_H
#include "rgb.h"

void setInstantInputMode(char enable);

void clearTerminal();
void startPosTerminal();
void setBackgroundColor(RGB color);
void setForegroundColor(RGB color);

void setCursorVisibility(char enable);
void setAltBuf(char enable);

#endif//TERMINAL_H
